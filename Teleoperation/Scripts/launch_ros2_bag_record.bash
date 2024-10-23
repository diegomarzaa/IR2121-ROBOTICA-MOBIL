#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
export TURTLEBOT3_MODEL=burger
ros2 bag record /clock /map /odom /scan /tf /tf_static /amcl_pose /particle_cloud /robot_description