; Thomas Hoerger - Copyright © 2024 X86 Fundamentals Lab
DATA SEGMENT
    msgPrompt DB '?', '$'              ; Prompt message to display '?'
    msgSumPart1 DB 13, 10, 'THE SUM OF ', '$'    ; First part of the message to display sum
    msgSumPart2 DB ' AND ', '$'        ; Second part of the message to display sum
    msgIs DB ' IS ', '$'              ; Message to display ' IS '
    errorMsg DB 13, 10, 'Sum is not less than 10.', 13, 10, '$'   ; Error message to display

    num1 DB ?   ; Reserve space for first digit
    num2 DB ?   ; Reserve space for second digit
    sum DB ?    ; Reserve space for sum
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA    ; Set up code and data segment assumptions

START:    ; Entry point for the program
    MOV AX, DATA    ; Load the data segment address into AX
    MOV DS, AX      ; Set the data segment register to point to the data segment

    ; Display prompt message
    MOV AH, 9        ; Function 9 of interrupt 21h displays a '$'-terminated string
    MOV DX, OFFSET msgPrompt   ; Load the offset address of msgPrompt into DX
    INT 21h          ; Call interrupt 21h to display the prompt message

    ; Read two decimal digits from the user
    MOV AH, 1        ; Function 1 of interrupt 21h reads a character from standard input
    INT 21h          ; Call interrupt 21h to read the first decimal digit
    SUB AL, '0'      ; Convert the ASCII character to its decimal value
    MOV num1, AL     ; Store the first digit in the variable num1

    MOV AH, 1        ; Read the second decimal digit
    INT 21h          ; Call interrupt 21h to read the second decimal digit
    SUB AL, '0'      ; Convert the ASCII character to its decimal value
    MOV num2, AL     ; Store the second digit in the variable num2

    ; Calculate the sum of the digits
    MOV AL, num1     ; Move the first digit into AL
    ADD AL, num2     ; Add the second digit to AL
    MOV sum, AL      ; Store the sum in the variable sum

    ; Check if the sum is less than 10
    CMP sum, 10      ; Compare the sum with 10
    JAE overflow     ; If sum is greater than or equal to 10, jump to the overflow label

    ; Display the sum message on a new line
    MOV AH, 9        ; Display the first part of the sum message
    MOV DX, OFFSET msgSumPart1   ; Load the offset address of msgSumPart1 into DX
    INT 21h

    MOV DL, num1     ; Display the first digit of the sum
    ADD DL, '0'      ; Convert the decimal value to ASCII character
    MOV AH, 2        ; Function 2 of interrupt 21h displays a character
    INT 21h

    MOV AH, 9        ; Display the second part of the sum message
    MOV DX, OFFSET msgSumPart2   ; Load the offset address of msgSumPart2 into DX
    INT 21h

    MOV DL, num2     ; Display the second digit of the sum
    ADD DL, '0'      ; Convert the decimal value to ASCII character
    MOV AH, 2        ; Function 2 of interrupt 21h displays a character
    INT 21h

    MOV AH, 9        ; Display the 'IS' part of the sum message
    MOV DX, OFFSET msgIs         ; Load the offset address of msgIs into DX
    INT 21h

    MOV DL, sum      ; Display the calculated sum
    ADD DL, '0'      ; Convert the decimal value to ASCII character
    MOV AH, 2        ; Function 2 of interrupt 21h displays a character
    INT 21h

    ; Display newline and carriage return
    MOV AH, 2        ; Function 2 of interrupt 21h displays a character
    MOV DL, 13       ; ASCII code for carriage return
    INT 21h

    MOV AH, 2        ; Function 2 of interrupt 21h displays a character
    MOV DL, 10       ; ASCII code for newline
    INT 21h

    ; Exit the program
    MOV AH, 4Ch      ; Function 4Ch of interrupt 21h terminates the program with the return code in AL
    INT 21h

overflow:
    ; Display an error message if the sum is 10 or greater on a new line
    MOV AH, 9        ; Display the error message
    MOV DX, OFFSET msgPrompt + 1   ; Load the offset address of msgPrompt + 1 to skip the '?'
    INT 21h

    MOV AH, 9        ; Display the error message
    MOV DX, OFFSET errorMsg       ; Load the offset address of errorMsg into DX
    INT 21h

    ; Display newline and carriage return
    MOV AH, 2        ; Function 2 of interrupt 21h displays a character
    MOV DL, 13       ; ASCII code for carriage return
    INT 21h

    MOV AH, 2        ; Function 2 of interrupt 21h displays a character
    MOV DL, 10       ; ASCII code for newline
    INT 21h

    ; Exit the program
    MOV AH, 4Ch      ; Function 4Ch of interrupt 21h terminates the program with the return code in AL
    INT 21h

CODE ENDS          ; End of the code segment
END START          ; End of the program, specifying the starting point
