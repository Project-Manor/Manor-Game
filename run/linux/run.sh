#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"

sh run/linux/build.sh
./out/bin/manor_game