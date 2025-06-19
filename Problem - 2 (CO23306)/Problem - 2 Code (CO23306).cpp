#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int SIZE = 100;

struct Address 
{
    string houseno;
    string street;
    string city;
    string state;
    string country;
};

struct Record 
{
    string roll_no;
    string name;
    int age;
    string f_name;
    string m_name;
    string Class;
    string semester;
    string branch;
    Address addr;
};

Record S_DB[SIZE];
int Lindex = 0; // to keep track of the number of records

void logFile(const string &message, const Record &rd = {}) 
{
    ofstream log("student_database.log", ios_base::app);
    log << message << endl;
    if (!rd.roll_no.empty()) {
        log << "Roll Number: " << rd.roll_no << endl;
        log << "Name: " << rd.name << endl;
        log << "Age: " << rd.age << endl;
        log << "Father's Name: " << rd.f_name << endl;
        log << "Mother's Name: " << rd.m_name << endl;
        log << "Class: " << rd.Class << endl;
        log << "Semester: " << rd.semester << endl;
        log << "Branch: " << rd.branch << endl;
        log << "Address: " << 
		rd.addr.houseno << 
		", " << rd.addr.street << 
		", " << rd.addr.city << 
		", " << rd.addr.state << 
		", " << rd.addr.country << endl <<"\n";
    }
    log.close();
}

void inputRecord(Record &rd) 
{
    cout << "\nInput Student Roll Number: ";
    getline(cin, rd.roll_no);
    cout << "Enter Student Name: ";
    getline(cin, rd.name);
    cout << "Enter Age: ";
    cin >> rd.age;
    cin.ignore();
    cout << "Enter Father's Name: ";
    getline(cin, rd.f_name);
    cout << "Enter Mother's Name: ";
    getline(cin, rd.m_name);
    cout << "Enter Class: ";
    getline(cin, rd.Class);
    cout << "Enter Semester: ";
    getline(cin, rd.semester);
    cout << "Enter Branch: ";
    getline(cin, rd.branch);
    cout << "Enter House No: ";
    getline(cin, rd.addr.houseno);
    cout << "Enter Street: ";
    getline(cin, rd.addr.street);
    cout << "Enter City: ";
    getline(cin, rd.addr.city);
    cout << "Enter State: ";
    getline(cin, rd.addr.state);
    cout << "Enter Country: ";
    getline(cin, rd.addr.country);
}

void addRecord() 
{
    if (Lindex >= SIZE) 
	{
        cout << "\nDatabase is full. Cannot add more records.\n\n";
        logFile("->Database is full. Cannot add more records.");
        return;
    }

    Record rd;
    inputRecord(rd);
    
    // Check for valid age
    if (!(rd.age >= 17 && rd.age <= 23)) 
	{
        cout << "\nInvalid age. Age must be between 17 and 23.\n\n";
        logFile("->Invalid age. Age must be between 17 and 23.");
        return;
    }

    // Check for duplicate roll number
    for (int i = 0; i < Lindex; ++i) 
	{
        if (S_DB[i].roll_no == rd.roll_no) {
            cout << "\nRoll number already exists. Cannot add duplicate record.\n\n";
            logFile("->Roll number already exists. Cannot add duplicate record.");
            return;
        }
    }

    S_DB[Lindex++] = rd;
    cout << "\nRecord added successfully.\n\n";
    logFile("->Record added successfully.", rd);
}

void deleteRecord() {
    string roll_no;
    cout << "\nEnter Roll Number to delete: ";
    getline(cin, roll_no);

    int index = -1;
    for (int i = 0; i < Lindex; ++i) 
	{
        if (S_DB[i].roll_no == roll_no) 
		{
            index = i;
            break;
        }
    }

    if (index != -1) 
	{
        Record rd = S_DB[index];
        for (int i = index; i < Lindex - 1; ++i) 
		{
            S_DB[i] = S_DB[i + 1];
        }
        --Lindex;
        cout << "\nRecord deleted successfully.\n\n";
        logFile("->Record deleted successfully.", rd);
    } else 
	{
        cout << "\nRecord not found.\n\n";
        logFile("->Record not found.");
    }
}

void displayRecord() 
{
    string roll_no;
    cout << "\nEnter Roll Number to display: ";
    getline(cin, roll_no);

    bool found = false;
    for (int i = 0; i < Lindex; ++i) 
	{
        const Record &rd = S_DB[i];
        if (rd.roll_no == roll_no) 
		{
            cout << "\nRoll Number: " << rd.roll_no << "\n";
            cout << "Name: " << rd.name << "\n";
            cout << "Age: " << rd.age << "\n";
            cout << "Father's Name: " << rd.f_name << "\n";
            cout << "Mother's Name: " << rd.m_name << "\n";
            cout << "Class: " << rd.Class << "\n";
            cout << "Semester: " << rd.semester << "\n";
            cout << "Branch: " << rd.branch << "\n";
            cout << "Address: " 
                 << rd.addr.houseno << 
                 ", " << rd.addr.street << 
                 ", " << rd.addr.city << 
                 ", " << rd.addr.state << 
                 ", " << rd.addr.country << "\n\n";
            found = true;
            logFile("->Record displayed successfully.", rd);
            break;
        }
    }
    if (!found) 
	{
        cout << "\nRecord not found.\n\n";
        logFile("->Record not found.");
    }
}

void search() 
{
    string location;
    cout << "\nSearch records by:\n";
    cout << "1. City\n";
    cout << "2. State\n";
    cout << "3. Country\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) 
	{
    case 1:
        cout << "\nEnter City: ";
        getline(cin, location);
        for (int i = 0; i < Lindex; ++i) 
		{
            if (S_DB[i].addr.city == location) 
			{
                cout << "\nRoll Number: " << S_DB[i].roll_no << "\n";
                cout << "Name: " << S_DB[i].name << "\n";
                cout << "Age: " << S_DB[i].age << "\n";
                cout << "Father's Name: " << S_DB[i].f_name << "\n";
                cout << "Mother's Name: " << S_DB[i].m_name << "\n";
                cout << "Class: " << S_DB[i].Class << "\n";
                cout << "Semester: " << S_DB[i].semester << "\n";
                cout << "Branch: " << S_DB[i].branch << "\n";
                cout << "Address: " << 
				S_DB[i].addr.houseno << 
				", " << S_DB[i].addr.street << 
				", " << S_DB[i].addr.city << 
				", " << S_DB[i].addr.state << 
				", " << S_DB[i].addr.country << "\n\n";
                logFile("->Record searched by city successfully.", S_DB[i]);
            }
        }
        break;
    case 2:
        cout << "\nEnter State: ";
        getline(cin, location);
        for (int i = 0; i < Lindex; ++i) 
		{
            if (S_DB[i].addr.state == location) 
			{
                cout << "\nRoll Number: " << S_DB[i].roll_no << "\n";
                cout << "Name: " << S_DB[i].name << "\n";
                cout << "Age: " << S_DB[i].age << "\n";
                cout << "Father's Name: " << S_DB[i].f_name << "\n";
                cout << "Mother's Name: " << S_DB[i].m_name << "\n";
                cout << "Class: " << S_DB[i].Class << "\n";
                cout << "Semester: " << S_DB[i].semester << "\n";
                cout << "Branch: " << S_DB[i].branch << "\n";
                cout << "Address: " << 
				S_DB[i].addr.houseno << 
				", " << S_DB[i].addr.street << 
				", " << S_DB[i].addr.city << 
				", " << S_DB[i].addr.state << 
				", " << S_DB[i].addr.country << "\n\n";
                logFile("->Record searched by state successfully.", S_DB[i]);
            }
        }
        break;
    case 3:
        cout << "\nEnter Country: ";
        getline(cin, location);
        for (int i = 0; i < Lindex; ++i) 
		{
            if (S_DB[i].addr.country == location) 
			{
                cout << "\nRoll Number: " << S_DB[i].roll_no << "\n";
                cout << "Name: " << S_DB[i].name << "\n";
                cout << "Age: " << S_DB[i].age << "\n";
                cout << "Father's Name: " << S_DB[i].f_name << "\n";
                cout << "Mother's Name: " << S_DB[i].m_name << "\n";
                cout << "Class: " << S_DB[i].Class << "\n";
                cout << "Semester: " << S_DB[i].semester << "\n";
                cout << "Branch: " << S_DB[i].branch << "\n";
                cout << "Address: " << 
				S_DB[i].addr.houseno << 
				", " << S_DB[i].addr.street << 
				", " << S_DB[i].addr.city << 
				", " << S_DB[i].addr.state << 
				", " << S_DB[i].addr.country << "\n\n";
                logFile("->Record searched by country successfully.", S_DB[i]);
            }
        }
        break;
    default:
        cout << "\nInvalid choice.\n\n";
        logFile("->Invalid choice in search.");
    }
}

int main() 
{
    int choice;
    while (true) 
	{
        cout << "Menu\n";
        cout << "1. Add Records\n";
        cout << "2. Delete Record\n";
        cout << "3. Display Records\n";
        cout << "4. Search Records\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character left in the buffer

        switch (choice) {
        case 1:
            addRecord();
            break;
        case 2:
            deleteRecord();
            break;
        case 3:
            displayRecord();
            break;
        case 4:
            search();
            break;
        case 5:
            logFile("->Program exited successfully.");
            return 0;
        default:
            cout << "Invalid choice. Try again.\n\n";
            logFile("->Invalid choice in main menu.");
        }
    }
    return 0;
}
