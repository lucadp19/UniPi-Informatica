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
    PUSH {R4, R5, R6}   @ storing R4, R5 and R6 in the stack to maintain their values
    MOV R4, #0          @ R4 contains the offset
    CMP R4, R2          
    BGE endf            @ if i >= n end function
cycle:  
    LDR R5, [R0, R4, LSL #2]    @ R5 contains x[i]
    LDR R6, [R1, R4, LSL #2]    @ R6 contains y[i]
    MUL R5, R5, R6              @ R5 <- x[i] * y[i]
    ADD R3, R3, R5              @ R3 <- sum + x[i] * y[i]
    ADD R4, R4, #1              @ move to next index in the vectors
    CMP R4, R2         
    BLT cycle                   @ if i < n keep repeating the cycle
endf:
    POP {R4, R5, R6}
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