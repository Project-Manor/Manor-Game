#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"
source "env/run/.inc.sh"

runImage "env/src/build.py" "-DDEBUG"

date=$(date +"%Y_%m_%d_%H_%M_%S")

if [ -d "out/latest" ]; then
    mv out/latest out/oldsince_$date
fi

copyImageData "Manor-Game/out" 1 0 "out/latest"