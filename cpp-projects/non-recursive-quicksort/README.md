# Non-Recursive Quicksort

## Overview
This is a C++ implementation of a non-recursive Quicksort algorithm, designed to sort an array of integers efficiently using a stack-based approach instead of recursion. The program uses the standard C++ library for input/output and stack operations, and includes a partitioning function to organize elements around a pivot.

## Features
- **Non-Recursive Sorting:** Uses a stack to manage sub-arrays, avoiding recursive function calls.
- **Partitioning Logic:** Selects the last element as the pivot and rearranges elements accordingly.
- **In-Place Sorting:** Modifies the input array directly, minimizing memory usage.
- **Simple Interface:** Includes a function to print the array before and after sorting for easy verification.
- **Efficient Stack Usage:** Pushes sub-array boundaries to a stack for iterative processing.

## File Structure
- **non-recursive-quicksort.cpp:** Contains the complete implementation, including the partition function, iterative Quicksort algorithm, array printing function, and main program.

## Requirements
- C++11 or later
- Standard C++ libraries (`<iostream>`, `<stack>`, `<utility>`)
- A C++ compiler (g++, clang++, or cl.exe for Windows)

## Compilation and Running
1. Clone or download the source code:
	```bash
	git clone <repository-url>
	cd <repository-directory>```
2. Compile the program:
	- On Unix-like systems (Linux/MacOS):
		```bash
		g++ -std=c++11 non-recursive-quicksort.cpp -o quicksort```
	- On Windows (with MSVC):
		```cmd
		cl /EHsc /std:c++11 non-recursive-quicksort.cpp /Fe:quicksort.exe```
3. Run the executable:
	- Unix-like systems:
		```bash
		./quicksort```
	- Windows:
		```cmd
		quicksort.exe```

## How It Works
1. The program initializes an example array of integers.
2. The printArray function displays the original array.
3. The iterativeQuicksort function sorts the array:
	- Uses a stack to store the boundaries (low and high) of sub-arrays.
	- Repeatedly pops sub-array boundaries, partitions the sub-array, and pushes new boundaries for unprocessed sub-arrays.
	- The partition function selects the last element as the pivot, places it in its correct position, and rearranges other elements relative to it.
4. The sorted array is displayed using the printArray function.

## Example Output
Original array: 12 4 5 6 7 3 1 15 2 10
Sorted array: 1 2 3 4 5 6 7 10 12 15

## Algorithm Notes
- Pivot Selection: The last element of each sub-array is chosen as the pivot.
- Partitioning: Elements smaller than or equal to the pivot are placed to its left, and larger elements to its right.
- Stack-Based Iteration: The stack stores pairs of indices (low, high) for sub-arrays, processed iteratively until the stack is empty.
- Time Complexity: O(n log n) on average, O(n²) in the worst case.
- Space Complexity: O(log n) for the stack in the average case.

## Future Improvements
- Allow user input for the array to be sorted.
- Implement different pivot selection strategies (e.g., median-of-three) to improve performance.
- Add performance benchmarking to compare with recursive Quicksort.
- Support sorting of other data types using templates.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2024 Non-Recursive Quicksort".