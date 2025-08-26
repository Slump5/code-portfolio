# Zip Code Data Processing System

## Overview
This is a C++ application for processing US postal code data from CSV files. It reads and buffers zip code data, converts CSV files to a length-indicated format with a header record, creates a primary key index for efficient lookups, identifies extreme zip codes (easternmost, westernmost, northernmost, southernmost) per state based on latitude and longitude, and outputs results to new CSV files. Additionally, it supports interactive zip code lookups using the index to display full records without loading the entire file into RAM. The program handles both ordered and row-randomized CSV inputs, fulfills Parts I and II of a software systems project, and includes Doxygen documentation, design docs, and user guide elements.

## My Contribution
Developer of `CSVLengthIndicated.h` and `CSVLengthIndicated.cpp`, responsible for implementing the conversion of CSV files to length-indicated format and reading length-indicated records.

## Features
- **CSV Reading and Buffering:** Loads zip code data from `us_postal_codes.csv` or randomized variants into a buffer class, supporting sequential processing.
- **Length-Indicated Conversion:** Converts CSV to a custom length-indicated format (ASCII, with two-digit length prefixes per field) and adds a header record.
- **Header Management:** A dedicated buffer class for reading/writing header records, including file structure, version, record counts, field metadata, and primary key info.
- **State Grouping and Extreme Calculation:** Organizes zip codes by state, finds extreme positions (east: min longitude, west: max longitude, north: max latitude, south: min latitude), and outputs to CSV.
- **Index Creation:** Builds a primary key index file mapping zip codes to byte offsets for random access lookups.
- **Zip Code Lookup:** Interactive input for multiple zip codes (separated by "-z"), uses the index to fetch and display individual records efficiently (only one record in RAM at a time).
- **Error Handling:** Checks for file operations, parsing errors, invalid zip codes, and console status messages.
- **Alphabetical Sorting:** States are sorted alphabetically via std::map for output.
- **Documentation Support:** Doxygen comments for API docs, design document, test docs, and user guide elements.
- **Column Reordering Support:** Works with reordered CSV columns via header metadata (though not fully tested in code).

## File Structure
- **buffer.h / buffer.cpp:** Defines and implements the Buffer class for CSV reading, length-indicated record unpacking, parsing, and state grouping.
- **CSVLengthIndicated.h / CSVLengthIndicated.cpp:** Functions for converting CSV to length-indicated format and reading records.
- **HeaderBuffer.h / HeaderBuffer.cpp:** Defines and implements the HeaderBuffer class for managing file headers.
- **IndexFile.h / IndexFile.cpp:** Defines and implements the IndexFile class for creating zip code index files.
- **CSVProcessing.h / CSVProcessing.cpp:** Defines and implements the CSVProcessing class for sorting buffer data, finding extremes, adding headers, and CSV output.
- **maintester.cpp:** Main entry point for processing CSVs, converting formats, creating indexes, and interactive zip code lookups.
- **headerBufferTest.cpp:** Test file for HeaderBuffer functionality.
- **us_postal_codes.csv:** Ordered input CSV with zip code data.
- **us_postal_codes_ROWS_RANDOMIZED.csv:** Row-randomized input CSV for testing.
- **output.csv:** Sample output CSV with state extremes.
- **output1.csv:** Generated extremes CSV for ordered input.
- **output2.csv:** Generated extremes CSV for randomized input.
- **RANDOM_ROW_output.csv:** Additional output CSV for randomized rows.
- **us_postal_codes_length_indicated.txt:** Length-indicated format for ordered CSV.
- **us_postal_codes_RANDOMIZED_length_indicated.txt:** Length-indicated format for randomized CSV.
- **index.txt / index2.txt:** Sample index files for lookups.
- **zip-code-data-processing-system-doxygen.pdf:** Doxygen-generated PDF documentation.
- **zip-code-data-processing-system-design-doc.pdf:** Design document describing classes and components.
- **instructions.html:** Project requirements and objectives.
- **project-1-instructions.html:** Earlier project instructions (for reference).

## Requirements
- C++11 or later
- Standard C++ libraries (<iostream>, <fstream>, <string>, <map>, <vector>, <sstream>, <iomanip>)
- A C++ compiler (g++, clang++, or cl.exe for Windows)
- Input files (`us_postal_codes.csv` and `us_postal_codes_ROWS_RANDOMIZED.csv`) must be in the same directory as the executable
- Optional: Doxygen for regenerating documentation, PDF reader for .pdf files

## Compilation and Running
1. Clone the repository (if applicable):
	```bash
	git clone <repository-url>
	cd <repository-directory>```
2. Compile the program (include all source files):
	- On Unix-like systems (Linux/MacOS):
		```bash
		g++ -std=c++11 maintester.cpp buffer.cpp CSVLengthIndicated.cpp HeaderBuffer.cpp IndexFile.cpp CSVProcessing.cpp -o zipprocessor```
	- On Windows (with MSVC):
		```cmd
		cl /EHsc /std:c++latest maintester.cpp buffer.cpp CSVLengthIndicated.cpp HeaderBuffer.cpp IndexFile.cpp CSVProcessing.cpp /Fe:zipprocessor.exe```
3. Run the executable:
	- Unix-like systems:
		```bash
		./zipprocessor```
	- Windows:
		```cmd
		zipprocessor.exe```

## How to Use
1. Ensure input CSVs (us_postal_codes.csv and us_postal_codes_ROWS_RANDOMIZED.csv) are in the current directory.
2. Compile and run the program as described above.
3. The program will:
	- Process and sort both CSVs to generate extreme zip code outputs (output1.csv and output2.csv).
	- Convert both CSVs to length-indicated format (us_postal_codes_length_indicated.csv and us_postal_codes_RANDOMIZED_length_indicated.csv).
	- Create an index file (index2.txt) for the length-indicated file.
	- Prompt: "Please enter the zip codes you want information about!"
4. Input zip codes separated by "-z" (e.g., "10001-z10002-z99999" for multiple; or just "10001" for one).
5. The program will use the index to lookup and display each record (or "not found" message).
6. Check the console for status messages and view generated files (CSVs, length-indicated files, indexes) in a text/spreadsheet editor.
7. To test with reordered columns: Modify input CSVs externally and re-run (header metadata should handle, but verify).

## Project Notes
- **Extreme Calculations:** Easternmost uses minimum longitude (least negative in US), westernmost maximum longitude, northernmost maximum latitude, southernmost minimum latitude.
- **Length-Indicated Format:** ASCII with two-digit length prefixes per field; header includes structure type, version, sizes, field metadata, and primary key (zip code, ordinal 0).
- **Index Format:** Simple text file with "zipcode offset" per line for random access.
- **Data Parsing:** Skips CSV headers, handles lat/long as doubles; length-indicated reading parses prefixes and fields.
- **Lookup Efficiency:** Only loads header, index, and one record at a time into RAM, as per requirements.
- **Input Handling:** Interactive via cin; splits on "-z" for multiple zips; supports invalid zips with messages.
- **Output Format:** Extremes CSV rows: "State,Easternmost,Westernmost,Northernmost,Southernmost" (zip codes only).
- **Performance:** Sequential for large files (~40,000 entries); index enables O(1) lookups.
- **Dependencies:** Assumes CSV columns: Zip Code, Place Name, State, County, Lat, Long; primary key is zip code.
- **Testing:** Includes header test file; main tester demonstrates full flow. Use scripts for automated testing as needed.
- **Documentation:** Run Doxygen on sources to regenerate PDF; design doc covers preliminaries.

## Future Improvements
- Implement command-line flags (-Zzipcode) for zip lookups instead of interactive input.
- Add binary length-indicated format support (beyond ASCII).
- Handle stale indexes or auto-rebuild if data changes.
- Support full column reordering via dynamic header parsing.
- Add visualization (map extremes using external libraries).
- Optimize for parallel processing on very large datasets.
- Create a full user guide PDF and test document with scripts.

## License
This project is for personal use. Retain the copyright notice: "CSCI 331 Group Project - Copyright © 2024 Zip Code Data Processing System".