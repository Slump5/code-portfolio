// CSCI 331 Group Project - Copyright © 2024 Zip Code Data Processing System
/**
 * @file CSVProcessing.cpp
 * @brief Implementation of CSV processing and zip code lookup functionality
 * @details This file contains implementations for CSV file processing, conversion to length-indicated format,
 *          and zip code lookup functionality using index files.
 */
#include "CSVProcessing.h"
#include "buffer.h"
#include "CSVLengthIndicated.h"
#include <iostream>
#include <fstream>
#include "IndexFile.h"
using namespace std;
/**
 * @brief Converts and sorts CSV data to a specified output file
 * @param origin CSVProcessing object that handles the CSV operations
 * @param file Output file name where the processed CSV will be saved
 * @details Generates a header row and processes the CSV data, reporting any errors encountered during the operation
 */
void csvConvert_sort( CSVProcessing origin, string file ) {
    cout << "Generating header row." << endl;
    origin.addHeader( file );  // Generate the header for the CSV file
    cout << "Checking for errors" << endl << "Errors: ";

    if ( origin.csvOutput( file ) ) {
        cout << "No" << endl << "File made!";
    }
    else {
        cout << "Yes" << endl << "File not made.";
    }
}
/**
 * @brief Splits a string containing zip codes separated by "-z" delimiter
 * @param str Input string containing zip codes
 * @return vector<string> Vector containing individual zip codes
 * @details Processes a string containing multiple zip codes separated by "-z" delimiter,
 *          handles special cases like strings starting with "-z" and empty segments
 */
std::vector<std::string> splitZipLine(const std::string& str) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find("-z", start);
    
    // Skip the first empty part if string starts with "-z"
    if (start == end) {
        start += 2;  // length of "-z"
        end = str.find("-z", start);
    }
    
    while (end != std::string::npos) {
        // Add the part between current position and next "-z"
        if (end - start > 0) {
            result.push_back(str.substr(start, end - start));
        }
        start = end + 2;  // Skip over "-z"
        end = str.find("-z", start);
    }
    
    // Add the last part if there's anything left
    if (start < str.length()) {
        result.push_back(str.substr(start));
    }
    
    return result;
}
/**
 * @brief Retrieves a record from a file at a specific offset
 * @param filename Name of the file to read from
 * @param offset Position in the file where the record starts
 * @return string The record found at the specified offset
 * @throws runtime_error If the file cannot be opened
 * @details Opens the specified file, seeks to the given offset position,
 *          and reads one line from that position
 */
std::string getRecordAtOffset(const std::string& filename, int offset) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open data file.");
    }
	offset = offset;
    file.seekg(offset);  // Jump to the ASCII character position
    std::string line;
   std::getline(file, line);
    file.close();
    return line;
}

/**
 * @brief Checks for and retrieves zip code information from indexed data
 * @param str Zip code to search for
 * @param outputfile Name of the file containing the actual data
 * @param indexName Name of the index file
 * @details Searches for a zip code in the index file and retrieves the corresponding
 *          record from the data file using the stored offset. Prints error message
 *          if zip code is not found
 */
void check( const std::string& str, const std::string& outputfile, const std::string& indexName){
	bool notfound = true;
	std::string correct_line;
	 std::ifstream file2(indexName); // Open the file add name later
    if (!file2.is_open()) {
        std::cerr << "Error opening file: index.txt " << std::endl;
        return;
    }
	// cout << "str is: " << str << endl;
	std::string strcopy = str;
//	while (strcopy.length() > 0 && strcopy[0] == '0') {
  //      strcopy.erase(0, 1);
    //}
	std::string length, zipcode; //Current word of the index being looked at
    //The length to be skipped to find the proper line
	int i = 5;
	
    while ((file2 >> zipcode >> length) && !file2.eof()) {  // reads word by word
        if(zipcode == str){
			int offset = std::stoi(length);
			// cout << "Offset is: " << offset<< endl;
            cout << "Length indicated record at " << zipcode << " is ";
			correct_line = getRecordAtOffset(outputfile, offset+i);
			cout << correct_line << endl;
			notfound = false;
			break;
			}
			else{
				i++;
				
			}
			
			}
			
	if(notfound){
			cout<< str << " was not found in the index.";
			}
			file2.close();
}
/**
 * @brief Main function that orchestrates CSV processing and zip code lookup
 * @return int Returns 0 on successful execution
 * @details Performs the following operations:
 *          1. Converts and sorts two CSV files
 *          2. Converts both CSV files to length-indicated format
 *          3. Creates an index file for zip code lookup
 *          4. Accepts user input for zip codes to look up
 *          5. Processes and displays information for requested zip codes
 */

int main() {
    CSVProcessing csvProcessor;
    std::string csvFileName1 = "us_postal_codes.csv";              // Input CSV file 1
    std::string csvFileName2 = "us_postal_codes_ROWS_RANDOMIZED.csv";  // Input CSV file 2
    std::string outputFileName1 = "output1.csv";                   // Output CSV file 1
    std::string outputFileName2 = "output2.csv";                   // Output CSV file 2

    // Step 1: Convert and sort both CSV files
    cout << "Processing and sorting both CSV files." << endl;
    csvConvert_sort( csvProcessor, outputFileName1 );
    csvConvert_sort( csvProcessor, outputFileName2 );

    // Step 2: Convert both CSV files to length-indicated format (ASCII)
    cout << "\nConverting both CSVs to length-indicated format (ASCII)." << endl;
    std::string lengthIndicatedFileName1 = "us_postal_codes_length_indicated.csv";  // Using .txt for ASCII output
    std::string lengthIndicatedFileName2 = "us_postal_codes_RANDOMIZED_length_indicated.csv";  // Using .txt for ASCII output
    // convertCSVToLengthIndicated( csvFileName1, lengthIndicatedFileName1 );
    // convertCSVToLengthIndicated( csvFileName2, lengthIndicatedFileName2 );
    cout << "Both CSV files converted to length-indicated ASCII format." << endl;
	cout << "Please enter the zip codes you want information about!" << endl;
	std::string text;
	cin >> text;
    auto result = splitZipLine(text);
    
    // Print results
	IndexFile iF;
	std::string indexName = "index2.txt";
    iF.createIndexFile( "us_postal_codes_length_indicated.csv", indexName );
    for (const auto& str : result) {
        //std::cout << str << std::endl;
		string output1 = "us_postal_codes_length_indicated.csv";
		string output2 = "us_postal_codes_RANDOMIZED_length_indicated.csv";
		//check(str,output1);
		check(str,output1, indexName );
    }
    
    return 0;
}
