#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"
source "env/run/.inc.sh"

runImage "env/src/hello.py"