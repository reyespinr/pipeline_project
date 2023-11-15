# Initialize registers
li $v0, 0x0040       # $v0 = 0040hex
li $v1, 0x1010       # $v1 = 1010hex
li $s2, 0x000F       # $s2 = 000Fhex
li $s3, 0x00F0       # $s3 = 00F0hex
li $t0, 0x0000       # $t0 = 0000hex
li $a0, 0x0010       # $a0 = 0010hex
li $a1, 0x0005       # $a1 = 0005hex

loop:                # While loop start
    bgtz $a1, loop_body  # Branch if $a1 > 0
    j end_loop           # Jump to end of loop if $a1 <= 0

loop_body:
    addi $a1, $a1, -1    # $a1 = $a1 - 1
    lw $t0, 0($a0)       # $t0 = Mem[$a0]

    # Check if $t0 > 0100hex
    li $t1, 0x0100
    ble $t0, $t1, else_block   # If $t0 <= 0x0100, jump to else block

    # If block
    srl $v0, $v0, 3      # $v0 = $v0 / 8
    or $v1, $v1, $v0     # $v1 = $v1 | $v0
    li $t2, 0xFF00
    sw $t2, 0($a0)       # Mem[$a0] = FF00hex
    j continue_loop

else_block:
    # Else block
    sll $s2, $s2, 2      # $s2 = $s2 * 4
    xor $s3, $s3, $s2    # $s3 = $s3 ^ $s2
    li $t2, 0x00FF
    sw $t2, 0($a0)       # Mem[$a0] = 00FFhex

continue_loop:
    addi $a0, $a0, 2     # $a0 = $a0 + 2
    j loop               # Jump back to the start of the loop

end_loop:
    # The return statement is usually a jump to the return address in MIPS,
    # but in this context, it's just the end of the program
    # jr $ra             # Normally, return to the calling function
