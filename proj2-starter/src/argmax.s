.globl argmax exit2

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 57
# =================================================================
argmax:
    # Prologue
    mv t0, x0 # max
    mv t2, x0
    bgt a1, zero, loop_start
    li a1, 57
    call exit2
loop_start:
    beq a1, zero, loop_end
    addi a1, a1, -1
    slli t1, a1, 2
    add t1, a0, t1
    lw t1, 0(t1)
    blt t1, t0, loop_continue
    mv t0, t1
    mv t2, a1
loop_continue:
    jal x0, loop_start
loop_end:
    # Epilogue
    mv a0, t2
    ret
