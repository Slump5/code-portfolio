// Thomas Hoerger - Copyright © 2024 File Input Validation Program

#include <iostream>
#include <fstream>

using namespace std;

// Function to read integers from file, verifying non-decreasing order
void readAndVerify(ifstream &infile, int A[], int size) {
    int index = 0;
    int previous_num, next_num;

    // Prime the loop
    if (infile >> previous_num) {
        A[index++] = previous_num;
    }

    // No short-circuit evaluation version
    while (true) {
        if (!(infile >> next_num)) {
            cout << "Reached end of file.\n";
            break;
        }

        if (index >= size) {
            cout << "Array is full.\n";
            break;
        }

        if (previous_num > next_num) {
            cout << "Encountered out-of-order item.\n";
            break;
        }

        A[index++] = next_num;
        previous_num = next_num;
    }

    // Print array elements
    cout << "Array elements: ";
    for (int i = 0; i < index; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main() {
    // Test case 1: End of file
    {
        ifstream infile("end_of_file.txt");
        const int size = 5;
        int A[size];

        cout << "Test case: End of file\n";
        readAndVerify(infile, A, size);

        infile.close();
        cout << endl;
    }

    // Test case 2: Item out of order
    {
        ifstream infile("out_of_order.txt");
        const int size = 5;
        int A[size];

        cout << "Test case: Item out of order\n";
        readAndVerify(infile, A, size);

        infile.close();
        cout << endl;
    }

    // Test case 3: End of array
    {
        ifstream infile("end_of_array.txt");
        const int size = 5;
        int A[size];

        cout << "Test case: End of array\n";
        readAndVerify(infile, A, size);

        infile.close();
        cout << endl;
    }

    return 0;
}
