#!/bin/bash

containerEngine=$(head -n 1 ./env/container_engine)
missingContainerEngineError="Hello, this is Lord Glowmouse hehe...\nI can't seem to find my 'container_engine'\nI left in 'env/'\nI wrote something really important in there, can't seem to remember what...\nWas it 'podman', was it 'docker', idk...\nFind it for me, and I'll give you a lil' bite... hehe..."
imageName=manor-game-env
containerFile=./env/Containerfile

deleteImage() {
    if [[ $containerEngine == podman ]]; then
        podman rmi -f $imageName:latest
    elif [[ $containerEngine == docker ]]; then
        if [ "$(sudo docker ps -a -q -f name=^${imageName})" ]; then
            sudo docker rm -f $imageName
        fi
    else
        echo -e $missingContainerEngineError
    fi
}

buildImage() {
    deleteImage

    if [[ $containerEngine == podman ]]; then
        podman build -f $containerFile -t $imageName:latest .
    elif [[ $containerEngine == docker ]]; then
        sudo docker buildx build -t $imageName:latest -f $containerFile .
    else
        echo -e $missingContainerEngineError
    fi
}

runImage() {
    local pyScript=$1
    local pyArgs=("${@:2}")
    buildImage

    if [[ $containerEngine == podman ]]; then
        podman run --replace --name $imageName $imageName:latest $pyScript ${pyArgs[@]}
    elif [[ $containerEngine == docker ]]; then
        sudo docker run --name $imageName $imageName:latest $pyScript ${pyArgs[@]}
    else
        echo -e $missingContainerEngineError
    fi
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

    if [[ $containerEngine == podman ]]; then
        podman cp "$imageName:/$dataPath" "./$outDir"
    elif [[ $containerEngine == docker ]]; then
        sudo docker cp "$imageName:/$dataPath" "./$outDir"
    else
        echo -e $missingContainerEngineError
    fi

    # sudo chown -R --reference=. "./$outDir"
}