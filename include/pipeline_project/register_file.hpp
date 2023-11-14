#ifndef PIPELINE_PROJECT_REGISTER_FILE_HPP
#define PIPELINE_PROJECT_REGISTER_FILE_HPP
#include <cstdint>
#include <vector>

class RegisterFile
{
private:
  std::vector<std::uint32_t> registers;

public:
  // Constructor: Initializes the register file with default values.
  RegisterFile() : registers(32, 0) {}

  // Reads the value from a specified register.
  auto read(std::uint8_t register_number) const -> std::uint32_t
  {
    if (register_number >= 32) {
      throw std::out_of_range("Register number out of bounds.");
    }

    // MIPS convention: Register 0 is always 0.
    if (register_number == 0) {
      return 0;
    }

    return registers[register_number];
  }

  // Writes a value to a specified register.
  auto write(std::uint8_t register_number, std::uint32_t value) -> void
  {
    if (register_number >= 32) {
      throw std::out_of_range("Register number out of bounds.");
    }

    // MIPS convention: Register 0 is always 0 and cannot be written to.
    if (register_number != 0) {
      registers[register_number] = value;
    }
  }

  void printRegisterState() const
  {
    std::cout << "Register File State:" << std::endl;
    for (size_t i = 0; i < registers.size(); ++i) {
      std::cout << "R" << i << ": " << registers[i] << std::endl;
    }
  }

  void reset() { std::fill(registers.begin(), registers.end(), 0); }
};

#endif  // PIPELINE_PROJECT_REGISTER_FILE_HPP
