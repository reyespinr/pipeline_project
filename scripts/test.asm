# R-Type Instructions
add $1, $2, $3    # Adds contents of $2 and $3, result in $1
sub $4, $5, $6    # Subtracts $5 from $6, result in $4

# I-Type Instructions
addi $8, $9, 10   # Adds immediate value 10 to contents of $9, result in $8
lw   $10, 4($11)  # Load word from memory address in $11 + offset 4 into $10
sw   $12, 8($13)  # Store word in $12 to memory address in $13 + offset 8
beq  $14, $15, 16 # Branch to instruction 16 if $14 and $15 are equal

# J-Type Instruction
j 1024            # Jump to instruction at address 1024