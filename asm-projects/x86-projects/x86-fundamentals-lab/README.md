# X86 Fundamentals Lab

## Overview
This repository contains a collection of x86 assembly language programs developed for a foundational lab exercise in X86 architecture. The programs demonstrate basic input/output operations, string handling, character manipulation, and rudimentary arithmetic in assembly. They include an echo program, a string printer, a case converter, and a custom program to sum two decimal digits (with sum less than 10). The lab involves editing, assembling-linking, and running these programs, fixing errors, and creating a new program based on specifications. A lab report PDF is included with source code, execution results, and descriptions.

## Features
- **Echo Program (PGM4_1):** Displays a "?" prompt, reads a character, and echoes it on a new line.
- **Print String Program (PGM4_2):** Displays the string "HELLO!".
- **Case Conversion Program (PGM4_3):** Prompts for a lowercase letter, converts it to uppercase, and displays it.
- **Digit Sum Program (DISPLAY):** Displays a "?" prompt, reads two decimal digits (sum < 10), and prints a sum message if sum < 10, else displays an error.
- **Link Maps:** Generated .MAP files showing memory segments for each program.
- **Lab Documents:** Includes the original lab assignment (.doc) and a completed report (.pdf) with explanations and screenshots.
- **DOS Interrupts:** Uses INT 21h for I/O operations like reading characters, displaying strings, and exiting.

## File Structure
- **PGM4_1.ASM / PGM4_1.MAP:** Source and map for the echo program.
- **PGM4_2.ASM / PGM4_2.MAP:** Source and map for the print string program.
- **PGM4_3.ASM / PGM4_3.MAP:** Source and map for the case conversion program.
- **DISPLAY.ASM / DISPLAY.MAP:** Source and map for the digit sum program.
- **x86-lab.doc:** Original lab assignment document with program listings and instructions.
- **x86-fundamentals-lab-report-thomashoerger.pdf:** Completed lab report with objectives, procedures, source code, and results.

## Requirements
- x86 Assembler (TASM or MASM)
- Linker (TLINK)
- DOS environment or emulator (DOSBox for modern systems)
- Text editor (Notepad) for editing .ASM files
- Optional: Word processor for viewing .doc files and PDF reader for the report

## Compilation and Running
1. Clone the repository:
	```bash
	git clone <repository-url>
	cd <repository-directory>```
2. Assemble the program (using TASM or MASM):
	- Example for PGM4_1:
		```bash
		tasm PGM4_1.asm```
		or
		```bash
		masm PGM4_1.asm;```
3. Link the object file:
	```bash
	tlink PGM4_1.obj;```
4. Run the executable (in DOS or DOSBox):
	```bash
	PGM4_1```
5. Repeat for other programs (PGM4_2, PGM4_3, DISPLAY).

## How to Run the Programs
1. Set up a DOS environment (launch DOSBox).
2. Navigate to the directory containing the .ASM files.
3. Assemble and link as described above.
4. Execute the program and interact:
	- PGM4_1: Type a character after "?"; it echoes on a new line.
	- PGM4_2: Automatically prints "HELLO!".
	- PGM4_3: Enter a lowercase letter; it displays the uppercase version.
	- DISPLAY: Enter two digits after "?" (27); prints sum message if sum < 10, else error.
5. Exit programs return to DOS automatically.

## Program Notes
- **Model and Stack:** All programs use .MODEL SMALL and .STACK 100H for simple memory management.
- **Data Segment:** Strings and variables are defined in .DATA for easy access.
- **Code Segment:** Main procedures handle initialization, I/O, and exit using MOV, LEA, INT 21h, etc.
- **Error Handling:** In DISPLAY, checks if sum >= 10 and displays an error.
- **ASCII Conversions:** Uses SUB/ADD with '0' for digit handling and 20H for case conversion.
- **Lab Fixes:** Programs include corrections for missing instructions (AH values for display).

## Future Improvements
- Add more advanced I/O features like reading multi-character inputs.
- Implement looping for repeated executions without restarting.
- Expand to include arithmetic operations for larger numbers or multiple inputs.
- Integrate with modern emulators for graphical output.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2024 X86 Fundamentals Lab".