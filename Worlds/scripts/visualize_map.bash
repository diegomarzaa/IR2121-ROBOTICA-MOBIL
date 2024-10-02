#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_DOMAIN_ID=8
export ROS_LOCALHOST_ONLY=0
export TURTLEBOT3_MODEL=burger
rviz2 -d config_map.rviz
