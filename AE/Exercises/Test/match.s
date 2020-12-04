    .text
    .global match

match: mov r3, #1         @ r3 <- risultato
       push {r4, r5, r6}
       mov r4, #0         @ r4 <- indice i
for:   cmp r4, r2         @ se i >= l
       bge end_m          @ vado a fine
       ldrb r5, [r0, r4]  @ prendo un carattere da r0
       ldrb r6, [r1, r4]  @ prendo un carattere da r1
       cmp r5, r6         @ confronto i due caratteri
       movne r3, #0       @ se sono diversi metto il risultato a 0 e vado a fine
       bne end_m
       add r4, r4, #1     @ altrimenti incremento l'indice di 1
       b for              @ e vado al for
end_m: pop {r4, r5, r6}
       mov r0, r3         @ metto il risultato in r0
       mov pc, lr         @ return



       