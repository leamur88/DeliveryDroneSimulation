#!/bin/bash

PORT=$2

if [ -z "$2" ]
then
    PORT=8081
fi

SCENE=$1
if [ -z "$1" ]
then
    SCENE=scenes/drone_and_robot_many_deliveries.json
fi

ROOTDIR=`git rev-parse --show-toplevel`

gdb --args ${ROOTDIR}-build/bin/web-app $PORT web $SCENE
