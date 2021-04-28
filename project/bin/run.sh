#!/bin/bash

PORT=$2

if [ -z "$2" ]
then
    PORT=8081
fi

SCENE=$1
if [ -z "$1" ]
then
    #SCENE=scenes/parabolic_drone.json
	#SCENE=scenes/drone_and_robot_many_deliveries.json
	#SCENE=presentation/all_features.json.json
	#SCENE=presentation/robot_mult_package.json
	SCENE=presentation/drone_multiple_pickup.json
	#SCENE=presentation/drone_low_battery.json
    #SCENE=scenes/drone_low_battery_b.json
fi

ROOTDIR=`git rev-parse --show-toplevel`

${ROOTDIR}-build/bin/web-app $PORT web $SCENE
