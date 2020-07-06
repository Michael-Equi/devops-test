#!/bin/bash

source /opt/ros/foxy/setup.bash

cd /opt/br/node || exit
colcon test
colcon test-result --all --verbose
echo "############################### REPO TOKEN ${DEVOPS_TEST_COVERALLS_REPO_TOKEN}"
coveralls --exclude lib --exclude tests --gcov-options '\-lp' -t "${DEVOPS_TEST_COVERALLS_REPO_TOKEN}"
