; Thomas Hoerger - Copyright © 2024 X86 Fundamentals Lab
TITLE PGM4_1: ECHO PROGRAM

.MODEL SMALL

.STACK 100H

.CODE

MAIN PROC

;display prompt
MOV AH,2 ;display character function
MOV DL, '?' ;character is '?'
INT 21H ;display it

;input a character
MOV AH,1 ;read character function
INT 21H ;character in AL
MOV BL,AL ;save it in BL

;go to a new line
MOV AH,2 ;display character function
MOV DL,0DH ;carriage return
INT 21H ;execute carriage return
MOV DL,0AH ;line feed
INT 21H ;execute line feed

;display character
MOV DL,BL ;retrieve character
INT 21H ;and display it

;return to DOS
MOV AH,4CH ;DOS exit function
INT 21H ;exit to DOS

MAIN ENDP

END MAIN
