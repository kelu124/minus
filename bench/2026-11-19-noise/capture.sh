#!/bin/bash
# Noise captures on board 3 (no pulse). usage: bash bench/2026-11-19-noise/capture.sh   (from the repo root, RP on /dev/ttyACM0)
# Files: <name>_r<k>.txt. Captures whose header is not the uniform 24.8x Msps (or the expected slower SAMC rate) are retried.
D=bench/2026-11-19-noise; R="python3 firmware/rp2354/tools/rpcli.py /dev/ttyACM0"
cap() {  # cap <name> <acq args> <nrec>
  local name=$1 args=$2 n=$3 k=1 tries=0
  while [ $k -le $n ] && [ $tries -lt $((n*4)) ]; do
    tries=$((tries+1)); $R "acq $args" --wait=4 > $D/tmp.txt
    fs=$(grep -o 'fs=[0-9.]*' $D/tmp.txt | cut -d= -f2)
    case "$name" in adc_*) ok=1;; *) [[ "$fs" == 24.8* ]] && ok=1 || ok=0;; esac
    if [ "$ok" = 1 ] && grep -q "^# acq" $D/tmp.txt; then mv $D/tmp.txt $D/${name}_r$k.txt; k=$((k+1)); fi
  done
  echo "$name: $((k-1))/$n records in $tries tries (last fs $fs)"
}
# 1) ADC alone: internal references (ADC1 code 15 = AD1AN15 band gap 0.8 V, 14 = AD1AN14 15/16 AVDD; ADC2 31/30 = AD2AN15/14)
for samc in 0 3; do for in in 15 14 31 30; do cap adc_in${in}_samc$samc "4 $samc $in 1" 3; done; done
# 2) chain at the ADC node (25) at every gain, and 3) taps (0 = OA1OUT, 1 = LNA out)
for g in "0 1 1" "0 1 0" "1 1 0" "2 1 0" "3 1 0" "0 0 0" "1 0 0" "2 0 0" "3 0 0"; do
  tag=g$(echo $g | tr -d ' '); $R "gain $g" --wait=1 | tail -1
  cap node_${tag} "4 0 25 1" 3
  case $tag in g011|g000|g300) cap oa1_${tag} "4 0 0 1" 2; cap lna_${tag} "4 0 1 1" 2;; esac
done
$R "gain 0" --wait=1 | tail -1; rm -f $D/tmp.txt
