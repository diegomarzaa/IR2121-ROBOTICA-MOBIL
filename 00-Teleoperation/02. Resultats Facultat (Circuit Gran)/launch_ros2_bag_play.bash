#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
export TURTLEBOT3_MODEL=burger
ros2 bag play CircuitoGrande/rosbag2_2024_09_19-10_38_22_circuitogrande/rosbag2_2024_09_19-10_38_22_0.db3
