*-----------------------------------------------------------
* Title      : String Copy Program
* Written by : Thomas Hoerger
* Date       : 1/27/24
* Description: Thomas Hoerger - Copyright © 2024 String Copy Program
*-----------------------------------------------------------
    ORG    $2000
    DC.L 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    ORG    $2020
    DC.L 'abcdefghijklmnopqrstuvwxyz'
    ORG    $2040
    DC.W '0123456789'  

START:
    LEA.L	$002000,A2
    LEA.L	$002020,A3
    LEA.L	$002040,A4
    LEA.L	$002200,A1

    MOVE.B	$002016,(A1)+
    MOVE.B	$002024,(A1)+
    MOVE.B	$00202B,(A1)+
    MOVE.B	$002022,(A1)+
    MOVE.B	$00202E,(A1)+
    MOVE.B	$00202C,(A1)+
    MOVE.B	$002024,(A1)+
    MOVE.B	#32,(A1)+
    MOVE.B	19(A3) ,(A1)+
    MOVE.B	14(A3) ,(A1)+
    MOVE.B	#32,(A1)+
    MOVE.B	2(A2) ,(A1)+
    MOVE.B	18(A2) ,(A1)+
    MOVE.B	2(A2) ,(A1)+
    MOVE.B	8(A2) ,(A1)+
    MOVE.B	#32,(A1)+
    MOVE.B	3(A4) ,(A1)+
    MOVE.B	2(A4) ,(A1)+
    MOVE.B	(A4) ,(A1)+
    MOVE.B	#33,(A1)+
    MOVE.B	#33,(A1)+
    MOVE.B	#33,(A1)+
    MOVE.B	#32,(A1)+
                  

    SIMHALT             ; halt simulator

* Put variables and constants here

    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
