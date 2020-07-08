#!/bin/bash

source /opt/ros/foxy/setup.bash

cd /opt/br/node || exit
colcon test
colcon test-result --all --verbose
# coveralls --exclude lib --exclude tests --gcov-options '\-lp' -t "${1}"
