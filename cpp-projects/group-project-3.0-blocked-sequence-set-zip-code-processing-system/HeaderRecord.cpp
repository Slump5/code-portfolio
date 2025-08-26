// CSCI 331 Group Project - Copyright © 2024 Blocked Sequence Set Zip Code Processing System
#include "HeaderRecord.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

/**
 * @brief Default constructor for HeaderRecord
 * 
 * Initializes all numeric members to sensible defaults
 */
HeaderRecord::HeaderRecord()
    : headerSize(0)
    , recordSizeBytes(-1)
    , blockSize(512)  // Default block size of 512 bytes
    , minBlockCapacity(0.5)  // Default 50% minimum capacity
    , recordCount(40933) // Record count of input data
    , blockCount(3679) 
    , fieldCount(6) // Default 6 as all used zipcode data has 6 peramiters
    , primaryKeyField(0)
    , availListRBN(-1)
    , activeListRBN(-1)
    , isStale(false) {
    fileStructureType = "blocked_sequence_set";
    version = "1.0";
    sizeFormatType = "ASCII";
}

/**
 * @brief Adds a new field definition to the header
 * @param name Name or ID of the field
 * @param schema Type and format information for the field
 */
void HeaderRecord::addField(const std::string& name, const std::string& schema) {
    FieldMetadata field;
    field.name = name;
    field.typeSchema = schema;
    fields.push_back(field);
    fieldCount = fields.size();
}

/**
 * @brief Writes the header information to an already open file stream
 * 
 * @param file Reference to an open output file stream
 * @return true if successful, false otherwise
 */
bool HeaderRecord::writeHeader(std::ofstream& file) {
    if (!file.is_open()) {
        std::cerr << "Error: File stream is not open" << std::endl;
        return false;
    }

    // Lambda to write length-indicated field
    auto writeField = [&file](const std::string& value) {
        std::string lengthStr = std::to_string(value.length());
        if (lengthStr.length() < 2) lengthStr = "0" + lengthStr;
        file << lengthStr << value << ",";
    };

    // Write main header fields
    writeField(fileStructureType);
    writeField(version);
    writeField(std::to_string(headerSize));
    writeField(std::to_string(recordSizeBytes));
    writeField(sizeFormatType);
    writeField(std::to_string(blockSize));
    writeField(std::to_string(static_cast<int>(minBlockCapacity * 100)));
    writeField(indexFileName);
    writeField(indexFileSchema);
    writeField(std::to_string(recordCount));
    writeField(std::to_string(blockCount));
    writeField(std::to_string(fieldCount));
    writeField(std::to_string(primaryKeyField));
    writeField(std::to_string(availListRBN));
    writeField(std::to_string(activeListRBN));
    file << (isStale ? "1" : "0") << "\n";

    // Write field metadata
    for (const auto& field : fields) {
        writeField(field.name);
        writeField(field.typeSchema);
        file << "\n";
    }

    return true;
}

/**
 * @brief Reads and parses header information from a file
 * 
 * @param filename Name of the file to read from
 * @return true if successful, false otherwise
 */
bool HeaderRecord::readHeader(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
        return false;
    }

    std::string line;
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        
        // Lambda to read length-indicated field
        auto readField = [](std::stringstream& ss) -> std::string {
            std::string lenStr;
            lenStr.resize(2);
            if (!ss.read(&lenStr[0], 2)) return "";
            
            if (!std::isdigit(lenStr[0]) || !std::isdigit(lenStr[1])) {
                throw std::runtime_error("Invalid length indicator");
            }
            
            int length = std::stoi(lenStr);
            std::string value;
            value.resize(length);
            if (!ss.read(&value[0], length)) return "";
            
            if (ss.peek() == ',') ss.ignore();
            return value;
        };

        try {
            // Read main header fields
            fileStructureType = readField(ss);
            version = readField(ss);
            headerSize = std::stoi(readField(ss));
            recordSizeBytes = std::stoi(readField(ss));
            sizeFormatType = readField(ss);
            blockSize = std::stoi(readField(ss));
            minBlockCapacity = std::stoi(readField(ss)) / 100.0;
            indexFileName = readField(ss);
            indexFileSchema = readField(ss);
            recordCount = std::stoi(readField(ss));
            blockCount = std::stoi(readField(ss));
            fieldCount = std::stoi(readField(ss));
            primaryKeyField = std::stoi(readField(ss));
            availListRBN = std::stoi(readField(ss));
            activeListRBN = std::stoi(readField(ss));
            
            std::string staleStr;
            ss >> staleStr;
            isStale = (staleStr == "1");

            // Read field metadata
            fields.clear();
            for (int i = 0; i < fieldCount && std::getline(file, line); i++) {
                std::stringstream fieldSS(line);
                FieldMetadata metadata;
                metadata.name = readField(fieldSS);
                metadata.typeSchema = readField(fieldSS);
                fields.push_back(metadata);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error parsing header: " << e.what() << std::endl;
            return false;
        }
    }

    file.close();
    return true;
}