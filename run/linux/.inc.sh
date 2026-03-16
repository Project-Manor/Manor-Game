#!/bin/bash

imageName=manor-game-env:latest

deleteImage() {
    sudo docker rmi -f $imageName
}

buildImage() {
    sudo docker buildx build -t $imageName -f ./env/Dockerfile.linux .
}

runImage() {
    local pyScript=$1

    sudo docker run $imageName $pyScript
}