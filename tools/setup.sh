#!/bin/bash

source /opt/ros/foxy/setup.bash

# install coveralls-cpp in order to send coveralls report
cd /
git clone https://github.com/eddyxu/cpp-coveralls.git
cd cpp-coveralls || exit
python3 setup.py install

cd /opt/br/node/src || exit
# vcs import < /tools/deps.repos
cd ..

colcon build --ament-cmake-args -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS}  -fprofile-arcs -ftest-coverage " \
        -DCMAKE_C_FLAGS="${CMAKE_C_FLAGS}  -fprofile-arcs -ftest-coverage "
