.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    addi sp, sp, -8
    sw ra, 0(sp)
    sw s0, 4(sp)

    addi s0, a0, -1
    blt s0, x0, finish
    
loop:
    mul a0, a0, s0
    addi s0, s0, -1
    beq s0, x0, finish
    jal x0, loop
    
finish:
    lw ra, 0(sp)
    lw s0, 4(sp)
    addi sp, sp, 8
    jr ra