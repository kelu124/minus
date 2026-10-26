#!/usr/bin/env python3
"""Read a KiCad netlist (XML, from `kicad-cli sch export netlist --format kicadxml`).

  python3 nets.py NETLIST.xml pins U1 U2 ...   # every pin of each ref: number, function, net, other nodes
  python3 nets.py NETLIST.xml shared U1 U2     # nets that touch BOTH refs (inter-chip links)
  python3 nets.py NETLIST.xml net SPI_MOSI     # all nodes on nets whose NAME contains the text (case-insensitive)
  python3 nets.py NETLIST.xml comps            # one line per component: ref, value, footprint
Power/ground nets are abbreviated to keep the output readable.
"""
import sys, signal, xml.etree.ElementTree as ET
signal.signal(signal.SIGPIPE, signal.SIG_DFL)   # quiet exit when piped into head

def load(path):
    r = ET.parse(path).getroot()
    comps = {c.get('ref'): (c.findtext('value') or '', c.findtext('footprint') or '') for c in r.iter('comp')}
    nets = {n.get('name'): [(x.get('ref'), x.get('pin'), x.get('pinfunction') or '') for x in n.findall('node')]
            for n in r.iter('net')}
    return comps, nets

def is_power(name, nodes):
    return len(nodes) > 25 or name.upper() in ('GND', 'VCC') or name.startswith('+')

def others(nodes, ref, limit=12):
    o = [f"{a}.{b}" for a, b, _ in nodes if a != ref]
    return ' '.join(o[:limit]) + (f' …(+{len(o)-limit})' if len(o) > limit else '')

def cmd_pins(comps, nets, refs):
    for ref in refs:
        print(f"\n### {ref} = {comps.get(ref, ('?', '?'))[0]}  [{comps.get(ref, ('', ''))[1]}]")
        rows = []
        for name, nodes in nets.items():
            for a, b, fn in nodes:
                if a == ref:
                    rows.append((int(b) if b.isdigit() else 10**6, b, fn, name, nodes))
        for _, pin, fn, name, nodes in sorted(rows):
            tail = '(power/gnd)' if is_power(name, nodes) else others(nodes, ref)
            print(f"  {pin:>4} {fn[:38]:38} {name[:30]:30} -> {tail}")

def cmd_shared(comps, nets, a, b):
    print(f"\n### nets shared by {a} and {b}")
    for name, nodes in nets.items():
        refs = {x for x, _, _ in nodes}
        if a in refs and b in refs and not is_power(name, nodes):
            pa = [f"{x}.{p}({f})" for x, p, f in nodes if x == a]
            pb = [f"{x}.{p}({f})" for x, p, f in nodes if x == b]
            rest = [f"{x}.{p}" for x, p, _ in nodes if x not in (a, b)]
            print(f"  {name:22} {' '.join(pa)} <-> {' '.join(pb)}   also: {' '.join(rest) or '-'}")

def cmd_net(comps, nets, pats):
    for name, nodes in nets.items():
        if any(p.lower() in name.lower() for p in pats):
            print(f"  {name}: " + ' '.join(f"{a}.{b}({c})" if c else f"{a}.{b}" for a, b, c in nodes))

def main():
    if len(sys.argv) < 3: sys.exit(__doc__)
    comps, nets = load(sys.argv[1]); cmd = sys.argv[2]; args = sys.argv[3:]
    if cmd == 'pins': cmd_pins(comps, nets, args)
    elif cmd == 'shared': cmd_shared(comps, nets, *args[:2])
    elif cmd == 'net': cmd_net(comps, nets, args)
    elif cmd == 'comps':
        for ref, (v, fp) in sorted(comps.items()): print(f"  {ref:8} {v[:40]:40} {fp}")
    else: sys.exit(__doc__)

if __name__ == '__main__': main()
