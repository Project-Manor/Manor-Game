#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"
source "run/linux/.inc.sh"

runImage "env/src/build.py"
copyImageData "Manor-Game/out" 1 0 "out"