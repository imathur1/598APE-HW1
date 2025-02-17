#!/bin/bash
set -e

FILENAME=${1:-pianoroom}
H=${2:-500}
W=${3:-500}

CORRECT_ICON="\U2705"
WRONG_ICON="\U274C"

./main.exe -i "inputs/$FILENAME.ray" --ppm -o "output/$FILENAME.ppm" -H $H -W $W

if cmp --silent -- "output/$FILENAME.ppm" "output/${FILENAME}_correct.ppm" ; then
  echo -e "$CORRECT_ICON $FILENAME ($H x $W) passed"
else
  echo -e "$WRONG_ICON $FILENAME ($H x $W) failed"
fi
