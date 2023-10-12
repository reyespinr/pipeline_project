#include <gtest/gtest.h>

#include <pipeline_project/example.hpp>

TEST(TestExample, CheckTestsAreWorking)
{
  const auto is_it_working = true;
  EXPECT_TRUE(is_it_working);
}

TEST(TestExample, CheckExecutableIsWorking)
{
  const auto is_it_working = checkContainer();
  EXPECT_TRUE(is_it_working);
}
