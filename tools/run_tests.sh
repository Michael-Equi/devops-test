#!/bin/bash

source /opt/ros/foxy/setup.bash

cd /opt/br/node || exit
colcon test
colcon test-result --all --verbose
