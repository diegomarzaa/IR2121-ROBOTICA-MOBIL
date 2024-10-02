#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_DOMAIN_ID=8
export ROS_LOCALHOST_ONLY=0
export TURTLEBOT3_MODEL=burger

ros2 run tf2_ros static_transform_publisher --x 1 --y 8 --z 0 \
  --qx 0 --qy 0 --qz 0 --qw 1 --frame-id map --child-frame-id odom
