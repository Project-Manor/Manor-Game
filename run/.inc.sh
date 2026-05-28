#!/bin/bash

imageName=manor-game-env
containerFile=./env/Containerfile

deleteImage() {
    # if [ "$(sudo docker ps -a -q -f name=^${imageName})" ]; then
    #     sudo docker rm -f $imageName
    # fi
    podman rmi -f $imageName:latest
}

buildImage() {
    deleteImage
    # sudo docker buildx build -t $imageName:latest -f ./env/Dockerfile.linux .
    podman build -f $containerFile -t $imageName:latest .
}

runImage() {
    local pyScript=$1
    local pyArgs=("${@:2}")
    buildImage
    # sudo docker run --name $imageName $imageName:latest $pyScript ${pyArgs[@]}
    podman run --replace --name $imageName $imageName:latest $pyScript ${pyArgs[@]}
}

copyImageData() {
    local dataPath=$1
    local removeExistingOutDir=$2
    local makeOutDir=$3
    local outDir=$4

    if [ "$removeExistingOutDir" -eq 1 ]; then
        if [ -d "$outDir" ]; then
            sudo rm -r "./$outDir"
        fi
    fi

    if [ "$makeOutDir" -eq 1 ]; then
        mkdir "./$outDir"
    fi

    # sudo docker cp "$imageName:/$dataPath" "./$outDir"
    podman cp "$imageName:/$dataPath" "./$outDir"
    # sudo chown -R --reference=. "./$outDir"
}