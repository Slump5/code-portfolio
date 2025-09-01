*-----------------------------------------------------------
* Title      : Vector Reversal Program
* Written by : Thomas Hoerger
* Date       : 2/24/2024
* Description: This program reverses the elements of a vector. Thomas Hoerger - Copyright © 2024 Vector Reversal Program.
*-----------------------------------------------------------

          ORG $004AC4            ; Set origin address

* Define ASCII vector
VECTOR    DC.B 'ABCDEFGHIJ',0    ; Define ASCII string 'ABCDEFGHIJ'

* Start of program
START     LEA VECTOR,A0          ; A0 points to the start of VECTOR
          MOVE.L #10,D1          ; Length of the vector (number of elements - 1)

REVERSE   MOVEQ #0,D2            ; Initialize D2 to 0
          MOVEQ #9,D3            ; Initialize D3 to 9 (the last index)

LOOP      MOVE.B (A0,D2),D4      ; Load byte from start of VECTOR to D4
          MOVE.B (A0,D3),D5      ; Load byte from end of VECTOR to D5

          MOVE.B D5,(A0,D2)      ; Store byte from D5 to start of VECTOR
          MOVE.B D4,(A0,D3)      ; Store byte from D4 to end of VECTOR

          ADDQ.L #1,D2           ; Increment start index
          SUBQ.L #1,D3           ; Decrement end index

          CMP.L D2,D3            ; Compare start and end indices
          BGE LOOP               ; Continue until start exceeds end

DONE      SIMHALT                ; Halt simulator

          END START              ; End of program


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
