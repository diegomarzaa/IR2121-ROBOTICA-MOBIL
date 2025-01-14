#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
export TURTLEBOT3_MODEL=burger

ros2 launch amcl.launch.py \
  use_sim_time:=True \
  map:=../TI_n1_edited.yaml

# ros2 launch amcl.launch.py \
#   use_sim_time:=True \
#   map:=../TD_n1.yaml

# Simulador:
## (Gazebo + modelo)/bringup + amcl + rviz2 + estimate 2D pose + move robot