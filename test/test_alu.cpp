#include <gtest/gtest.h>

#include <pipeline_project/alu.hpp>

TEST(TestALU, Addition)
{
  ALU32Bit alu;
  alu.setInputs(5, 7, std::bitset<3>(0b000));  // Addition
  ASSERT_EQ(alu.performOperation(), 12);
}

TEST(TestALU, Subtraction)
{
  ALU32Bit alu;
  alu.setInputs(7, 5, std::bitset<3>(0b001));  // Subtraction
  ASSERT_EQ(alu.performOperation(), 2);
}

TEST(TestALU, BitwiseAND)
{
  ALU32Bit alu;
  alu.setInputs(0b1100, 0b1010, std::bitset<3>(0b010));  // Bitwise AND
  ASSERT_EQ(alu.performOperation(), 0b1000);
}

TEST(TestALU, BitwiseOR)
{
  ALU32Bit alu;
  alu.setInputs(0b1100, 0b1010, std::bitset<3>(0b011));  // Bitwise OR
  ASSERT_EQ(alu.performOperation(), 0b1110);
}

TEST(TestALU, LogicalLeftShift)
{
  ALU32Bit alu;
  alu.setInputs(0b1100, 0b1, std::bitset<3>(0b100));  // Logical left shift
  ASSERT_EQ(alu.performOperation(), 0b11000);
}

TEST(TestALU, LogicalRightShift)
{
  ALU32Bit alu;
  alu.setInputs(0b1100, 0b1, std::bitset<3>(0b101));  // Logical right shift
  ASSERT_EQ(alu.performOperation(), 0b110);
}

TEST(TestALU, ArithmeticLeftShift)
{
  ALU32Bit alu;
  alu.setInputs(0b1100, 0b1, std::bitset<3>(0b110));  // Arithmetic left shift
  ASSERT_EQ(alu.performOperation(), 0b11000);
}

TEST(TestALU, ArithmeticRightShiftPositive)
{
  ALU32Bit alu;
  alu.setInputs(0b1100, 0b1, std::bitset<3>(0b111));  // Arithmetic right shift
  ASSERT_EQ(alu.performOperation(), 0b110);
}

TEST(TestALU, ArithmeticRightShiftNegative)
{
  ALU32Bit alu;
  uint32_t negativeValue = 0xFFFFFFFF;                     // Represents -1 in two's complement
  alu.setInputs(negativeValue, 0, std::bitset<3>(0b111));  // Arithmetic right shift
  ASSERT_EQ(alu.performOperation(), negativeValue);  // Should remain negative (MSB remains set)
}

TEST(TestALU, AdditionWithOverflow)
{
  ALU32Bit alu;
  alu.setInputs(0x80000000, 0x80000000, std::bitset<3>("000"));
  ASSERT_EQ(alu.performOperation(), 0x00000000);
}

TEST(TestALU, SubtractionWithUnderflow)
{
  ALU32Bit alu;
  alu.setInputs(0x00000000, 0x00000001, std::bitset<3>("001"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFF);
}

TEST(TestALU, BitwiseANDMixedBits)
{
  ALU32Bit alu;
  alu.setInputs(0x00F0F0F0, 0xFF0F0F0F, std::bitset<3>("010"));
  ASSERT_EQ(alu.performOperation(), 0x00000000);
}

TEST(TestALU, BitwiseORMixedBits)
{
  ALU32Bit alu;
  alu.setInputs(0x00F0F0F0, 0xFF0F0F0F, std::bitset<3>("011"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFF);
}

TEST(TestALU, LogicalLeftShiftMax)
{
  ALU32Bit alu;
  alu.setInputs(0x00000001, 31, std::bitset<3>("100"));
  ASSERT_EQ(alu.performOperation(), 0x80000000);
}

TEST(TestALU, LogicalRightShiftMax)
{
  ALU32Bit alu;
  alu.setInputs(0x80000000, 31, std::bitset<3>("101"));
  ASSERT_EQ(alu.performOperation(), 0x00000001);
}

TEST(TestALU, ArithmeticLeftShiftNegative)
{
  ALU32Bit alu;
  alu.setInputs(0xFFFFFFFF, 1, std::bitset<3>("110"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFE);
}

TEST(TestALU, ArithmeticRightShiftLargerNegative)
{
  ALU32Bit alu;
  alu.setInputs(0x80FFFFFF, 1, std::bitset<3>("111"));
  ASSERT_EQ(alu.performOperation(), 0xC07FFFFF);
}

TEST(TestALU, ArithmeticRightShiftLargerPositive)
{
  ALU32Bit alu;
  alu.setInputs(0x7FFFFFFF, 1, std::bitset<3>("111"));
  ASSERT_EQ(alu.performOperation(), 0x3FFFFFFF);
}

TEST(TestALU, BitwiseANDRandomValues)
{
  ALU32Bit alu;
  alu.setInputs(0x55555555, 0xAAAAAAAA, std::bitset<3>("010"));
  ASSERT_EQ(alu.performOperation(), 0x00000000);
}

TEST(TestALU, BitwiseORRandomValues)
{
  ALU32Bit alu;
  alu.setInputs(0x55555555, 0xAAAAAAAA, std::bitset<3>("011"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFF);
}
