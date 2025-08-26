// CSCI 331 Group Project - Copyright © 2024 Blocked Sequence Set Zip Code Processing System
#include "Block.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "HeaderRecord.h"

using namespace std;

/**
 * @brief Global map of blocks indexed by Relative Block Number (RBN).
 * 
 * This map stores all blocks, where the key is the RBN, and the value is the block object.
 */
map<int, Block> blocks;

/**
 * @brief Head of the active block list (RBN).
 * 
 * Stores the RBN of the first block in the active (logical) sequence.
 */
int listHeadRBN = -1;

/**
 * @brief Head of the available block list (RBN).
 * 
 * Stores the RBN of the first block in the available (free) list.
 */
int availHeadRBN = -1;

/**
 * @brief Creates a block file from an input CSV file.
 * 
 * This function reads an input CSV file, divides its data into fixed-size blocks, 
 * and writes those blocks into a new output file.
 * 
 * @param inputFile Path to the input CSV file.
 * @param outputFile Path to the output block file.
 * @param BLOCK_SIZE Maximum size of each block in bytes.
 * @return True if the file was successfully created, false otherwise.
 */
bool createBlockFile(const std::string& inputFile, const std::string& outputFile, size_t BLOCK_SIZE) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);
    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error: Could not open input or output file: " << inputFile << " | " << outputFile << endl;
        return false;
    }

    HeaderRecord header;
    
    // Set basic header information
    header.setFileStructureType("blocked_sequence_set");
    header.setVersion("1.0");
    header.setBlockSize(512);  // Default block size
    header.setMinBlockCapacity(0.5);  // 50% minimum capacity
    header.setIndexFileName("headerTest.idx");
    header.setIndexSchema("key:string,rbn:int");
    
    // Set primary key field (zip_code is field 0)
    header.setPrimaryKeyField(0);

    // First write the header
    if (!header.writeHeader(outFile)) {
        std::cerr << "Failed to write header to output file" << std::endl;
        return false;
    }

    size_t blockNumber = 1;               ///< Current block number being written
    size_t currentBlockSize = 0;          ///< Current size of the block in bytes
    vector<string> blockRecords;          ///< Records for the current block

    string line;
    getline(inFile, line); // Skip header
    while (getline(inFile, line)) {
        size_t lineSize = line.size() + 1; // Include newline character
        if (currentBlockSize + lineSize > BLOCK_SIZE) {
            // Write the current block to the output file
            outFile << blockNumber << ":";
            for (size_t i = 0; i < blockRecords.size(); i++) {
                outFile << blockRecords[i];
                if (i < blockRecords.size() - 1) outFile << ",";
            }
            outFile << "\n";

            blockRecords.clear();
            currentBlockSize = 0;
            blockNumber++;
        }

        blockRecords.push_back(line);
        currentBlockSize += lineSize;
    }

    // Write the last block if there are remaining records
    if (!blockRecords.empty()) {
        outFile << blockNumber << ":";
        for (size_t i = 0; i < blockRecords.size(); i++) {
            outFile << blockRecords[i];
            if (i < blockRecords.size() - 1) outFile << ",";
        }
        outFile << "\n";
    }

    inFile.close();
    outFile.close();

    return true;
}

/**
 * @brief Parses a block file and populates the global map of blocks.
 * 
 * This function reads a block file, splits its content into blocks, 
 * and populates the `blocks` map with their respective details.
 * 
 * @param blockFile Path to the block file to parse.
 */
void parseBlockFile(const string& blockFile) {
    ifstream inFile(blockFile);
    if (!inFile.is_open()) {
        cerr << "Error: Could not open block file: " << blockFile << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        size_t colonPos = line.find(':');
        int RBN = stoi(line.substr(0, colonPos));  ///< Extracted RBN of the block
        string recordsPart = line.substr(colonPos + 1);

        vector<string> records;                   ///< Records in the block
        stringstream recordStream(recordsPart);
        string record;
        while (getline(recordStream, record, ',')) {
            records.push_back(record);
        }

        // Create a block using the parsed data
        createBlock(RBN, false, records, -1, -1);
    }

    inFile.close();
}

/**
 * @brief Dumps all blocks in physical order.
 * 
 * This function iterates through all blocks stored in the global `blocks` map 
 * and prints their details in ascending order of their RBNs.
 */
void dumpPhysicalOrder() {
    cout << "Dumping Blocks by Physical Order:\n";                                        
    for (const auto& [RBN, block] : blocks) {
        cout << "RBN: " << RBN << " ";
        for (const string& record : block.records) {
            cout << record << " ";
        }
        cout << "\n";
    }
}

/**
 * @brief Dumps all blocks in logical order starting from the active list head.
 * 
 * This function follows the logical chain of blocks using their successor links 
 * and prints the details of each block in sequence.
 */
void dumpLogicalOrder() {
    cout << "Dumping Blocks by Logical Order:\n";
    int currentRBN = listHeadRBN;  ///< Start from the logical list head
    while (currentRBN != -1) {
        const Block& block = blocks[currentRBN];
        cout << "RBN: " << currentRBN << " ";
        for (const string& record : block.records) {
            cout << record << " " ;
        }
        cout << "\n";
        currentRBN = block.successorRBN;  ///< Move to the next block in the chain
    }
}
/**
 * @brief Represents geographical location information for a zip code
 *
 * This struct stores detailed geographical data including state, 
 * zip code, latitude, and longitude coordinates
 */
struct mostStorage {
    std::string state, zip_code, county, other;
    double latitude;
    double longitude;
};
/**
 * @brief Finds and lists the extreme points (easternmost, westernmost, 
 *        northernmost, southernmost) for each state
 *
 * This function processes a collection of blocks containing location records,
 * identifying the extreme geographical points for each state based on 
 * longitude and latitude coordinates.
 * 
 * @details The function performs the following steps:
 * - Iterates through all blocks and their records
 * - Extracts state, ZIP code, latitude, and longitude information
 * - Tracks the extreme points for each state
 * - Stores the results in a map of state to extreme locations
 * - Prints out the extreme point ZIP codes for each state
 *
 * @note Assumes records are in a specific order:
 *       - Record 1: ZIP code
 *       - Record 3: State
 *       - Record 5: Latitude
 *       - Record 6: Longitude
 * 
 * @pre Requires a global `blocks` container with records
 * @post Prints extreme point information for each state
 */
void listMost() {
	int currentRBN = listHeadRBN;
	int recordPart = 0;
	int testnum = 0;
	mostStorage current, easternmost, westernmost, northernmost, southernmost;
	std::map<string, std::vector<mostStorage>> sorted_directions;


	for (const auto& [RBN, block] : blocks) {
		  bool initialized = false;
	
			for (const string& record : block.records) {
					recordPart++;
					if(recordPart == 1){
					current.zip_code = record;
					}

					if(recordPart == 3){
					current.state = record;
					}
			 
				if(recordPart == 5){
					current.latitude = std::stod(record);
				}
				if(recordPart == 6){
					current.longitude = std::stod(record);
					if (!initialized) {
                    easternmost = current;
                    westernmost = current;
                    northernmost = current;
                    southernmost = current;
                    initialized = true;
                }
				if ( current.longitude < easternmost.longitude ) {
					easternmost = current;
				}
				if ( current.longitude > westernmost.longitude ) {
					westernmost = current;
				}
				if ( current.latitude > northernmost.latitude ) {
					northernmost = current;
				}
				if ( current.latitude < southernmost.latitude ) {
					southernmost = current;
				}
				recordPart=0;
				sorted_directions[ current.state ] = { easternmost, westernmost, northernmost, southernmost };
				}
			
			
			
			
			 }
							}
				 
            
						
		 
		 
	cout <<"State: "<< "Easternmost: " << "westernmost: "<< "northernnmost: "<< "southernnmost: " <<endl;
	for (const auto& [state, locations] : sorted_directions) {
        if (locations.size() == 4) {  // Ensure we have all 4 directional records
				cout << state << ","
				<< locations[0].zip_code << ","  // Easternmost
                 << locations[1].zip_code << ","  // Westernmost
                 << locations[2].zip_code << ","  // Northernmost 
                 << locations[3].zip_code << "\n";  // Southernmost
		}
	}
}
/**
 * @brief Splits a string containing zip codes separated by "-z" delimiter
 * @param str Input string containing zip codes
 * @return vector<string> Vector containing individual zip codes
 * @details Processes a string containing multiple zip codes separated by "-z" delimiter,
 *          handles special cases like strings starting with "-z" and empty segments
 */
std::vector<std::string> splitZipLine(const std::string& str) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find("-z", start);
    
    // Skip the first empty part if string starts with "-z"
    if (start == end) {
        start += 2;  // length of "-z"
        end = str.find("-z", start);
    }
    
    while (end != std::string::npos) {
        // Add the part between current position and next "-z"
        if (end - start > 0) {
            result.push_back(str.substr(start, end - start));
        }
        start = end + 2;  // Skip over "-z"
        end = str.find("-z", start);
    }
    
    // Add the last part if there's anything left
    if (start < str.length()) {
        result.push_back(str.substr(start));
    }
    
    return result;
}


/**
 * @brief Retrieves a block by its Relative Block Number (RBN)
 * 
 * This function searches the global blocks map for a block with the specified RBN.
 * It returns a pointer to the block if found, or nullptr if the block does not exist.
 * 
 * @param requestedRBN The Relative Block Number of the block to retrieve
 * @return Block* Pointer to the block if found, nullptr otherwise
 * 
 * @note Uses the global `blocks` map to perform the lookup
 * @warning Returns nullptr if the block is not found
 * 
 * @see blocks
 * @see Block
 */
Block* getBlockByRBN(int requestedRBN) {
    // Check if the block exists in the global blocks map
    auto it = blocks.find(requestedRBN);
    
    if (it != blocks.end()) {
        // Block found, return a pointer to the block
        return &(it->second);
    } else {
        // Block not found
        std::cerr << "Block with RBN " << requestedRBN << " not found." << std::endl;
        return nullptr;
    }
}

/**
 * @brief Searches for a specific zip code in the block file and index file
 * 
 * This function performs the following steps:
 * 1. Opens the index file and block file
 * 2. Searches for the given zip code in the index file
 * 3. If found, retrieves the corresponding block
 * 4. Parses the block records to extract and display matching record details
 * 
 * @param str The zip code to search for
 * @param indexName The name of the index file containing zip code to RBN mappings
 * 
 * @pre Requires a valid index file and block file to be present
 * @post Prints the details of the matching record or a "not found" message
 * 
 * @note Uses mostStorage struct to store and display record information
 * @note Assumes a specific record structure within each block
 * 
 * @see mostStorage
 * @see Block
 */

void search(const std::string& str, const std::string& indexName){
	mostStorage current;
	bool notfound = true;
	std::string correct_line;
	 std::ifstream file2(indexName); // Open the file add name later
    if (!file2.is_open()) {
        std::cerr << "Error opening file: index.txt " << std::endl;
        return;
    }
	 std::ifstream file3("block.txt"); // Open the file add name later
    if (!file3.is_open()) {
        std::cerr << "Error opening file: block.txt " << std::endl;
        return;
    }
	std::string strcopy = str;

	std::string rbn, zipcode, line;
	int recordPart = 0;
	//int i = 5;
	getline( file2, line );
	line = "";
    while ((file2 >> zipcode >> rbn) && !file2.eof()) {  // reads word by word
        if(zipcode == str){
			int block = std::stoi(rbn);
            cout << "Zipcode:  " << zipcode << " is at "<< block <<endl;
			Block* myBlock = getBlockByRBN(block);
			for (const string& record : myBlock->records) {
					recordPart++;
					if(recordPart == 1){
					current.zip_code = record;
					
					}
					if(recordPart == 2){
					current.other = record;
					
					}
					if(recordPart == 3){
					current.state = record;
					}
					if(recordPart == 4){
					current.county = record;
					
					}
				if(recordPart == 5){
					current.latitude = std::stod(record);
				}
				if(recordPart == 6){
					current.longitude = std::stod(record);
					
					if(current.zip_code == zipcode){
						cout << current.zip_code << " " <<current.other << " "<<current.state << " "<<current.county 
					<< " "<<current.latitude << " " <<current.longitude << " "<< endl;
					notfound = false;
					break;
					}
				//	current.longitude = std::stod(record);
				/*	if (!initialized) {
                    easternmost = current;
                    westernmost = current;
                    northernmost = current;
                    southernmost = current;
                    initialized = true;*/
                

				recordPart=0;
			}
				}
			}
			
			
		//	break;
			}
			
			
			
	if(notfound){
			cout<< str << " was not found in the file."<<endl;
			}
			file2.close();
}


/**
 * @brief Creates a new block and inserts it into the global map.
 * 
 * This function initializes a new block with the provided details and inserts 
 * it into the `blocks` map. It also updates the global head pointers for the 
 * active and available block lists as needed.
 * 
 * @param RBN Relative Block Number of the new block.
 * @param isAvailable Flag indicating whether the block is available (true) or active (false).
 * @param records List of records to store in the block.
 * @param predecessorRBN RBN of the predecessor block in the chain.
 * @param successorRBN RBN of the successor block in the chain.
 */
void createBlock(int RBN, bool isAvailable, const vector<string>& records, int predecessorRBN, int successorRBN) {
    Block block;
    block.RBN = RBN;
    block.isAvailable = isAvailable;
    block.records = records;
    block.predecessorRBN = predecessorRBN;
    block.successorRBN = successorRBN;

    blocks[RBN] = block;

    // Update the global head pointers
    if (!isAvailable && listHeadRBN == -1) {
        listHeadRBN = RBN;
    }
    if (isAvailable && availHeadRBN == -1) {
        availHeadRBN = RBN;
    }
}
