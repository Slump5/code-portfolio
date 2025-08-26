// CSCI 331 Group Project - Copyright © 2024 Zip Code Data Processing System
/**
 * @file CSVLengthIndicated.h
 * @brief Header file for functions to handle length-indicated file conversion and reading.
 * 
 * This header file declares functions for converting a CSV file into a length-indicated format
 * and for reading records from a length-indicated file. The length-indicated format prefixes each 
 * record with the byte length of the record, facilitating variable-length data handling.
 * 
 * @details
 * The length-indicated format is a custom structure where each record’s length is stored before
 * the actual data, allowing for efficient parsing of variable-length records. Functions included:
 * - `convertCSVToLengthIndicated()`: Converts CSV data to a length-indicated format.
 * - `readLengthIndicatedRecord()`: Reads a record from a length-indicated file.
 * 
 * @author
 * Thomas Hoerger
 * @date
 * October 18 2024
 */

#ifndef CSV_LENGTH_INDICATED_H
#define CSV_LENGTH_INDICATED_H

#include <string>
#include <fstream>
#include <vector>

/**
 * @brief Converts a CSV file to a length-indicated format.
 * 
 * Reads a CSV file, processes each record to prefix each field with its length, 
 * and writes the result to an output file in the length-indicated format.
 * 
 * @param csvFile The name of the input CSV file to be converted.
 * @param outputFile The name of the output file where the length-indicated format data will be saved.
 * 
 * @note The header row of the CSV is written without length indications, while all data rows
 * have each field prefixed by a two-digit length indicator.
 */
void convertCSVToLengthIndicated(const std::string &csvFile, const std::string &outputFile);

/**
 * @brief Reads a length-indicated record from a file stream.
 * 
 * Reads a single record from the provided length-indicated file stream. Each record is parsed
 * by reading the specified length prefix before each field. The function returns the record data 
 * as a vector of strings, with each string representing a field in the record.
 * 
 * @param fileStream The input file stream from which to read the length-indicated record.
 * @return A vector of vectors of strings, where each inner vector represents a record read from the file.
 * 
 * @note This function assumes each field is prefixed by its length as a two-digit integer.
 * @warning The file stream should be opened in binary mode for correct reading.
 */
std::vector<std::vector<std::string>> readLengthIndicatedRecord( const std::string& filename );

#endif // CSV_LENGTH_INDICATED_H
