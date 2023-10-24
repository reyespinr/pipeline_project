#ifndef PIPELINE_PROJECT_MEMORY_HPP
#define PIPELINE_PROJECT_MEMORY_HPP
#include <cstdint>
#include <vector>

const auto DEFAULT_MEMORY_SIZE = 1024;

class Memory
{
public:
  // Constructor initializing the memory with a specified size.
  explicit Memory(std::size_t size = DEFAULT_MEMORY_SIZE) : memory_array(size, 0xDEADBEEF) {}

  auto reset() -> void { std::fill(memory_array.begin(), memory_array.end(), 0xDEADBEEF); }

  // Writes a word (32-bit value) to the specified address.
  auto writeWord(std::uint32_t address, std::uint32_t value) -> void
  {
    if (address % 4 != 0) {
      throw std::runtime_error("Misaligned word write attempt.");
    }

    if (address / 4 < memory_array.size()) {
      memory_array[address / 4] = value;
    } else {
      throw std::out_of_range("Address out of bounds in writeWord.");
    }
  }

  // Reads a word (32-bit value) from the specified address.
  auto readWord(std::uint32_t address) const -> std::uint32_t
  {
    if (address % 4 != 0) {
      throw std::runtime_error("Misaligned word read attempt.");
    }

    if (address / 4 < memory_array.size()) {
      return memory_array[address / 4];
    } else {
      throw std::out_of_range("Address out of bounds in readWord.");
    }
    return 0;  // Default return for now.
  }

  // Writes a half word (16-bit value) to the specified address.
  auto writeHalfWord(std::uint32_t address, std::uint16_t value) -> void
  {
    if (address % 2 != 0) {
      throw std::runtime_error("Misaligned half-word write attempt.");
    }
    if (address < memory_array.size() * 4) {
      std::uint32_t word = memory_array[address / 4];
      if (address % 4 == 0) {
        word = (word & 0xFFFF0000) | value;  // Lower half-word in little endian
      } else if (address % 4 == 2) {
        word = (word & 0x0000FFFF) |
               (static_cast<std::uint32_t>(value) << 16);  // Upper half-word in little endian
      }
      memory_array[address / 4] = word;
    }
  }

  auto readHalfWord(std::uint32_t address) const -> std::uint16_t
  {
    if (address % 2 != 0) {
      throw std::runtime_error("Misaligned half-word read attempt.");
    }
    if (address < memory_array.size() * 4) {
      std::uint32_t word = memory_array[address / 4];
      if (address % 4 == 0) {
        return static_cast<std::uint16_t>(word & 0x0000FFFF);
      } else if (address % 4 == 2) {
        return static_cast<std::uint16_t>((word & 0xFFFF0000) >> 16);
      } else {
        throw std::out_of_range("Address out of bounds in readHalfWord.");
      }
    }
    return 0;
  }

  auto writeByte(std::uint32_t address, std::uint8_t value) -> void
  {
    if (address / 4 < memory_array.size()) {
      std::uint32_t word = memory_array[address / 4];
      switch (address % 4) {
        case 0:
          word = (word & 0xFFFFFF00) | value;
          break;
        case 1:
          word = (word & 0xFFFF00FF) | (static_cast<std::uint32_t>(value) << 8);
          break;
        case 2:
          word = (word & 0xFF00FFFF) | (static_cast<std::uint32_t>(value) << 16);
          break;
        case 3:
          word = (word & 0x00FFFFFF) | (static_cast<std::uint32_t>(value) << 24);
          break;
      }
      memory_array[address / 4] = word;
    } else {
      throw std::out_of_range("Address out of bounds in writeByte.");
    }
  }

  // Reads a byte (8-bit value) from the specified address.
  auto readByte(std::uint32_t address) const -> std::uint8_t
  {
    if (address / 4 < memory_array.size()) {
      std::uint32_t word = memory_array[address / 4];
      switch (address % 4) {
        case 0:
          return static_cast<std::uint8_t>(word & 0x000000FF);
        case 1:
          return static_cast<std::uint8_t>((word & 0x0000FF00) >> 8);
        case 2:
          return static_cast<std::uint8_t>((word & 0x00FF0000) >> 16);
        case 3:
          return static_cast<std::uint8_t>((word & 0xFF000000) >> 24);
      }

    } else {
      throw std::out_of_range("Address out of bounds in readByte.");
    }

    return 0;
  }

  // Return size of the memory array
  auto size() -> int { return memory_array.size(); }

private:
  std::vector<std::uint32_t> memory_array;
};

#endif  // PIPELINE_PROJECT_MEMORY_HPP
