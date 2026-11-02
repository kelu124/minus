import sys
from collections import Counter
for fn in sys.argv[1:]:
    v=[int(l) for l in open(fn) if l.strip() and not l.startswith('#')]
    n=len(v); rng=max(v)-min(v); thr=rng*0.25
    d=[v[i]-v[i-1] for i in range(1,n)]
    ed=[]  # (index, sign), with 4-sample dead time
    last=-99
    for i,x in enumerate(d, start=1):
        if abs(x)>thr and i-last>4: ed.append((i, 1 if x>0 else -1)); last=i
    rises=[i for i,s in ed if s>0]; falls=[i for i,s in ed if s<0]
    pr=Counter(b-a for a,b in zip(rises,rises[1:]))
    hw=Counter(next((f for f in falls if f>r),r)-r for r in rises[:-1])
    dup=sum(1 for i in range(1,n) if v[i]==v[i-1])
    mp=sum(k*c for k,c in pr.items())/max(1,sum(pr.values()))
    print(f"{fn.split('/')[-1]:24s} n={n} range={min(v)}..{max(v)} edges={len(ed)} rise-rise={sorted(pr.items())} high={sorted(hw.items())} mean_period={mp:.3f} adj_equal={dup}")
