#!/usr/bin/env python3
"""Check register bitfield names and #pragma config names against a Microchip DFP, without a compiler.

  python3 dfp_check.py <pack_dir> <device> bits U1CON U1STAT RPINR9 ...   # members of <REG>bits structs
  python3 dfp_check.py <pack_dir> <device> config [JTAGEN WDTEN ...]      # pragma names + allowed values
  python3 dfp_check.py <pack_dir> <device> sfr U1TXB SPI1BUF              # plain SFR exists?
<pack_dir> = unpacked .atpack (e.g. ~/microchip/packs/PIC32AK-GC_DFP/1.1.53); <device> = 32AK1216GC41048
"""
import re, sys, html, glob, os

def find_header(pack, dev):
    hits = glob.glob(os.path.join(pack, '**', f'p{dev}.h'), recursive=True)
    if not hits: sys.exit(f"no p{dev}.h under {pack}")
    return hits[0]

def bits(pack, dev, regs):
    h = open(find_header(pack, dev), errors='ignore').read()
    for r in regs:
        m = re.search(r'typedef struct tag' + r + r'BITS \{(.*?)\} ' + r + r'BITS;', h, re.S)
        if not m: print(f"{r}bits: NOT FOUND"); continue
        print(f"{r}bits -> " + ' '.join(re.findall(r'\b([A-Za-z]\w*):\d+;', m.group(1))))

def sfr(pack, dev, names):
    h = open(find_header(pack, dev), errors='ignore').read()
    for n in names: print(f"{n}: {'ok' if re.search(r'extern volatile \w+ ' + n + r'\b', h) else 'NOT FOUND'}")

def config(pack, dev, keys):
    hits = glob.glob(os.path.join(pack, '**', 'config_docs', f'{dev}.html'), recursive=True)
    if not hits: sys.exit("no config_docs html found")
    t = html.unescape(re.sub(r'<[^>]+>', '\n', open(hits[0], errors='ignore').read()))
    L = [l.strip() for l in t.split('\n') if l.strip()]
    settings = [l for l in L if re.fullmatch(r'[A-Z][A-Z0-9_]{2,}', l)]
    if not keys: print(' '.join(dict.fromkeys(s for s in settings if '_' not in s))); return
    for k in keys:
        idx = [i for i, l in enumerate(L) if l == k]
        if not idx: print(f"{k}: NOT a config setting"); continue
        i = idx[0]; vals = [l for l in L[i+1:i+14] if re.match(k + r' = \w+', l)]
        print(f"{k}: {L[i+1]} | values: {', '.join(v.split(' = ')[1] for v in vals)}")

if __name__ == '__main__':
    if len(sys.argv) < 4: sys.exit(__doc__)
    pack, dev, cmd, args = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4:]
    {'bits': bits, 'sfr': sfr, 'config': config}.get(cmd, lambda *a: sys.exit(__doc__))(pack, dev, args)
