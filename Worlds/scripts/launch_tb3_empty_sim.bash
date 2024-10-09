#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_DOMAIN_ID=30
export ROS_LOCALHOST_ONLY=0
export TURTLEBOT3_MODEL=burger
ros2 launch turtlebot3_gazebo \
     empty_world.launch.py

