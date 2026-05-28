#!/bin/bash
clear
cd "$(realpath -m "$0/../..")"

if [[ -d ".zed" ]]; then
    rm -r .zed
fi

if [ -d "out" ]; then
    rm -r out
fi

if [[ -d "vnd" ]]; then
    rm -r vnd
fi

if [[ -f ".clangd" ]]; then
    rm -r .clangd
fi