/*Roll No :- CO23306
Name :- Abhay Pratap Singh*/
#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

const int MAX_SIZE = 100;

// Bubble Sort
template <typename T>
void bubbleSort(T A[], int size) {
    if (size <= 0) {
        cout << "Output Underflow! Empty data" << endl;
        return;
    }
    for (int i = 0; i < size - 1; i++) {
        T temp;
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; j++) {
            if (A[j] > A[j + 1]) {
                temp = A[j + 1];
                A[j + 1] = A[j];
                A[j] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// Insertion Sort
template <typename T>
void insertionSort(T A[], int size) {
    for (int i = 1; i < size; i++) {
        T key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

// Selection Sort
template <typename T>
void selectionSort(T A[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (A[minIndex] > A[j]) {
                minIndex = j;
            }
        }
        T temp = A[i];
        A[i] = A[minIndex];
        A[minIndex] = temp;
    }
}

// Quick Sort
template <typename T>
int partition(T A[], int low, int high) {
    T pivot = A[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[high]);
    return (i + 1);
}

template <typename T>
void quickSort(T A[], int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);
        quickSort(A, low, pi - 1);
        quickSort(A, pi + 1, high);
    }
}

// Radix Sort
template <typename T>
void radixSort(T A[], int size) {
    T max = A[0];
    for (int i = 1; i < size; i++) {
        if (A[i] > max) {
            max = A[i];
        }
    }
    for (T place = 1; max / place > 0; place *= 10) {
        int output[size];
        int count[10] = {0};
        for (int i = 0; i < size; i++) {
            int index = (A[i] / place) % 10;
            count[index]++;
        }
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (int i = size - 1; i >= 0; i--) {
            int index = (A[i] / place) % 10;
            output[count[index] - 1] = A[i];
            count[index]--;
        }
        for (int i = 0; i < size; i++) {
            A[i] = output[i];
        }
    }
}

// Read file
template <typename T>
void readFile(const string& filename, T A[], int& size) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        ofstream createFile(filename);
        createFile.close();
        cout << "File created: " << filename << endl;
        return;
    }
    while (size < MAX_SIZE && inFile >> A[size]) {
        size++;
    }
    inFile.close();
}

// Write file
template <typename T>
void writeFile(const string& filename, T A[], int size) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Unable to open file for writing: " << filename << endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        outFile << A[i] << " ";
    }
    outFile.close();
}

// Search functions
template <typename T>
int linearSearch(T A[], int size, T key) {
    for (int i = 0; i < size; i++) {
        if (A[i] == key) {
            return i; // Return the index where key is found
        }
    }
    return -1; // Return -1 if not found
}

template <typename T>
int binarySearch(T A[], int size, T key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (A[mid] == key) {
            return mid; // Return the index where key is found
        }
        if (A[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Return -1 if not found
}

// Function to get user input manually
template <typename T>
void inputDataManually(T A[], int& size) {
    cout << "Enter number of elements: ";
    cin >> size;
    cout << "Enter " << size << " elements:" << endl;
    for (int i = 0; i < size; i++) {
        cin >> A[i];
    }
}

void sortIntegers() {
    int intArray[MAX_SIZE];
    int intSize = 0;
    int choice;

    cout << "Choose input method:\n1. Load from file\n2. Enter manually\n";
    cin >> choice;

    if (choice == 1) {
        readFile("int_input.txt", intArray, intSize);
    } else {
        inputDataManually(intArray, intSize);
    }

    cout << "Choose a sorting algorithm:\n";
    cout << "1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n4. Radix Sort\n5. Quick Sort\n";
    cin >> choice;

    switch (choice) {
        case 1: bubbleSort(intArray, intSize); break;
        case 2: insertionSort(intArray, intSize); break;
        case 3: selectionSort(intArray, intSize); break;
        case 4: radixSort(intArray, intSize); break;
        case 5: quickSort(intArray, 0, intSize - 1); break;
        default: cout << "Invalid choice." << endl; return;
    }

    cout << "Sorted integers: ";
    for (int i = 0; i < intSize; i++) {
        cout << intArray[i] << " ";
    }
    cout << endl;
    writeFile("int_output.txt", intArray, intSize);
}

void sortStrings() {
    string strArray[MAX_SIZE];
    int strSize = 0;
    int choice;

    cout << "Choose input method:\n1. Load from file\n2. Enter manually\n";
    cin >> choice;

    if (choice == 1) {
        readFile("str_input.txt", strArray, strSize);
    } else {
        inputDataManually(strArray, strSize);
    }

    cout << "Choose a sorting algorithm:\n";
    cout << "1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n4. Quick Sort\n";
    cin >> choice;

    switch (choice) {
        case 1: bubbleSort(strArray, strSize); break;
        case 2: insertionSort(strArray, strSize); break;
        case 3: selectionSort(strArray, strSize); break;
        case 4: quickSort(strArray, 0, strSize - 1); break;
        default: cout << "Invalid choice." << endl; return;
    }

    cout << "Sorted strings: ";
    for (int i = 0; i < strSize; i++) {
        cout << strArray[i] << " ";
    }
    cout << endl;
    writeFile("str_output.txt", strArray, strSize);
}

void sortDecimals() {
    double doubleArray[MAX_SIZE];
    int doubleSize = 0;
    int choice;

    cout << "Choose input method:\n1. Load from file\n2. Enter manually\n";
    cin >> choice;

    if (choice == 1) {
        readFile("double_input.txt", doubleArray, doubleSize);
    } else {
        inputDataManually(doubleArray, doubleSize);
    }

    cout << "Choose a sorting algorithm:\n";
    cout << "1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n4. Quick Sort\n";
    cin >> choice;

    switch (choice) {
        case 1: bubbleSort(doubleArray, doubleSize); break;
        case 2: insertionSort(doubleArray, doubleSize); break;
        case 3: selectionSort(doubleArray, doubleSize); break;
        case 4: quickSort(doubleArray, 0, doubleSize - 1); break;
        default: cout << "Invalid choice." << endl; return;
    }

    cout << "Sorted decimals: ";
    for (int i = 0; i < doubleSize; i++) {
        cout << doubleArray[i] << " ";
    }
    cout << endl;
    writeFile("double_output.txt", doubleArray, doubleSize);
}

void sortCharacters() {
    char charArray[MAX_SIZE];
    int charSize = 0;
    int choice;

    cout << "Choose input method:\n1. Load from file\n2. Enter manually\n";
    cin >> choice;

    if (choice == 1) {
        readFile("char_input.txt", charArray, charSize);
    } else {
        inputDataManually(charArray, charSize);
    }

    cout << "Choose a sorting algorithm:\n";
    cout << "1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n4. Quick Sort\n";
    cin >> choice;

    switch (choice) {
        case 1: bubbleSort(charArray, charSize); break;
        case 2: insertionSort(charArray, charSize); break;
        case 3: selectionSort(charArray, charSize); break;
        case 4: quickSort(charArray, 0, charSize - 1); break;
        default: cout << "Invalid choice." << endl; return;
    }

    cout << "Sorted characters: ";
    for (int i = 0; i < charSize; i++) {
        cout << charArray[i] << " ";
    }
    cout << endl;
    writeFile("char_output.txt", charArray, charSize);
}

void searchIntegers() {
    int intArray[MAX_SIZE];
    int intSize = 0;
    int choice;

    readFile("int_input.txt", intArray, intSize);

    cout << "Enter the integer to search: ";
    int key;
    cin >> key;

    cout << "Choose a search algorithm:\n";
    cout << "1. Linear Search\n2. Binary Search (requires sorted input)\n";
    cin >> choice;

    int index = -1;
    switch (choice) {
        case 1: index = linearSearch(intArray, intSize, key); break;
        case 2:
            bubbleSort(intArray, intSize); // Ensure it's sorted
            index = binarySearch(intArray, intSize, key); break;
        default: cout << "Invalid choice." << endl; return;
    }

    if (index != -1) {
        cout << "Integer found at index: " << index << endl;
    } else {
        cout << "Integer not found." << endl;
    }
}

void searchStrings() {
    string strArray[MAX_SIZE];
    int strSize = 0;
    int choice;

    readFile("str_input.txt", strArray, strSize);

    cout << "Enter the string to search: ";
    string key;
    cin >> key;

    cout << "Choose a search algorithm:\n";
    cout << "1. Linear Search\n2. Binary Search (requires sorted input)\n";
    cin >> choice;

    int index = -1;
    switch (choice) {
        case 1: index = linearSearch(strArray, strSize, key); break;
        case 2:
            bubbleSort(strArray, strSize); // Ensure it's sorted
            index = binarySearch(strArray, strSize, key); break;
        default: cout << "Invalid choice." << endl; return;
    }

    if (index != -1) {
        cout << "String found at index: " << index << endl;
    } else {
        cout << "String not found." << endl;
    }
}

void searchDecimals() {
    double doubleArray[MAX_SIZE];
    int doubleSize = 0;
    int choice;

    readFile("double_input.txt", doubleArray, doubleSize);

    cout << "Enter the decimal to search: ";
    double key;
    cin >> key;

    cout << "Choose a search algorithm:\n";
    cout << "1. Linear Search\n2. Binary Search (requires sorted input)\n";
    cin >> choice;

    int index = -1;
    switch (choice) {
        case 1: index = linearSearch(doubleArray, doubleSize, key); break;
        case 2:
            bubbleSort(doubleArray, doubleSize); // Ensure it's sorted
            index = binarySearch(doubleArray, doubleSize, key); break;
        default: cout << "Invalid choice." << endl; return;
    }

    if (index != -1) {
        cout << "Decimal found at index: " << index << endl;
    } else {
        cout << "Decimal not found." << endl;
    }
}

void searchCharacters() {
    char charArray[MAX_SIZE];
    int charSize = 0;
    int choice;

    readFile("char_input.txt", charArray, charSize);

    cout << "Enter the character to search: ";
    char key;
    cin >> key;

    cout << "Choose a search algorithm:\n";
    cout << "1. Linear Search\n2. Binary Search (requires sorted input)\n";
    cin >> choice;

    int index = -1;
    switch (choice) {
        case 1: index = linearSearch(charArray, charSize, key); break;
        case 2:
            bubbleSort(charArray, charSize); // Ensure it's sorted
            index = binarySearch(charArray, charSize, key); break;
        default: cout << "Invalid choice." << endl; return;
    }

    if (index != -1) {
        cout << "Character found at index: " << index << endl;
    } else {
        cout << "Character not found." << endl;
    }
}

int main() {
    int choice;
    do {
        system("cls");
        cout << "Main Menu:\n";
        cout << "1. Sort Data\n";
        cout << "2. Search Data\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1: { // Sorting
                int sortChoice;
                cout << "Choose data type to sort:\n";
                cout << "1. Integers\n2. Strings\n3. Decimals\n4. Characters\n";
                cout << "Enter your choice: ";
                cin >> sortChoice;

                switch (sortChoice) {
                    case 1: sortIntegers(); break;
                    case 2: sortStrings(); break;
                    case 3: sortDecimals(); break;
                    case 4: sortCharacters(); break;
                    default: cout << "Invalid choice. Please try again." << endl; break;
                }
                break;
            }
            case 2: { // Searching
                int searchChoice;
                cout << "Choose data type to search:\n";
                cout << "1. Integers\n2. Strings\n3. Decimals\n4. Characters\n";
                cout << "Enter your choice: ";
                cin >> searchChoice;

                switch (searchChoice) {
                    case 1: searchIntegers(); break;
                    case 2: searchStrings(); break;
                    case 3: searchDecimals(); break;
                    case 4: searchCharacters(); break;
                    default: cout << "Invalid choice. Please try again." << endl; break;
                }
                break;
            }
            case 3:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout << "Press any key to continue!";
        getch();
    } while (choice != 3);

    return 0;
}
