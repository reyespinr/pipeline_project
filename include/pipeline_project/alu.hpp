#ifndef PIPELINE_PROJECT_ALU_HPP
#define PIPELINE_PROJECT_ALU_HPP
#include <bitset>
#include <cmath>
#include <cstdint>
#include <iostream>  // Include for debugging output

#include "utils.hpp"

class ALU
{
private:
  uint32_t a;
  uint32_t b;
  std::bitset<4> alu_ctr;  // Change to 4-bit to match control unit's alu_op
  bool zero_flag;
  bool overflow_flag;
  bool carry_out_flag;
  float p;

public:
  ALU() : a(0), b(0), alu_ctr(0), zero_flag(false), overflow_flag(false), carry_out_flag(false) {}

  auto setInputs(uint32_t a_, uint32_t b_, std::bitset<4> alu_ctr_) -> void  // Change to 4-bit
  {
    a = a_;
    b = b_;
    alu_ctr = alu_ctr_;
  }

  auto setFloatInput(float p_, std::bitset<4> alu_ctr_) -> void
  {
    p = p_;
    alu_ctr = alu_ctr_;
  }

  auto performOperation() -> uint32_t
  {
    uint32_t result = 0;

    switch (alu_ctr.to_ulong()) {
      case 0b0010:  // ADD
        result = a + b;
        overflow_flag =
          ((a & 0x80000000) == (b & 0x80000000)) && ((result & 0x80000000) != (a & 0x80000000));
        carry_out_flag = result < a;
        break;
      case 0b0110:  // SUB
        result = a - b;
        overflow_flag =
          ((a & 0x80000000) != (b & 0x80000000)) && ((result & 0x80000000) != (a & 0x80000000));
        carry_out_flag = a < b;
        break;
      case 0b0000:  // AND
        result = a & b;
        break;
      case 0b0001:  // OR
        result = a | b;
        break;
      case 0b0011:       // XOR
        result = a ^ b;  // Use the XOR operator
        break;
      case 0b0100:  // NOR
        result = ~(a | b);
        break;
      case 0b0101:  // SLT (Set on Less Than)
        result = (static_cast<int32_t>(a) < static_cast<int32_t>(b)) ? 1 : 0;
        break;
      case 0b0111:  // SLL (Shift Left Logical)
        // Assuming b holds the shift amount, which should be masked since only the lower 5 bits are used
        result = a << b;
        break;
      case 0b1000:        // SRL (Shift Right Logical)
        result = a >> b;  // Shift by the value of b
        break;
      case 0b1001:        // SLA (Shift Left Arithmetic)
        result = a << b;  // Shift by the value of b
        break;
      case 0b1010:             // SRA (Shift Right Arithmetic)
        if (a & 0x80000000) {  // If MSB (sign bit) is 1, it's negative
          result = a >> b;
          result |= (1 << (32 - b));  // Set MSB to 1
        } else {
          result = a >> b;
        }
        break;
      case 0b1011:  // MULT (Multiplication)
        result = a * b;
        break;
      // If your system has SRL (Shift Right Logical) add the case here
      // Add other cases as needed for the instructions you're implementing
      default:
        result = 0;
        break;
    }

    zero_flag = (result == 0);
    return result;
  }

  auto performFloatOperation() -> float
  {
    float result = 0;
    switch (alu_ctr.to_ulong()) {
      case 0b1100:  // DIV (Division)
        result = float(a) / float(b);
        break;
      case 0b1101:  // SQR (Square Root)
        result = sqrt(p);
        break;
      case 0b1110:  // FISQR (Fast Inverse Square Root)
        result = q_rsqrt(p);
        break;
      default:
        result = 0;
        break;
    }
    zero_flag = (result == 0);
    return result;
  }

  auto isZero() const -> bool { return zero_flag; }
  auto hasOverflow() const -> bool { return overflow_flag; }
  auto hasCarryOut() const -> bool { return carry_out_flag; }
};

#endif  // PIPELINE_PROJECT_ALU_HPP
