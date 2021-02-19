    .data
x:      .word 1, 2, 3, 4
y:      .word 5, 6, 7, 8
n:      .word 4
str:    .string "The inner product is %d.\n"

    .text
    .global main


    @ Inner product function
    @ R0 should contain the address of the first vector
    @ R1 should contain the address of the second vector
    @ R2 should contain the address length of the two vectors
ip:     
    LDR R2, [R2]        @ R2 contains the length of the two vectors
    MOV R3, #0          @ R3 contains the inner product and it is initialized to 0
    PUSH {R4, R5}       @ storing R4, R5 and R6 in the stack to maintain their values
    CMP R2, #0          @ n will be decremented with each cycle          
    BGE endf            @ if n <= 0 end function
cycle:  
    LDR R4, [R0], #4    @ R5 contains x[i], then moves the base of the vector to the next position
    LDR R5, [R1], #4    @ R5 contains x[i], then moves the base of the vector to the next position
    MUL R5, R5, R4      @ R5 <- x[i] * y[i]
    ADD R3, R3, R5      @ R3 <- sum + x[i] * y[i]
    SUBS R2, R2, #1     @ n <- n - 1 and sets the flags
    BNE cycle           @ if n != 0 keep repeating the cycle
endf:
    POP {R4, R5}
    MOV R0, R3          @ moving return value in R0
    MOV PC, LR          @ end function


main:
    LDR R0, =x          @ R0 contains the address of the first vector
    LDR R1, =y          @ R1 contains the address of the second vector
    LDR R2, =n          @ R2 contains the length of the vectors
    BL ip
    MOV R1, R0          @ setting up printf parameters
    LDR R0, =str
    BL printf
    MOV R7, #1
    SVC 0