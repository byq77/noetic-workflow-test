#!/usr/bin/env bash

set -e

# Setup ROS environment
catkin init --workspace /ros_ws --reset

# Build ROS workspace
catkin build
