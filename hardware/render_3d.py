#!/usr/bin/env python3
"""Render top / bottom / angled 3D views of a minUS board with kicad-cli.

Usage:  python3 hardware/render_3d.py hardware/minUS_08112026 [--quick]

Writes <board>/minUS_F.png, minUS_B.png, minUS_angled.png.
The design file is never modified: a patched copy goes to a temp dir.

What the patch does (see docs/claude/memory for the why):
  * EasyEDA model paths (D:/... Windows paths, ${KICAD_3RD_PARTY}, ${KIPRJMOD})
    -> hardware/3dmodels/EasyEDA/ (vendored).
  * EasyEDA models we don't have -> closest stock KiCad model (SUBST).
  * Per-footprint fixups (FIXUPS): orientation/offset of substitutes, stray
    duplicate models.
  * Always OMIT models of the 2xN pin headers / IDC box header and the SMA
    edge connectors (owner preference, 2026-11-11).
"""
import os, re, subprocess, sys, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
EASY = os.path.join(HERE, "3dmodels", "EasyEDA")
KM = os.environ.get("KICAD10_3DMODEL_DIR", "/usr/share/kicad/3dmodels")

# EasyEDA model basename (no ext) -> stock KiCad model (relative to KM)
SUBST = {
    "QFN-60_L7.0-W7.0-P0.40-TL-EP3.4": "Package_DFN_QFN.3dshapes/QFN-56-1EP_7x7mm_P0.4mm_EP4x4mm.step",
    "PIC32AK1216GC41048-I_PT": "Package_QFP.3dshapes/TQFP-48_7x7mm_P0.5mm.step",
    "TSSOP-16_L5.0-W4.3-P0.65-LS6.4-BL": "Package_SO.3dshapes/TSSOP-16_4.4x5mm_P0.65mm.step",
    "SOT-25-5_L2.9-W1.6-P0.95-LS2.8-BL": "Package_TO_SOT_SMD.3dshapes/SOT-23-5.step",
    "SC-70-6_L2.0-W1.3-H1.0-P0.65": "Package_TO_SOT_SMD.3dshapes/SOT-363_SC-70-6.step",
    "SOT-23-3L_L2.9-W1.6-H1.1-LS2.8-P0.95": "Package_TO_SOT_SMD.3dshapes/SOT-23.step",
    "MSOP8_MC_MCH_TC4427A": "Package_SO.3dshapes/MSOP-8_3x3mm_P0.65mm.step",
    "LED0603_L1.6-W0.8-H0.6": "LED_SMD.3dshapes/LED_0603_1608Metric.step",
    "OSC-SMD_4P-L2.5-W2.0-H0.6": "Crystal.3dshapes/Crystal_SMD_2520-4Pin_2.5x2.0mm.step",
    "IND-SMD_L2.0-W1.6_AOTA-B201610S3R3-101-T": "Inductor_SMD.3dshapes/L_Walsin_WLFM201609x.step",
    "IPEX-SMD_3P-L2.6-W2.6-LS3.0": "Connector_Coaxial.3dshapes/U.FL_Hirose_U.FL-R-SMT-1_Vertical.step",
}

# footprint-name regex -> replace all its models with ONE model at offset/rotate
# (substitutes have a different native orientation/origin than EasyEDA's)
FIXUPS = {
    r"EasyEDA:TSSOP-16_L5\.0-W4\.3-P0\.65-LS6\.4-BL": ("Package_SO.3dshapes/TSSOP-16_4.4x5mm_P0.65mm.step", (0, 0, 0), (0, 0, 270)),
    # EasyEDA IPEX: signal pad at (0,+0.4), GND tabs at (+-1.3,-0.4); KiCad U.FL: signal at -x, body centred on origin
    r"EasyEDA:IPEX-SMD_3P-L2\.6-W2\.6-LS3\.0": ("Connector_Coaxial.3dshapes/U.FL_Hirose_U.FL-R-SMT-1_Vertical.step", (0, 0.4, 0), (0, 0, 90)),
}

# footprints whose 3D models are always stripped from renders
OMIT = [r"EasyEDA:HDR-TH_\d+P-P2\.54-V-M-R2-", r"EasyEDA:IDC-TH_", r"EasyEDA:SMA-"]

MODEL_RE = re.compile(r'\n\t\t\(model "([^"]*)".*?\n\t\t\)', re.S)


def model_block(path, off, rot):
    f = lambda v: " ".join(str(x) for x in v)
    return (f'\n\t\t(model "{path}"\n\t\t\t(offset\n\t\t\t\t(xyz {f(off)})\n\t\t\t)\n'
            f'\t\t\t(scale\n\t\t\t\t(xyz 1 1 1)\n\t\t\t)\n\t\t\t(rotate\n\t\t\t\t(xyz {f(rot)})\n\t\t\t)\n\t\t)')


def remap(m):
    path = m.group(1)
    base, _ = os.path.splitext(os.path.basename(path))
    if path.startswith("${KICAD10_3DMODEL_DIR}"):
        return m.group(0)
    if base in SUBST:
        new = os.path.join(KM, SUBST[base])
    else:
        new = None
        for ext in (".step", ".stp", ".wrl"):
            cand = os.path.join(EASY, base + ext)
            if os.path.isfile(cand):
                new = cand
                break
        if new is None:
            print(f"  no model for {base}", file=sys.stderr)
            return ""
    return m.group(0).replace(f'"{path}"', f'"{new}"', 1)


def patch_footprint(m):
    name, body = m.group(1), m.group(2)
    if any(re.match(p, name) for p in OMIT):
        return m.group(0).replace(body, MODEL_RE.sub("", body))
    for pat, (mdl, off, rot) in FIXUPS.items():
        if re.match(pat, name):
            body2 = MODEL_RE.sub("", body)
            # insert before the footprint's closing paren (body ends just before it)
            return m.group(0).replace(body, body2 + model_block(os.path.join(KM, mdl), off, rot))
    return m.group(0).replace(body, MODEL_RE.sub(remap, body))


def main():
    board = os.path.abspath(sys.argv[1])
    quick = "--quick" in sys.argv
    pcb = os.path.join(board, "minUS.kicad_pcb")
    t = open(pcb).read()
    t = re.sub(r'\n\t\(footprint "([^"]*)"(.*?)(?=\n\t\))', patch_footprint, t, flags=re.S)
    tmp = tempfile.mkdtemp(prefix="render3d_")
    p2 = os.path.join(tmp, "minUS.kicad_pcb")
    open(p2, "w").write(t)
    env = dict(os.environ, KICAD10_3DMODEL_DIR=KM)
    common = ["-w", "2000", "-h", "1500", "--background", "opaque", "--floor",
              "--quality", "basic" if quick else "high"]
    views = {
        "minUS_F.png": ["--side", "top"],
        "minUS_B.png": ["--side", "bottom"],
        "minUS_angled.png": ["--side", "top", "--perspective", "--rotate", "-45,0,30", "--zoom", "0.9"],
    }
    procs = [subprocess.Popen(["kicad-cli", "pcb", "render", "-o", os.path.join(board, out)] + common + v + [p2],
                              env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
             for out, v in views.items()]
    rc = [p.wait() for p in procs]
    for out, r in zip(views, rc):
        print(("ok   " if r == 0 else "FAIL ") + os.path.join(board, out))
    sys.exit(max(rc))


if __name__ == "__main__":
    main()
