#!/bin/bash
clear
cd "$(realpath -m "$0/../../..")"

sh env/run/build.sh
./out/latest/bin/manor_game