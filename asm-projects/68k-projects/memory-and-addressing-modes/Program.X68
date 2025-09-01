*-----------------------------------------------------------
* Title      : Memory and Addressing
* Written by : Thomas Hoerger
* Date       : 2/10/2024
* Description: Thomas Hoerger - Copyright © 2024 Memory and Addressing Modes
*-----------------------------------------------------------
    ORG    $1000
* Initialize memory
MEMORY_START EQU $2518
MEMORY_END   EQU $2544
    
    DC.W 4433
    DC.W 4241
    DC.W 0000
    DC.W 0000
    DC.W 2553
    DC.W 0000
    DC.W $01EF
    DC.W $ABCD
    DC.W 5476
    DC.W $CC22  
    DC.W $FF34  
    DC.W $12FF  
    DC.W $A267  
    DC.W $1FEE  
    DC.W $FFFF  
    DC.W $FFFF  
    DC.W $0100  
    DC.W 0000
    DC.W $ABCD  
    DC.W $FFFF  
    DC.W 0000
    DC.W 0000

* Initialize registers    
A3_START EQU $A3
A4_START EQU $A4
A6_START EQU $A6
D3_START EQU $D3
D5_START EQU $D5
D6_START EQU $D6

    ORG A3_START
A3: DC.L $002468FA
    ORG A4_START
A4: DC.L $00002544
    ORG A6_START
A6: DC.L $00002518
    ORG D3_START
D3: DC.L $00000000
    ORG D5_START
D5: DC.L $FFFFFFFF
    ORG D6_START
D6: DC.L $00000000
    
START: 
    MOVE.B 3(A6), D3        ; Instruction 1
    MOVE.W 4(A4), 6(A6)     ; Instruction 2
    MOVE.L (A6)+, D5        ; Instruction 3
    MOVE.W (A4)+, $002522   ; Instruction 4
    MOVE.B $00252E, -(A4)   ; Instruction 5
    LEA.L $00252A, A3       ; Instruction 6
    MOVE.W (A3), D6         ; Instruction 7                 

    SIMHALT             ; halt simulator



    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
