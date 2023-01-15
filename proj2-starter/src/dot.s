.globl dot exit2

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 57
# - If the stride of either vector is less than 1,
#   this function terminates the program with error code 58
# =======================================================
dot:
    # Prologue
    ble a2, zero, err57
    ble a3, zero, err58
    ble a4, zero, err58
    mv t0, x0 # index of v0
    mv t1, x0 # index of v1
    mv t2, x0 # result
loop_start:
    beq a2, zero, loop_end
    slli t3, t0, 2
    add t3, a0, t3
    lw t3, 0(t3)
    slli t4, t1, 2
    add t4, a1, t4
    lw t4, 0(t4)
    mul t3, t3, t4
    add t2, t2, t3
    add t0, t0, a3
    add t1, t1, a4
    addi a2, a2, -1
    jal x0, loop_start
loop_end:
    # Epilogue
    mv a0, t2
    ret
err57:
    li a1, 57
    call exit2
err58:
    li a1, 58
    call exit2