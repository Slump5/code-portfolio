# Insertion Sort in Lisp

## Overview
This is a Common Lisp implementation of the Insertion Sort algorithm, designed to sort a list of numbers in descending order. The program defines functions to insert elements into a sorted list and perform the insertion sort iteratively, maintaining a descending order. It includes global variables to store the original and sorted lists, and provides example usage with a sample list. The code is structured for clarity and includes docstrings for key functions.

## Features
- **Descending Insertion Sort:** Sorts a list of numbers in descending order using the Insertion Sort algorithm.
- **Recursive Implementation:** Uses recursion for both inserting elements into a sorted list and performing the full sort.
- **Global Variables:** Stores the original list in `*my-list*` and the sorted list in `*sorted-list*` for easy access.
- **Docstrings:** Includes descriptive docstrings for all functions to explain their purpose and operation.
- **Example Usage:** Demonstrates sorting a sample list `(5 2 9 1 5 6 3 8 4 7)` and printing both original and sorted results.
- **Simple and Lightweight:** Minimal dependencies, relying only on standard Common Lisp functions.

## File Structure
- **insertion-sort.lisp:** Main Lisp file containing the implementation of the descending insertion sort algorithm, global variables, and example usage.

## Requirements
- A Common Lisp environment (SBCL, CLISP, or CCL)
- No external libraries or dependencies required

## Compilation and Running
1. Ensure a Common Lisp environment is installed (SBCL, CLISP).
2. Save the code in a file named `insertion-sort.lisp`.
3. Load and run the code:
	- In SBCL:
		```bash
		sbcl --script insertion-sort.lisp```
	- In CLISP:
		```bash
		clisp insertion-sort.lisp```
	- Alternatively, load interactively in a Lisp REPL:
		```lisp
		(load "insertion-sort.lisp")```
4. The program will print the original list and the sorted list in descending order.

## How to Use
1. Save the provided Lisp code in `insertion-sort.lisp`.
2. Load the file in a Common Lisp environment as described above.
3. The program will:
	- Define a sample list (5 2 9 1 5 6 3 8 4 7) in *my-list*.
	- Perform descending insertion sort and store the result in *sorted-list*.
	- Print the original list and the sorted list ((9 8 7 6 5 5 4 3 2 1)).
4. To sort a custom list, modify *my-list* in the code or call (descending-insertion-sort your-list) directly in a REPL:
	```lisp
	(setq *my-list* '(your numbers here))
	(setq *sorted-list* (descending-insertion-sort *my-list*))
	(print *sorted-list*)```

## Project Notes
- **Algorithm Details:** Insertion Sort builds the sorted list one element at a time, inserting each element into its correct position in a descending-ordered list.
- **Recursive Approach:** The insert-into-sorted function recursively places an item in the correct position, and insertion-sort recursively processes the unsorted list.
- **Descending Order:** Ensures larger elements appear first in the sorted list (9 > 8 > 7).
- **Error Handling:** Assumes input is a list of comparable elements (numbers). Non-numeric inputs may require additional comparison logic.
- **Performance:** O(n²) time complexity, suitable for small to medium-sized lists. Not optimized for large datasets.
- **Extensibility:** Can be modified to support ascending order by changing the comparison in insert-into-sorted from >= to <=.

## Future Improvements
- Add support for ascending order sorting with a configurable parameter.
- Include input validation to handle non-numeric or mixed-type lists.
- Optimize for larger lists by exploring iterative approaches or alternative algorithms.
- Add unit tests to verify sorting correctness for various input cases.
- Create a command-line interface for passing lists as input.
- Extend to support sorting custom objects with a user-defined comparison function.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2024 Insertion Sort".