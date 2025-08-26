// CSCI 331 Group Project - Copyright © 2024 Zip Code Data Processing System
#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>

// Define ZipCodeRecord structure
struct ZipCodeRecord {
    std::string zip_code;
    std::string city;   
    std::string state_id;
    double latitude;
    double longitude;
};

// Define Buffer class
class Buffer {
public:
    // Method to read a CSV file and store records
    bool read_csv();

    // Method to get records grouped by state
    std::map<std::string, std::vector<ZipCodeRecord>> get_state_zip_codes() const;

    // Method to read and unpack a length-indicated Zip Code record
    bool readLengthIndicatedRecord(std::ifstream &fileStream, ZipCodeRecord &record);

private:
    // Vector to store ZipCodeRecord entries
    std::vector<ZipCodeRecord> records;

    // Method to parse a line from CSV into ZipCodeRecord
    ZipCodeRecord parse_csv_line(const std::string& line) const;
};

#endif
