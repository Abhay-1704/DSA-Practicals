/*Roll No:- CO23306, CSE
Name :- Abhay Pratap Singh*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <windows.h>
#include <conio.h>
#include <limits>
#include <iomanip>

using namespace std;

const size_t MAX_LENGTH = 20; // Maximum length for each field

struct Node {
    long long int aadhar;
    char name[MAX_LENGTH];
    char gender[MAX_LENGTH];
    char fatherName[MAX_LENGTH];
    char motherName[MAX_LENGTH];
    char dob[MAX_LENGTH];
    Node* next;
    Node* prev;

    Node(long long int aadhar = 0, const char* name = "", const char* gender = "", const char* fatherName = "", const char* motherName = "", const char* dob = "")
        : aadhar(aadhar), next(nullptr), prev(nullptr) {
        strncpy(this->name, name, MAX_LENGTH);
        strncpy(this->gender, gender, MAX_LENGTH);
        strncpy(this->fatherName, fatherName, MAX_LENGTH);
        strncpy(this->motherName, motherName, MAX_LENGTH);
        strncpy(this->dob, dob, MAX_LENGTH);
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    string filename;

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    void saveToFile() {
        ofstream file(filename, ios::binary);
        if (!file) {
            cout << "Error opening file for writing!" << endl;
            return;
        }
        Node* current = head;
        while (current) {
            file.write(reinterpret_cast<const char*>(&current->aadhar), sizeof(current->aadhar));
            file.write(current->name, MAX_LENGTH);
            file.write(current->gender, MAX_LENGTH);
            file.write(current->fatherName, MAX_LENGTH);
            file.write(current->motherName, MAX_LENGTH);
            file.write(current->dob, MAX_LENGTH);

            current = current->next;
        }
    }

    void loadFromFile() {
        ifstream file(filename, ios::binary);
        if (!file) {
            cout << "Error opening file for reading!" << endl;
            return;
        }

        clear(); // Clear existing list
        while (file) {
            long long int aadhar;
            char name[MAX_LENGTH];
            char gender[MAX_LENGTH];
            char fatherName[MAX_LENGTH];
            char motherName[MAX_LENGTH];
            char dob[MAX_LENGTH];

            file.read(reinterpret_cast<char*>(&aadhar), sizeof(aadhar));
            file.read(name, MAX_LENGTH);
            file.read(gender, MAX_LENGTH);
            file.read(fatherName, MAX_LENGTH);
            file.read(motherName, MAX_LENGTH);
            file.read(dob, MAX_LENGTH);

            // Check if the read operation was successful
            if (file.gcount() >= sizeof(aadhar)) {
                // Ensure the file is not at the end and data is valid
                insertRecord(aadhar, name, gender, fatherName, motherName, dob);
            }
        }
    }

public:
    bool isDuplicate(long long int aadhar) {
        Node* current = head;
        while (current) {
            if (current->aadhar == aadhar) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool isValidAadhar(long long int aadhar) {
        int count = 0;
        while (aadhar) {
            count++;
            aadhar /= 10;
        }
        return count == 12;
    }
    
    // Utility function to check if a string is a valid digit
    bool isDigitString(const char* str) {
        for (int i = 0; str[i]; i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    // Utility function to check if a year is a leap year
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // Utility function to validate the date of birth
    bool isValidDate(const char* dob) {
        if (strlen(dob) != 10) {
            return false; // Must be exactly 10 characters
        }

        // Check the format
        if (dob[2] != '-' || dob[5] != '-') {
            return false; // Hyphens should be at positions 2 and 5
        }

        // Extract day, month, and year parts
        char day[3], month[3], year[5];
        strncpy(day, dob, 2);
        day[2] = '\0';
        strncpy(month, dob + 3, 2);
        month[2] = '\0';
        strncpy(year, dob + 6, 4);
        year[4] = '\0';

        // Validate the extracted parts
        if (!isDigitString(day) || !isDigitString(month) || !isDigitString(year)) {
            return false; // All parts must be digits
        }

        int d = atoi(day);
        int m = atoi(month);
        int y = atoi(year);

        // Validate month range
        if (m < 1 || m > 12) {
            return false;
        }

        // Validate day range based on the month and year
        if (d < 1 || d > 31) {
            return false; // Days must be between 1 and 31
        }

        // Check days in month
        switch (m) {
            case 4: case 6: case 9: case 11:
                if (d > 30) return false; // April, June, September, November have 30 days
                break;
            case 2:
                if (isLeapYear(y)) {
                    if (d > 29) return false; // February has 29 days in a leap year
                } else {
                    if (d > 28) return false; // February has 28 days in a non-leap year
                }
                break;
        }

        return true;
    }
    
    DoublyLinkedList(const string& filename) : head(nullptr), tail(nullptr), filename(filename) {
        loadFromFile(); // Load data from file when the object is created
    }

    ~DoublyLinkedList() {
        saveToFile(); // Save data to file when the object is destroyed
        clear();
    }

    void insertRecord(long long int aadhar, const char* name, const char* gender, const char* fatherName, const char* motherName, const char* dob) {
        Node* newNode = new Node(aadhar, name, gender, fatherName, motherName, dob);

        if (!head) {
            head = tail = newNode;
        } else {
            Node* current = head;
            Node* previous = nullptr;

            while (current && current->aadhar < aadhar) {
                previous = current;
                current = current->next;
            }

            if (!previous) {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            } else {
                newNode->next = current;
                newNode->prev = previous;
                previous->next = newNode;
                if (current) {
                    current->prev = newNode;
                } else {
                    tail = newNode;
                }
            }
        }
    }

    void deleteRecord(long long int aadhar) {
        Node* current = head;
        while (current && current->aadhar != aadhar) {
            current = current->next;
        }

        if (!current) {
            cout << "Record not found!" << endl;
            return;
        }

        if (current->prev) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }

        if (current->next) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
        
        cout << "Record deleted successfully!" << endl;

        delete current;
    }

    void updateRecord(long long int aadhar, const char* name, const char* gender, const char* fatherName, const char* motherName, const char* dob) {
        Node* current = head;
        while (current && current->aadhar != aadhar) {
            current = current->next;
        }

        if (!current) {
            cout << "Record not found!" << endl;
            return; // Exit immediately if record is not found
        }

        // Update the record if found
        strncpy(current->name, name, MAX_LENGTH);
        strncpy(current->gender, gender, MAX_LENGTH);
        strncpy(current->fatherName, fatherName, MAX_LENGTH);
        strncpy(current->motherName, motherName, MAX_LENGTH);
        strncpy(current->dob, dob, MAX_LENGTH);

        cout << "Record updated successfully!" << endl; //Notify that the update was successful
    }

    void findRecord(long long int aadhar) {
        Node* current = head;
        while (current && current->aadhar != aadhar) {
            current = current->next;
        }

        if (!current) {
            cout << "Record not found!" << endl;
            return;
        }

        cout << "Aadhaar: " << current->aadhar << endl;
        cout << "Name: " << current->name << endl;
        cout << "Gender: " << current->gender << endl;
        cout << "Father's Name: " << current->fatherName << endl;
        cout << "Mother's Name: " << current->motherName << endl;
        cout << "Date of Birth: " << current->dob << endl;
    }

    void generateReport(long long int aadhar) {
        findRecord(aadhar); // Report is essentially the same as finding a record
    }

    void partialReport(const char* attribute, const char* value) {
        Node* current = head;
        while (current) {
            bool match = false;
            if (strcmp(attribute, "name") == 0 && strcmp(current->name, value) == 0) {
                match = true;
            } else if (strcmp(attribute, "gender") == 0 && strcmp(current->gender, value) == 0) {
                match = true;
            } else if (strcmp(attribute, "fatherName") == 0 && strcmp(current->fatherName, value) == 0) {
                match = true;
            } else if (strcmp(attribute, "motherName") == 0 && strcmp(current->motherName, value) == 0) {
                match = true;
            } else if (strcmp(attribute, "dob") == 0 && strcmp(current->dob, value) == 0) {
                match = true;
            }

            if (match) {
                cout << "Aadhaar: " << current->aadhar << endl;
                cout << "Name: " << current->name << endl;
                cout << "Gender: " << current->gender << endl;
                cout << "Father's Name: " << current->fatherName << endl;
                cout << "Mother's Name: " << current->motherName << endl;
                cout << "Date of Birth: " << current->dob << endl;
                cout << "--------------------" << endl;
            }

            current = current->next;
        }
    }

    void displayAllRecords() {
        Node* current = head;
    
        // Print table header
        cout << left << setw(20) << "Aadhaar" << setw(30) << "Name" << endl;
        cout << string(50, '-') << endl; // Print a line separator

        while (current) {
            cout << left << setw(20) << current->aadhar << setw(30) << current->name << endl;
            current = current->next;
        }
    }
};

int main() {
    string filename = "records.bin";
    DoublyLinkedList db(filename);

    int choice;
    long long int aadhar;
    char name[MAX_LENGTH], gender[MAX_LENGTH], fatherName[MAX_LENGTH], motherName[MAX_LENGTH], dob[11], attribute[MAX_LENGTH], value[MAX_LENGTH];

    do {
        system("cls");
        cout << "1. Insert Record" << endl;
        cout << "2. Delete Record" << endl;
        cout << "3. Update Record" << endl;
        cout << "4. Find Record" << endl;
        cout << "5. Generate Report by Aadhaar Card Number" << endl;
        cout << "6. Generate Partial Report" << endl;
        cout << "7. Display All Records" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";

        // Validate input choice
        while (!(cin >> choice) || choice < 1 || choice > 8) {
            cout << "Invalid choice! Please enter a number between 1 and 8: ";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter Aadhaar Card Number (12 digits): ";
                cin >> aadhar;
                cin.ignore();
                while (!db.isValidAadhar(aadhar) || db.isDuplicate(aadhar)) {
                    if (!db.isValidAadhar(aadhar)) {
                        cout << "Invalid Aadhaar number! Must be a 12-digit number." << endl;
                    } else if (db.isDuplicate(aadhar)) {
                        cout << "Record with this Aadhaar number already exists!" << endl;
                    }
                    cout << "Enter a valid Aadhaar Card Number (12 digits): ";
                    cin >> aadhar;
                    cin.ignore();
                }
                cout << "Enter Name: ";
                cin.getline(name, MAX_LENGTH);
                
                // Gender input validation
                while (true) {
                    cout << "Enter Gender (Male/Female/Other): ";
                    cin.getline(gender, MAX_LENGTH);
                    if (strcmp(gender, "Male") == 0 || strcmp(gender, "Female") == 0 || strcmp(gender, "Other") == 0) {
                        break; // Exit loop if gender is valid
                    } else {
                        cout << "Invalid Gender! Please enter Male, Female, or Other." << endl;
                    }
                }

                cout << "Enter Father's Name: ";
                cin.getline(fatherName, MAX_LENGTH);
                cout << "Enter Mother's Name: ";
                cin.getline(motherName, MAX_LENGTH);
                
                while (true) {
                    cout << "Enter Date of Birth (dd-mm-yyyy): ";
                    cin.getline(dob, 11);

                    if (db.isValidDate(dob)) {
                        break; // Exit loop if date is valid
                    } else {
                        cout << "Date of Birth is invalid. Please enter in the format dd-mm-yyyy." << endl;
                    }
                }
                db.insertRecord(aadhar, name, gender, fatherName, motherName, dob);
                break;

            case 2:
                cout << "Enter Aadhaar Card Number to delete: ";
                cin >> aadhar;
                cin.ignore();
                db.deleteRecord(aadhar);
                break;

            case 3:
                cout << "Enter Aadhaar Card Number to update: ";
                cin >> aadhar;
                if (!db.isDuplicate(aadhar)){
                    cout << "Record not found! " << endl;
                    break;
                }
                cin.ignore();
                cout << "Enter new Name: ";
                cin.getline(name, MAX_LENGTH);
                
                // Gender input validation
                while (true) {
                    cout << "Enter new Gender (Male/Female/Other): ";
                    cin.getline(gender, MAX_LENGTH);
                    if (strcmp(gender, "Male") == 0 || strcmp(gender, "Female") == 0 || strcmp(gender, "Other") == 0) {
                        break; // Exit loop if gender is valid
                    } else {
                        cout << "Invalid Gender! Please enter Male, Female, or Other." << endl;
                    }
                }

                cout << "Enter new Father's Name: ";
                cin.getline(fatherName, MAX_LENGTH);
                cout << "Enter new Mother's Name: ";
                cin.getline(motherName, MAX_LENGTH);
                
                while (true) {
                    cout << "Enter Date of Birth (dd-mm-yyyy): ";
                    cin.getline(dob, 11);

                    if (db.isValidDate(dob)) {
                        break; // Exit loop if date is valid
                    } else {
                        cout << "Date of Birth is invalid. Please enter in the format dd-mm-yyyy." << endl;
                    }
                }
                db.updateRecord(aadhar, name, gender, fatherName, motherName, dob);
                break;

            case 4:
                cout << "Enter Aadhaar Card Number to find: ";
                cin >> aadhar;
                cin.ignore();
                db.findRecord(aadhar);
                break;

            case 5:
                cout << "Enter Aadhaar Card Number for report: ";
                cin >> aadhar;
                cin.ignore();
                db.generateReport(aadhar);
                break;

            case 6:
                cout << "Enter attribute to search (name/gender/fatherName/motherName/dob): ";
                cin.getline(attribute, MAX_LENGTH);
                cout << "Enter value to search: ";
                cin.getline(value, MAX_LENGTH);
                db.partialReport(attribute, value);
                break;

            case 7:
                db.displayAllRecords();
                break;

            case 8:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
        cout << "Press any key to continue...";
        getch();
    } while (choice != 8);

    return 0;
}