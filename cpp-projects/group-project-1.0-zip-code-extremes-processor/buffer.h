// CSCI 331 Group Project - Copyright © 2024 Zip Code Extremes Processor
#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>

/**
 * @file buffer.h
 * @brief Header file for the Buffer class and ZipCodeRecord struct.
 * 
 * This file contains the declarations for the Buffer class, which handles reading 
 * and storing Zip Code records from a CSV file, and the ZipCodeRecord struct.
 * 
 * @author 
 * Thomas Hoerger
 * @date 
 * 9/27/2024
 */

/**
 * @brief Structure to hold a single Zip Code record.
 * 
 * This struct stores information about a Zip Code, including the Zip Code
 * itself, the state it belongs to, and its geographical coordinates (latitude and longitude).
 */
struct ZipCodeRecord {
    std::string zip_code;    ///< The Zip Code as a string
    std::string state_id;    ///< The two-character state ID
    double latitude;         ///< Latitude of the Zip Code location
    double longitude;        ///< Longitude of the Zip Code location
};

/**
 * @brief Buffer class for reading and storing Zip Code records from a CSV file.
 * 
 * This class handles reading Zip Code data from a CSV file, storing the records, and
 * providing a method to retrieve the records grouped by state. The records include
 * information such as the Zip Code, state, and geographical coordinates.
 */
class Buffer {
public:
    /**
     * @brief Reads the CSV file and populates the zip code records.
     * 
     * This function reads a CSV file containing Zip Code data and stores the data
     * in a vector of ZipCodeRecord structures.
     * 
     * @param file_name The path to the CSV file containing Zip Code data.
     * @return True if the file is successfully read and parsed, false otherwise.
     */
    bool read_csv(const std::string& file_name);

    /**
     * @brief Retrieves the records grouped by state.
     * 
     * This function organizes the Zip Code records by state and returns a map where each
     * state ID maps to a vector of its corresponding ZipCodeRecord structures.
     * 
     * @return A map with state IDs as keys and vectors of ZipCodeRecord as values.
     */
    std::map<std::string, std::vector<ZipCodeRecord>> get_state_zip_codes() const;

    // std::vector<ZipCodeRecord> get_records_for_state(const std::string& state_id) const; (Vectors instead of map)

private:
    std::vector<ZipCodeRecord> records; ///< A vector holding all the Zip Code records

    /**
     * @brief Parses a single CSV line into a ZipCodeRecord.
     * 
     * This function takes a line of CSV data as input and converts it into a
     * ZipCodeRecord structure, extracting fields like the Zip Code, state ID, latitude,
     * and longitude.
     * 
     * @param line A string representing a single line from the CSV file.
     * @return A ZipCodeRecord structure containing the parsed data.
     */
    ZipCodeRecord parse_csv_line(const std::string& line) const;
};

#endif // BUFFER_H
