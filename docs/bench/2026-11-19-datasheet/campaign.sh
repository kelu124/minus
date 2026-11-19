#!/bin/bash
# Datasheet measurement campaign, board 3 (minUS_08112026), rp 0.1.33 / pic 0.1.24. Run from the repo root.
D=docs/bench/2026-11-19-datasheet; R="python3 firmware/rp2354/tools/rpcli.py /dev/ttyACM0"
log() { echo "$@" | tee -a $D/campaign.log; }
: > $D/campaign.log
# T1 identification
$R "version" "raw ID?" "pc" "gain" "i2c" --wait=2 > $D/t1_ident.txt
for i in $(seq 1 20); do $R "ping" --wait=1 | grep -o "ok, [0-9]* us"; done > $D/t1_ping.txt
log "T1 done: $(wc -l < $D/t1_ping.txt) pings"
# T3 timing of one pe (host wall clock, includes 8190 B at 115200 baud)
$R "gain 0 1 0" --wait=1 >/dev/null
for i in 1 2 3 4 5; do s=$(date +%s.%N); $R "pe" --wait=4 > $D/t3_pe_$i.txt; e=$(date +%s.%N); echo "$(echo "$e - $s" | bc) $(grep -o '[0-9] shot' $D/t3_pe_$i.txt)"; done > $D/t3_timing.txt
log "T3 done"
# T4 pulse width sweep (hi) at lo 500, and clamp sweep (lo) at hi 200; gain 0 1 0 (OA2 x3.7, ~11 dB)
for hi in 50 100 150 200 250 300 400 600; do for k in 1 2; do $R "pe $hi 500 25" --wait=5 > $D/t4_hi${hi}_r$k.txt; done; done
for lo in 1 100 250 500 1000 2000; do for k in 1 2; do $R "pe 200 $lo 25" --wait=5 > $D/t4_lo${lo}_r$k.txt; done; done
log "T4 done"
# T5 main bang / latency at unity gain, ADC node and OA2OUT
$R "gain 0 1 1" --wait=1 >/dev/null
for in in 25 17 0; do $R "pe 200 500 $in" --wait=5 > $D/t5_mb_in$in.txt; done
log "T5 done"
# T7 repeatability + averaging: 16 shots at gain 2 0 0 (both stages leg 2, ~38 dB) and 16 at 0 1 0
for g in "2 0 0" "0 1 0"; do tag=$(echo $g | tr -d ' '); $R "gain $g" --wait=1 >/dev/null
  for k in $(seq 1 16); do $R "pe" --wait=5 > $D/t7_g${tag}_r$k.txt; done; done
log "T7 done"
# T9 noise with the firmware pattern correction (no pulse), every gain, + ADC alone
for g in "0 1 1" "0 1 0" "1 1 0" "2 1 0" "3 1 0" "0 0 0" "1 0 0" "2 0 0" "3 0 0"; do tag=$(echo $g | tr -d ' '); $R "gain $g" --wait=1 >/dev/null
  k=0; t=0; while [ $k -lt 2 ] && [ $t -lt 8 ]; do t=$((t+1)); $R "acq 4 0 25 1" --wait=4 > $D/tmp.txt; grep -q "fs=24.8" $D/tmp.txt && { k=$((k+1)); mv $D/tmp.txt $D/t9_g${tag}_r$k.txt; }; done; done
for k in 1 2; do $R "acq 4 3 31 1" --wait=4 > $D/t9_adc_r$k.txt; done
log "T9 done"
# T10 sample-rate options (div 4 = 25 Msps, 10 = 20, 20 = 10, 40 = 5) at gain 0 1 0, ADC node
$R "gain 0 1 0" --wait=1 >/dev/null
for div in 4 10 20 40; do $R "acq $div 0 25 1" --wait=4 | grep "^#" > $D/t10_div$div.txt; done
$R "gain 0" --wait=1 >/dev/null; rm -f $D/tmp.txt
log "campaign done"
