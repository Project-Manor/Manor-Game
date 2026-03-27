#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"
source "run/linux/.inc.sh"

runImage "env/src/hello.py"
copyImageData "Manor-Game/env" 1 1 "out"