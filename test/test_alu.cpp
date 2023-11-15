#include <gtest/gtest.h>

#include <pipeline_project/alu.hpp>
#include <pipeline_project/utils.hpp>

TEST(TestALU, Addition)
{
  ALU alu;
  alu.setInputs(5, 7, std::bitset<4>(0b0010));  // Addition
  ASSERT_EQ(alu.performOperation(), 12);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, AdditionWithOverflow)
{
  ALU alu;
  alu.setInputs(0x80000000, 0x80000000, std::bitset<4>("0010"));
  ASSERT_EQ(alu.performOperation(), 0x00000000);
  ASSERT_TRUE(alu.isZero());
  ASSERT_TRUE(alu.hasOverflow());
  ASSERT_TRUE(alu.hasCarryOut());
}

TEST(TestALU, Subtraction)
{
  ALU alu;
  alu.setInputs(7, 5, std::bitset<4>(0b0110));  // Subtraction
  ASSERT_EQ(alu.performOperation(), 2);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, SubtractionWithUnderflow)
{
  ALU alu;
  alu.setInputs(0x00000000, 0x00000001, std::bitset<4>("0110"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFF);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_TRUE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseAND)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1010, std::bitset<4>(0b000));  // Bitwise AND
  ASSERT_EQ(alu.performOperation(), 0b1000);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseANDMixedBits)
{
  ALU alu;
  alu.setInputs(0x00F0F0F0, 0xFF0F0F0F, std::bitset<4>("0000"));
  ASSERT_EQ(alu.performOperation(), 0x00000000);
  ASSERT_TRUE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseANDRandomValues)
{
  ALU alu;
  alu.setInputs(0x55555555, 0xAAAAAAAA, std::bitset<4>("0000"));
  ASSERT_EQ(alu.performOperation(), 0x00000000);
  ASSERT_TRUE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseOR)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1010, std::bitset<4>(0b001));  // Bitwise OR
  ASSERT_EQ(alu.performOperation(), 0b1110);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseORMixedBits)
{
  ALU alu;
  alu.setInputs(0x00F0F0F0, 0xFF0F0F0F, std::bitset<4>("0001"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFF);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, BitwiseORRandomValues)
{
  ALU alu;
  alu.setInputs(0x55555555, 0xAAAAAAAA, std::bitset<4>("0001"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFF);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, SetOnLessThanPositive)
{
  ALU alu;
  alu.setInputs(
    5, 10, std::bitset<4>(0b101));       // SLT, assuming the ALU operation code for SLT is 0b101
  ASSERT_EQ(alu.performOperation(), 1);  // 5 is less than 10, so result should be 1
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, SetOnLessThanNegative)
{
  ALU alu;
  // Testing with negative numbers
  alu.setInputs(
    0xFFFFFFFA, 0x5, std::bitset<4>(0b101));  // SLT, 0xFFFFFFFA is -6 in two's complement
  ASSERT_EQ(alu.performOperation(), 1);       // -6 is less than 5, so result should be 1
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, SetOnLessThanFalse)
{
  ALU alu;
  alu.setInputs(10, 5, std::bitset<4>(0b101));  // SLT
  ASSERT_EQ(alu.performOperation(), 0);         // 10 is not less than 5, so result should be 0
  ASSERT_TRUE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ShiftLeftLogical)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1, std::bitset<4>(0b0111));  // Logical left shift
  ASSERT_EQ(alu.performOperation(), 0b11000);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ShiftLeftLogicalMax)
{
  ALU alu;
  alu.setInputs(0x00000001, 31, std::bitset<4>("0111"));
  ASSERT_EQ(alu.performOperation(), 0x80000000);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ShiftRightLogical)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1, std::bitset<4>(0b1000));  // Logical right shift
  ASSERT_EQ(alu.performOperation(), 0b110);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ShiftRightLogicalMax)
{
  ALU alu;
  alu.setInputs(0x80000000, 31, std::bitset<4>("1000"));
  ASSERT_EQ(alu.performOperation(), 0x00000001);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ShiftLeftArithmetic)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1, std::bitset<4>(0b1001));  // Arithmetic left shift
  ASSERT_EQ(alu.performOperation(), 0b11000);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ShiftLeftArithmeticNegative)
{
  ALU alu;
  alu.setInputs(0xFFFFFFFF, 1, std::bitset<4>("1001"));
  ASSERT_EQ(alu.performOperation(), 0xFFFFFFFE);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ShiftRightArithmeticPositive)
{
  ALU alu;
  alu.setInputs(0b1100, 0b1, std::bitset<4>(0b1010));  // Arithmetic right shift
  ASSERT_EQ(alu.performOperation(), 0b110);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ShiftRightArithmeticNegative)
{
  ALU alu;
  uint32_t negativeValue = 0xFFFFFFFF;                      // Represents -1 in two's complement
  alu.setInputs(negativeValue, 0, std::bitset<4>(0b1010));  // Arithmetic right shift
  ASSERT_EQ(alu.performOperation(), negativeValue);  // Should remain negative (MSB remains set)
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ShiftRightArithmeticLargerNegative)
{
  ALU alu;
  alu.setInputs(0x80FFFFFF, 1, std::bitset<4>("1010"));
  ASSERT_EQ(alu.performOperation(), 0xC07FFFFF);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, ShiftRightArithmeticLargerPositive)
{
  ALU alu;
  alu.setInputs(0x7FFFFFFF, 1, std::bitset<4>("1010"));
  ASSERT_EQ(alu.performOperation(), 0x3FFFFFFF);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, Multiplication)
{
  ALU alu;
  alu.setInputs(7, 5, std::bitset<4>(0b1011));  // Multiplication
  ASSERT_EQ(alu.performOperation(), 35);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());

  alu.setInputs(3, 3, std::bitset<4>(0b1011));
  ASSERT_EQ(alu.performOperation(), 9);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, Division)
{
  ALU alu;
  alu.setInputs(15, 3, std::bitset<4>(0b1100));  // Division
  ASSERT_EQ(alu.performFloatOperation(), 5);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());

  alu.setInputs(3, 3, std::bitset<4>(0b1100));
  ASSERT_EQ(alu.performFloatOperation(), 1);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());

  alu.setInputs(1, 2, std::bitset<4>(0b1100));
  ASSERT_EQ(alu.performFloatOperation(), 0.5);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, SquareRoot)
{
  ALU alu;
  alu.setFloatInput(9, std::bitset<4>(0b1101));  // Square Root
  ASSERT_EQ(alu.performFloatOperation(), 3);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());

  alu.setFloatInput(1525225, std::bitset<4>(0b1101));
  ASSERT_EQ(alu.performFloatOperation(), 1235);
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}

TEST(TestALU, FastInverseSquareRoot)
{
  ALU alu;
  alu.setFloatInput(0.01234567901, std::bitset<4>(0b1110));  // Fast Inverse Square Root
  ASSERT_TRUE(almostEqual(alu.performFloatOperation(), 8.99679));
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());

  alu.setFloatInput(3211, std::bitset<4>(0b1110));
  ASSERT_TRUE(almostEqual(alu.performFloatOperation(), 0.0176398));
  ASSERT_FALSE(alu.isZero());
  ASSERT_FALSE(alu.hasOverflow());
  ASSERT_FALSE(alu.hasCarryOut());
}