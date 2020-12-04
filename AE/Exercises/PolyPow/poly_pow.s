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
end:    MOV R7, #1
        MOV R0, #0
        SVC 0


poly:   MOV R2, R0              @ R2 <- x
        MOV R3, #2              @ R3 <- index
        PUSH {R4, R5}           @ pushing R4 onto the stack
        MOV R4, R0              @ R4 will contain x^k
cycle:  CMP R3, R1              @ if index > n
        POPGT {R4, R5}
        MOVGT PC, LR            @ end function
        MUL R4, R4, R2          @ R4 <- x^(k-1) * x = x^k
        MUL R5, R4, R3          @ R5 <- k * x^k
        ADD R0, R0, R5          @ R0 += k * x^k
        ADD R3, R3, #1          @ k++
        B cycle

