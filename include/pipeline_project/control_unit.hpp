#ifndef PIPELINE_PROJECT_CONTROL_UNIT_HPP
#define PIPELINE_PROJECT_CONTROL_UNIT_HPP

#include <bitset>
#include <cstdint>

class ControlUnit
{
private:
  std::bitset<6> opcode;

  bool reg_dst;
  bool branch;
  bool jump;
  bool mem_read;
  bool mem_write;
  bool reg_write;
  bool mem_to_reg;
  bool alu_src;
  std::bitset<3> alu_op;

public:
  ControlUnit()
  : opcode(0),
    reg_dst(false),
    branch(false),
    jump(false),  // added for jump signal
    mem_read(false),
    mem_write(false),
    reg_write(false),
    mem_to_reg(false),
    alu_src(false),
    alu_op(0b000)
  {
  }

  auto set_opcode(std::bitset<6> opcode_) -> void
  {
    opcode = opcode_;
    decode_opcode();
  }

  // Getters...
  auto get_reg_dst() const -> bool { return reg_dst; }
  auto get_branch() const -> bool { return branch; }
  auto get_jump() const -> bool { return jump; }  // added for jump signal
  auto get_mem_read() const -> bool { return mem_read; }
  auto get_mem_write() const -> bool { return mem_write; }
  auto get_reg_write() const -> bool { return reg_write; }
  auto get_mem_to_reg() const -> bool { return mem_to_reg; }
  auto get_alu_src() const -> bool { return alu_src; }
  auto get_alu_op() const -> std::bitset<3> { return alu_op; }

  auto decode_opcode() -> void
  {
    // Resetting control signals
    reg_dst = false;
    branch = false;
    jump = false;  // added for jump reset
    mem_read = false;
    mem_write = false;
    reg_write = false;
    mem_to_reg = false;
    alu_src = false;
    alu_op = 0b000;

    switch (opcode.to_ulong()) {
      case 0b100011:  // lw (load word)
        mem_read = true;
        reg_write = true;
        mem_to_reg = true;
        alu_src = true;
        alu_op = 0b000;  // Addition operation for address calculation
        break;

      case 0b101011:  // sw (store word)
        mem_write = true;
        alu_src = true;
        alu_op = 0b000;  // Addition operation for address calculation
        break;

      case 0b000100:  // beq (branch if equal)
        branch = true;
        alu_op = 0b001;  // Subtraction to compare operands
        break;

      case 0b000101:  // bne (branch if not equal)
        branch = true;
        alu_op = 0b001;  // Subtraction to compare operands
        break;

      case 0b000010:  // j (jump)
        jump = true;
        break;

        // ... Add more opcodes as needed

      default:
        // NOP or some default action
        break;
    }
  }
};

#endif  // PIPELINE_PROJECT_CONTROL_UNIT_HPP
