// CSCI 331 Group Project - Copyright © 2024 Blocked Sequence Set Zip Code Processing System
#ifndef HEADER_RECORD_H
#define HEADER_RECORD_H

#include <string>
#include <vector>

/**
 * @brief Metadata structure for field information in the header
 */
struct FieldMetadata {
    std::string name;        ///< Name or ID of the field
    std::string typeSchema;  ///< Type and format information for the field
};

/**
 * @class HeaderRecord
 * @brief Manages the header record for blocked sequence set files
 * 
 * This class handles reading and writing header records that contain metadata
 * about the file structure, block organization, and field definitions.
 */
class HeaderRecord {
public:
    HeaderRecord();
    
    /**
     * @brief Writes the header information to a file
     * @param file ofstream of the file to write to
     * @return true if successful, false otherwise
     */
    bool writeHeader(std::ofstream& file);
    
    /**
     * @brief Reads and parses header information from a file
     * @param filename Name of the file to read from
     * @return true if successful, false otherwise
     */
    bool readHeader(const std::string& filename);
    
    // Setters
    void setFileStructureType(const std::string& type) { fileStructureType = type; }
    void setVersion(const std::string& ver) { version = ver; }
    void setBlockSize(int size) { blockSize = size; }
    void setMinBlockCapacity(double capacity) { minBlockCapacity = capacity; }
    void setIndexFileName(const std::string& name) { indexFileName = name; }
    void setIndexSchema(const std::string& schema) { indexFileSchema = schema; }
    void setPrimaryKeyField(int field) { primaryKeyField = field; }
    void setAvailListRBN(int rbn) { availListRBN = rbn; }
    void setActiveListRBN(int rbn) { activeListRBN = rbn; }
    void setStaleFlag(bool flag) { isStale = flag; }
    void addField(const std::string& name, const std::string& schema);
    
    // Getters
    std::string getFileStructureType() const { return fileStructureType; }
    std::string getVersion() const { return version; }
    int getBlockSize() const { return blockSize; }
    double getMinBlockCapacity() const { return minBlockCapacity; }
    std::string getIndexFileName() const { return indexFileName; }
    std::string getIndexSchema() const { return indexFileSchema; }
    int getPrimaryKeyField() const { return primaryKeyField; }
    int getAvailListRBN() const { return availListRBN; }
    int getActiveListRBN() const { return activeListRBN; }
    bool getStaleFlag() const { return isStale; }
    const std::vector<FieldMetadata>& getFields() const { return fields; }
    
private:
    std::string fileStructureType;     ///< Type of file structure
    std::string version;               ///< Version of the file structure
    int headerSize;                    ///< Size of the header record in bytes
    int recordSizeBytes;               ///< Number of bytes for record size integers
    std::string sizeFormatType;        ///< Format type for sizes (ASCII/binary)
    int blockSize;                     ///< Size of each block in bytes
    double minBlockCapacity;           ///< Minimum block capacity (default 50%)
    std::string indexFileName;         ///< Name of the index file
    std::string indexFileSchema;       ///< Schema information for the index file
    int recordCount;                   ///< Total number of records
    int blockCount;                    ///< Total number of blocks
    int fieldCount;                    ///< Number of fields per record
    std::vector<FieldMetadata> fields; ///< Metadata for each field
    int primaryKeyField;               ///< Ordinal number of primary key field
    int availListRBN;                  ///< RBN link to block avail-list
    int activeListRBN;                 ///< RBN link to active sequence set list
    bool isStale;                      ///< Stale flag for header
};

#endif // HEADER_RECORD_H