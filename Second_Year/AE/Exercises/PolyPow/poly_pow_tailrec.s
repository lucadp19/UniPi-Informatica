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

poly:   PUSH {LR}
        MOV R2, R0
        BL polyAux
        POP {PC}

polyAux:CMP R1, #1
        MOVLE R0, R2
        MOVLE PC, LR
        PUSH {R0, R1, R2, LR}
        BL pow
        MOV R3, R0
        POP {R0, R1, R2, LR}
        MUL R3, R3, R1
        ADD R2, R2, R3
        SUB R1, R1, #1
        B polyAux


pow:    PUSH {LR}
        MOV R2, R0
        BL powAux
        POP {PC}

powAux: CMP R1, #1
        MOVLE R0, R2        @ R0 <- acc
        MOVLE PC, LR
        SUB R1, R1, #1
        MUL R2, R2, R0
        B powAux
