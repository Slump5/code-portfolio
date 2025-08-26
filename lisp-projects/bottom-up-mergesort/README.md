# Bottom-Up Merge Sort Implementation

## Overview
This is a Common Lisp implementation of a bottom-up merge sort algorithm. The program sorts a list of elements using an iterative merge sort approach, dividing the list into smaller sublists, merging them pairwise, and iteratively combining the results until the entire list is sorted. The implementation is designed to be efficient and stable, maintaining the relative order of equal elements.

## Features
- **Bottom-Up Merge Sort:** Iteratively divides the input list into smaller sublists, merges them pairwise, and combines results to produce a sorted list.
- **Stable Sorting:** Preserves the relative order of equal elements during the merge process.
- **Generic Input Support:** Works with lists of numbers, strings, or other comparable elements (using Lisp's comparison operators).
- **Functional Design:** Implements the algorithm in a functional style, avoiding destructive operations on the input list.
- **Efficient Merging:** Uses a bottom-up approach to minimize recursive calls and optimize performance for large lists.

## File Structure
- **bottom-up-mergesort.lisp:** The main Lisp file containing the bottom-up merge sort implementation, including functions for splitting lists, merging sublists, and the main sorting algorithm.

## Requirements
- A Common Lisp implementation (SBCL, CLISP, or CCL)
- No external libraries required; uses standard Common Lisp functions

## Compilation and Running
1. Ensure a Common Lisp environment is installed (SBCL):
	- Installing SBCL on Unix-like systems
		```bash
		sudo apt-get install sbcl```  # Debian/Ubuntu
		or
		```bash
		brew install sbcl```  # macOS
2. Clone the repository (if applicable):
	```bash
	git clone <repository-url>
	cd <repository-directory>```
3. Load and run the program in a Lisp REPL:
	- Start the Lisp REPL (sbcl)
	- Load the file:
		```lisp
		(load "bottom-up-mergesort.lisp")```
	- Example usage in the REPL:
		```lisp
		(bottom-up-merge-sort '(5 2 9 1 5 6))```

## How to Use
1. Load bottom-up-mergesort.lisp into your Lisp environment.
2. Call the main sorting function with a list:
	```lisp
	(bottom-up-merge-sort <your-list>)```
3. The function returns a new sorted list, leaving the input list unchanged.
4. Test with different input types (numbers, strings) as long as they support comparison operators (< or >).

## Project Notes
- **Algorithm Details:** The bottom-up merge sort works by treating the input list as a collection of single-element sublists, merging adjacent pairs iteratively, and doubling the sublist size in each iteration until the entire list is sorted.
- **Performance:** Achieves O(n log n) time complexity, with O(n) space complexity for the temporary sublists during merging.
- **Stability:** The merge function ensures stability by preserving the order of equal elements.
- **Input Handling:** Accepts any Lisp list with comparable elements; no preprocessing required.
- **Error Handling:** Assumes valid input; invalid comparisons (e.g., mixed types without defined ordering) may raise errors in the Lisp environment.

## Future Improvements
- Add support for custom comparison functions to allow sorting with user-defined predicates.
- Optimize memory usage by reusing sublists where possible.
- Add error handling for invalid inputs (non-list inputs or incomparable elements).
- Implement parallel merging for large lists using Lisp's threading capabilities.
- Include test cases and a test suite to verify correctness and stability.
- Add documentation comments for compatibility with Lisp documentation tools.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2024 Bottom-up Mergesort".