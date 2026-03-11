#!/bin/bash
clear
cd "$(realpath -m "$0/../..")"
sudo docker buildx build -t manor-game-env:latest -f ./env/Dockerfile.linux .
sudo docker run manor-game-env:latest "env/src/hello.py"