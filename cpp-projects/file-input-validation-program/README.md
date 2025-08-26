# File Input Validation Program

## Overview
This is a C++ console-based program designed to read integers from a file and verify that they are in non-decreasing order. The program includes two versions: one using short-circuit evaluation and another without. It processes input files to detect three conditions: reaching the end of the file, encountering an out-of-order item, or filling the array to its capacity. The program outputs the array elements and the reason for stopping the read operation.

## Features
- **Input Validation:** Reads integers from a file and ensures they are in non-decreasing order.
- **Two Versions:**
  - Short-circuit evaluation version (`file-input-validation-program.cpp`) using a single condition check.
  - Non-short-circuit evaluation version (`file-input-validation-program-no-short-circuit.cpp`) with explicit condition checks.
- **Error Handling:** Detects and reports three exit conditions:
	- End of file reached.
	- Array is full.
	- Out-of-order item encountered. 
- **Test Cases:** Handles three scenarios:
  - End of file (`end_of_file.txt`): Stops when the file ends.
  - Out-of-order item (`out_of_order.txt`): Stops when a number is smaller than the previous one.
  - Array full (`end_of_array.txt`): Stops when the array reaches its capacity.
- **Output:** Displays the array elements and the reason for stopping (end of file, out-of-order item, or array full).

## File Structure
- **file-input-validation-program.cpp:** Implements the short-circuit evaluation version of the input validation logic.
- **file-input-validation-program-no-short-circuit.cpp:** Implements the non-short-circuit evaluation version with multiple test cases.
- **CMakeLists.txt:** Configuration file for building the project with CMake.
- **end_of_file.txt:** Test file with fewer numbers than the array size (1 2 3).
- **out_of_order.txt:** Test file with numbers out of order (1 2 5 3 4).
- **end_of_array.txt:** Test file with more numbers than the array size (1 2 3 4 5 6 7).
- **file-input-validation-program-no-short-circuitScript:** Script output showing the execution results of the non-short-circuit version.
- **file-input-validation-programScript:** Empty script file (not used in this project).

## Requirements
- C++11 or later
- Standard C++ libraries (`<iostream>`, `<fstream>`, `<climits>`)
- A C++ compiler (g++, clang++, or cl.exe for Windows)
- Input files (end_of_file.txt, out_of_order.txt, end_of_array.txt) in the same directory as the executable
- Optional: Visual Studio Code with C/C++ extension for IntelliSense support

## Compilation and Running
1. Ensure input files (`end_of_file.txt`, `out_of_order.txt`, `end_of_array.txt`) are in the working directory.
2. Compile the program:
	- For short-circuit version:
		```bash
		g++ -std=c++11 file-input-validation-program.cpp -o file_validator```
	- For non-short-circuit version:
		```bash
		g++ -std=c++11 file-input-validation-program-no-short-circuit.cpp -o file_validator_no_short```
	- On Windows (with MSVC):
		```cmd
		cl /EHsc /std:c++11 file-input-validation-program.cpp /Fe:file_validator.exe
		cl /EHsc /std:c++11 file-input-validation-program-no-short-circuit.cpp /Fe:file_validator_no_short.exe```
3. Run the executable:
	- Short-circuit version (reads from data.txt):
		```bash
		./file_validator```
	- Non-short-circuit version (runs all test cases):
		```bash
		./file_validator_no_short```
	- Windows:
		```cmd
		file_validator.exe
		file_validator_no_short.exe```
		
## How to Use
1. Short-Circuit Version (file-input-validation-program.cpp):
	- Create a data.txt file with space-separated integers (1 2 3).
	- Run the program to read integers into an array of size 5, stopping if:
		- The end of the file is reached.
		- An out-of-order item is encountered.
		- The array is full.
	- The program outputs the array elements and the stop condition.
2. Non-Short-Circuit Version (file-input-validation-program-no-short-circuit.cpp):
	- Uses three predefined test files: end_of_file.txt, out_of_order.txt, and end_of_array.txt.
	- Runs three test cases, each reading from one of the test files into an array of size 5.
	- Outputs the array elements and the stop condition for each test case.

## Notes
- The short-circuit version requires a data.txt file, which is not provided in the project but can be created manually. Replace with one of the test files (end_of_file.txt, out_of_order.txt, or end_of_array.txt) for testing.
- The non-short-circuit version includes all necessary test files and runs multiple test cases automatically.
- The array size is fixed at 5 for all test cases.
- The program assumes input files contain space-separated integers.

## Future Improvements
- Add error handling for file opening failures.
- Support dynamic array sizes based on input file content.
- Allow user-specified input file names via command-line arguments.
- Add validation for non-integer inputs in the file.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2024 File Input Validation Program".