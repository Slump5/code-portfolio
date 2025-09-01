# Memory and Addressing Modes

## Overview
This Motorola 68000 assembly language program, designed for the EASy68K simulator, demonstrates memory manipulation and addressing modes as part of Lab 2.C. The program initializes specific memory locations ($2518–$2544) and registers (A3, A4, A6, D3, D5, D6) with predefined values, then executes a sequence of seven instructions to manipulate data using various addressing modes. The program is run in trace mode to observe changes in registers and memory, fulfilling the lab’s goal of studying memory partitions and addressing techniques.

## Features
- **Memory Initialization:** Sets up memory from $2518 to $2544 with specific 16-bit values (e.g., $4433, $4241, ..., $0000).
- **Register Initialization:** Initializes registers A3 ($002468FA), A4 ($00002544), A6 ($00002518), D3 ($00000000), D5 ($FFFFFFFF), D6 ($00000000).
- **Addressing Modes:** Demonstrates:
  - Displacement (d(An)): `MOVE.B 3(A6),D3`.
  - Displacement with destination (d(An)): `MOVE.W 4(A4),6(A6)`.
  - Post-increment ((An)+): `MOVE.L (A6)+,D5`.
  - Post-increment with absolute addressing: `MOVE.W (A4)+,$002522`.
  - Pre-decrement (-(An)): `MOVE.B $00252E,-(A4)`.
  - Absolute long addressing: `LEA.L $00252A,A3`.
  - Address register indirect ((An)): `MOVE.W (A3),D6`.
- **Trace Mode Execution:** Logs instruction-by-instruction changes to registers and memory for analysis.
- **Simulator Compatibility:** Designed for EASy68K with SIMHALT for clean termination.
- **Memory Output:** Changes viewable in memory range $2518–$2544 and specific locations (e.g., $2522, $252E) post-execution.
- **Learning Focus:** Emphasizes memory access, register manipulation, and addressing mode effects.

## File Structure
- **Program.X68:** The main source code file in 68K assembly.
- **Program.L68:** Assembler listing file with line numbers, opcodes, and symbol table.
- **Program.S68:** S-record file for loading the assembled program into the simulator.
- **Program_RunLog.txt:** Execution log capturing register and memory states in trace mode.
- **Program_OutLog.txt:** Output log (incomplete in provided data).
- **Lab 2C instructions.docx:** Lab activity document specifying memory/register setup and instructions.
- **memory-and-addressing-report-thomashoerger.pdf:** PDF report including objectives, procedure, and trace mode results.

## Requirements
- EASy68K Editor/Assembler (version 5.16.01 or compatible).
- Motorola 68000 assembly knowledge.
- A simulator environment like EASy68K for execution (no compilation to native binary needed).
- Optional: Text editor for viewing/editing .X68 files.

## Compilation and Running
1. Download and install EASy68K (available from easy68k.com).
2. Open the project:
   - Launch EASy68K.
   - Open `Program.X68` in the editor.
3. Assemble the program:
   - Click "Assemble" (or press F9).
   - This generates `Program.L68` and `Program.S68` if successful (despite 3 warnings noted in listing).
4. Load and Run in Trace Mode:
   - Load the S-record (`Program.S68`) into the simulator.
   - Set the program counter (PC) to $00DA.
   - Configure logging: Options > Log Output, select Instructions, Registers, and Memory, specify range (e.g., $2518–$2544), and set output file (e.g., `Program_RunLog.txt`).
   - Run in trace mode: Run > Log Start > Auto Trace.
   - Step through each instruction to observe changes.
   - After execution, open the memory window and inspect $2518–$2544, $2522, and $252E.
5. Sample Command Sequence:
	- .PC 00DA
	- T
	- GO
	- MM 2518
	- MM 2522
	- MM 252E

## How to Use
1. **Prepare Input:** The program initializes:
- Memory at $2518–$2544 with values from `DC.W` directives (e.g., $4433, $4241, ..., $0000).
- Registers A3 ($002468FA), A4 ($00002544), A6 ($00002518), D3 ($00000000), D5 ($FFFFFFFF), D6 ($00000000) via `DC.L` directives.
2. **Run the Program:** Assemble, load, and execute in trace mode as above.
3. **View Output:**
- **Registers Post-Execution (from Program_RunLog.txt):**
  - D3: $000000FF (from `MOVE.B 3(A6),D3`).
  - D5: $0000FFFF (from `MOVE.L (A6)+,D5`).
  - D6: $0000FFFF (from `MOVE.W (A3),D6`).
  - A3: $0000252A (from `LEA.L $00252A,A3`).
  - A4: $00002542 (decremented by pre-decrement; incremented by post-increment).
  - A6: $0000251C (incremented by post-increment).
- **Memory Changes:**
  - $251E: Set to $A267 (from `MOVE.W 4(A4),6(A6)`).
  - $2522: Set to $1FEE (from `MOVE.W (A4)+,$002522`).
  - $2542: Set to $FF (from `MOVE.B $00252E,-(A4)`).
- Use the simulator’s memory window (MM 2518 or MM 2522) to verify.
4. **Trace Mode:** Step through instructions to log changes in `Program_RunLog.txt` for analysis.
5. **Debugging:** Use DI (disassemble) or MM (memory display) commands to verify memory and register contents.

## Program Notes
- **Instruction Effects:**
- **Instruction 1:** `MOVE.B 3(A6),D3` loads byte at $251B ($FF) into D3.
- **Instruction 2:** `MOVE.W 4(A4),6(A6)` copies word at $2548 ($1FEE) to $251E.
- **Instruction 3:** `MOVE.L (A6)+,D5` loads longword at $2518 ($0000FFFF) into D5, increments A6 to $251C.
- **Instruction 4:** `MOVE.W (A4)+,$002522` copies word at $2544 ($A267) to $2522, increments A4 to $2546.
- **Instruction 5:** `MOVE.B $00252E,-(A4)` copies byte at $252E ($FF) to $2543, decrements A4 to $2542.
- **Instruction 6:** `LEA.L $00252A,A3` sets A3 to $252A.
- **Instruction 7:** `MOVE.W (A3),D6` loads word at $252A ($FFFF) into D6.
- **Memory Layout:** Predefined values at $2518–$2544 are critical for instruction outcomes.
- **Addressing Modes:** All required modes are used, showcasing their effects on memory and registers.
- **No Loops:** Linear execution for fixed instruction sequence.
- **Limitations:** Hardcoded memory and register values; no user input or dynamic processing.
- **Warnings:** The `Program.L68` notes 3 warnings, likely due to unusual `ORG` directives for registers (e.g., `ORG A3_START`), but the program executes correctly.

## Future Improvements
- Add user input to set initial memory or register values.
- Implement a loop to process multiple memory regions dynamically.
- Enhance logging with custom output formatting for clearer trace analysis.
- Add error checking for invalid memory addresses or register values.
- Include comments explaining each instruction’s effect on memory/registers.
- Simulate real-world use cases (e.g., data transfer in a larger system).

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2024 Memory and Addressing Modes".