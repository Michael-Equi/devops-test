cmake_minimum_required(VERSION 3.5)
project(test_node)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

include_directories(
        include)

add_library(incrementer SHARED
        src/incrementer.cpp)

#target_include_directories(incrementer PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/test-node>
#        $<INSTALL_INTERFACE:include/test-node>)

add_executable(node src/test-node.cpp)

#target_include_directories(node PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/test-node>
#        $<INSTALL_INTERFACE:include/test-node>)

target_link_libraries(node
        incrementer)

ament_target_dependencies(node rclcpp std_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
  find_package(ament_cmake_gtest REQUIRED)
  add_subdirectory(test)
endif()

install(TARGETS
        node
        DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/
        DESTINATION include/)

ament_package()
