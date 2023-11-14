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
  }
};

TEST_F(RTypeInstructionTest, TestAdd)
{
  // Set up initial register values
  simulator.getRegisterFile().write(2, 5);   // $2 = 5
  simulator.getRegisterFile().write(3, 10);  // $3 = 10
  simulator.executeLine(0);
  uint32_t result = simulator.getRegisterFile().read(1);  // Read the result from $1
  ASSERT_EQ(result, 15);                                  // $1 should be 15 (5 + 10)
}

TEST_F(RTypeInstructionTest, TestSub)
{
  // Set up initial register values
  simulator.getRegisterFile().write(5, 20);  // $5 = 20
  simulator.getRegisterFile().write(6, 15);  // $6 = 15
  simulator.executeLine(1);
  uint32_t result = simulator.getRegisterFile().read(4);  // Read the result from $4
  ASSERT_EQ(result, 5);                                   // $4 should be 5 (20 - 15)
}

TEST_F(RTypeInstructionTest, TestAnd)
{
  // Set initial register values for AND operation
  simulator.getRegisterFile().write(9, 0xF0F0F0F0);   // $9 = 0xF0F0F0F0
  simulator.getRegisterFile().write(10, 0x0F0F0F0F);  // $10 = 0x0F0F0F0F
  simulator.executeLine(2);
  uint32_t result = simulator.getRegisterFile().read(8);  // Read the result from $8
  ASSERT_EQ(result, 0x00000000);  // $8 should be 0x00000000 after AND operation with $9 and $10
}

TEST_F(RTypeInstructionTest, TestOr)
{
  // Set initial register values for OR operation
  simulator.getRegisterFile().write(9, 0xF0F0F0F0);   // $9 = 0xF0F0F0F0
  simulator.getRegisterFile().write(10, 0x0F0F0F0F);  // $10 = 0x0F0F0F0F
  simulator.executeLine(3);
  uint32_t result = simulator.getRegisterFile().read(8);  // Read the result from $8
  ASSERT_EQ(result, 0xFFFFFFFF);  // $8 should be 0xFFFFFFFF after OR operation with $9 and $10
}

TEST_F(RTypeInstructionTest, TestXor)
{
  // Set initial register values for XOR operation
  simulator.getRegisterFile().write(9, 0xFF00FF00);   // $9 = 0xFF00FF00
  simulator.getRegisterFile().write(10, 0x00FF00FF);  // $10 = 0x00FF00FF
  simulator.executeLine(4);
  uint32_t result = simulator.getRegisterFile().read(8);  // Read the result from $8
  ASSERT_EQ(result, 0xFFFFFFFF);  // $8 should be 0xFFFFFFFF after XOR operation with $9 and $10
}

TEST_F(RTypeInstructionTest, TestNor)
{
  // Set initial register values for NOR operation
  simulator.getRegisterFile().write(9, 0x00000000);   // $9 = 0x00000000
  simulator.getRegisterFile().write(10, 0x00000000);  // $10 = 0x00000000
  simulator.executeLine(5);
  uint32_t result = simulator.getRegisterFile().read(8);  // Read the result from $8
  ASSERT_EQ(
    result,
    0xFFFFFFFF);  // $8 should be 0xFFFFFFFF after NOR operation with $9 and $10 (since NOR of zeros is all ones)
}

TEST_F(RTypeInstructionTest, TestSll)
{
  // Set up initial register values for SLL operation
  simulator.getRegisterFile().write(2, 0b0001);  // $2 = 1
  //   simulator.getRegisterFile().printRegisterState();
  simulator.executeLine(6);  // Execute the line corresponding to the SLL instruction
                             //   simulator.getRegisterFile().printRegisterState();
  uint32_t result = simulator.getRegisterFile().read(11);  // Read the result from $11
  ASSERT_EQ(result, 0b0100);  // $11 should be 4 after shifting $2 left by 2 bits
}

TEST_F(RTypeInstructionTest, TestSrl)
{
  // Set up initial register values for SRL operation
  simulator.getRegisterFile().write(5, 0b0100);  // $5 = 4
  simulator.executeLine(7);  // Execute the line corresponding to the SRL instruction
                             //   simulator.getRegisterFile().printRegisterState();
  uint32_t result = simulator.getRegisterFile().read(12);  // Read the result from $12
  ASSERT_EQ(result, 0b0010);  // $12 should be 2 after shifting $5 right by 1 bit
}

TEST_F(RTypeInstructionTest, TestSra)
{
  // Set up initial register values for SRA operation
  simulator.getRegisterFile().write(6, 0xFFFFFFFC);  // $6 = -4 (in two's complement)
  simulator.executeLine(8);  // Execute the line corresponding to the SRA instruction
  uint32_t result = simulator.getRegisterFile().read(13);  // Read the result from $13
  ASSERT_EQ(
    result, 0xFFFFFFFE);  // $13 should be -2 after arithmetically shifting $6 right by 1 bit
}

TEST_F(RTypeInstructionTest, TestSla)
{
  // Set up initial register values for SLA operation
  simulator.getRegisterFile().write(3, 0b0001);  // $3 = 1
  simulator.executeLine(9);  // Execute the line corresponding to the SLA instruction
  uint32_t result = simulator.getRegisterFile().read(14);  // Read the result from $14
  ASSERT_EQ(
    result,
    0b0100);  // $14 should be 4 after shifting $3 left by 2 bits (arithmetic shift assumed similar to logical shift)
}