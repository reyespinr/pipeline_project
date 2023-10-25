#ifndef PIPELINE_PROJECT_DATAPATH_HPP
#define PIPELINE_PROJECT_DATAPATH_HPP

#include "alu.hpp"
#include "control_flow_unit.hpp"
#include "control_unit.hpp"
#include "immediate.hpp"
#include "memory.hpp"
#include "register_file.hpp"

class Datapath
{
private:
  ALU alu;
  ControlFlowUnit controlFlowUnit;
  ControlUnit controlUnit;
  Memory memory;
  RegisterFile registerFile;
  Immediate immediate;

  auto extractOpcode(uint32_t instruction) -> std::bitset<6>
  {
    // Extract and return the opcode from the instruction.
    return std::bitset<6>((instruction >> 26) & 0x3F);
  }

  auto extractImmediate(uint32_t instruction) -> std::bitset<16>
  {
    // Extract and return the immediate value from the instruction.
    return std::bitset<16>(instruction & 0xFFFF);
  }

public:
  Datapath()
  {
    // Initialization code, if needed
  }

  auto executeInstruction(uint32_t instruction) -> void
  {
    std::bitset<6> opcode = extractOpcode(instruction);

    controlUnit.set_opcode(opcode);  // Setting the opcode in the Control Unit

    // Based on control signals from controlUnit, decide the operations on other units

    if (controlUnit.get_mem_read() || controlUnit.get_mem_write()) {
      // Perform memory operations using the Memory component
    }

    if (controlUnit.get_reg_dst() || controlUnit.get_reg_write()) {
      // Perform operations on the Register File
    }

    if (controlUnit.get_jump() || controlUnit.get_branch()) {
      // For now, a placeholder logic
      controlFlowUnit.setTargetAddress(0x1000, 4);  // Placeholder logic; modify as needed
    }

    if (controlUnit.get_alu_src()) {
      std::bitset<16> imm_value = extractImmediate(instruction);
      immediate.setImmediate(imm_value);
      // Use immediate in ALU or other components as needed
    }

    // Use ALU based on the control signals
    // This is a basic example. Modify as per requirement.
    if (opcode == 0b100011 || opcode == 0b101011) {  // lw or sw
      alu.performOperation(/* inputs and ALU control signals for add operation */);
    } else if (opcode == 0b000100 || opcode == 0b000101) {  // beq or bne
      alu.performOperation(/* inputs and ALU control signals for subtraction operation */);
    }
    // ... and so on for other opcodes and control signals
  }

  // Add other helper functions or getters/setters to help in testing or manipulating the datapath state
};

#endif  // PIPELINE_PROJECT_DATAPATH_HPP
