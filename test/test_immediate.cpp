#include <gtest/gtest.h>

#include <pipeline_project/immediate.hpp>

class TestImmediate : public ::testing::Test
{
protected:
  Immediate immediateGen;
};

// Test for sign extension of a positive immediate
TEST_F(TestImmediate, SignExtendPositive)
{
  std::uint32_t result = immediateGen.signExtend(0x1234);
  ASSERT_EQ(result, 0x00001234);
}

// Test for sign extension of a negative immediate
TEST_F(TestImmediate, SignExtendNegative)
{
  std::uint32_t result = immediateGen.signExtend(0xFFFF);  // -1 in 16-bit two's complement
  ASSERT_EQ(result, 0xFFFFFFFF);
}

// Test for upper placement of a positive immediate
TEST_F(TestImmediate, UpperPlacePositive)
{
  std::uint32_t result = immediateGen.placeImmediateUpper(0x1234);
  ASSERT_EQ(result, 0x12340000);
}

// Test for upper placement of a negative immediate
TEST_F(TestImmediate, UpperPlaceNegative)
{
  std::uint32_t result = immediateGen.placeImmediateUpper(0x8765);
  ASSERT_EQ(result, 0x87650000);
}
