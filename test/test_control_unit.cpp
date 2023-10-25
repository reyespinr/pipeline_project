#include <gtest/gtest.h>

#include <pipeline_project/control_unit.hpp>

class TestControlUnit : public ::testing::Test
{
protected:
  ControlUnit cu;

  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(TestControlUnit, LoadWordTest)
{
  cu.set_opcode(0b100011);  // lw (load word)
  EXPECT_EQ(cu.get_mem_read(), true);
  EXPECT_EQ(cu.get_reg_write(), true);
  EXPECT_EQ(cu.get_mem_to_reg(), true);
  EXPECT_EQ(cu.get_alu_src(), true);
  EXPECT_EQ(cu.get_alu_op(), 0b000);
}

TEST_F(TestControlUnit, StoreWordTest)
{
  cu.set_opcode(0b101011);  // sw (store word)
  EXPECT_EQ(cu.get_mem_write(), true);
  EXPECT_EQ(cu.get_alu_src(), true);
  EXPECT_EQ(cu.get_alu_op(), 0b000);
}

TEST_F(TestControlUnit, BranchIfEqualTest)
{
  cu.set_opcode(0b000100);  // beq (branch if equal)
  EXPECT_EQ(cu.get_branch(), true);
  EXPECT_EQ(cu.get_alu_op(), 0b001);
}

TEST_F(TestControlUnit, BranchIfNotEqualTest)
{
  cu.set_opcode(0b000101);  // bne (branch if not equal)
  EXPECT_EQ(cu.get_branch(), true);
  EXPECT_EQ(cu.get_alu_op(), 0b001);
}

TEST_F(TestControlUnit, JumpTest)
{
  cu.set_opcode(0b000010);  // j (jump)
  EXPECT_EQ(cu.get_jump(), true);
}