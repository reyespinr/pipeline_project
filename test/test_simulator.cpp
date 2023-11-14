#include <gtest/gtest.h>

#include <pipeline_project/simulator.hpp>

class RTypeInstructionTest : public ::testing::Test
{
protected:
  MipsSimulator simulator;

  RTypeInstructionTest() : simulator("../../test/test_files/r_type_test_input.txt") {}

  void SetUp() override
  {
    simulator.reset();  // Reset simulator state before each test

    // Set up initial register values
    simulator.getRegisterFile().write(2, 5);   // $2 = 5
    simulator.getRegisterFile().write(3, 10);  // $3 = 10
    simulator.getRegisterFile().write(5, 20);  // $5 = 20
    simulator.getRegisterFile().write(6, 15);  // $6 = 15
  }
};

TEST_F(RTypeInstructionTest, TestAdd)
{
  simulator.execute();
  uint32_t result = simulator.getRegisterFile().read(1);  // Read the result from $1
  ASSERT_EQ(result, 15);                                  // $1 should be 15 (5 + 10)
}

TEST_F(RTypeInstructionTest, TestSub)
{
  simulator.execute();
  uint32_t result = simulator.getRegisterFile().read(4);  // Read the result from $4
  ASSERT_EQ(result, 5);                                   // $4 should be 5 (20 - 15)
}
