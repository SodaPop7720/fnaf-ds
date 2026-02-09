#!/bin/bash

BLOCKSDS="${BLOCKSDS:-/opt/blocksds/core/}"
GRIT=$BLOCKSDS/tools/grit/grit

$GRIT static0.png -ftB -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
$GRIT static1.png -ftB -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
$GRIT static2.png -ftB -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
$GRIT static3.png -ftB -fh! -gTFF00FF -gt -gB8 -mR8 -mLs

mv *.pal *.img *.map nitrofiles/bg
