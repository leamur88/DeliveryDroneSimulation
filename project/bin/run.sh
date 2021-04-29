#!/bin/bash

PORT=$2

if [ -z "$2" ]
then
    PORT=8081
fi

SCENE=$1
if [ -z "$1" ]
then
	SCENE=presentation/all_features.json
	#SCENE=presentation/robot_mult_package.json
	#SCENE=presentation/drone_multiple_pickup.json
	#SCENE=presentation/drone_low_battery.json
fi

ROOTDIR=`git rev-parse --show-toplevel`

${ROOTDIR}-build/bin/web-app $PORT web $SCENE
