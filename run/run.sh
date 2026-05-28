#!/bin/bash
clear
cd "$(realpath -m "$0/../..")"

sh run/build.sh
./out/latest/bin/manor_game