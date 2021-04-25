#!/bin/bash

PORT=$2

if [ -z "$2" ]
then
    PORT=8081
fi

SCENE=$1
if [ -z "$1" ]
then
    #SCENE=iter1_scenes/multiple_packages.json
    #SCENE=iter1_scenes/umn.json
    #SCENE=scenes/parabolic_drone.json
    #SCENE=scenes/drone_and_robot.json
	SCENE=scenes/drone_and_robot_many_deliveries.json
    #SCENE=scenes/drone_low_battery_b.json
	#SCENE=scenes/drone_delivers_two_packages_at_once.json
	#SCENE=scenes/drone_cant_carry_two_packages.json
fi

ROOTDIR=`git rev-parse --show-toplevel`

${ROOTDIR}-build/bin/web-app $PORT web $SCENE
