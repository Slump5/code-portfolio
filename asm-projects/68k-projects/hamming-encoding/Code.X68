*-----------------------------------------------------------
* Title      : Hamming Encoding
* Written by : Thomas Hoerger
* Date       : 4/6/2024
* Description: Converts a given message into an encoded message. Thomas Hoerger - Copyright © 2024 Hamming Encoding.
*-----------------------------------------------------------
    ORG    $1000        ; Start of program at memory address $1000
START:
    MOVE.L #0,D2         ; Initialize register D2 to 0
    MOVE.L #0,D3         ; Initialize register D3 to 0
    MOVE.L #0,D4         ; Initialize register D4 to 0
    MOVE.L #0,D5         ; Initialize register D5 to 0
    MOVE.L #0,D6         ; Initialize register D6 to 0
    MOVE.L #0,D7         ; Initialize register D7 to 0
    

    MOVE.B #11,$00002400 ; Load byte from memory address $00002400 into D1
    LEA.L $00002400,A0   ; Load effective address of $00002400 into A0
    MOVE.B (A0),D1       ; Move byte from memory into D1
    

    MOVE.L #1,D2         ; Load 1 into D2
    MOVE.L #2,D3         ; Load 2 into D3
    MOVE.L #4,D4         ; Load 4 into D4
    MOVE.L #8,D5         ; Load 8 into D5

    AND.W D1,D2           ; Bitwise AND between D1 and D2, storing result in D2 (D2 = D)
    AND.W D1,D3           ; Bitwise AND between D1 and D3, storing result in D3 (D3 = C)
    AND.W D1,D4           ; Bitwise AND between D1 and D4, storing result in D4 (D4 = B)
    AND.W D1,D5           ; Bitwise AND between D1 and D5, storing result in D5 (D5 = A)

    LSR.W #1,D3           ; Logical shift right by 1 bit in D3 (right shift b bit)
    LSR.W #2,D4           ; Logical shift right by 2 bits in D4 (right shift c bit)
    LSR.W #3,D5           ; Logical shift right by 3 bits in D5 (right shift d bit)

    MOVE.B D5,D0          ; Move D5 (A bit) into D0

    EOR.W D4,D5           ; Bitwise exclusive OR between D4 and D5, storing result in D5 (D5 = R)
    EOR.W D3,D5           ; Bitwise exclusive OR between D3 and D5, storing result in D5 (D5 = R)

    LSR.W #1,D1           ; Logical shift right by 1 bit in D1 (right shift a bit)
    LSL.W #1,D1           ; Logical shift left by 1 bit in D1 (left shift a bit)

    EOR.W D5,D1           ; Bitwise exclusive OR between D5 and D1, storing result in D1 (D1 = ABCR)
    LSL.W #1,D1           ; Logical shift left by 1 bit in D1 (left shift ABCR to ABCR0)

    EOR.W D2,D1           ; Bitwise exclusive OR between D2 and D1, storing result in D1 (D1 = ABCRD)
    LSL.W #1,D1           ; Logical shift left by 1 bit in D1 (left shift ABCRD to ABCRD0)

    EOR.W D0,D4           ; Bitwise exclusive OR between D0 and D4, storing result in D4 (D4 = S)

    EOR.W D0,D3           ; Bitwise exclusive OR between D0 and D3, storing result in D3 (D3 = T)

    EOR.W D4,D1           ; Bitwise exclusive OR between D4 and D1, storing result in D1 (D1 = ABCRDS)
    LSL.W #1,D1           ; Logical shift left by 1 bit in D1 (left shift ABCRDS to ABCRDS0)

    EOR.W D3,D1           ; Bitwise exclusive OR between D3 and D1, storing result in D1 (D1 = ABCRDST)

* Put program code here

    SIMHALT             ; halt simulator

* Put variables and constants here

    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
