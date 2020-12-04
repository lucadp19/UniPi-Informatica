    .text
    .global mystrstr

mystrstr: push {lr}
          @ first strlen
          push {r0, r1}
          bl strlen
          mov r2, r0
          pop {r1}            @ r1 <- stringa
          pop {r0}            @ r2 <- parola
          @ seconda strlen 
          @ Le push sono in questo ordine per poter poi 
          @       rimettere stringa e parola al posto giusto
          push {r2}           
          push {r0, r1}
          bl strlen
          mov r3, r0
          pop {r1}
          pop {r0, r2}
          @ preparazione al for
          push {r4, r5, r6}
          mov r4, #-1
          sub r5, r2, r3          
          add r5, r5, #1          
          mov r6, #0              
          mov r2, r3              
for:      cmp r6, r5
          bge end_st
          push {r0, r1, r2}
          bl match
          mov r3, r0
          pop {r0, r1, r2}
          @ se la match dà come risultato 1
          cmp r3, #1
          moveq r0, r6
          popeq {r4, r5, r6}
          popeq {pc}
          @ altrimenti
          add r0, r0, #1
          add r6, r6, #1
          b for
end_st:   mov r0, r4
          pop {r4, r5, r6}
          pop {pc}