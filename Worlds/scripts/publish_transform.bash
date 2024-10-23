#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
ros2 run tf2_ros static_transform_publisher --x 1 --y 8 --z 0 \
  --qx 0 --qy 0 --qz 0 --qw 1 --frame-id map --child-frame-id odom

# ros2 run tf2_ros static_transform_publisher --x 0 --y 0 --z 0 \
#   --qx 0 --qy 0 --qz 0 --qw 1 --frame-id source_frame --child-frame-id target_frame

# ros2 run tf2_ros tf2_echo source_frame target_frame

# ros2 run tf2_tools view_frames.py