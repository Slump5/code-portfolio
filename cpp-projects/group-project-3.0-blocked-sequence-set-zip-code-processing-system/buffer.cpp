// CSCI 331 Group Project - Copyright © 2024 Blocked Sequence Set Zip Code Processing System
#include "Buffer.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <map>
#include <vector>
#include <unordered_map>

/**
 * @brief A buffer class to manage individual blocks of data.
 */
    // BlockBuffer class method definitions
BlockBuffer::BlockBuffer(const std::unordered_map<std::string, ZipCodeRecord>& block)
    : block_data(block) {}

std::vector<ZipCodeRecord> BlockBuffer::unpack_block() const {
    std::vector<ZipCodeRecord> records;
    for (const auto& entry : block_data) {
        records.push_back(entry.second);
    }
    return records;
}


/**
 * @brief A buffer class to manage individual records.
 */
// RecordBuffer class method definitions
RecordBuffer::RecordBuffer(const ZipCodeRecord& record)
    : record_data(record) {}

void RecordBuffer::unpack_record() {
    zip_code = record_data.zip_code;
    city = record_data.city;
    state_id = record_data.state_id;
    latitude = record_data.latitude;
    longitude = record_data.longitude;
}

void RecordBuffer::print_record() const {
    std::cout << "ZipCode: " << zip_code
              << ", City: " << city
              << ", State: " << state_id
              << ", Latitude: " << latitude
              << ", Longitude: " << longitude
              << std::endl;
}


/**
 * @brief Reads a CSV file and stores the records in the buffer.
 * 
 * @param csv_filename The name of the CSV file to read.
 * @param records_per_block The maximum number of records per block.
 * @return true If the CSV file was successfully read and processed.
 * @return false If the file could not be opened or read.
 */
bool Buffer::read_csv(const std::string& csv_filename, size_t records_per_block) {
    std::ifstream file(csv_filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << csv_filename << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line); // Skip the header line

    size_t block_number = 0;
    size_t record_count = 0;

    while (std::getline(file, line)) {
        ZipCodeRecord record = parse_csv_line(line);
        add_record(block_number, record);

        if (++record_count >= records_per_block) {
            block_number++;
            record_count = 0;
        }
    }

    file.close();
    std::cout << "CSV loaded into the buffer successfully." << std::endl;
    return true;
}

/**
 * @brief Parses a single line from the CSV file into a ZipCodeRecord.
 * 
 * @param line A string containing a single CSV line.
 * @return ZipCodeRecord The parsed ZipCodeRecord.
 */
ZipCodeRecord Buffer::parse_csv_line(const std::string& line) const {
    std::stringstream ss(line);
    std::string token;
    ZipCodeRecord record;

    std::getline(ss, record.zip_code, ',');
    std::getline(ss, record.city, ',');
    std::getline(ss, record.state_id, ',');
    std::getline(ss, token, ',');
    record.latitude = std::stod(token);
    std::getline(ss, token, ',');
    record.longitude = std::stod(token);

    return record;
}

/**
 * @brief Processes the buffer block-by-block, unpacking records and fields.
 */
void Buffer::process_blocks() {
    for (const auto& block_entry : blocks) {
        size_t block_number = block_entry.first;
        const auto& block = block_entry.second;

        BlockBuffer block_buffer(block);
        std::vector<ZipCodeRecord> records = block_buffer.unpack_block();

        std::cout << "Processing Block " << block_number << std::endl;
        for (const auto& record : records) {
            RecordBuffer record_buffer(record);
            record_buffer.unpack_record();
            record_buffer.print_record();
        }
    }
}

/**
 * @brief Sorts all records in the buffer by zip code.
 */
void Buffer::sort_records() {
    std::map<std::string, ZipCodeRecord> sorted_records;

    for (const auto& record : records) {
        sorted_records[record.zip_code] = record;
    }

    std::cout << "Records sorted by Zip Code:" << std::endl;
    for (const auto& entry : sorted_records) {
        const auto& record = entry.second;
        std::cout << "ZipCode: " << record.zip_code
                  << ", City: " << record.city
                  << ", State: " << record.state_id
                  << ", Latitude: " << record.latitude
                  << ", Longitude: " << record.longitude
                  << std::endl;
    }
}

/**
 * @brief Adds a ZipCodeRecord to a specific block and the main records list.
 * 
 * @param block_number The block number to which the record should be added.
 * @param record The ZipCodeRecord to be added.
 */
void Buffer::add_record(size_t block_number, const ZipCodeRecord& record) {
    blocks[block_number][record.zip_code] = record;
    records.push_back(record);
}

/**
 * @brief Retrieves all blocks of ZipCodeRecords.
 * 
 * @return std::unordered_map<size_t, std::unordered_map<std::string, ZipCodeRecord>> 
 * A map where the key is the block number and the value is a map of ZipCodeRecords 
 * within that block.
 */
std::unordered_map<size_t, std::unordered_map<std::string, ZipCodeRecord>> Buffer::get_blocks() const {
    return blocks;
}

/**
 * @brief Prints the contents of each block for debugging purposes.
 */
void Buffer::dump_blocks() const {
    for (const auto& block : blocks) {
        std::cout << "Block " << block.first << " contains the following ZipCodeRecords:" << std::endl;
        for (const auto& record_pair : block.second) {
            std::cout << "ZipCode: " << record_pair.second.zip_code
                      << ", City: " << record_pair.second.city
                      << ", State: " << record_pair.second.state_id
                      << ", Latitude: " << record_pair.second.latitude
                      << ", Longitude: " << record_pair.second.longitude
                      << std::endl;
        }
    }
}
