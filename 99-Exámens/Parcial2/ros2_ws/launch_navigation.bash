#!/usr/bin/env bash

source /opt/ros/humble/setup.bash
source ./install/setup.bash

export ROS_LOCALHOST_ONLY=1
export TURTLEBOT3_MODEL=waffle_pi

ros2 launch turtlebot3_navigation2 navigation2.launch.py use_sim_time:=True map:=/home/usuario/Documentos/GitHub/IR2121-ROBOTICA-MOBIL/Exámens/Parcial2/ros2_ws/maps/map_rtabmap_5.yaml
