.globl relu exit2

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 57
# ==============================================================================
relu:
    # Prologue
    bgt a1, zero, loop_start
    li a1, 57
    call exit2
loop_start:
    beq a1, zero, loop_end
    addi a1, a1, -1
    slli t0, a1, 2
    add t0, a0, t0
    lw t1, 0(t0)
    bge t1, zero, loop_continue
    sw zero, 0(t0)
loop_continue:
    jal x0, loop_start
loop_end:
    # Epilogue
	ret
