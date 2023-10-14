#include <gtest/gtest.h>

#include <pipeline_project/alu.hpp>

TEST(TestALU, Addition)
{
  ALU alu;
  alu.setInputs(5, 7, std::bitset<3>(0b000));  // Addition
  ASSERT_EQ(alu.performOperation(), 12);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, Subtraction)
{
  ALU alu;
  alu.setInputs(7, 5, std::bitset<3>(0b001));  // Subtraction
  ASSERT_EQ(alu.performOperation(), 2);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseAND)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1010, std::bitset<3>(0b010));  // Bitwise AND
  ASSERT_EQ(alu.performOperation(), 0b1000);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseOR)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1010, std::bitset<3>(0b011));  // Bitwise OR
  ASSERT_EQ(alu.performOperation(), 0b1110);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, LogicalLeftShift)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1, std::bitset<3>(0b100));  // Logical left shift
  ASSERT_EQ(alu.performOperation(), 0b11000);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, LogicalRightShift)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1, std::bitset<3>(0b101));  // Logical right shift
  ASSERT_EQ(alu.performOperation(), 0b110);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ArithmeticLeftShift)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1, std::bitset<3>(0b110));  // Arithmetic left shift
  ASSERT_EQ(alu.performOperation(), 0b11000);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ArithmeticRightShiftPositive)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1, std::bitset<3>(0b111));  // Arithmetic right shift
  ASSERT_EQ(alu.performOperation(), 0b110);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ArithmeticRightShiftNegative)
{
  ALU alu;
  uint32_t negativeValue = 0xFFFFFFFF;                     // Represents -1 in two's complement
  alu.setInputs(negativeValue, 0, std::bitset<3>(0b111));  // Arithmetic right shift
  ASSERT_EQ(alu.performOperation(), negativeValue);  // Should remain negative (MSB remains set)
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, AdditionWithOverflow)
{
  ALU alu;
  alu.setInputs(0x80000000, 0x80000000, std::bitset<3>("000"));
  ASSERT_EQ(alu.performOperation(), 0x00000000);
  ASSERT_TRUE(alu.isZero());
  ASSERT_TRUE(alu.hasOverflow());
  ASSERT_TRUE(alu.hasCarryOut());
}

TEST(TestALU, SubtractionWithUnderflow)
{
  ALU alu;
  alu.setInputs(0x00000000, 0x00000001, std::bitset<3>("001"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFF);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_TRUE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseANDMixedBits)
{
  ALU alu;
  alu.setInputs(0x00F0F0F0, 0xFF0F0F0F, std::bitset<3>("010"));
  ASSERT_EQ(alu.performOperation(), 0x00000000);
  ASSERT_TRUE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseORMixedBits)
{
  ALU alu;
  alu.setInputs(0x00F0F0F0, 0xFF0F0F0F, std::bitset<3>("011"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFF);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, LogicalLeftShiftMax)
{
  ALU alu;
  alu.setInputs(0x00000001, 31, std::bitset<3>("100"));
  ASSERT_EQ(alu.performOperation(), 0x80000000);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, LogicalRightShiftMax)
{
  ALU alu;
  alu.setInputs(0x80000000, 31, std::bitset<3>("101"));
  ASSERT_EQ(alu.performOperation(), 0x00000001);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ArithmeticLeftShiftNegative)
{
  ALU alu;
  alu.setInputs(0xFFFFFFFF, 1, std::bitset<3>("110"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFE);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ArithmeticRightShiftLargerNegative)
{
  ALU alu;
  alu.setInputs(0x80FFFFFF, 1, std::bitset<3>("111"));
  ASSERT_EQ(alu.performOperation(), 0xC07FFFFF);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ArithmeticRightShiftLargerPositive)
{
  ALU alu;
  alu.setInputs(0x7FFFFFFF, 1, std::bitset<3>("111"));
  ASSERT_EQ(alu.performOperation(), 0x3FFFFFFF);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseANDRandomValues)
{
  ALU alu;
  alu.setInputs(0x55555555, 0xAAAAAAAA, std::bitset<3>("010"));
  ASSERT_EQ(alu.performOperation(), 0x00000000);
  ASSERT_TRUE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseORRandomValues)
{
  ALU alu;
  alu.setInputs(0x55555555, 0xAAAAAAAA, std::bitset<3>("011"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFF);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}
