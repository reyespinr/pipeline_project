#include <gtest/gtest.h>

#include "register_file.hpp"

class TestRegisterFile : public ::testing::Test
{
protected:
  RegisterFile reg_file;

  // Set up for each test.
  virtual void SetUp()
  {
    // By default, reset all registers to zero before each test.
    for (uint8_t i = 0; i < 32; ++i) {
      reg_file.write(i, 0);
    }
  }
};

// Test reading from register 0. It should always return 0 regardless of writes.
TEST_F(TestRegisterFile, ReadRegisterZero)
{
  reg_file.write(0, 12345);
  ASSERT_EQ(reg_file.read(0), 0);
}

// Test writing and reading from a general-purpose register.
TEST_F(TestRegisterFile, WriteAndReadGeneralRegister)
{
  reg_file.write(5, 0xDEADBEEF);
  ASSERT_EQ(reg_file.read(5), 0xDEADBEEF);
}

// Test if writing to one register does not affect others.
TEST_F(TestRegisterFile, NoInterferenceBetweenRegisters)
{
  reg_file.write(3, 0xABCDEF12);
  reg_file.write(4, 0x34567890);
  ASSERT_EQ(reg_file.read(3), 0xABCDEF12);
  ASSERT_EQ(reg_file.read(4), 0x34567890);
}

// Test exception when reading from an out-of-bounds register number.
TEST_F(TestRegisterFile, OutOfBoundsRead) { ASSERT_THROW(reg_file.read(32), std::out_of_range); }

// Test exception when writing to an out-of-bounds register number.
TEST_F(TestRegisterFile, OutOfBoundsWrite)
{
  ASSERT_THROW(reg_file.write(32, 0x12345678), std::out_of_range);
}

// Test if reading after writing multiple times to the same register returns the last written value.
TEST_F(TestRegisterFile, MultipleWritesToSameRegister)
{
  reg_file.write(7, 0x11111111);
  reg_file.write(7, 0x22222222);
  reg_file.write(7, 0x33333333);
  ASSERT_EQ(reg_file.read(7), 0x33333333);
}
