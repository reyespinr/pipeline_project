#include <bitset>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "alu.hpp"
#include "control_flow_unit.hpp"
#include "control_unit.hpp"
#include "immediate.hpp"
#include "memory.hpp"
#include "register_file.hpp"

class MipsSimulator
{
public:
  MipsSimulator(const std::string & inputFilePath) : inputFilePath(inputFilePath)
  {
    readFile(inputFilePath);
  }

  void reset()
  {
    registerFile.reset();     // Reset the register file
    machineCode.clear();      // Clear the existing machine code
    readFile(inputFilePath);  // Re-read the input file
  }

  void execute()
  {
    // Initialize components if needed
    // ...

    for (const auto & instruction : machineCode) {
      //   std::cout << "Executing instruction: " << instruction << std::endl;

      decodeAndExecute(instruction);
      // Update the state of the simulator (registers, memory, etc.)
    }

    // Optionally: Print the final state of registers, memory, etc.
  }

  void executeLine(int n)
  {
    decodeAndExecute(machineCode[n]);

    // Optionally: Print the final state of registers, memory, etc.
  }

  RegisterFile & getRegisterFile() { return registerFile; }

private:
  std::string inputFilePath;
  std::vector<std::string> machineCode;
  ControlUnit controlUnit;
  ALU alu;
  RegisterFile registerFile;

  void readFile(const std::string & filePath)
  {
    // std::cout << "Full path: " << std::filesystem::absolute(filePath) << std::endl;

    std::ifstream file(filePath);
    if (!file) {
      std::cerr << "Error opening file: " << filePath << std::endl;
      return;
    }

    std::string line;
    while (std::getline(file, line)) {
      if (!line.empty()) {
        machineCode.push_back(line);
        // std::cout << "Reading line: " << line << std::endl;
      }
    }
  }

  void decodeAndExecute(const std::string & instruction)
  {
    std::string opcode = instruction.substr(0, 6);

    if (opcode == "000000") {  // R-Type
      executeRType(instruction);
    } else if (opcode == "000010" || opcode == "000011") {  // J-Type
      executeJType(instruction);
    } else {  // I-Type
      executeIType(instruction);
    }
  }

  void executeRType(const std::string & instruction)
  {
    // std::cout << "Executing R-Type instruction: " << instruction << std::endl;

    // Extracting the fields from the instruction
    std::uint8_t rs = static_cast<std::uint8_t>(std::stoi(instruction.substr(6, 5), nullptr, 2));
    std::uint8_t rt = static_cast<std::uint8_t>(std::stoi(instruction.substr(11, 5), nullptr, 2));
    std::uint8_t rd = static_cast<std::uint8_t>(std::stoi(instruction.substr(16, 5), nullptr, 2));
    std::uint8_t shamt =
      static_cast<std::uint8_t>(std::stoi(instruction.substr(21, 5), nullptr, 2));
    std::bitset<6> funct(std::stoi(instruction.substr(26, 6), nullptr, 2));

    controlUnit.set_funct(funct);
    controlUnit.decode_funct();

    // For shift operations, use shamt as the second operand.
    std::uint32_t operand1 =
      controlUnit.get_alu_src() ? registerFile.read(rt) : registerFile.read(rs);
    std::uint32_t operand2 = controlUnit.get_alu_src() ? shamt : registerFile.read(rt);

    alu.setInputs(operand1, operand2, controlUnit.get_alu_op());
    // std::cout << "Going into the ALU: |" << operand1 << " | " << operand2 << " | "
    //           << controlUnit.get_alu_op() << "\n";
    std::uint32_t result = alu.performOperation();

    if (controlUnit.get_reg_write()) {
      registerFile.write(rd, result);
    }
  }

  void executeIType(const std::string & instruction)
  {
    // Extract the fields from the instruction
    std::uint8_t rs = static_cast<std::uint8_t>(std::stoi(instruction.substr(6, 5), nullptr, 2));
    std::uint8_t rt = static_cast<std::uint8_t>(std::stoi(instruction.substr(11, 5), nullptr, 2));
    std::int16_t immediate = static_cast<std::int16_t>(
      std::stoi(instruction.substr(16, 16), nullptr, 2));  // Sign-extended

    // Decode the opcode and set control signals
    std::bitset<6> opcode(std::stoi(instruction.substr(0, 6), nullptr, 2));
    controlUnit.set_opcode(opcode);

    // Perform operations based on the opcode
    // For example, if it's a load word (lw) instruction:
    if (controlUnit.get_mem_read()) {
      // Calculate the address
      std::uint32_t address = registerFile.read(rs) + immediate;
      // Perform memory read operation and write the result to the target register
      // std::uint32_t data = memory.read(address);
      // registerFile.write(rt, data);
    }
    // Similarly, handle other I-type instructions like addi, beq, bne, etc.
  }

  void executeJType(const std::string & instruction)
  {
    // Extract the address field from the instruction
    std::uint32_t address =
      static_cast<std::uint32_t>(std::stoi(instruction.substr(6, 26), nullptr, 2));

    // Decode the opcode
    std::bitset<6> opcode(std::stoi(instruction.substr(0, 6), nullptr, 2));
    controlUnit.set_opcode(opcode);

    // Perform jump
    if (controlUnit.get_jump()) {
      // Update the program counter (PC) to the target address
      // This is typically done by setting the lower 28 bits of the PC
      // and keeping the upper 4 bits unchanged
      // pc = (pc & 0xF0000000) | (address << 2);
    }
    // If it's a jal (jump and link) instruction, also save the return address
    // if (opcode == "000011") {
    // The return address is typically PC + 4, saved in $ra ($31)
    // registerFile.write(31, pc + 4);
    // }
  }
};
