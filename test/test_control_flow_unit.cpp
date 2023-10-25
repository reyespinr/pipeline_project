#include <gtest/gtest.h>

#include <pipeline_project/control_flow_unit.hpp>

class ControlFlowUnitTest : public ::testing::Test
{
protected:
  ControlFlowUnit cfu;

  void SetUp() override { cfu.reset(); }
};

TEST_F(ControlFlowUnitTest, BranchConditionTest)
{
  cfu.setBranchCondition(true, true);
  EXPECT_TRUE(cfu.shouldBranch());

  cfu.setBranchCondition(false, true);
  EXPECT_FALSE(cfu.shouldBranch());

  cfu.setBranchCondition(true, false);
  EXPECT_FALSE(cfu.shouldBranch());
}

TEST_F(ControlFlowUnitTest, TargetAddressTest)
{
  cfu.setTargetAddress(0x1000, 4);
  EXPECT_EQ(cfu.getTargetAddress(), 0x1010);

  cfu.setTargetAddress(0x2000, -4);
  EXPECT_EQ(cfu.getTargetAddress(), 0x1FF0);
}

TEST_F(ControlFlowUnitTest, JumpTest)
{
  cfu.setJumpTaken(true);
  cfu.setTargetAddress(0x3000, 0, 0x4000);  // Setting jump target to 0x4000
  EXPECT_TRUE(cfu.shouldJump());
  EXPECT_EQ(cfu.getTargetAddress(), 0x4000);

  cfu.setJumpTaken(false);
  EXPECT_FALSE(cfu.shouldJump());
}

TEST_F(ControlFlowUnitTest, ResetTest)
{
  cfu.setBranchCondition(true, true);
  cfu.setTargetAddress(0x1000, 4);
  cfu.reset();
  EXPECT_FALSE(cfu.shouldBranch());
  EXPECT_EQ(cfu.getTargetAddress(), 0);
}
