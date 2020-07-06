// Copyright 2020 Bytes Robotics

#include "test-node/incrementer.h"
#include "gtest/gtest.h"

TEST(incremeter, increment) {
  int var = 0;
  var = increment(var);
  EXPECT_EQ(var, 1);
}
