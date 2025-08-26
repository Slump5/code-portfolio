// CSCI 331 Group Project - Copyright © 2024 Blocked Sequence Set Zip Code Processing System
#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>

// Define a struct to represent a zip code record.
struct ZipCodeRecord {
    std::string zip_code;
    std::string city;
    std::string state_id;
    double latitude;
    double longitude;
};

// Forward declaration of the Buffer class
class Buffer;

/**
 * @brief A class to manage and process blocks of data.
 */
class BlockBuffer {
public:
    explicit BlockBuffer(const std::unordered_map<std::string, ZipCodeRecord>& block);

    /**
     * @brief Unpacks a block into a vector of records.
     * @return A vector of ZipCodeRecords contained in the block.
     */
    std::vector<ZipCodeRecord> unpack_block() const;

private:
    std::unordered_map<std::string, ZipCodeRecord> block_data;
};

/**
 * @brief A class to manage and process individual records.
 */
class RecordBuffer {
public:
    explicit RecordBuffer(const ZipCodeRecord& record);

    /**
     * @brief Unpacks fields from the record into individual attributes.
     */
    void unpack_record();

    /**
     * @brief Prints the contents of the record.
     */
    void print_record() const;

private:
    ZipCodeRecord record_data;
    std::string zip_code;
    std::string city;
    std::string state_id;
    double latitude;
    double longitude;
};

/**
 * @brief A buffer class to manage ZipCodeRecords and process blocks of data.
 */
class Buffer {
public:
    /**
     * @brief Reads a CSV file and stores the records in the buffer.
     * @param csv_filename The name of the CSV file to read.
     * @param records_per_block The maximum number of records per block.
     * @return True if the CSV file was successfully read, false otherwise.
     */
    bool read_csv(const std::string& csv_filename, size_t records_per_block);

    /**
     * @brief Parses a single line from the CSV file into a ZipCodeRecord.
     * @param line A string containing a single CSV line.
     * @return A parsed ZipCodeRecord object.
     */
    ZipCodeRecord parse_csv_line(const std::string& line) const;

    /**
     * @brief Processes the buffer block-by-block, unpacking records and fields.
     */
    void process_blocks();

    /**
     * @brief Sorts all records in the buffer by zip code.
     */
    void sort_records();

    /**
     * @brief Adds a ZipCodeRecord to a specific block and the main records list.
     * @param block_number The block number to which the record should be added.
     * @param record The ZipCodeRecord to be added.
     */
    void add_record(size_t block_number, const ZipCodeRecord& record);

    /**
     * @brief Retrieves all blocks of ZipCodeRecords.
     * @return A map where the key is the block number, and the value is a map of ZipCodeRecords.
     */
    std::unordered_map<size_t, std::unordered_map<std::string, ZipCodeRecord>> get_blocks() const;

    /**
     * @brief Prints the contents of each block for debugging purposes.
     */
    void dump_blocks() const;

private:
    // Map where the key is the block number, and the value is a map of ZipCodeRecords in the block.
    std::unordered_map<size_t, std::unordered_map<std::string, ZipCodeRecord>> blocks;

    // A flat list of all ZipCodeRecords, used for sorting and other operations.
    std::vector<ZipCodeRecord> records;
};

#endif // BUFFER_H
