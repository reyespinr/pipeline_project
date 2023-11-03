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
  cu.set_opcode(0b000011);  // j (jump)
  EXPECT_EQ(cu.get_jump(), true);
}

// Additional tests for R-type instructions
TEST_F(TestControlUnit, AddTest)
{
  cu.set_opcode(0b000000);  // R-type
  cu.set_funct(0b100000);   // add
  EXPECT_EQ(cu.get_reg_dst(), true);
  EXPECT_EQ(cu.get_reg_write(), true);
  EXPECT_EQ(cu.get_alu_op(), 0b000);
}

TEST_F(TestControlUnit, SubTest)
{
  cu.set_opcode(0b000000);  // R-type
  cu.set_funct(0b100010);   // sub
  EXPECT_EQ(cu.get_reg_dst(), true);
  EXPECT_EQ(cu.get_reg_write(), true);
  EXPECT_EQ(cu.get_alu_op(), 0b001);
}

TEST_F(TestControlUnit, SltTest)
{
  cu.set_opcode(0b000000);  // R-type
  cu.set_funct(0b101010);   // slt
  EXPECT_EQ(cu.get_reg_dst(), true);
  EXPECT_EQ(cu.get_reg_write(), true);
  EXPECT_EQ(cu.get_alu_op(), 0b010);
}

TEST_F(TestControlUnit, AndTest)
{
  cu.set_opcode(0b000000);  // R-type instructions have opcode 0
  cu.set_funct(0x24);       // funct code for AND
  EXPECT_EQ(cu.get_reg_dst(), true);
  EXPECT_EQ(cu.get_reg_write(), true);
  EXPECT_EQ(cu.get_alu_op(), 0b010);  // Assume 0b010 is the ALU code for AND
}

TEST_F(TestControlUnit, OrTest)
{
  cu.set_opcode(0b000000);  // R-type
  cu.set_funct(0x25);       // funct code for OR
  EXPECT_EQ(cu.get_reg_dst(), true);
  EXPECT_EQ(cu.get_reg_write(), true);
  EXPECT_EQ(cu.get_alu_op(), 0b011);  // Assume 0b011 is the ALU code for OR
}

TEST_F(TestControlUnit, XorTest)
{
  cu.set_opcode(0b000000);  // R-type
  cu.set_funct(0x26);       // funct code for XOR
  EXPECT_EQ(cu.get_reg_dst(), true);
  EXPECT_EQ(cu.get_reg_write(), true);
  EXPECT_EQ(cu.get_alu_op(), 0b100);  // Assume 0b100 is the ALU code for XOR
}

TEST_F(TestControlUnit, NorTest)
{
  cu.set_opcode(0b000000);  // R-type
  cu.set_funct(0x27);       // funct code for NOR
  EXPECT_EQ(cu.get_reg_dst(), true);
  EXPECT_EQ(cu.get_reg_write(), true);
  EXPECT_EQ(cu.get_alu_op(), 0b101);  // Assume 0b101 is the ALU code for NOR
}