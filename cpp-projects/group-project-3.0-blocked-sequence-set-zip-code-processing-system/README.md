# Blocked Sequence Set Zip Code Processing System

## Overview
This C++ application processes US postal code data from CSV files into a blocked sequence set file structure, supporting efficient storage, retrieval, and management of zip code records. It converts CSV data into a length-indicated format with a header record, organizes records into fixed-size blocks (default 512 bytes), generates a primary key index for fast lookups, and provides interactive block management and zip code querying capabilities. The system includes buffer classes for block and record processing, dump methods for physical and logical block ordering, and functionality to handle insertions and deletions with an available (free) block list. It fulfills the requirements of CSCI 331 Project 3.0, including Doxygen documentation, design documents, a user guide, and test documents.

## My Contribution
## My Contribution
Developer of `Block.h`, `Block.cpp`, and `main.cpp`, responsible for implementing the blocked sequence set structure, block management functions, and the interactive menu-driven interface for block querying and zip code lookups.

## Features
- **CSV to Blocked Sequence Set Conversion:** Reads `us_postal_codes.csv`, converts it to a length-indicated format with a header record, and organizes records into fixed-size blocks (default 512 bytes) in `block.txt`.
- **Header Management:** Uses `HeaderRecord` class to read/write header records containing metadata like file structure type, block size, field definitions, primary key (zip code), and RBN links for active and available block lists.
- **Block Management:** Supports fixed-size blocks with metadata (record count, predecessor/successor RBNs) for active blocks and minimal metadata (successor RBN) for available blocks.
- **Buffer Classes:** Implements `BlockBuffer` and `RecordBuffer` classes to unpack blocks into records and records into fields, respectively, for efficient processing.
- **Index Creation:** Generates `index.idx` mapping zip codes to block numbers (RBNs) for fast lookups using the `Index` class.
- **Interactive Menu:** Provides options to:
  - Dump blocks in physical order (sequential RBNs).
  - Dump blocks in logical order (following successor RBNs).
  - Query a block by RBN to display its details (availability, records, predecessor/successor RBNs).
  - List extreme zip codes per state (e.g., easternmost, westernmost, northernmost, southernmost).
  - Search for multiple zip codes using the index.
- **Zip Code Lookup:** Supports querying multiple zip codes (separated by "-z") via `index.idx`, retrieving and displaying full records efficiently.
- **Error Handling:** Manages file I/O errors, invalid zip codes, and malformed records with console status messages.
- **Documentation Support:** Includes Doxygen-generated PDF (`project3.pdf`), design document (`Project 3 design document.pdf`), user guide (`Project 3 User Guide.pdf`), and test document (`Preliminary Test Document Project 3.pdf`).

## File Structure
- **Block.h / Block.cpp:** Defines and implements the `Block` structure, global block map, and functions for block creation, parsing, and dumping (physical and logical order).
- **Buffer.h / buffer.cpp:** Defines and implements `Buffer`, `BlockBuffer`, and `RecordBuffer` classes for reading CSVs, parsing records, and processing blocks.
- **HeaderRecord.h / HeaderRecord.cpp:** Defines and implements the `HeaderRecord` class for managing header records with metadata like file structure, block size, and field schemas.
- **Index.h / Index.cpp:** Defines and implements the `Index` class for creating an index file mapping zip codes to RBNs.
- **main.cpp:** Main entry point providing an interactive menu for block management and zip code queries.
- **HeaderTest.cpp:** Test file for header record functionality, creating sample CSVs and headers.
- **us_postal_codes.csv:** Input CSV with zip code data (zip code, city, state, county, latitude, longitude).
- **headerTest.csv:** Small sample CSV for testing (5 records).
- **headerTest_with_header.dat:** Sample length-indicated file with header and 5 records.
- **us_postal_codes_length_indicated.txt:** Length-indicated format for the full CSV dataset.
- **block.txt / blocks.txt:** Blocked sequence set files with header and records organized into blocks.
- **index.idx:** Index file mapping zip codes to block RBNs.
- **p3Script:** Script file demonstrating program execution and sample interactions.
- **blocked-sequence-set-zip-code-processing-system-doxygen.pdf:** Doxygen-generated documentation (88 pages).
- **blocked-sequence-set-zip-code-processing-system-design-document.pdf:** Design document outlining system architecture (5 pages).
- **blocked-sequence-set-zip-code-processing-system-user-guide.pdf:** User guide for running the program (5 pages).
- **project-3.0-preliminary-test-document.pdf:** Test document with test cases for adding/deleting records (11 pages).
- **instructions.html:** Project requirements and objectives.

## Requirements
- C++11 or later
- Standard C++ libraries (`<iostream>`, `<fstream>`, `<string>`, `<map>`, `<unordered_map>`, `<vector>`, `<sstream>`, `<iomanip>`)
- A C++ compiler (g++, clang++, or MSVC)
- Input file (`us_postal_codes.csv`) must be in the same directory as the executable
- Optional: Doxygen for regenerating documentation, PDF reader for viewing .pdf files

## Compilation and Running
1. Ensure all source files and `us_postal_codes.csv` are in the current directory.
2. Compile the program:
	- On Unix-like systems (Linux/MacOS):
		```bash
		g++ -std=c++11 main.cpp Block.cpp buffer.cpp HeaderRecord.cpp Index.cpp -o app.exe```
	- On Windows (with MSVC):
		```cmd
		cl /EHsc /std:c++latest main.cpp Block.cpp buffer.cpp HeaderRecord.cpp Index.cpp /Fe:app.exe```
3. Run the executable:
	- Unix-like systems:
		```bash
		./app.exe```
	- Windows:
		```cmd
		app.exe```

## How to Use
1. Place us_postal_codes.csv in the same directory as the executable.
2. Compile and run the program as described above.
3. The program will:
	- Convert us_postal_codes.csv to block.txt (blocked sequence set format).
	- Generate index.idx mapping zip codes to block RBNs.
	- Display the Block Management Menu with options 1–6.
4. Select an option:
	- 1: Dump Blocks in Physical Order - Displays all blocks sequentially by RBN.
	- 2: Dump Blocks in Logical Order - Displays blocks following successor RBN links.
	- 3: Query a Block by RBN - Enter an RBN to view block details (availability, records, predecessor/successor).
	- 4: Get the most of each state - Lists extreme zip codes per state (not fully implemented in provided code).
	- 5: Search for several zip codes - Enter zip codes separated by "-z" (e.g., "501-z1010-z1031") to retrieve records using the index.
	- 6: Exit - Terminates the program.
5. Check the console for output and view generated files (block.txt, index.idx) in a text editor.
6. For testing with small datasets, use headerTest.csv or modify main.cpp to use headerTest_with_header.dat.

## Project Notes
- **Blocked Sequence Set:** Records are stored in fixed-size blocks (512 bytes) with metadata (record count, predecessor/successor RBNs). Available blocks are linked via availHeadRBN.
- **Length-Indicated Format:** Fields are prefixed with two-digit ASCII length indicators (e.g., 03501 for zip code "501").
- **Index Format:** index.idx contains lines in the format "ZipCode RBN" for efficient lookups.
- **Buffer Processing:** BlockBuffer unpacks blocks into records; RecordBuffer unpacks records into fields (zip code, city, state, county, latitude, longitude).
- **Dump Methods:** Physical order iterates over RBNs in the block map; logical order follows successor RBN links (currently identical post-creation, as no insertions/deletions modify links).
- **Primary Key:** Zip code (field 0) serves as the primary key.
- **Testing:** Preliminary Test Document Project 3.pdf outlines test cases for adding/deleting records, but these are not implemented in the provided code.
- **Performance:** Sequential processing for ~40,000 records; index enables O(1) zip code lookups.
- **Dependencies:** Assumes CSV columns: Zip Code, Place Name, State, County, Lat, Long.

## Future Improvements
- Implement record insertion/deletion with block splitting and merging, updating the available list as per test document requirements.
- Complete listMost() to calculate and display extreme zip codes per state (easternmost, westernmost, northernmost, southernmost).
- Fix predecessor/successor RBN handling to use block metadata instead of hardcoded values.
- Support dynamic block sizes via command-line options.
- Add binary length-indicated format support.
- Implement stale flag handling for header updates.
- Enhance error handling for malformed input files.
- Create automated test scripts for insertion/deletion scenarios.

## License
This project is for academic and personal use. Retain the copyright notice: "CSCI 331 Group Project - Copyright © 2024 Blocked Sequence Set Zip Code Processing System".