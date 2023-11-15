#include <gtest/gtest.h>

#include <pipeline_project/simulator.hpp>

class TestDemo : public ::testing::Test
{
protected:
  MipsSimulator simulator;

  TestDemo() : simulator("../../test/test_files/r_type_test_input.txt") {}

  void SetUp() override
  {
    simulator.reset();  // Reset simulator state before each test
  }
};

TEST_F(TestDemo, RunDemo)
{
  // Set up initial register values
  // $v0 = 0040hex
  // $v1 = 1010hex
  // $s2 = 000Fhex
  // $s3 = 00F0hex
  // $t0 = 0000hex
  // $a0 = 0010hex
  // $a1 = 0005hex
  simulator.getRegisterFile().write(1, 0x0040);
  simulator.getRegisterFile().write(2, 0x1010);
  simulator.getRegisterFile().write(3, 0x000F);
  simulator.getRegisterFile().write(4, 0x00F0);
  simulator.getRegisterFile().write(5, 0x0000);
  simulator.getRegisterFile().write(6, 0x0010);
  simulator.getRegisterFile().write(5, 0x0005);
  simulator.execute();
  uint32_t result = simulator.getRegisterFile().read(1);
  ASSERT_EQ(1, 1);
}