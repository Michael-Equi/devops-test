#!/bin/bash

source /opt/ros/foxy/setup.bash

cd /opt/br/node
colcon test
colcon test-result --all --verbose
