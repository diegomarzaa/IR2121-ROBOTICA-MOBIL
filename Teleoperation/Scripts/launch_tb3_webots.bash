#!/bin/bash

# Source ROS2 Humble setup
source /opt/ros/humble/setup.bash

# Restrict ROS communication to localhost
export ROS_LOCALHOST_ONLY=1

# Set the Webots home directory
export WEBOTS_HOME=$HOME/webots-R2023b

# Launch the Webots TurtleBot3 simulation
ros2 launch webots_ros2_turtlebot robot_launch.py
