#!/bin/bash
set -e

FILENAME=${1:-pianoroom}
H=${2:-500}
W=${3:-500}
F=${4:-24}

CORRECT_ICON="\U2705"
WRONG_ICON="\U274C"

if [ "$FILENAME" == "globe" ]; then
  ./main.exe -i "inputs/$FILENAME.ray" --ppm -a "inputs/$FILENAME.animate" --movie -F $F -H $H -W $W
  for ((i=0; i<F; i++)); do
    FRAME_NUM=$(printf "%07d" $i)
    if cmp --silent -- "output/output.mp4.tmp.${FRAME_NUM}.ppm" "output/globe_correct.mp4.tmp.${FRAME_NUM}.ppm" ; then
      echo -e "$CORRECT_ICON Frame $FRAME_NUM passed"
    else
      echo -e "$WRONG_ICON Frame $FRAME_NUM failed"
    fi
  done
else
  ./main.exe -i "inputs/$FILENAME.ray" --ppm -o "output/$FILENAME.ppm" -H $H -W $W
  if cmp --silent -- "output/$FILENAME.ppm" "output/${FILENAME}_correct.ppm" ; then
    echo -e "$CORRECT_ICON $FILENAME ($H x $W) passed"
  else
    echo -e "$WRONG_ICON $FILENAME ($H x $W) failed"
  fi
fi
