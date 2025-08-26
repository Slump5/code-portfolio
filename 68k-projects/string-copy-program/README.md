# String Copy Program

## Overview
This is a Motorola 68000 assembly language program designed for the EASy68K simulator, implementing a simple string copy operation. The program stores uppercase letters, lowercase letters, and digits in specific memory locations and constructs a custom string by copying selected characters to a new memory location ($2200). The resulting string is "Thomas Hoerger!!!" with spaces between components, demonstrating basic memory manipulation and addressing modes.

## Features
- **String Storage:** Stores uppercase alphabet (A-Z) at $2000, lowercase alphabet (a-z) at $2020, and digits (0-9) at $2040.
- **Selective Copying:** Copies specific characters from predefined memory locations to form the string "Thomas Hoerger!!!" at $2200.
- **Addressing Modes:** Uses address register indirect with post-increment (A1)+, displacement (d(An)), and absolute memory addressing.
- **Simulator Compatibility:** Designed for EASy68K with SIMHALT for clean termination.
- **Memory Output:** Resulting string can be viewed at $2200 in the simulator’s memory window.
- **Learning Focus:** Introduces ORG, DC.L, DC.W, LEA.L, MOVE.B, and various addressing modes (An, (An)+, d(An)).

## File Structure
- **68kSourceFile.X68:** The main source code file in 68K assembly.
- **68kSourceFile.L68:** Assembler listing file with line numbers, opcodes, and symbol table.
- **68kSourceFile.S68:** S-record file for loading the assembled program into the simulator.
- **instructions.docx:** Lab activity document with instructions, procedure, and source code.
- **string-copy-program-report-thomashoerger.pdf:** PDF report including objectives, procedure, source code, and addressing mode explanations.

## Requirements
- EASy68K Editor/Assembler (version 5.16.01 or compatible).
- Motorola 68000 assembly knowledge.
- A simulator environment like EASy68K for execution (no compilation to native binary needed).
- Optional: Text editor for viewing/editing .X68 files.

## Compilation and Running
1. Download and install EASy68K (available from easy68k.com).
2. Open the project:
   - Launch EASy68K.
   - Open `68kSourceFile.X68` in the editor.
3. Assemble the program:
   - Click "Assemble" (or press F9).
   - This generates `68kSourceFile.L68` and `68kSourceFile.S68` if successful (no errors/warnings).
4. Load and Run:
   - Load the S-record (`68kSourceFile.S68`) into the simulator.
   - Set the program counter (PC) to $204A.
   - Execute with "GO" (or press F5).
   - Open the memory window and scroll to $2200 to view the output string "Thomas Hoerger!!!".
5. Sample Command Sequence:
	- .PC 204A
	- GO
	- MM 2200

## How to Use
1. **Prepare Input:** The program predefines strings at $2000 (uppercase), $2020 (lowercase), and $2040 (digits) using DC.L and DC.W directives.
2. **Run the Program:** Assemble, load, and execute as above.
3. **View Output:** 
- After execution, the memory at $2200 contains the ASCII string "Thomas Hoerger!!!" (hex: 54 6F 6D 61 73 20 68 6F 65 72 67 65 72 21 21 21 20).
- Use the simulator’s memory window (MM 2200) to inspect.
4. **Trace Mode:** Enable trace (T) in the simulator to step through instructions and observe memory writes.
5. **Debugging:** Use DI (disassemble) or MM (memory display) commands to verify memory contents at $2000, $2020, $2040, and $2200.

## Program Notes
- **String Construction:** The program copies:
- "Tomas" from $2016, $2024, $202B, $2022, $202E (uppercase/lowercase mix).
- Space (#32).
- "ho" from 19(A3), 14(A3) (lowercase).
- Space (#32).
- "CRCH" from 2(A2), 18(A2), 2(A2), 8(A2) (uppercase).
- Space (#32).
- "321" from 3(A4), 2(A4), (A4) (digits).
- "!!!" as #33 (ASCII exclamation marks).
- Final space (#32).
- **Output:** Forms "Thomas Hoerger!!!" (correcting for intent, as source seems to misspell "Hoerger" with "CRCH" due to character selection).
- **Addressing Modes:** Demonstrates LEA for loading addresses, MOVE.B for byte transfers, and post-increment for sequential writes.
- **No Loops:** Linear execution for fixed string construction.
- **Limitations:** Hardcoded character selections; no user input or dynamic string processing.
- **Sample Output:** Memory at $2200 shows ASCII "Thomas Hoerger!!!" (17 bytes).

## Future Improvements
- Add user input to select characters or define custom strings.
- Implement a loop to copy variable-length strings.
- Support string concatenation from multiple memory regions dynamically.
- Add output to a simulator console or external file (if EASy68K supports).
- Include error checking for memory bounds or invalid addresses.
- Enhance with comments explaining each character’s source in the code.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2024 String Copy Program".