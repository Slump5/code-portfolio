// CSCI 331 Group Project - Copyright © 2024 Blocked Sequence Set Zip Code Processing System
#include "Block.h"
#include "Index.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Main function to interactively manage blocks.
 * 
 * This function provides an interactive menu-driven interface for managing and querying blocks. 
 * It performs the following steps:
 * 
 * 1. Creates a block file from an input CSV file.
 * 2. Parses the block file to populate the global `blocks` map.
 * 3. Enters an infinite loop providing the user with the following options:
 *    - Dump all blocks in physical order.
 *    - Dump all blocks in logical order.
 *    - Query a specific block by its RBN.
 *    - Exit the program.
 * 
 * The user can query the details of a specific block by entering its RBN, including
 * availability, records, and predecessor/successor RBNs.
 * 
 * @return int Exit code. Returns 0 if successful.
 */
int main() {
    string inputFile = "us_postal_codes.csv";
    string outputFile = "block.txt";

    // Step 1: Create the block file from the input CSV
    if (createBlockFile(inputFile, outputFile)) {
        cout << "Block file created successfully.\n";
    } else {
        cerr << "Failed to create block file.\n";
        return 1;
    }

    Index index;
    index.processBlockData( outputFile, "index.idx" );
    // Step 2: Parse the block file to populate the global blocks map
    parseBlockFile(outputFile);

    // Step 3: Enter an infinite loop to provide a user menu
    while (true) {
        cout << "\n===== Block Management Menu =====\n";
        cout << "1. Dump Blocks in Physical Order\n";
        cout << "2. Dump Blocks in Logical Order\n";
        cout << "3. Query a Block by RBN\n";
		cout << "4. Get the most of each state.\n";
		cout << "5. Search for several zip codes.\n";
        cout << "6. Exit\n";
		
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n----- Physical Order Dump -----\n";
                dumpPhysicalOrder();
                break;

            case 2:
                cout << "\n----- Logical Order Dump -----\n";
                dumpLogicalOrder();
                break;

            case 3: {
                cout << "\nEnter the RBN of the block you want to query: ";
                int RBN;
                cin >> RBN;

                if (blocks.find(RBN) != blocks.end()) {
                    const Block& block = blocks[RBN];
                    cout << "\nDetails of Block RBN " << RBN << ":\n";
                    cout << "Available: " << (block.isAvailable ? "Yes" : "No") << "\n";
                    cout << "Records: ";
                    for (const string& record : block.records) {
                        cout << record << " ";
                    }
                    cout << "\nPredecessor RBN: " << RBN-1 << "\n";
                    cout << "Successor RBN: " << RBN+1 << "\n";
                } else {
                    cout << "\nError: Block with RBN " << RBN << " not found.\n";
                }
                break;
            }
			
			case 4: {
				listMost();
                cout << "\n----- State Most Data -----\n";
                break;
            }
			
			
			case 5: {
				cout << "Please enter the zip codes you want!" << endl;
		std::string text;
		cin >> text;
		auto result = splitZipLine(text);
		for (const auto& str : result) {
		search(str, "index.idx");
    }
		break;
			}

            case 6:{
                cout << "Exiting the program. Goodbye!\n";
                return 0;
			}

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
