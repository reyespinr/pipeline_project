#include <bitset>
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
    // Implementation for I-Type instructions
  }

  void executeJType(const std::string & instruction)
  {
    // Implementation for J-Type instructions
  }
};
