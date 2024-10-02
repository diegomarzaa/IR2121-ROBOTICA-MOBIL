#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_DOMAIN_ID=8
export ROS_LOCALHOST_ONLY=0
export TURTLEBOT3_MODEL=burger
ros2 run turtlebot3_teleop teleop_keyboard
