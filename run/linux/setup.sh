#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"
source "run/linux/.inc.sh"

runImage "env/src/setup.py"
copyImageData "Manor-Game/vnd" 1 0 "vnd"