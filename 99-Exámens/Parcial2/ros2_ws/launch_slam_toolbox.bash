#!/usr/bin/env bash

source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
export TURTLEBOT3_MODEL=waffle_pi

ros2 launch slam_toolbox online_async_launch.py use_sim_time:=True

