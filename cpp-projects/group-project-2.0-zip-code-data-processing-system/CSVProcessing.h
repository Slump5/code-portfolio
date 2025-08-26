// CSCI 331 Group Project - Copyright © 2024 Zip Code Data Processing System
#ifndef CSVProcessing_H
#define CSVProcessing_H

#include "buffer.h"
#include <iostream>
#include <fstream>
#include <string>
#include "HeaderBuffer.h"

using namespace std;

class CSVProcessing {
public:
    /**
     * @brief Sorts the CSV buffer and finds the zip codes (eastmost, westmost, northmost, southmost) for each state.
     *
     * This method reads the CSV data, processes it to identify the easternmost, westernmost, northernmost,
     * and southernmost zip codes for each state, and then stores these in a map (automatically sorts alphebetically).
     *
     * @return A map where the key is the state ID and the value is a vector containing the four ZipCodeRecord. The output looks as follows:
     * [stateID] : {
            { east most zip, stateID, Cords },
            { west most zip, stateID, Cords },
            { northern most zip, stateID, Cords },
            { southern most zip, stateID, Cords }
        }
    *
    */
    map<string, vector<ZipCodeRecord>> sortBuffer(); // sort by state with the hashmap but how once it is sorted we can do the direction farthest zip
    // we could also set up a const variable that will have the state ids based on their index/hasmap key and with that we can instantlly find where the zip should go
    //void printZipCodeRecord( const ZipCodeRecord& record ); for testing purposes
    /**
     * @brief Creates and adds a header to the CSV file.
     *
     * This function adds a header row to the specified CSV file. The header includes
     * columns for State, Easternmost, Westernmost, Northernmost, and Southernmost zip codes.
     *
     * @param file_name The name of the CSV file to which the header will be added.
     */
    void addHeader( string& file_name ); // state id, Easternmost (least longitude), Westernmost, Northernmost (greatest latitude), and Southernmost Zip Code
    /**
     * @brief Outputs the processed zip code data to a CSV file.
     *
     * This function takes the sorted buffer of zip code records and writes them to a CSV file.
     * Each row contains the state ID and the zip codes for the easternmost, westernmost,
     * northernmost, and southernmost points in that state.
     *
     * @param file_name The name of the CSV file to which the data will be written.
     * @return true if the data was successfully written to the file, false otherwise.
     */
    bool csvOutput( string& file_name ); // fill from the sortered buffer? either output as we go from the buffer or create an array or vector to put all the sorting and then output to the csv
};

#endif