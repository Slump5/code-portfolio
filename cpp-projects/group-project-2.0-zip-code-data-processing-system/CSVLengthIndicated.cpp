// CSCI 331 Group Project - Copyright © 2024 Zip Code Data Processing System
/**
 * @file CSVLengthIndicated.cpp
 * @brief Contains functions for converting a CSV file to a length-indicated format and reading length-indicated records.
 *
 * This file provides the implementation of functions that convert a CSV file to a length-indicated format
 * and read records from a CSV file. The length-indicated format is a custom representation where each field
 * is prefixed by its length, allowing for variable-length records.
 *
 * @details
 * The provided functions include:
 * - `convertCSVToLengthIndicated()`: Converts the data in a CSV file to a length-indicated format.
 * - `readCSV()`: Reads a CSV file, ignoring the header row, and returns data as a vector of rows.
 * @note Length-indicated records are written as plain text, with each field prefixed by its length as a two-digit integer.
 *
 * @author
 * Thomas Hoerger
 * @date
 * October 18 2024
 */

#include "CSVLengthIndicated.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>  // Added this for std::cerr
#include <vector>
#include "HeaderBuffer.h"


 /**
  * @brief Converts a CSV file to a length-indicated format.
  *
  * Reads each record from a CSV file and writes it to an output file, where each field in the record
  * is prefixed by its length as a two-digit integer. The header row is written without length indicators.
  *
  * @param csvFileName The name of the CSV file to be converted.
  * @param outputFileName The name of the output file where length-indicated records will be stored.
  *
  * @note Each field's length is formatted as a two-digit number, padded with zeroes if necessary.
  * @note If a field exceeds 99 characters, it will be truncated to fit within the two-digit length limit.
  */

void convertCSVToLengthIndicated( const std::string& csvFileName, const std::string& outputFileName ) {
    std::ifstream inputFile( csvFileName );  // Open the CSV file for reading
    std::ofstream outputFile( outputFileName );  // Open the output file for writing
    // Check if either file failed to open
    if ( !inputFile.is_open() || !outputFile.is_open() ) {
        std::cerr << "Failed to open file(s)." << std::endl;
        return;
    }

    std::string line;
    bool isFirstRow = true;  // Flag to check if we're on the header row

    // Process each line in the CSV file
    while ( std::getline( inputFile, line ) ) {
        // Skip the header row and write it as-is without length indicators
        if ( isFirstRow ) {
            isFirstRow = false;  // Set the flag to false after processing the header
            continue;
        }

        std::istringstream ss( line );  // String stream to parse each field in the line
        std::string token;
        std::string lengthIndicatedLine;
        bool isFirstToken = true;  // Flag for adding commas between fields

        // Process each comma-separated field in the line
        while ( std::getline( ss, token, ',' ) ) {
            // Add a comma before each field except the first one
            if ( !isFirstToken ) {
                lengthIndicatedLine += ",";
            }

            // Remove enclosing quotation marks if they exist
            if ( !token.empty() && token.front() == '"' && token.back() == '"' ) {
                token = token.substr( 1, token.length() - 2 );
            }

            // Limit the field length to 99 characters, and log a warning if truncated
            if ( token.length() > 99 ) {
                std::cerr << "Field length exceeds two-digit limit: " << token << std::endl;
                token = token.substr( 0, 99 );
            }

            // If the field contains a decimal, format it as a fixed-precision floating-point number
            if ( token.find( '.' ) != std::string::npos && ( isdigit( token[ 0 ] ) || token[ 0 ] == '-' ) ) {
                double num = std::stod( token );  // Convert the string to a double
                std::ostringstream oss;
                oss << std::fixed << std::setprecision( 6 ) << num;  // Format with fixed precision
                token = oss.str();
            }

            int fieldLength = token.length();  // Calculate the field length

            // Create a formatted string with the field length followed by the field value
            std::stringstream lengthToken;
            lengthToken << std::setw( 2 ) << std::setfill( '0' ) << fieldLength << token;
            lengthIndicatedLine += lengthToken.str();  // Append the formatted field to the output line

            isFirstToken = false;  // Set flag to false after the first token
        }

        outputFile << lengthIndicatedLine << std::endl;  // Write the formatted line to the output file
    }

    inputFile.close();  // Close the input file
    outputFile.close();  // Close the output file
}

/**
 * @brief Reads data from a CSV file, skipping the header row.
 *
 * Reads each row of a CSV file into a vector of strings, where each inner vector represents a row in the CSV.
 * The header row is ignored, and only data rows are returned.
 *
 * @param filename The name of the CSV file to be read.
 * @return A vector of vectors, where each inner vector represents a row of fields.
 *
 * @note This function assumes a simple CSV structure with fields separated by commas.
 * @warning An error message is displayed if the file cannot be opened.
 */
std::vector<std::vector<std::string>> readLengthIndicatedRecord( const std::string& filename ) {
    std::vector<std::vector<std::string>> data;  // Outer vector to store all rows

    std::ifstream file( filename );  // Open the CSV file for reading
    if ( !file.is_open() ) {  // Check if the file failed to open
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    std::string line;
    bool isHeader = true;  // Flag to skip the header row

    // Read each line from the file
    while ( std::getline( file, line ) ) {
        if ( isHeader ) {  // Skip the header row
            isHeader = false;
            continue;
        }

        std::istringstream ss( line );  // String stream for parsing the line
        std::vector<std::string> row;  // Inner vector to store fields in each row
        std::string field;

        // Parse each field separated by commas
        while ( std::getline( ss, field, ',' ) ) {
            row.push_back( field );  // Add the field to the row vector
        }

        data.push_back( row );  // Add the row vector to the data vector
    }

    file.close();  // Close the file
    return data;   // Return the populated data
}