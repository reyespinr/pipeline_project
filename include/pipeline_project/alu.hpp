#ifndef PROJECT_LIBRARY_ALU_HPP
#define PROJECT_LIBRARY_ALU_HPP
#include <bitset>
#include <cstdint>

class ALU32Bit
{
private:
  uint32_t a;
  uint32_t b;
  std::bitset<3> alu_ctr;
  bool zero_flag;
  bool overflow_flag;
  bool carry_out_flag;

public:
  ALU32Bit() : a(0), b(0), alu_ctr(0), zero_flag(false), overflow_flag(false), carry_out_flag(false)
  {
  }

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
        break;
      case 0b001:  // Subtraction
        result = a - b;
        break;
      case 0b010:  // Bitwise AND
        result = a & b;
        break;
      case 0b011:  // Bitwise OR
        result = a | b;
        break;
      case 0b100:  // Logical left shift
        result = a << b; // Shift by the value of b
        break;
      case 0b101:  // Logical right shift
        result = a >> b; // Shift by the value of b
        break;
      case 0b110:  // Arithmetic left shift (similar to logical left shift)
        result = a << b; // Shift by the value of b
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

    // Update flags
    zero_flag = (result == 0);
    overflow_flag =
      false;  // Simple check. More complicated operations will need a more robust check.
    carry_out_flag = false;  // Placeholder for now, need to handle in addition/subtraction.

    return result;
}

  auto isZero() const -> bool { return zero_flag; }
  auto hasOverflow() const -> bool { return overflow_flag; }
  auto hasCarryOut() const -> bool { return carry_out_flag; }
};

#endif  // PROJECT_LIBRARY_ALU_HPP
