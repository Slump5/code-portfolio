// CSCI 331 Group Project - Copyright © 2024 Blocked Sequence Set Zip Code Processing System
#include "Index.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * @brief Splits a string into tokens based on a specified delimiter.
 *
 * @param line The input string to be split.
 * @param delimiter The character used as the delimiter for splitting the string.
 * @return A vector containing the tokens extracted from the input string.
 */
vector<string> Index::split( const string& line, char delimiter ) {
  vector<string> tokens;
  string token;
  stringstream ss( line );
  while ( getline( ss, token, delimiter ) ) {
    tokens.push_back( token );
  }
  return tokens;
}

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
void Index::processBlockData( const string& inputFileName, const string& outputFileName ) {
  ifstream inputFile( inputFileName );
  if ( !inputFile.is_open() ) {
    cerr << "Error: Could not open " << inputFileName << endl;
    return;
  }

  ofstream outputFile( outputFileName );
  if ( !outputFile.is_open() ) {
    cerr << "Error: Could not open " << outputFileName << endl;
    return;
  }

  outputFile << "Block,Zip Code\n";
  string line;
  getline( inputFile, line );
  line = "";
  while ( getline( inputFile, line ) ) {
    if ( line.empty() ) continue;

    // Check if the line contains a colon; if not, skip it
    size_t colonPos = line.find( ':' );
    if ( colonPos == string::npos ) {
      // If no colon, perform additional validation
      vector<string> fields = split( line, ',' );
      if ( fields.size() < 2 || !isdigit( fields[ 0 ][ 0 ] ) ) {
        // Skip malformed lines
        continue;
      }
    }
    else {
      // Process lines with valid block:data format
      string block = line.substr( 0, colonPos ); // Block number
      string data = line.substr( colonPos + 1 ); // Rest of the data

      // Split data into fields
      vector<string> fields = split( data, ',' );

      // Extract zip codes (skip 5 fields for each)
      for ( size_t i = 0; i < fields.size(); i += 6 ) {
        if ( !fields[ i ].empty() && isdigit( fields[ i ][ 0 ] ) ) {
          string zipCode = fields[ i ];
          outputFile << zipCode << " " << block << "\n";
        }
      }
    }
  }

  inputFile.close();
  outputFile.close();

  cout << "Data successfully organized and saved to '" << outputFileName << "'.\n";
}

