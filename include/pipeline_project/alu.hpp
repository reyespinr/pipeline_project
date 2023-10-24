#ifndef PIPELINE_PROJECT_ALU_HPP
#define PIPELINE_PROJECT_ALU_HPP
#include <bitset>
#include <cstdint>

class ALU
{
private:
  uint32_t a;
  uint32_t b;
  std::bitset<3> alu_ctr;
  bool zero_flag;
  bool overflow_flag;
  bool carry_out_flag;

public:
  ALU() : a(0), b(0), alu_ctr(0), zero_flag(false), overflow_flag(false), carry_out_flag(false) {}

  auto setInputs(uint32_t a_, uint32_t b_, std::bitset<3> alu_ctr_) -> void
  {
    a = a_;
    b = b_;
    alu_ctr = alu_ctr_;
  }

  auto performOperation() -> uint32_t
  {
    uint32_t result = 0;
    switch (alu_ctr.to_ulong()) {
      case 0b000:  // Addition
        result = a + b;
        // Overflow check for addition
        overflow_flag =
          ((a & 0x80000000) == (b & 0x80000000)) && ((result & 0x80000000) != (a & 0x80000000));
        carry_out_flag = result < a;
        break;
      case 0b001:  // Subtraction
        result = a - b;
        // Overflow check for subtraction
        overflow_flag =
          ((a & 0x80000000) != (b & 0x80000000)) && ((result & 0x80000000) == (b & 0x80000000));
        carry_out_flag = a < b;
        break;
      case 0b010:  // Bitwise AND
        result = a & b;
        break;
      case 0b011:  // Bitwise OR
        result = a | b;
        break;
      case 0b100:         // Logical left shift
        result = a << b;  // Shift by the value of b
        break;
      case 0b101:         // Logical right shift
        result = a >> b;  // Shift by the value of b
        break;
      case 0b110:         // Arithmetic left shift (similar to logical left shift)
        result = a << b;  // Shift by the value of b
        break;
      case 0b111:              // Arithmetic right shift
        if (a & 0x80000000) {  // If MSB (sign bit) is 1, it's negative
          result = a >> b;
          result |= (1 << (32 - b));  // Set MSB to 1
        } else {
          result = a >> b;
        }
        break;
      default:
        result = 0;
        break;
    }

    // Update the zero flag
    zero_flag = (result == 0);
    return result;
  }

  auto isZero() const -> bool { return zero_flag; }
  auto hasOverflow() const -> bool { return overflow_flag; }
  auto hasCarryOut() const -> bool { return carry_out_flag; }
};

#endif  // PIPELINE_PROJECT_ALU_HPP
