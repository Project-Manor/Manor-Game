#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"
source "env/run/.inc.sh"

sh env/run/prune.sh

editor="editor=none"
clangd="clangd=0"

read -p ":: Generate Zed Editor Project Files [y/n] " zed
if [[ "$zed" == "y" || "$zed" == "Y" ]]; then
    editor="editor=zed"
fi

read -p ":: Generate .clangd File [y/n] " clgd
if [[ "$clgd" == "y" || "$clgd" == "Y" ]]; then
    clangd="clangd=1"
fi

runImage "env/src/setup.py" $editor $clangd

mkdir out

copyImageData "Manor-Game/vnd" 1 0 "vnd"

if [[ "$zed" == "y" || "$zed" == "Y" ]]; then
    copyImageData "Manor-Game/.zed" 1 0 ".zed"
fi

if [[ "$clgd" == "y" || "$clgd" == "Y" ]]; then
    copyImageData "Manor-Game/.clangd" 1 0 ".clangd"
    sed -i "s|__INSERT_PROJECT_PATH__|$(pwd)|g" ".clangd"
fi