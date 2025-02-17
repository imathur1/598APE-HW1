#!/bin/bash
set -e

FILENAME=${1:-pianoroom}

CORRECT_ICON="\U2705"
WRONG_ICON="\U274C"

taskset -c 3 ./main.exe -i "inputs/$FILENAME.ray" --ppm -o "output/$FILENAME.ppm" -H 500 -W 500

if cmp --silent -- "output/$FILENAME.ppm" "output/${FILENAME}_correct.ppm" ; then
  echo -e "$CORRECT_ICON $FILENAME passed"
else
  echo -e "$WRONG_ICON $FILENAME failed"
fi
