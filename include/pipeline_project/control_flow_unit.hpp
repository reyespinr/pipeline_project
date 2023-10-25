#ifndef PIPELINE_PROJECT_CONTROL_FLOW_UNIT_HPP
#define PIPELINE_PROJECT_CONTROL_FLOW_UNIT_HPP

#include <cstdint>

class ControlFlowUnit
{
private:
  bool branch_taken;
  bool jump_taken;
  uint32_t target_address;

public:
  ControlFlowUnit() : branch_taken(false), jump_taken(false), target_address(0) {}

  // Set the branch condition based on ALU zero flag and branch signal
  auto setBranchCondition(bool alu_zero, bool branch_signal) -> void
  {
    // For a simple "branch if equal" scenario.
    branch_taken = alu_zero && branch_signal;
  }

  // Set the jump signal
  auto setJumpTaken(bool jump_signal) -> void { jump_taken = jump_signal; }

  // Set the target address for jumps and conditional branches
  auto setTargetAddress(uint32_t current_address, int16_t offset, uint32_t jump_target = 0) -> void
  {
    if (jump_taken) {
      // Directly set jump target for jumps
      target_address = jump_target;
    } else {
      // Convert the 16-bit offset to a 32-bit signed value first (to handle negative values correctly).
      // Then shift left by 2 bits and add to the current address for branches.
      target_address = current_address + (static_cast<int32_t>(offset) << 2);
    }
  }

  // Check if a branch should be taken or not
  auto shouldBranch() const -> bool { return branch_taken; }

  // Check if a jump should be taken
  auto shouldJump() const -> bool { return jump_taken; }

  // Get the target address to jump/branch to
  auto getTargetAddress() const -> uint32_t { return target_address; }

  // Reset for next instruction cycle
  auto reset() -> void
  {
    branch_taken = false;
    jump_taken = false;
    target_address = 0;
  }
};

#endif  // PIPELINE_PROJECT_CONTROL_FLOW_UNIT_HPP
