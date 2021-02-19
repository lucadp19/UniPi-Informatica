    .text
    .global mystrstr

mystrstr: push {r0, r1, lr}
          bl strlen
          mov r2, r0              @ r2 <- ls
          pop {r1, r0, lr}        @ r1 <- parola, r0 <- stringa
          push {r1, r0, r2, lr}   @ le metto sullo stack
          bl strlen
          mov r3, r0              @ r3 <- lp
          pop {r0, r1, r2, lr}    @ le riprendo dallo stack

          push {r4, r5, r6, lr}
          mov r4, #-1             @ r4 <- trovata
          sub r5, r2, r3          @ r5 <- ls - lp
          add r5, r5, #1          @ r5 <- ls - lp + 1
          mov r6, #0              @ r6 <- indice i
          mov r2, r3              @ r2 <- lp
for:      cmp r6, r5              @ se i >= (ls - lp + 1)
          bge end_st
          push {r0, r1, r2}
          bl match                @ match non modifica i parametri in r4, r5, r6
          mov r3, r0              @ risultato della match in r3
          cmp r3, #1              @ se il risultato della match è 1
          popeq {r0, r1, r2}
          moveq r4, r6            @ il risultato è l'indice i
          beq end_st
          pop {r0, r1, r2}
          add r0, r0, #1          @ mando avanti di 1 il puntatore
          b for
end_st:   mov r0, r4              @ metto il risultato in r0
          push {r4, r5, r6, lr}
          mov pc, lr

