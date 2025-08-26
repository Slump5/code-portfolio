// CSCI 331 Group Project - Copyright © 2024 Zip Code Extremes Processor
#include "buffer.h"
#include "CSVProcessing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
//using namespace std;


// void CSVProcessing::printZipCodeRecord( const ZipCodeRecord& record ) {
//     std::cout << "Zip Code: " << record.zip_code
//         << ", State ID: " << record.state_id
//         << ", Latitude: " << record.latitude
//         << ", Longitude: " << record.longitude << std::endl;
// }
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
std::map<string, std::vector<ZipCodeRecord>> CSVProcessing::sortBuffer() {
    float eastMost, westMost, northMost, southMost;
    Buffer CSVBuffer;
    CSVBuffer.read_csv( );
    std::map<string, std::vector<ZipCodeRecord>> state_zip_map = CSVBuffer.get_state_zip_codes();
    std::map<string, std::vector<ZipCodeRecord>> sorted_directions;
    for ( auto& state : state_zip_map ) {
        const std::string& stateID = state.first;
        const std::vector<ZipCodeRecord>& stateInfo = state.second;
        // intial loading of directions
        ZipCodeRecord easternmost = stateInfo[ 0 ];
        ZipCodeRecord westernmost = stateInfo[ 0 ];
        ZipCodeRecord northernmost = stateInfo[ 0 ];
        ZipCodeRecord southernmost = stateInfo[ 0 ];
        // checks if the current records zip is one of the maxed directions
        for ( const auto& record : stateInfo ) {
            if ( record.longitude < easternmost.longitude ) {
                easternmost = record;
            }
            if ( record.longitude > westernmost.longitude ) {
                westernmost = record;
            }
            if ( record.latitude > northernmost.latitude ) {
                northernmost = record;
            }
            if ( record.latitude < southernmost.latitude ) {
                southernmost = record;
            }
        }
        sorted_directions[ stateID ] = { easternmost, westernmost, northernmost, southernmost };
        // std::cout << "State: " << stateID << std::endl;
        // std::cout << "  Easternmost: ";
        // printZipCodeRecord( easternmost );
        // std::cout << "  Westernmost: ";
        // printZipCodeRecord( westernmost );
        // std::cout << "  Northernmost: ";
        // printZipCodeRecord( northernmost );
        // std::cout << "  Southernmost: ";
        // printZipCodeRecord( southernmost );
        // std::cout << std::endl;  // Add an extra line for readability
    }
    // sorted_directions looks like this
    // [stateID] : {
    //     { east most zip, stateID, directions },
    //     { west most zip, stateID, directions },
    //     { northern most zip, stateID, directions },
    //     { southern most zip, stateID, directions }
    // }
    
    return sorted_directions;
}   

/**
 * @brief Creates and adds a header to the CSV file.
 * 
 * This function adds a header row to the specified CSV file. The header includes
 * columns for State, Easternmost, Westernmost, Northernmost, and Southernmost zip codes.
 * 
 * @param file_name The name of the CSV file to which the header will be added.
 */
void CSVProcessing::addHeader(std::string& file_name) {
    std::ofstream file(file_name);
    if (file.is_open()) {
        file << "State,Easternmost,Westernmost,Northernmost,Southernmost\n";
        file.close();
        std::cout << "Header added successfully to " << file_name << std::endl;
    } else {
        std::cerr << "Unable to open file: " << file_name << std::endl;
    }
}
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
bool CSVProcessing::csvOutput(std::string& file_name) {
    std::map<std::string, std::vector<ZipCodeRecord>> sorted_data = sortBuffer();
    std::ofstream file(file_name, std::ios::app);  // Open in append mode
    
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << file_name << std::endl;
        return false;
    }
    for (const auto& [state, records] : sorted_data) {
        if (records.size() == 4) {  // Ensure we have all 4 directional records
            file << state << ","
                 << records[0].zip_code << ","  // Easternmost
                 << records[1].zip_code << ","  // Westernmost
                 << records[2].zip_code << ","  // Northernmost
                 << records[3].zip_code << "\n";  // Southernmost
        }
    }
    file.close();
    std::cout << "Data successfully written to " << file_name << std::endl;
    return true;
}