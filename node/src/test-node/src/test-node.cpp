// Copyright 2020 Bytes Robotics

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "test-node/incrementer.h"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    count_ = increment(count_);
    message.data = "Hello, world!! " + std::to_string(count_);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    // std::cout << "f.Hello, world!! " << std::to_string(count_) << std::endl;
    // std::cout << "[node-1] [INFO] [1594179542.574017815] [minimal_publisher]: Publishing: 'Hello, world!! " << std::to_string(count_) << "'" << std::endl;

    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  std::cout << "Starting Up" << std::endl;
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
