#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"
source "run/linux/.inc.sh"

editor="editor=none"

read -p ":: Generate Zed Editor Project Files [y/n] " zed
if [[ "$zed" == "y" || "$zed" == "Y" ]]; then
    editor="editor=zed"
fi

runImage "env/src/setup.py" $editor

copyImageData "Manor-Game/vnd" 1 0 "vnd"

if [[ "$zed" == "y" || "$zed" == "Y" ]]; then
    copyImageData "Manor-Game/.zed" 1 0 ".zed"
fi