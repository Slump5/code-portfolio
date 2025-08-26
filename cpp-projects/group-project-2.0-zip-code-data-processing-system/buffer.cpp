// CSCI 331 Group Project - Copyright © 2024 Zip Code Data Processing System
#include "buffer.h"
#include <sstream>
#include <iostream>

/**
 * @file Buffer.cpp
 * @brief Implementation of the Buffer class and ZipCodeRecord struct.
 * 
 * Implementation of the Buffer class for handling Zip Code data read 
 * from the CSV file us_postal_codes.csv. 
 * 
 * @author 
 * Daniel Eze
 * @date 
 * 9/29/2024
 */

/**
 * @brief Reads the CSV file and stores the zip code records.
 * 
 * This function opens the CSV file, reads its contents, and 
 * parses each line into a ZipCodeRecord, which is stored in a vector.
 * 
 * @param file_name The path to the CSV file (us_postal_codes.csv).
 * @return True if the file is read successfully, false otherwise.
 */
bool Buffer::read_csv() {
    std::ifstream file("us_postal_codes.csv"); // Open the file
    if (!file.is_open()) {
        std::cerr << "Error opening file: us_postal_codes.csv" << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line); // Skip the header line

    // Read each line of the file
    while (std::getline(file, line)) {
        records.push_back(parse_csv_line(line)); // Parse and store the line
    }

    file.close(); // Close the file
    std::cout << "CSV is now in the buffer" << std::endl;
    return true; // Return true if reading was successful
}

/**
 * @brief Groups the Zip Code records by state.
 * 
 * This function organizes the Zip Code records into a map where each 
 * state ID is a key, and the value is a vector of ZipCodeRecord 
 * structures associated with that state.
 * 
 * @return A map with state IDs as keys and vectors of ZipCodeRecord 
 *         structures as values.
 */
std::map<std::string, std::vector<ZipCodeRecord>> Buffer::get_state_zip_codes() const {
    std::map<std::string, std::vector<ZipCodeRecord>> state_zip_map; // Create a map to hold state records
    
    // Loop through all records
    for (const auto& record : records) {
        state_zip_map[record.state_id].push_back(record); // Add record to the correct state
    }

    return state_zip_map; // Return the grouped records
}

/**
 * @brief Parses a line from the CSV into a ZipCodeRecord.
 * 
 * This function takes a single line of CSV data and extracts the 
 * Zip Code, city, state ID, latitude, and longitude to populate a 
 * ZipCodeRecord structure.
 * 
 * @param line A string representing a single line from the CSV file.
 * @return A ZipCodeRecord structure containing the parsed data.
 */
ZipCodeRecord Buffer::parse_csv_line(const std::string& line) const {
    std::stringstream ss(line); // Use stringstream to parse the line
    ZipCodeRecord record; // Create a ZipCodeRecord to hold the data
    std::string skip;

    // Extract and store each field
    std::getline(ss, record.zip_code, ','); // Get Zip Code
    std::getline(ss, record.city, ',');     // Get City
    std::getline(ss, record.state_id, ','); // Get State ID
    std::getline(ss, skip, ',');            // Skip a field
    std::string latitude_str, longitude_str;
    std::getline(ss, latitude_str, ',');    // Get Latitude as string
    std::getline(ss, longitude_str, ',');   // Get Longitude as string
    
    try {
        if (!latitude_str.empty()) {
            record.latitude = std::stod(latitude_str); // Convert to double
        } else {
            std::cerr << "Invalid latitude value for Zip Code: " << record.zip_code << std::endl;
            record.latitude = 0.0; // Default value or handle appropriately
        }

        if (!longitude_str.empty()) {
            record.longitude = std::stod(longitude_str); // Convert to double
        } else {
            std::cerr << "Invalid longitude value for Zip Code: " << record.zip_code << std::endl;
            record.longitude = 0.0; // Default value or handle appropriately
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid numeric value in CSV for Zip Code: " << record.zip_code << " " << record.state_id << std::endl;
        record.latitude = 0.0;  // Default value or handle appropriately
        record.longitude = 0.0; // Default value or handle appropriately
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Out of range numeric value in CSV for Zip Code: " << record.zip_code << std::endl;
        record.latitude = 0.0;  // Default value or handle appropriately
        record.longitude = 0.0; // Default value or handle appropriately
    }

    return record; // Return the populated record
}

/**
 * @brief Reads a length-indicated record from a binary file.
 * 
 * This function reads a record from a length-indicated binary file, 
 * unpacks the fields, and stores them in a ZipCodeRecord.
 * 
 * @param fileStream The input binary file stream.
 * @param record The ZipCodeRecord structure to populate.
 * @return True if a record is successfully read, false if end-of-file is reached or an error occurs.
 */
bool Buffer::readLengthIndicatedRecord( std::ifstream& fileStream, ZipCodeRecord& record ) {
    if ( !fileStream.is_open() || fileStream.eof() ) {
        return false;
    }

    std::string line;
    if ( !std::getline( fileStream, line ) ) {
        return false;  // EOF reached
    }

    std::stringstream ss( line );

    auto parseField = [ ]( std::stringstream& ss ) -> std::string {
        // Skip any leading whitespace
        while ( std::isspace( ss.peek() ) ) {
            ss.get();
        }

        // Read the two-digit length
        char lengthChars[ 3 ] = { 0 };  // Two digits + null terminator
        if ( !ss.read( lengthChars, 2 ) ) {
            throw std::runtime_error( "Failed to read field length." );
        }

        std::string lengthStr( lengthChars, 2 );  // Ensure we have exactly 2 characters
        int fieldLength = 0;

        try {
            fieldLength = std::stoi( lengthStr );
        }
        catch ( const std::exception& e ) {
            std::cerr << "Invalid field length: '" << lengthStr << "'" << std::endl;
            throw;
        }

        // Read the field data
        std::string fieldData( fieldLength, '\0' );
        if ( !ss.read( &fieldData[ 0 ], fieldLength ) ) {
            throw std::runtime_error( "Failed to read field data." );
        }

        // Check if we've read the expected number of characters
        if ( fieldData.length() != static_cast< size_t >( fieldLength ) ) {
            throw std::runtime_error( "Field data length mismatch." );
        }

        // Consume the comma delimiter if not at the end
        if ( ss.peek() == ',' ) {
            ss.get();
        }

        return fieldData;
        };

    try {
        // Parse all fields, including 'County'
        record.zip_code = parseField( ss );        // Field 1: Zip Code
        record.city = parseField( ss );            // Field 2: City
        record.state_id = parseField( ss );        // Field 3: State ID
        std::string county = parseField( ss );     // Field 4: County
        std::string latitude_str = parseField( ss );   // Field 5: Latitude
        std::string longitude_str = parseField( ss );  // Field 6: Longitude

        // Convert latitude and longitude from string to double
        record.latitude = std::stod( latitude_str );
        record.longitude = std::stod( longitude_str );
    }
    catch ( const std::exception& e ) {
        std::cerr << "Error parsing record: " << e.what() << std::endl;
        return false;
    }

    return true;
}