# Zip Code Extremes Processor

## Overview
This is a C++ application for processing a CSV file containing US postal codes data. It reads the data into a buffer, groups zip codes by state, identifies the easternmost, westernmost, northernmost, and southernmost zip codes for each state based on latitude and longitude, and outputs the results to a new CSV file. The program is designed for sequential processing and demonstrates file I/O, data parsing, and geographic sorting in C++. It fulfills the requirements of a software systems project, including Doxygen documentation and design docs.

## My Contribution
Developer of `buffer.h` and contributed to `buffer.cpp`, responsible for implementing the reading of CSV files and grouping zip code records by state.

## Features
- **CSV Reading and Buffering:** Loads zip code data from `us_postal_codes.csv` into a buffer class for efficient storage and access.
- **State Grouping:** Organizes zip codes into a map keyed by state ID for quick retrieval.
- **Extreme Point Calculation:** Determines the zip codes with the most extreme positions (east: max longitude, west: min longitude, north: max latitude, south: min latitude) per state.
- **CSV Output Generation:** Creates an output CSV with a header and rows for each state, listing the extreme zip codes.
- **Error Handling:** Includes checks for file opening and parsing errors, with console output for status.
- **Alphabetical Sorting:** States are automatically sorted alphabetically via std::map.
- **Documentation Support:** Includes Doxygen comments for generating API docs and a preliminary design document.

## File Structure
- **buffer.h / buffer.cpp:** Defines and implements the Buffer class for reading CSV data, parsing lines into ZipCodeRecord structs, and grouping records by state.
- **CSVProcessing.h / CSVProcessing.cpp:** Defines and implements the CSVProcessing class for sorting the buffer data, finding extreme zip codes per state, adding CSV headers, and writing output.
- **main.cpp:** Entry point that initializes CSVProcessing, generates the header, processes the data, and outputs to `output.csv`.
- **us_postal_codes.csv:** Input CSV file containing zip code data (zip code, place name, state, county, latitude, longitude).
- **output.csv:** Generated output CSV with state extremes.
- **zip-code-extremes-processor-design-doc.pdf:** Preliminary design document describing classes, purposes, and components.
- **zip-code-extremes-processor-doxygen.pdf:** Doxygen-generated PDF documentation of the code.
- **project-1-instructions.html:** Project requirements and objectives.

## Requirements
- C++11 or later
- Standard C++ libraries (<iostream>, <fstream>, <string>, <map>, <vector>, <sstream>)
- A C++ compiler (g++, clang++, or cl.exe for Windows)
- The input file `us_postal_codes.csv` must be in the same directory as the executable
- Optional: Doxygen for generating documentation, PDF reader for .pdf

## Compilation and Running
1. Clone the repository:
	```bash
	git clone <repository-url>
	cd <repository-directory>```
2. Compile the program:
	- On Unix-like systems (Linux/MacOS):
		```bash
		g++ -std=c++11 main.cpp CSVProcessing.cpp buffer.cpp -o zipprocessor```
	- On Windows (with MSVC):
		```bash
		cl /EHsc /std:c++latest main.cpp CSVProcessing.cpp buffer.cpp /Fe:zipprocessor.exe```
3. Run the executable:
	- Unix-like systems:
		```bash
		./zipprocessor```
	- Windows:
		```bash
		zipprocessor.exe```

## How to Use
1. Ensure us_postal_codes.csv is in the current directory.
2. Compile and run the program as described above.
3. The program will:
	- Read the input CSV and buffer the data.
	- Sort and process to find extreme zip codes per state.
	- Generate output.csv with the results.
4. Check the console for status messages ("Header added successfully", "Data successfully written").
5. View output.csv in a spreadsheet editor to see the table of state extremes.
6. To test with data sorted by another field (as per project requirements), sort the CSV externally (e.g., by county in a spreadsheet) and re-run.

## Project Notes
- **Extreme Calculations:** Easternmost uses the maximum longitude (least negative in US coordinates), westernmost the minimum longitude, northernmost the maximum latitude, and southernmost the minimum latitude.
- **Data Parsing:** Skips the CSV header, handles empty or invalid lat/long with defaults (0.0) and error messages.
- **Output Format:** Each row is "State,Easternmost,Westernmost,Northernmost,Southernmost" with zip codes only (no coordinates in output).
- **Performance:** Sequential processing suitable for large CSVs like US postal codes (~40,000 entries).
- **Dependencies:** Relies on the input CSV structure; assumes columns in order: Zip Code, Place Name, State, County, Lat, Long.
- **Documentation:** Run Doxygen on the source files to regenerate the PDF API docs.

## Future Improvements
- Add support for sorting by other CSV fields (e.g., county or place name) directly in code.
- Implement command-line arguments for input/output file names.
- Add visualization (plot extremes on a map using external libraries).
- Handle non-US territories or international postal codes.
- Optimize for very large datasets with parallel processing.

## License
This project is for personal use. Retain the copyright notice: "CSCI 331 Group Project - Copyright © 2024 Zip Code Extremes Processor".