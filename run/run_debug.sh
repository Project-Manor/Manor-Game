#!/bin/bash
clear
cd "$(realpath -m "$0/../..")"

sh run/build_debug.sh
./out/latest/bin/manor_game