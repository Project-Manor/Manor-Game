#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"
source "run/linux/.inc.sh"

deleteImage
buildImage
runImage "env/src/hello.py"
deleteImage