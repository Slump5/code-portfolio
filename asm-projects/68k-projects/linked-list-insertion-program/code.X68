*-----------------------------------------------------------
* Title      : Linked List Insertion Program Lab 5
* Written by : Thomas Hoerger
* Date       : 3/30/2024
* Description: This program inserts a new element into a linked list.
*-----------------------------------------------------------
    ORG    $1000

START: 
    ; Initialize memory for e1
    MOVE.L  #data1,D0     ; Load data for e1 into D0
    MOVE.L  D0,$0074A8    ; Store data for e1 at address $0074A8
    MOVE.L  #e2,D0        ; Load address of e2 into D0
    MOVE.L  D0,$0074AC    ; Store address of e2 (next pointer of e1) at address $0074AC

    ; Initialize memory for e2
    MOVE.L  #data2,D0     ; Load data for e2 into D0
    MOVE.L  D0,$0074D0    ; Store data for e2 at address $0074D0
    MOVE.L  #e3,D0        ; Load address of e3 into D0
    MOVE.L  D0,$0074D4    ; Store address of e3 (next pointer of e2) at address $0074D4

    ; Initialize memory for e3
    MOVE.L  #data3,D0     ; Load data for e3 into D0
    MOVE.L  D0,$0074B8    ; Store data for e3 at address $0074B8
    MOVE.L  #e4,D0        ; Load address of e4 into D0
    MOVE.L  D0,$0074BC    ; Store address of e4 (next pointer of e3) at address $0074BC

    ; Initialize memory for the new element
    MOVE.L  #data_new,D0  ; Load data for the new element into D0
    MOVE.L  D0,$0074B0    ; Store data for the new element at address $0074B0
    MOVE.L  #e3,D0        ; Load address of e3 into D0
    MOVE.L  D0,4+$0074B0 ; Store address of e3 (next pointer of the new element) at offset 4 from $0074B0

    ; Update the next pointer of e2 to point to the new element
    MOVE.L  #e2,D0        ; Load address of e2 into D0
    MOVE.L  $0074B0,D1    ; Load address of the new element into D1
    MOVE.L  D1,4(A0)      ; Store address of the new element (next pointer of e2) at offset 4 from e2

    SIMHALT               ; halt simulator

* Put variables and constants here
data1:    DC.L   41414141   ; data for e1
data2:    DC.L   42424242   ; data for e2
data3:    DC.L   43434343   ; data for e3
data4:    DC.L   44444444   ; data for e4
data_new: DC.L   45454545   ; data for the new element
e2:       DC.L   $0074D0    ; address of e2
e3:       DC.L   $0074B8    ; address of e3
e4:       DC.L   $0074C0    ; address of e4

    END    START               ; last line of source









*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
