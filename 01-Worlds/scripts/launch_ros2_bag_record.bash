#!/bin/bash
source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
export TURTLEBOT3_MODEL=burger

# Basic teleop
# ros2 bag record /odom /tf /tf_static

# Maps:
ros2 bag record /clock /map /odom /scan /tf /tf_static

# Maps físico:
# ros2 bag record /map /odom /scan /tf /tf_static
## /scan -> Reliability: Best effort.   Durability: Volatile

# Maps + AMCL:
# ros2 bag record /clock /map /odom /scan /tf /tf_static /amcl_pose /particle_cloud /robot_description