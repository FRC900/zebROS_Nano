#!/usr/bin/env bash

# Setup ROS for Jetson Slave
source /opt/ros/melodic/setup.bash
source /home/ubuntu/zebROS_Nano/zebROS_ws/devel/setup.bash
export ROS_MASTER_URI=http://10.9.0.12:5802
export ROS_IP=`ip route get 10.9.0.1 | sed 's/ via [[:digit:]]\+\.[[:digit:]]\+\.[[:digit:]]\+\.[[:digit:]]\+//' | sed 's/lo //' | head -1 | cut -d ' ' -f 5`
export ROSLAUNCH_SSH_UNKNOWN=1
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

exec "$@"
