# Hamming Encoding

## Overview
This is an implementation of Hamming code encoding for a 4-bit message in Motorola 68000 assembly language, designed for the EASy68K simulator. The program takes a byte from memory (using the lower 4 bits as data bits a, b, c, d) and computes the 3 parity bits to form a 7-bit Hamming-encoded word. The encoded result is stored in register D1. This project demonstrates bitwise operations, shifts, and XOR for parity calculation at the architecture level, extending a class activity on shift and rotate instructions.

## Features
- **Hamming Encoding:** Converts 4-bit data (xxxxabcd) into a 7-bit codeword (ABCRDST) with parity bits R, S, T.
- **Bitwise Operations:** Uses AND, LSR, LSL, and EOR to extract bits and compute parity.
- **Memory Interaction:** Loads data from address $2400 and processes it in registers.
- **Register Initialization:** Clears registers D2-D7 before processing.
- **Simulator Compatibility:** Designed for EASy68K, with SIMHALT for clean termination.
- **Tested Examples:** Encodes values like decimal 11 (binary 1011) to 0x55, decimal 3 to 0x1E, as shown in sample runs.
- **Error Detection Insight:** While focused on encoding, the structure supports understanding single-bit error correction in Hamming codes.

## File Structure
- **Code.X68:** The main source code file in 68K assembly.
- **Code.L68:** Assembler listing file with line numbers, opcodes, and symbol table.
- **Code.S68:** S-record file for loading the assembled program into the simulator.
- **HammingEncodingActivity.docx:** Lab activity document with decoding/encoding samples, tutor commands, and test runs.
- **hamming-encoding-report-thomashoerger.pdf:** PDF report including objectives, procedure, source code screenshots, and execution results.

## Requirements
- EASy68K Editor/Assembler (version 5.16.01 or compatible).
- Motorola 68000 assembly knowledge.
- A simulator environment like EASy68K for execution (no compilation to native binary needed).
- Optional: Text editor for viewing/editing .X68 files.

## Compilation and Running
1. Download and install EASy68K (available from easy68k.com).
2. Open the project:
   - Launch EASy68K.
   - Open `Code.X68` in the editor.
3. Assemble the program:
   - Click "Assemble" (or press F9).
   - This generates `Code.L68` and `Code.S68` if successful (no errors/warnings).
4. Load and Run:
   - Load the S-record (`Code.S68`) into the simulator.
   - Set the program counter (PC) to $1000.
   - Initialize memory at $2400 with the input byte (e.g., use "MS 2400 0B" for decimal 11).
   - Set breakpoints if needed (e.g., at $104E for halt).
   - Execute with "GO" (or press F5).
   - View results in registers (encoded value in D1) and memory.
   - After execution, D1 holds the encoded value (e.g., $0055 for input 11).
5. Sample Command Sequence:
	- MS 2400 0B
	- .PC 1000
	- GO
	
## How to Use
1. **Prepare Input:** Store the 4-bit message in the lower bits of byte at $2400 (e.g., #9 for binary 1001, #3 for 0011).
2. **Run the Program:** Assemble, load, and execute as above.
3. **View Output:** 
   - The 7-bit encoded Hamming code is in the lower bits of D1 (e.g., 0x4C for one test, 0x1E for another).
   - Use the simulator's register dump or memory viewer to inspect.
4. **Trace Mode:** Enable trace (T) in the simulator to step through instructions and see register changes line-by-line.
5. **Test Cases:**
   - Input: 11 (0x0B, binary xxxx1011) → Output: 0x55 (binary 01010101).
   - Input: 3 (0x03, binary xxxx0011) → Output: 0x1E (binary 00011110).
   - Modify $2400 and re-run for different inputs.
6. **Debugging:** Set breakpoints (e.g., BR 104E) and use DI (disassemble) or MM (memory modify/display) commands.

## Program Notes
- **Data Bits:** Input byte at $2400 uses bits 0-3 (d,c,b,a); higher bits are ignored.
- **Parity Calculation:** 
  - R = A XOR B XOR C (parity over positions 1,2,4).
  - S = A XOR B XOR D (parity over positions 1,2,5).
  - T = A XOR C XOR D (parity over positions 1,3,5).
  - Codeword: Positions follow Hamming scheme (power-of-2 for parity).
- **Register Usage:** D1 holds input and final code; D2-D5 for bit extractions; D0 temporary.
- **Shifts:** LSR for bit isolation (e.g., #3 for A bit); LSL to position bits in codeword.
- **No Loops:** Linear execution for single-byte encoding; extendable for multi-byte.
- **Limitations:** Handles 4 data bits (7-bit code); no error correction implemented (focus on encoding).
- **Sample Output:** From lab: For input 0x0B, D1=0x0055; registers shown in trace mode.

## Future Improvements
- Add decoding routine to detect/correct single-bit errors.
- Support encoding multiple bytes or a string message.
- Implement full 8-bit data encoding (15-bit code with 4 parity bits).
- Add user input via simulator prompts instead of fixed memory.
- Integrate with a higher-level language (e.g., C calling assembly).
- Visualize bit positions and parity calculations in comments or a separate tool.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2024 Hamming Encoding".