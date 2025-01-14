#!/usr/bin/env bash

source /opt/ros/humble/setup.bash
source ./install/setup.bash
source /usr/share/gazebo-11/setup.bash

export ROS_LOCALHOST_ONLY=1
export TURTLEBOT3_MODEL=waffle_pi
#export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:./src/aws-robomaker-bookstore-world/models

ros2 launch aws_robomaker_bookstore_world turtlebot3_bookstore.launch.py 

