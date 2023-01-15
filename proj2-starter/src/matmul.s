.globl matmul dot exit2

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 59
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 59
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 59
# =======================================================
matmul:
    # Error checks
    ble a1, zero, err59
    ble a2, zero, err59
    ble a4, zero, err59
    ble a5, zero, err59
    bne a2, a4, err59

    # Prologue
    addi sp, sp, -12
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)

    mv s0, x0 # i
outer_loop_start:
    mv s1, x0 # j
inner_loop_start:
    addi sp, sp, -28
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    sw a5, 20(sp)
    sw a6, 24(sp)

    slli t0, s0, 2
    mul t0, t0, a2
    add t0, t0, a0
    slli t1, s1, 2
    add t1, t1, a3
    mv a0, t0
    mv a1, t1
    li a3, 1
    mv a4, a5
    jal ra, dot
    mv t1, a0

    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 12(sp)
    lw a4, 16(sp)
    lw a5, 20(sp)
    lw a6, 24(sp)
    addi sp, sp, 28

    mul t0, s0, a5
    add t0, t0, s1
    slli t0, t0, 2
    add t0, t0, a6
    sw t1, 0(t0)

    addi s1, s1, 1
    beq s1, a5, inner_loop_end
    jal x0, inner_loop_start
inner_loop_end:
    addi s0, s0, 1
    beq s0, a1, outer_loop_end
    jal x0, outer_loop_start
outer_loop_end:
    # Epilogue
    lw s1, 8(sp)
    lw s0, 4(sp)
    lw ra, 0(sp)
    addi sp, sp, 12

    ret
err59:
    li a1, 59
    call exit2