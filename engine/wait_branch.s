    .syntax unified
    .arm
    .text
    .align 2
    .macro wait_branch name, budget, original, flags
    .global \name
    .type \name, %function
\name:
    ldr r0, =astraWaitPc
    ldr r0, [r0]
    cmp r4, r0
    bne \original
    and r0, r9, #0xf0000000
    cmp r0, #\flags
    bne \original
    mov r0, r7
    mov r1, r5
    bl \budget
    mov r5, r0
    b \original
    .size \name, .-\name
    .endm
    wait_branch AstraTaskBranch, astraTaskBudget, AstraCycloneDbra, 0
    wait_branch Astra1944Branch, astra1944Budget, AstraCycloneBeq, 0x40000000
    .section .note.GNU-stack,"",%progbits
