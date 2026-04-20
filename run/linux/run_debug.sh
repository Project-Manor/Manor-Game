#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"

sh run/linux/build_debug.sh
./out/bin/manor_game