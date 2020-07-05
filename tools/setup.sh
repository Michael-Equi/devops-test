#!/bin/bash

source /opt/ros/foxy/setup.bash

cd /opt/br/node/src
# vcs import < /tools/deps.repos
cd ..
colcon build
colcon test
colcon test-results --all --verbose
