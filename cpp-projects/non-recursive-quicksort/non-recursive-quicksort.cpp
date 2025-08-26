// Thomas Hoerger - Copyright © 2024 Non-Recursive Quicksort

#include <iostream>
#include <stack>


// Function to partition the array
int partition(int arr[], int low, int high) {
    // Choose the last element as the pivot
    int pivot = arr[high];
    // Initialize the index of the smaller element
    int i = low - 1;

    // Traverse through the array and rearrange elements based on the pivot
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            // Increment the index of the smaller element and swap elements
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    // Swap the pivot to its correct position
    std::swap(arr[i + 1], arr[high]);
    // Return the index of the pivot
    return i + 1;
}

// Function to perform non-recursive Quicksort
void iterativeQuicksort(int arr[], int low, int high) {
    // Create a stack to keep track of sub-arrays
    std::stack<std::pair<int, int>> stack;
    stack.push(std::make_pair(low, high));

    // Process the stack until it becomes empty
    while (!stack.empty()) {
        // Get the boundaries of the current sub-array
        low = stack.top().first;
        high = stack.top().second;
        stack.pop();

        // Partition the current sub-array and get the pivot index
        int pivotIndex = partition(arr, low, high);

        // If there are elements on the left of the pivot, push that sub-array to the stack
        if (pivotIndex - 1 > low) {
            stack.push(std::make_pair(low, pivotIndex - 1));
        }

        // If there are elements on the right of the pivot, push that sub-array to the stack
        if (pivotIndex + 1 < high) {
            stack.push(std::make_pair(pivotIndex + 1, high));
        }
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Example array for testing
    int arr[] = {12, 4, 5, 6, 7, 3, 1, 15, 2, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Display the original array
    std::cout << "Original array: ";
    printArray(arr, size);

    // Call the non-recursive Quicksort function
    iterativeQuicksort(arr, 0, size - 1);

    // Display the sorted array
    std::cout << "Sorted array: ";
    printArray(arr, size);

    return 0;
}