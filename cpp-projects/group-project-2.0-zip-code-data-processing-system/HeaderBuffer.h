// CSCI 331 Group Project - Copyright © 2024 Zip Code Data Processing System
#ifndef HEADER_BUFFER_H
#define HEADER_BUFFER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

/**
 * @brief Structure to hold field metadata information
 */
struct FieldMetadata {
    std::string name;       // Field name/ID
    std::string typeSchema; // Format to read/write
};

/**
 * @brief Class for handling the data file header record
 */
class HeaderBuffer {
private:
    std::string fileStructureType;  // Type of file structure
    std::string version;            // Version of file structure
    int headerRecordSize;           // Size of header record in bytes
    int recordSizeBytes;            // Bytes for each record size integer
    std::string sizeFormatType;     // ASCII or binary
    std::string indexFileName;      // Name of primary key index file
    int recordCount;                // Number of records in file
    int fieldCount;                 // Number of fields per record
    int primaryKeyField;            // Ordinal number of primary key field
    std::vector<FieldMetadata> fields; // Metadata for each field

public:
    // Constructor
    HeaderBuffer();

    // File operations
    bool writeHeader(const std::string& filename);
    bool readHeader(const std::string& filename);

    // Setters
    void setFileStructureType(const std::string& type) { fileStructureType = type; }
    void setVersion(const std::string& ver) { version = ver; }
    void setHeaderSize(int size) { headerRecordSize = size; }
    void setRecordSizeBytes(int bytes) { recordSizeBytes = bytes; }
    void setSizeFormat(const std::string& format) { sizeFormatType = format; }
    void setIndexFileName(const std::string& name) { indexFileName = name; }
    void setRecordCount(int count) { recordCount = count; }
    void setFieldCount(int count) { fieldCount = count; }
    void setPrimaryKeyField(int field) { primaryKeyField = field; }
    void addFieldMetadata(const std::string& name, const std::string& schema) {
        fields.push_back({name, schema});
    }

    // Getters
    std::string getFileStructureType() const { return fileStructureType; }
    std::string getVersion() const { return version; }
    int getHeaderSize() const { return headerRecordSize; }
    int getRecordSizeBytes() const { return recordSizeBytes; }
    std::string getSizeFormat() const { return sizeFormatType; }
    std::string getIndexFileName() const { return indexFileName; }
    int getRecordCount() const { return recordCount; }
    int getFieldCount() const { return fieldCount; }
    int getPrimaryKeyField() const { return primaryKeyField; }
    const std::vector<FieldMetadata>& getFields() const { return fields; }
};

#endif // HEADER_BUFFER_H