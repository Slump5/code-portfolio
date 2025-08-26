// CSCI 331 Group Project - Copyright © 2024 Blocked Sequence Set Zip Code Processing System
/**
 * @file Block.h
 * @brief Declaration of the Block structure and related global variables and functions for managing a blocked sequence set.
 * 
 * This file defines the structure of a block and declares global variables and functions
 * used to manage a sequence of blocks for a blocked file system. It supports operations
 * such as dumping blocks in physical or logical order.
 * 
 * @date 11/21/2024
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
#include <map>

/**
 * @struct Block
 * @brief Represents a single block in the blocked sequence set.
 * 
 * A block can either be part of the active list or the available list. It contains metadata
 * such as predecessor and successor links and a list of records. Each block is uniquely
 * identified by a Relative Block Number (RBN).
 */
struct Block {
    int RBN;                           ///< Relative Block Number (unique identifier for the block)
    bool isAvailable;                  ///< Flag indicating whether the block is available
    std::vector<std::string> records;  ///< Records stored in the block
    int predecessorRBN;                ///< RBN of the predecessor block in the chain
    int successorRBN;                  ///< RBN of the successor block in the chain
};

/** 
 * @brief Global map of blocks indexed by Relative Block Number (RBN).
 * 
 * This map stores all blocks, with the RBN as the key and the corresponding block as the value.
 */
extern std::map<int, Block> blocks;

/** 
 * @brief Head of the active block list (RBN).
 * 
 * Stores the RBN of the first block in the logical (active) sequence.
 */
extern int listHeadRBN;

/** 
 * @brief Head of the available block list (RBN).
 * 
 * Stores the RBN of the first block in the available (free) list.
 */
extern int availHeadRBN;

/**
 * @brief Dumps blocks in physical order based on their RBNs.
 * 
 * This function iterates over all blocks in ascending order of their RBNs and prints their details.
 * Available blocks are explicitly marked.
 */
void dumpPhysicalOrder();

/**
 * @brief Dumps blocks in logical order starting from the active list head.
 * 
 * This function follows the logical chain of blocks using their successor links and prints details of each block.
 */
void dumpLogicalOrder();

/**
 * @brief Creates a new block and inserts it into the global map.
 * 
 * @param RBN Relative Block Number of the new block.
 * @param isAvailable Flag indicating whether the block is available (true) or active (false).
 * @param records List of records to store in the block.
 * @param predecessorRBN RBN of the predecessor block in the chain.
 * @param successorRBN RBN of the successor block in the chain.
 * 
 * This function initializes a new block with the provided parameters and adds it to the global map.
 */
void createBlock(int RBN, bool isAvailable, const std::vector<std::string>& records, int predecessorRBN, int successorRBN);

/**
 * @brief Parses a block file and populates the global map of blocks.
 * 
 * This function reads a block file, extracts block information, and populates the global `blocks` map.
 * 
 * @param blockFile Path to the block file to parse.
 */
void parseBlockFile(const std::string& blockFile);

/**
 * @brief Creates a block file from an input CSV file.
 * 
 * This function reads an input CSV file, divides the data into blocks of a specified size, and writes the blocks to an output file.
 * 
 * @param inputFile Path to the input CSV file.
 * @param outputFile Path to the output block file.
 * @param BLOCK_SIZE Maximum size of each block in bytes (default is 512).
 * @return True if successful, false otherwise.
 */
bool createBlockFile(const std::string& inputFile, const std::string& outputFile, size_t BLOCK_SIZE = 512);



void listMost();

void search(const std::string& str, const std::string& indexName);

std::vector<std::string> splitZipLine(const std::string& str);

#endif // BLOCK_H
