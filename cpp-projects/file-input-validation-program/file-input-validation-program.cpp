// Thomas Hoerger - Copyright © 2024 File Input Validation Program

#include <iostream>
#include <fstream>
#include <climits> // Add include directive for "climits"

using namespace std;

// Function to read integers from file, verifying non-decreasing order
void readAndVerify(ifstream& infile, int A[], int size) {
    int index = 0;
    int prev = INT_MIN; // Smallest possible int

    while (index < size && infile >> A[index]) {
        if (A[index] >= prev) {
            prev = A[index];
            index++;
        } else {
            break;
        }
    }

    // Print array elements
    cout << "Array elements: ";
    for (int i = 0; i < index; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    // Print exit condition
    if (infile.eof()) {
        cout << "Reached end of file.\n";
    } else if (index == size) {
        cout << "Array is full.\n";
    } else {
        cout << "Encountered out-of-order item.\n";
    }
}

int main() {
    ifstream infile("data.txt");
    const int size = 5;
    int A[size];

    cout << "Short-circuit evaluation version:\n";
    readAndVerify(infile, A, size);

    infile.close();

    return 0;
}
