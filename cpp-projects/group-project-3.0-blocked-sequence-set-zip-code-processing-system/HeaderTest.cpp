// CSCI 331 Group Project - Copyright © 2024 Blocked Sequence Set Zip Code Processing System
// #include "HeaderRecord.h"
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <vector>

// /**
//  * @brief Creates a sample CSV file with zip code data
//  * @param filename Name of the file to create
//  * @return true if successful, false otherwise
//  */
// bool createSampleCSV(const std::string& filename) {
//     std::ofstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Error: Unable to create sample CSV file: " << filename << std::endl;
//         return false;
//     }

//     // Write header row
//     file << "zip_code,city,state,latitude,longitude\n";

//     // Write some sample data
//     std::vector<std::string> sampleData = {
//         "12345,Springfield,IL,39.7817,-89.6501",
//         "23456,Riverside,CA,33.9533,-117.3961",
//         "34567,Lakewood,OH,41.4819,-81.7984",
//         "45678,Maplewood,MN,44.9530,-93.0275",
//         "56789,Oakland,CA,37.8044,-122.2711"
//     };

//     for (const auto& record : sampleData) {
//         file << record << "\n";
//     }

//     file.close();
//     return true;
// }

// /**
//  * @brief Creates a new file with header and copies CSV data
//  * @param csvFile Original CSV file
//  * @param outputFile Output file with header
//  * @param header HeaderRecord object
//  * @return true if successful, false otherwise
//  */
// bool createFileWithHeader(const std::string& csvFile, const std::string& outputFile, HeaderRecord& header) {
//     // First write the header
//     if (!header.writeHeader(outputFile)) {
//         std::cerr << "Failed to write header to output file" << std::endl;
//         return false;
//     }
//     std::ofstream file(outputFile);
//     if (file.is_open()) {
//         if (!header.writeHeader(file)) {
//             // Handle error
//         }
//     // Continue using the file stream for other operations
//     file.close();

//     // Now append the CSV data
//     std::ifstream inFile(csvFile);
//     std::ofstream outFile(outputFile, std::ios::app);  // Open in append mode

//     if (!inFile.is_open() || !outFile.is_open()) {
//         std::cerr << "Error opening files for copying data" << std::endl;
//         return false;
//     }

//     std::string line;
//     getline(inFile, line);  // Skip the CSV header

//     // Copy the rest of the file
//     while (getline(inFile, line)) {
//         outFile << line << "\n";
//     }

//     inFile.close();
//     outFile.close();
//     return true;
// }

// int main() {
//     const std::string csvFilename = "headerTest.csv";
//     const std::string outputFilename = "headerTest_with_header.dat";

//     // Create sample CSV file
//     std::cout << "Creating sample CSV file..." << std::endl;
//     if (!createSampleCSV(csvFilename)) {
//         std::cerr << "Failed to create sample CSV file" << std::endl;
//         return 1;
//     }

//     // Create and configure header
//     std::cout << "Configuring header record..." << std::endl;
//     HeaderRecord header;
    
//     // Set basic header information
//     header.setFileStructureType("blocked_sequence_set");
//     header.setVersion("1.0");
//     header.setBlockSize(512);  // Default block size
//     header.setMinBlockCapacity(0.5);  // 50% minimum capacity
//     header.setIndexFileName("headerTest.idx");
//     header.setIndexSchema("key:string,rbn:int");
    
//     // Add field definitions
//     // header.addField("zip_code", "string(5)");
//     // header.addField("city", "string(64)");
//     // header.addField("state", "string(2)");
//     // header.addField("latitude", "decimal(8,4)");
//     // header.addField("longitude", "decimal(8,4)");
    
//     // Set primary key field (zip_code is field 0)
//     header.setPrimaryKeyField(0);

//     // Create the output file with header
//     std::cout << "Creating output file with header..." << std::endl;
//     if (!createFileWithHeader(csvFilename, outputFilename, header)) {
//         std::cerr << "Failed to create output file with header" << std::endl;
//         return 1;
//     }

//     // Verify by reading back the header
//     std::cout << "\nVerifying header by reading it back..." << std::endl;
//     HeaderRecord readHeader;
//     if (readHeader.readHeader(outputFilename)) {
//         std::cout << "Header verification successful!\n" << std::endl;
//         std::cout << "File structure type: " << readHeader.getFileStructureType() << std::endl;
//         std::cout << "Version: " << readHeader.getVersion() << std::endl;
//         std::cout << "Block size: " << readHeader.getBlockSize() << std::endl;
//         std::cout << "Index file: " << readHeader.getIndexFileName() << std::endl;
//         std::cout << "Primary key field: " << readHeader.getPrimaryKeyField() << std::endl;
//         std::cout << "Number of fields: " << readHeader.getFields().size() << std::endl;
        
//         std::cout << "\nField definitions:" << std::endl;
//         const auto& fields = readHeader.getFields();
//         for (size_t i = 0; i < fields.size(); i++) {
//             std::cout << i << ": " << fields[i].name << " (" << fields[i].typeSchema << ")" << std::endl;
//         }
//     } else {
//         std::cerr << "Failed to read back header" << std::endl;
//         return 1;
//     }

//     std::cout << "\nTest completed successfully!" << std::endl;
//     return 0;
// }