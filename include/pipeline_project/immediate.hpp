#ifndef PIPELINE_PROJECT_IMMEDIATE_HPP
#define PIPELINE_PROJECT_IMMEDIATE_HPP

#include <cstdint>

class Immediate
{
public:
  // Default constructor
  Immediate() = default;

  // Sign-extend a 16-bit immediate value to 32-bit
  auto signExtend(std::uint16_t immediate) const -> std::int32_t
  {
    // Check the sign bit (15th bit) of the immediate
    if (immediate & 0x8000) {
      return static_cast<std::int32_t>(immediate | 0xFFFF0000);
    } else {
      return static_cast<std::int32_t>(immediate);
    }
  }

  // For instructions like 'lui', the 16-bit immediate is placed in the upper half
  auto placeImmediateUpper(std::uint16_t immediate) const -> std::uint32_t
  {
    return static_cast<std::uint32_t>(immediate) << 16;
  }

  // If other types of immediate handling become necessary, we can add more methods here.
};

#endif  // PIPELINE_PROJECT_IMMEDIATE_HPP
