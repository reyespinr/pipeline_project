#ifndef PIPELINE_PROJECT_CONTROL_UNIT_HPP
#define PIPELINE_PROJECT_CONTROL_UNIT_HPP

#include <bitset>
#include <cstdint>

class ControlUnit
{
private:
  std::bitset<6> opcode;
  std::bitset<6> funct;  // Added for R-type instruction decoding

  bool reg_dst;
  bool branch;
  bool jump;
  bool mem_read;
  bool mem_write;
  bool reg_write;
  bool mem_to_reg;
  bool alu_src;
  std::bitset<4> alu_op;

public:
  ControlUnit()
  : opcode(0),
    funct(0),  // Initialization for funct
    reg_dst(false),
    branch(false),
    jump(false),
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

  auto set_funct(std::bitset<6> funct_) -> void
  {
    funct = funct_;
    decode_funct();
  }

  // Getters...
  auto get_reg_dst() const -> bool { return reg_dst; }
  auto get_branch() const -> bool { return branch; }
  auto get_jump() const -> bool { return jump; }
  auto get_mem_read() const -> bool { return mem_read; }
  auto get_mem_write() const -> bool { return mem_write; }
  auto get_reg_write() const -> bool { return reg_write; }
  auto get_mem_to_reg() const -> bool { return mem_to_reg; }
  auto get_alu_src() const -> bool { return alu_src; }
  auto get_alu_op() const -> std::bitset<4> { return alu_op; }

  auto decode_opcode() -> void
  {
    // Resetting control signals
    reg_dst = false;
    branch = false;
    jump = false;
    mem_read = false;
    mem_write = false;
    reg_write = false;
    mem_to_reg = false;
    alu_src = false;
    alu_op = 0b0000;

    switch (opcode.to_ulong()) {
      case 0x23:  // lw
        mem_read = true;
        reg_write = true;
        mem_to_reg = true;
        alu_src = true;
        alu_op = 0b000;
        break;

      case 0x2B:  // sw
        mem_write = true;
        alu_src = true;
        alu_op = 0b000;
        break;

      case 0x04:  // beq
        branch = true;
        alu_op = 0b001;
        break;

      case 0x05:  // bne
        branch = true;
        alu_op = 0b001;
        break;

      case 0x03:  // j or jal
        jump = true;
        // Further differentiation based on funct may be needed
        break;

      case 0x00:  // This is the R-type instructions' opcode
        decode_funct();
        break;

      default:
        // NOP or some default action
        break;
    }
  }

  auto decode_funct() -> void
  {
    switch (funct.to_ulong()) {
      case 0x20:  // add
        reg_dst = true;
        reg_write = true;
        alu_op = 0b0010;  // Unique code for ADD
        break;

      case 0x22:  // sub
        reg_dst = true;
        reg_write = true;
        alu_op = 0b0110;  // Unique code for SUB
        break;

      case 0x24:  // and
        reg_dst = true;
        reg_write = true;
        alu_op = 0b0000;  // Unique code for AND
        break;

      case 0x25:  // or
        reg_dst = true;
        reg_write = true;
        alu_op = 0b0001;  // Unique code for OR
        break;

      case 0x26:  // xor
        reg_dst = true;
        reg_write = true;
        alu_op = 0b0011;  // Unique code for XOR
        break;

      case 0x27:  // nor
        reg_dst = true;
        reg_write = true;
        alu_op = 0b0100;  // Unique code for NOR
        break;

      case 0x2A:  // slt
        reg_dst = true;
        reg_write = true;
        alu_op = 0b0101;  // Unique code for SLT
        break;

      case 0x00:  // sll
        reg_dst = true;
        reg_write = true;
        alu_src = true;
        alu_op = 0b0111;  // Unique code for SLL
        break;

      case 0x02:  // srl (shift right logical)
        reg_dst = true;
        reg_write = true;
        alu_src = true;
        alu_op = 0b1000;  // Unique code for SRL
        break;

      case 0x03:  // sra (shift right arithmetic)
        reg_dst = true;
        reg_write = true;
        alu_src = true;
        alu_op = 0b1010;  // New unique code for SRA (assuming 4-bit alu_op)
        break;

      case 0x04:  // sla (shift left arithmetic)
        reg_dst = true;
        reg_write = true;
        alu_src = true;
        alu_op = 0b1001;  // New unique code for SRA (assuming 4-bit alu_op)
        break;
      default:
        // NOP or some default action
        break;
    }
    // std::cout << "Decoded funct: " << funct << std::endl;
    // std::cout << "ALU Operation: " << alu_op << ", reg_write: " << reg_write << std::endl;
  }
};

#endif  // PIPELINE_PROJECT_CONTROL_UNIT_HPP
