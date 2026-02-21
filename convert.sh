#!/bin/bash

BLOCKSDS="${BLOCKSDS:-/opt/blocksds/core/}"
GRIT=$BLOCKSDS/tools/grit/grit

$GRIT officePowerOut.png -ftB -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
$GRIT officePowerOutFreddy.png -ftB -fh! -gTFF00FF -gt -gB8 -mR8 -mLs

mv *.pal *.img *.map nitrofiles/bg
