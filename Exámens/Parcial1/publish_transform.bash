#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
ros2 run tf2_ros static_transform_publisher --x 2.2 --y 2.4 --z 0 \
  --qx 0 --qy 0 --qz 0 --qw 1 --frame-id map --child-frame-id odom
