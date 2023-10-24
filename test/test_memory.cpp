#include <gtest/gtest.h>

#include <pipeline_project/memory.hpp>

class TestMemory : public ::testing::Test
{
protected:
  Memory mem;
};

TEST_F(TestMemory, WriteAndReadWord)
{
  mem.writeWord(0, 0xDEADBEEF);
  ASSERT_EQ(mem.readWord(0), 0xDEADBEEF);
}

TEST_F(TestMemory, WriteAndReadHalfWord)
{
  mem.writeWord(0, 0);
  ASSERT_EQ(mem.readWord(0), 0);  // Initial condition

  mem.writeHalfWord(0, 0xCAFE);
  ASSERT_EQ(mem.readWord(0), 0x0000CAFE);
  ASSERT_EQ(mem.readHalfWord(0), 0xCAFE);

  mem.writeWord(4, 0);
  ASSERT_EQ(mem.readWord(4), 0);  // Initial condition for second word

  mem.writeHalfWord(4, 0xBABE);
  ASSERT_EQ(mem.readWord(4), 0x0000BABE);
  ASSERT_EQ(mem.readHalfWord(4), 0xBABE);
}

TEST_F(TestMemory, WriteAndReadByte)
{
  mem.writeWord(0, 0);  // Clearing initial position

  mem.writeByte(0, 0xAA);
  ASSERT_EQ(mem.readWord(0), 0xAA);

  mem.writeByte(1, 0xBB);
  ASSERT_EQ(mem.readWord(0), 0xBBAA);
  ASSERT_EQ(mem.readByte(1), 0xBB);

  mem.writeByte(2, 0xCC);
  ASSERT_EQ(mem.readWord(0), 0xCCBBAA);
  ASSERT_EQ(mem.readByte(2), 0xCC);

  mem.writeByte(3, 0xDD);
  ASSERT_EQ(mem.readWord(0), 0xDDCCBBAA);
  ASSERT_EQ(mem.readByte(3), 0xDD);
}

TEST_F(TestMemory, OutOfBoundsAccess)
{
  // Assuming default size is 1024 words (4096 bytes)
  ASSERT_THROW(
    mem.readWord(4096), std::out_of_range);  // Should throw out_of_range since out of bounds

  ASSERT_THROW(
    mem.writeWord(4096, 0xFF),
    std::out_of_range);  // Should also throw out_of_range since out of bounds

  ASSERT_THROW(
    mem.readWord(4096), std::out_of_range);  // Should again throw out_of_range since out of bounds
}

TEST_F(TestMemory, AlmostOutOfBoundsAccess)
{
  // Assuming default size is 1024 words (4096 bytes)
  ASSERT_EQ(mem.readWord(4092), 0xDEADBEEF);  // Should return the default value
  mem.writeWord(4092, 0xFF);
  ASSERT_EQ(mem.readWord(4092), 0xFF);
}

TEST_F(TestMemory, BoundaryAccess)
{
  // Assuming default size is 1024 words (4096 bytes)
  mem.writeWord(0, 0x12345678);
  ASSERT_EQ(mem.readWord(0), 0x12345678);

  mem.writeWord(4092, 0x87654321);
  ASSERT_EQ(mem.readWord(4092), 0x87654321);
}

TEST_F(TestMemory, SimultaneousWrites)
{
  mem.writeWord(0, 0);
  mem.writeByte(0, 0xAA);
  mem.writeHalfWord(2, 0xBBBB);
  ASSERT_EQ(mem.readWord(0), 0xBBBB00AA);
}
TEST_F(TestMemory, MemoryReset)
{
  mem.writeWord(0, 0x12345678);
  mem.reset();
  ASSERT_EQ(mem.readWord(0), 0xDEADBEEF);
}
