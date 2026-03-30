#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"
source "run/linux/.inc.sh"

runImage "env/src/hello.py"