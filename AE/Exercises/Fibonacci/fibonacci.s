    .text
    .global main

main: mov r0, #5
      mov r1, #0
      mov r2, #1
      mov r3, #0
      cmp r0, #0
      moveq pc, lr
      cmp r0, #1
      moveq r3, #1
      moveq pc, lr
while: cmp r0, #1
       movle pc, lr
       add r3, r2, r1
       mov r1, r2
       mov r2, r3
       sub r0, r0, #1
       b while