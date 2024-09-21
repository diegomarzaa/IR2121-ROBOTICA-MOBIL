#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
export TURTLEBOT3_MODEL=burger
ros2 bag play rosbag2_2024_09_21-17_00_20/rosbag2_2024_09_21-17_00_20_0.db3
