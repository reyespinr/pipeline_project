import re


class InstructionParser:
    def __init__(self):
        # R-Type instructions
        self.RTypePattern = re.compile(
            r'(\w+)\s+\$(\d+),\s*\$(\d+),\s*\$(\d+)')
        # I-Type instructions (general format)
        self.ITypePattern = re.compile(
            r'(\w+)\s+\$(\d+),\s*(?:\$(\d+),\s*)?(-?\d+)(?:\(\$?(\d+)\))?')
        # J-Type instructions
        self.JTypePattern = re.compile(r'(\w+)\s+(\d+)')

        # Define opcode and function code mappings
        self.opcodeMap = {
            'add': '000000', 'sub': '000000', 'addi': '001000',
            'lw': '100011', 'sw': '101011', 'beq': '000100', 'j': '000010'
        }
        self.functMap = {
            'add': '100000', 'sub': '100010'
        }

    def convert(self, instr):
        # Check for R-type
        if self.RTypePattern.match(instr):
            return self.convertRType(instr)
        # Check for I-type
        elif self.ITypePattern.match(instr):
            return self.convertIType(instr)
        # Check for J-type
        elif self.JTypePattern.match(instr):
            return self.convertJType(instr)
        else:
            raise ValueError(f"Invalid instruction format: {instr}")

    def convertRType(self, instr):
        match = self.RTypePattern.match(instr)
        opcode = '000000'  # For R-type instructions, opcode is always '000000'
        rs = format(int(match.group(3)), '05b')  # Source register
        rt = format(int(match.group(4)), '05b')  # Target register
        rd = format(int(match.group(2)), '05b')  # Destination register
        shamt = '00000'  # Shift amount is zero for basic ADD and SUB instructions
        funct = self.functMap[match.group(1)]
        return opcode + rs + rt + rd + shamt + funct

    def convertIType(self, instr):
        match = self.ITypePattern.match(instr)
        if not match:
            raise ValueError(f"Invalid I-type instruction format: {instr}")

        opcode = self.opcodeMap[match.group(1)]
        rt = format(int(match.group(2)), '05b')

        # Check for immediate type instructions like addi, andi, ori
        if match.group(3) is not None:
            rs = format(int(match.group(3)), '05b')
        else:
            rs = '00000'  # Use '0' as the default for source register if not present

        # Immediate value handling
        immediate = format(int(match.group(4)) & 0xFFFF, '016b')

        return opcode + rs + rt + immediate

    def convertJType(self, instr):
        match = self.JTypePattern.match(instr)
        opcode = self.opcodeMap[match.group(1)]
        # Address is converted to a 26-bit binary
        address = format(int(match.group(2)) & 0x3FFFFFF, '026b')
        return opcode + address
