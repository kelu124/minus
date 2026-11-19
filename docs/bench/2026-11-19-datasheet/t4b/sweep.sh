#!/bin/bash
# Fine pulse-width sweep (owner request 2026-11-19): t_hi 12.5..150 ns step 12.5 (12 points) + 175..600 ns; lo 500; gain 0 1 0; in 25; 2 reps.
export LC_NUMERIC=C
D=docs/bench/2026-11-19-datasheet/t4b; R="python3 firmware/rp2354/tools/rpcli.py /dev/ttyACM0"
for hi in 12.5 25 37.5 50 62.5 75 87.5 100 112.5 125 137.5 147 150 175 200 250 300 400 600; do
  ns=$(printf "%.0f" $hi); for k in 1 2; do $R "pe $ns 500 25" --wait=1.6 > $D/hi${ns}_r$k.txt; done
  echo "$ns $(grep -o 'pulse: +5V [0-9.]* ns\|+5V [0-9]* /' $D/hi${ns}_r1.txt | head -1) $(grep -c '# pulse fired' $D/hi${ns}_r1.txt)"
done
