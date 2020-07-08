// Copyright 2020 Bytes Robotics

#include <memory>

#include "gtest/gtest.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class TestNode : public rclcpp::Node
{
public:
  TestNode()
  : Node("tester")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "topic", 10, std::bind(&TestNode::topic_callback, this, _1));
    message_received = false;
  }

  bool message_received;

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg)
  {
    message_received = true;
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TestNode>();
  testing::InitGoogleTest(&argc, argv);

  int ret = RUN_ALL_TESTS();
  RCLCPP_INFO(rclcpp::get_logger("tester"), "gtest return value: %d", ret);

  // rclcpp::spin(node);
  rclcpp::shutdown();

  return ret;
}
