#!/bin/bash

imageName=manor-game-env

deleteImage() {
    if [ "$(sudo docker ps -a -q -f name=^${imageName})" ]; then
        sudo docker rm -f $imageName
    fi
}

buildImage() {
    deleteImage
    sudo docker buildx build -t $imageName:latest -f ./env/Dockerfile.linux .
}

runImage() {
    local pyScript=$1
    buildImage
    sudo docker run --name $imageName $imageName:latest $pyScript
}

copyImageData() {
    local dataPath=$1
    local outDir=$2

    if [ -d "$outDir" ]; then
        sudo rm -r "./$outDir"
    fi
    mkdir "./$outDir"

    sudo docker cp "$imageName:/$dataPath" "./$outDir"
}