// CSCI 331 Group Project - Copyright © 2024 Zip Code Data Processing System
#include "CSVLengthIndicated.h"
#include "IndexFile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// zipcode, length offeset
// zipcode, length offeset

bool IndexFile::createIndexFile( const std::string& csvFileName, const std::string& outputFileName ) {
    std::ofstream outputFile( outputFileName );
    if ( !outputFile.is_open() ) {
        std::cerr << "Failed to open output file." << std::endl;
        return false;
    }

    int cumulativeOffset = 0;  // Initialize cumulative offset
    std::vector<std::vector<std::string>> records = readLengthIndicatedRecord( csvFileName );

    // outputFile << records[ 0 ][ 0 ].substr( 2 ) << " " << 0 << std::endl;
    int rowOffset = 0;  // Initialize offset for the current row

    // Loop through all rows
    for ( const auto& row : records ) {
        if ( row.empty() ) continue;  // Skip empty rows
        cumulativeOffset += rowOffset;
        // Extract and correct the zip code (first field of the row)
        std::string correctedZip = row[ 0 ].substr( 2 );

        // Write the corrected zip code and the cumulative offset to the output file
        outputFile << correctedZip << " " << cumulativeOffset << std::endl;
        rowOffset = 0;  

        // Nested loop: Process each field within the current row
        for ( const auto& field : row ) {
            if ( field.size() >= 2 ) {  // Ensure the field has at least two characters
                std::string offsetInString = field.substr( 0, 2 );  // Get the first two characters
                int fieldOffset = std::stoi( offsetInString );  // Convert to integer
                
                rowOffset += fieldOffset + 2;  // Add to the row's total offset
            }
        }
		rowOffset += 5;

        // Add the row's total offset to the cumulative offset
    }
    outputFile.close();  // Close the output file
    return true;
}