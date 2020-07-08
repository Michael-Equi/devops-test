#!/bin/bash

source /opt/ros/foxy/setup.bash

cd /opt/br/node || exit
coveralls --exclude lib --exclude tests --gcov-options '\-lp' -t "${1}"
