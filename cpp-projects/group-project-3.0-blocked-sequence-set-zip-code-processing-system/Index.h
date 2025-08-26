// CSCI 331 Group Project - Copyright © 2024 Blocked Sequence Set Zip Code Processing System
#ifndef INDEX_H
#define INDEX_H
#include <vector>
#include <string>

using namespace std;

class Index {
public:
  /**
 * @brief Splits a string into tokens based on a specified delimiter.
 *
 * @param line The input string to be split.
 * @param delimiter The character used as the delimiter for splitting the string.
 * @return A vector containing the tokens extracted from the input string.
 */
  void processBlockData( const string& inputFileName, const string& outputFileName );
  /**
 * @brief Processes block data from an input file and organizes it into an output file.
 *
 * This method reads data from an input file, extracts and processes relevant information,
 * and writes the results into an output file. Each valid block and zip code pair is stored
 * in the output file in the format "Block,Zip Code".
 *
 * @param inputFileName The name of the input file containing block data.
 * @param outputFileName The name of the output file where processed data will be saved.
 */
  std::vector<std::string> split( const std::string& line, char delimiter );
};

#endif 