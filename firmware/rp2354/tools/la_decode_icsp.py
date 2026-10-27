#!/usr/bin/env python3
"""Decode a sigrok .sr logic-analyser capture of the RP -> PIC32AK ICSP traffic (DS70005583).
usage: la_decode_icsp.py capture.sr [--mclr=CH] [--pgc=CH] [--pgd=CH]   (channel numbers 0-7, default 0/1/3)
Prints, per `pic id` run: key clock period, the 32-bit key, the two 0x00801000 entry words, the opcodes
and the three CMDSEQRD read-backs (sampled on the PGC rising edge and mid-bit), plus MCLR activity.
Run it with `python3 -I` on files you did not create yourself."""
import sys, os, zipfile, configparser, io
args=[a for a in sys.argv[1:] if not a.startswith('--')]; opt={a.split('=')[0][2:]:int(a.split('=')[1]) for a in sys.argv[1:] if a.startswith('--')}
CH_MCLR,CH_PGC,CH_PGD=opt.get('mclr',0),opt.get('pgc',1),opt.get('pgd',3)
z=zipfile.ZipFile(args[0]); cp=configparser.ConfigParser(); cp.read_string(z.read('metadata').decode())
dev=cp['device 1']; unit=int(dev.get('unitsize','1')); FS=float(dev['samplerate'].split()[0])*({'MHz':1e6,'kHz':1e3,'Hz':1}[dev['samplerate'].split()[1]])
raw=b''.join(z.read(nm) for nm in sorted(z.namelist()) if nm.startswith(dev.get('capturefile','logic-1')))
if unit!=1: raw=bytes(raw[i] for i in range(0,len(raw),unit))
n=len(raw); print(f"{args[0]}: {n} samples at {FS/1e6:g} MHz, probes: "+", ".join(f"{k}={v}" for k,v in dev.items() if k.startswith('probe')))
bit=lambda ch:[(b>>ch)&1 for b in raw]
mclr,pgc,pgd=bit(CH_MCLR),bit(CH_PGC),bit(CH_PGD)
rise=[i for i in range(1,n) if pgc[i] and not pgc[i-1]]
if not rise: sys.exit("no clock edges on PGC channel %d"%CH_PGC)
runs=[[rise[0]]]
for r in rise[1:]: (runs.append([r]) if (r-runs[-1][-1])/FS>50e-3 else runs[-1].append(r))
print("runs (clocks each):",[len(r) for r in runs])
word=lambda bits: sum(b<<i for i,b in enumerate(bits))
for ri,run in enumerate(runs):
    if len(run)<276: print(f"--- run {ri}: only {len(run)} clocks, skipped"); continue
    bits=[pgd[r] for r in run]
    print(f"--- run {ri}: key period {(run[31]-run[0])/FS/31*1e6:.2f} us, gap after key {(run[32]-run[31])/FS*1e6:.0f} us")
    print("  key    = 0x%08X (expect 0x8A12C2B2)"%word(bits[0:32]))
    print("  step9  cmd=%s 0x%08X | step10 cmd=%s 0x%08X (expect 00 0x00801000)"%(bits[32:34],word(bits[34:66]),bits[66:68],word(bits[68:100])))
    i=100
    for name,kind in [("MOV.SL VISI,W8 (A0001F03)","exec"),("MOV.SL addr,W0 (81F08003)","exec"),("dummy SEQRD","rd"),("SEQRD DEVID","rd"),("SEQRD REVID","rd")]:
        cmd=bits[i:i+2]
        if kind=="exec": print(f"  {name:28s} cmd={cmd} 0x{word(bits[i+2:i+34]):08X}"); i+=34
        else:
            mid=[pgd[(run[k]+run[k+1])//2] for k in range(i+3,i+35)]
            print(f"  {name:28s} cmd={cmd} idle={bits[i+2]} data@rise=0x{word(bits[i+3:i+35]):08X} data@mid=0x{word(mid):08X}"); i+=36
    a=max(0,run[0]-int(3e-3*FS)); b=min(n,run[-1]+int(1e-3*FS))
    low=[k for k in range(a,b) if not mclr[k]]
    if low: print(f"  MCLR low from {(low[0]-run[0])/FS*1e6:.0f} us to {(low[-1]-run[0])/FS*1e6:.0f} us relative to the first clock ({len(low)/FS*1e6:.0f} us total)")
    else: print("  MCLR never low in this window -> probe not on MCLR, or reset not reaching J1.1")
