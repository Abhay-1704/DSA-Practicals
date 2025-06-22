/*Problem-10 Code
Roll-No :- co23306
Name :- Abhay Pratap Singh
Cse, 2nd Year*/

#include <bits/stdc++.h>
using namespace std;

struct Employee {
    int key;             // Unique 4-digit key for each employee
    string name;
    int age;
    string gender;
    string phoneNumber;
    string email;
    string qualification;

    // Default constructor for initialization
    Employee() : key(0), age(0) {}
};

// HashTable Class
class HashTable {
private:
    vector<Employee> table;
    int M; // Number of slots in the hash table

    // Hash function using remainder method (K % M)
    int hashFunction(int key) {
        return key % M;
    }

public:
    // Constructor to initialize hash table with size M
    HashTable(int size) : M(size) {
        table.resize(M);  // Resize vector to M slots
    }

    // Insert an employee record into the hash table
    void insert(const Employee& emp) {
        int index = hashFunction(emp.key);
        int originalIndex = index;

        // Linear probing to handle collisions
        while (table[index].key != 0) { // 0 means the slot is empty
            if (table[index].key == emp.key) {
                cout << "Duplicate key! Employee with key " << emp.key << " already exists." << endl;
                return;  // Return early if key already exists
            }
            index = (index + 1) % M;
            if (index == originalIndex) {
                cout << "Hash Table is full!" << endl;
                return;
            }
        }
        table[index] = emp;
    }

    // Search for an employee by key
    Employee* search(int key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].key != 0) {
            if (table[index].key == key) {
                return &table[index];
            }
            index = (index + 1) % M;
            if (index == originalIndex) {
                break;
            }
        }
        return nullptr;  // Employee not found
    }

    // Delete an employee record by key
    void deleteRecord(int key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].key != 0) {
            if (table[index].key == key) {
                table[index].key = 0;  // Set the slot to empty
                cout << "Employee with key " << key << " deleted." << endl;
                return;
            }
            index = (index + 1) % M;
            if (index == originalIndex) {
                break;
            }
        }
        cout << "Employee with key " << key << " not found!" << endl;
    }

    // Update an existing employee's record
    void update(int key, const Employee& updatedEmp) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].key != 0) {
            if (table[index].key == key) {
                table[index] = updatedEmp;  // Update employee details
                cout << "Employee with key " << key << " updated." << endl;
                return;
            }
            index = (index + 1) % M;
            if (index == originalIndex) {
                break;
            }
        }
        cout << "Employee with key " << key << " not found!" << endl;
    }

    // Display the hash table
    void display() {
        for (int i = 0; i < M; i++) {
            if (table[i].key != 0) {
                // Print employee details
                cout << "Index " << i << ": " 
                     << table[i].key << " " 
                     << table[i].name << " " 
                     << table[i].age << " "
                     << table[i].gender << " "
                     << table[i].phoneNumber << " "
                     << table[i].email << " "
                     << table[i].qualification << endl;
            } else {
                // Print "empty" for unused slots
                cout << "Index " << i << ": empty" << endl;
            }
        }
    }

    // Load employees from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Failed to open file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Employee emp;
            ss >> emp.key;
            ss.ignore();  // Ignore space after key
            getline(ss, emp.name, '\t');
            ss >> emp.age;
            ss.ignore();  // Ignore space after age
            getline(ss, emp.gender, '\t');
            getline(ss, emp.phoneNumber, '\t');
            getline(ss, emp.email, '\t');
            getline(ss, emp.qualification);

            insert(emp); // Insert the employee into the hash table
        }

        file.close();
        cout << "Employees loaded from file successfully!" << endl;
    }
};

// Function to prompt user to enter employee details and ensure the key is not a duplicate
Employee enterEmployeeDetails(HashTable& ht) {
    Employee emp;
    cout << "Enter employee details:" << endl;
    
    // Ensure the key is a 4-digit number and not already in the hash table
    do {
        cout << "Employee Key (4-digit number): ";
        cin >> emp.key;

        // Check if the key exists in the hash table
        if (ht.search(emp.key)) {
            cout << "Duplicate key! Employee with key " << emp.key << " already exists. Please enter a different key." << endl;
        } else if (emp.key < 1000 || emp.key > 9999) {
            cout << "Invalid input! Please enter a 4-digit key." << endl;
        } else {
            break; // Valid key and no duplicates
        }
    } while (true);  // Repeat until valid key is entered

    cin.ignore();  // Ignore the newline character after the key input

    cout << "Name: ";
    getline(cin, emp.name);
    cout << "Age: ";
    cin >> emp.age;
    cin.ignore();  // Ignore the newline after age input
    cout << "Gender (M/F): ";
    getline(cin, emp.gender);
    cout << "Phone Number: ";
    getline(cin, emp.phoneNumber);
    cout << "Email: ";
    getline(cin, emp.email);
    cout << "Qualification: ";
    getline(cin, emp.qualification);
    return emp;
}

int main() {
    // Step 1: Get the size of the hash table from the user
    int M;
    cout << "Enter the size of the hash table: ";
    cin >> M;

    // Step 2: Create a hash table with size M
    HashTable ht(M);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Employee Manually\n";
        cout << "2. Load Employees from File\n";
        cout << "3. Search Employee\n";
        cout << "4. Update Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Display Hash Table\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore the newline character after choice input

        switch (choice) {
            case 1: {
                // Insert employee manually
                Employee emp = enterEmployeeDetails(ht);  // Pass hash table to check for duplicate keys
                ht.insert(emp);
                break;
            }
            case 2: {
                // Load employees from file
                ht.loadFromFile("EMP.dat");
                break;
            }
            case 3: {
                // Search employee by key
                int keyToSearch;
                cout << "Enter the employee key to search: ";
                cin >> keyToSearch;
                Employee* emp = ht.search(keyToSearch);
                if (emp) {
                    cout << "\nFound employee with key " << keyToSearch << ": " 
                         << emp->name << " " << emp->age << " "
                         << emp->gender << " " << emp->phoneNumber << " "
                         << emp->email << " " << emp->qualification << endl;
                } else {
                    cout << "Employee with key " << keyToSearch << " not found!" << endl;
                }
                break;
            }
            case 4: {
                // Update employee details
                int keyToUpdate;
                cout << "Enter the employee key to update: ";
                cin >> keyToUpdate;
                Employee updatedEmp = enterEmployeeDetails(ht);  // Pass hash table to check for duplicate keys
                ht.update(keyToUpdate, updatedEmp);
                break;
            }
            case 5: {
                // Delete employee
                int keyToDelete;
                cout << "Enter the employee key to delete: ";
                cin >> keyToDelete;
                ht.deleteRecord(keyToDelete);
                break;
            }
            case 6: {
                // Display the hash table
                cout << "\nHash Table Contents:" << endl;
                ht.display();
                break;
            }
            case 7:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}