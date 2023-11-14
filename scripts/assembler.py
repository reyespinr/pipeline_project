from instruction_parser import InstructionParser


class Assembler:
    def __init__(self, input_file, output_file):
        self.input_file = input_file
        self.output_file = output_file
        self.parser = InstructionParser()

    def Assemble(self):
        with open(self.input_file, 'r') as file:
            lines = file.readlines()

        machine_code = []

        for line in lines:
            line = line.strip()
            # Assuming '#' is for comments
            if line and not line.startswith('#'):
                binary_instruction = self.parser.convert(line)
                if binary_instruction:
                    machine_code.append(binary_instruction)

        with open(self.output_file, 'w') as file:
            for code in machine_code:
                # Write the binary string to file
                file.write(code + '\n')


if __name__ == "__main__":
    input_file = 'r_type_test.asm'
    output_file = 'r_type_test_input.txt'

    assembler = Assembler(input_file, output_file)
    assembler.Assemble()
