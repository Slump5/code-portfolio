// CSCI 331 Group Project - Copyright © 2024 Zip Code Data Processing System
#ifndef INDEX_FILE_H
#define INDEX_FILE_H

#include <iostream>
#include <vector>
#include <string>
/**
 * @brief A class responsible for creating an index file from a CSV file.
 *
 * The `IndexFile` class provides functionality to parse a CSV file and
 * generate an index file that maps zip codes to their corresponding byte
 * offsets in the CSV file. This is useful for efficient data retrieval
 * based on zip codes without loading the entire file into memory.
 */
class IndexFile {
public:
    /**
 * @brief Creates an index file from a specified CSV file.
 *
 * This method reads the provided CSV file, calculates the byte offsets
 * for each record, and writes an index file where each entry contains
 * a zip code and its associated offset. The index file can then be
 * used to quickly access records in the CSV file using random access.
 *
 * @param csvFile The path to the input CSV file containing records.
 * @param outputFile The path where the generated index file will be saved.
 * @return `true` if the index file was created successfully, `false` otherwise.
 *
 * @note The CSV file should be properly formatted, and each record must
 * begin with a zip code followed by other fields separated by commas.
 *
 * @warning If the CSV file cannot be opened or read, the method will
 * return `false` and the index file will not be created.
 *
 */
    bool createIndexFile( const std::string& csvFile, const std::string& outputFile );
};

#endif