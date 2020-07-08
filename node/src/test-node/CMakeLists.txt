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
find_package(std_msgs REQUIRED)
find_package(rclcpp REQUIRED)

set(dependencies
    std_msgs
    rclcpp)

include_directories(include)

add_library(incrementer SHARED
        src/incrementer.cpp)

# properly install the library
install(
  TARGETS incrementer
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

add_executable(node src/test-node.cpp)

target_link_libraries(node
        incrementer)

ament_target_dependencies(node ${dependencies})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
  find_package(ament_cmake_gtest REQUIRED)
  find_package(launch_testing_ament_cmake)
  add_subdirectory(test)
endif()

install(TARGETS
        node
        DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/
        DESTINATION include/)

ament_package()
