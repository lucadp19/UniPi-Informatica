@ calcolo di x + 2x^2 + 3x^3 + ... + nx^n

        .data
fmt:    .string "Risultato: <%d>."

        .text
        .global main

main:   MOV R0, #2              @ R0 <- x
        MOV R1, #5              @ R1 <- n
        BL poly
        MOV R1, R0
        LDR R0, =fmt
        BL printf
        MOV R7, #1
        MOV R0, #0
        SVC 0

poly:   CMP R1, #1
        MOVLE PC, LR
        PUSH {R0, R1, LR}
        SUB R1, R1, #1
        BL poly
        MOV R2, R0
        POP {R0, R1, LR}
        PUSH {R0, R1, R2, LR}
        BL pow                  @ R0 <- x^n
        POP {R1, R2, R3, LR}    @ R1 <- x, R2 <- n, R3 <- rec_res
        MUL R0, R0, R2          @ R0 <- nx^n
        ADD R0, R0, R3
        MOV PC, LR

pow:    CMP R1, #1
        MOVLE PC, LR
        PUSH {R0, R1, LR}
        SUB R1, R1, #1
        BL pow
        POP {R1, R2, LR}
        MUL R0, R0, R1
        MOV PC, LR



