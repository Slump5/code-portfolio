; Thomas Hoerger - Copyright © 2024 X86 Fundamentals Lab
TITLE PGM4_2: PRINT STRING PROGRAM

.MODEL SMALL

.STACK 100H

.DATA
MSG DB 'HELLO!$'

.CODE

MAIN PROC

;initialize DS
MOV AX,@DATA
MOV DS,AX ;initialize DS

;display message
LEA DX,MSG ;get message
MOV AH,9 ;display string function
INT 21H ;display message

;return to DOS
MOV AH,4CH
INT 21H ;DOS exit

MAIN ENDP

END MAIN
