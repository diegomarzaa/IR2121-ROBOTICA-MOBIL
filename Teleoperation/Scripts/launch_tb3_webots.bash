#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
export WEBOTS_HOME=$HOME/webots-R2023b
ros2 launch webots_ros2_turtlebot robot_launch.py
