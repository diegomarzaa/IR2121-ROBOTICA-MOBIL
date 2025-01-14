#!/usr/bin/env bash

source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1

rviz2 -d config_slam.rviz

