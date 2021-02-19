      .data
v:    .word 1, 2, 3, 4, 5, 6, 7, 8
w:    .word 8, 7, 6, 5, 4, 3, 2, 1
fmt:  .string "%d\n"

      .text
      .global main

main: ldr r0, =v
      mov r1, #8
      mov r2, #4
      bl mult
      ldr r0, =v
      mov r1, #8
      bl print_vec
      mov r7, #1
      svc 0

mult: cmp r1, #0
      movle pc, lr
      ldr r3, [r0]
      mul r3, r3, r2
      str r3, [r0], #4
      sub r1, r1, #1
      b mult

print_vec:  push {r4, r5, lr}
            mov r4, r0
            mov r5, r1
while:      cmp r5, #0
            pople {r4, r5, pc}
            ldr r0, =fmt
            ldr r1, [r4], #4
            bl printf
            sub r5, r5, #1
            b while
          
