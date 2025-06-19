/* Name - Abhay Pratap Singh
Roll No - CO23306
Problem - 3 Code, Data Structures*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;

// Define the structure for an employee record
struct Employee 
{
    int id;
    char name[100];
    char fatherName[100];
    char motherName[100];
    char position[100];
    char department[100];
    int doj;
    char homeNo[20];
    char street[100];
    char city[50];
    char state[50];
    char country[50];
    int pin;
    Employee* next;
};

// Function to log output in a file
void logOutput(string message, Employee* emp, string filename) 
{
    time_t now = time(0);
    char* dt = ctime(&now);
    ofstream logFile(filename.c_str(), ios_base::app);
    logFile << dt << message << endl;
    logFile << "-----------------------------" << endl;
    logFile << "Employee ID: " << emp->id << endl;
    logFile << "Name: " << emp->name << endl;
    logFile << "Father's Name: " << emp->fatherName << endl;
    logFile << "Mother's Name: " << emp->motherName << endl;
    logFile << "Position: " << emp->position << endl;
    logFile << "Department: " << emp->department << endl;
    logFile << "Date of Joining: ";
    logFile << std::setw(2) << std::setfill('0') << emp->doj / 1000000 << "/";
    logFile << std::setw(2) << std::setfill('0') << emp->doj / 10000 % 100 << "/";
    logFile << std::setw(2) << std::setfill('0') << emp->doj % 10000 << endl;
    logFile << "Address... " << endl;
    logFile << "Home/House No: " << emp->homeNo << endl;
    logFile << "Street Name: " << emp->street << endl;
    logFile << "City: " << emp->city << endl;
    logFile << "State: " << emp->state << endl;
    logFile << "Country: " << emp->country << endl;
    logFile << "Pin: " << emp->pin << endl;
    logFile << "\n";
    logFile.close();
}

// Function to Display Logfiles
void displayLogFile() 
{
    cout << "Log File:" << endl;

    // Read and display the contents of the log files
    ifstream insertLog("Insert_log.txt");
    if (insertLog.is_open()) 
    {
        char ch;
        while ((ch = insertLog.get()) != EOF) 
        {
            cout << ch;
        }
        insertLog.close();
    }
    else 
	{
    	cout << "No Operations Done Yet!" << endl;
	}

    ifstream deleteLog("Delete_log.txt");
    if (deleteLog.is_open()) 
    {
        char ch;
        while ((ch = deleteLog.get()) != EOF) 
        {
            cout << ch;
        }
        deleteLog.close();
    }

    ifstream foundLog("Found_log.txt");
    if (foundLog.is_open()) 
    {
        char ch;
        while ((ch = foundLog.get()) != EOF) 
        {
            cout << ch;
        }
        foundLog.close();
    }


    ifstream updateLog("Update_log.txt");
    if (updateLog.is_open()) 
    {
        char ch;
        while ((ch = updateLog.get()) != EOF) 
        {
            cout << ch;
        }
        updateLog.close();
    }

    ifstream displayLog("Display_log.txt");
    if (displayLog.is_open()) 
    {
        char ch;
        while ((ch = displayLog.get()) != EOF) 
        {
            cout << ch;
        }
        displayLog.close();
    }

    ifstream reportLog("Report_log.txt");
    if (reportLog.is_open()) 
    {
        char ch;
        while ((ch = reportLog.get()) != EOF) 
        {
            cout << ch;
        }
        reportLog.close();
    }
}

// Function to check for duplicate IDs
bool checkDuplicateId(Employee* head, int id) 
{
    Employee* temp = head;
    while (temp != NULL) 
    {
        if (temp->id == id)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

int getIntegerInput() 
{
    int input;
    while (true) 
    {
        if (cin >> input) 
        {
            return input;
        } 
        else 
        {
            cout << "Invalid input. Please enter a valid integer." << endl;
            cin.clear();  // Clear the error flag
            cin.ignore(10000, '\n');  // Ignore the invalid input
        }
    }
}

// Function to get input from the user
void getInput(char* str, int maxLen) 
{
    while (true) 
    {
        char c = cin.get();

        if (c == '\n') // If user pressed enter without input
        {
            cout << "Please enter a value. Input cannot be empty: ";
            continue;
        }

        str[0] = c;
        int i = 1;

        // Read the rest of the input
        while (i < maxLen - 1 && (c = cin.get()) != '\n') 
        {
            str[i++] = c;
        }

        // Null-terminate the string
        str[i] = '\0';

        // Replace full stops with spaces
        for (i = 0; str[i] != '\0'; i++) 
        {
            if (str[i] == '.') 
            {
                str[i] = ' ';
            }
        }

        // Validate input
        bool valid = true;
        for (i = 0; str[i] != '\0'; i++) 
        {
            if (!isalpha(str[i]) && str[i] != ' ' && str[i] != ' ')  
            {
                valid = false;
                break;
            }
        }

        if (!valid) 
        {
            cout << "Invalid input. Please enter only alphabets, spaces and fullstop." << endl;
        } 
        else 
        {
            break; // Exit the loop if input is valid
        }
    }
}

// Function to get a line of input from the user
void getAll(char* str, int maxLen) 
{
    while (true) 
    {
        char c = cin.get();

        if (c == '\n') // If user pressed enter without input
        {
            cout << "Please enter a value. Input cannot be empty: ";
            continue;
        }

        str[0] = c;
        int i = 1;

        // Read the rest of the input
        while (i < maxLen - 1 && (c = cin.get()) != '\n') 
        {
            str[i++] = c;
        }

        // Null-terminate the string
        str[i] = '\0';

        break; // Exit the loop if input is not empty
    }
}

// Function to create a new employee record
Employee* createRecord(Employee* head) 
{
    Employee* newRecord = new Employee();
    while (true) 
    {
        cout << "Enter Employee Id (6 digits): ";
        newRecord->id = getIntegerInput();
        if (newRecord->id >= 100000 && newRecord->id <= 999999) 
        {
            if (!checkDuplicateId(head, newRecord->id)) 
            {
                break;
            } 
            else 
            {
                cout << "ID already exists. Please try again." << endl;
            }
        } 
        else 
        {
            cout << "ID must be 6 digits. Please try again." << endl;
        }
    }
    cout << "Enter Employee Name: ";
    cin.ignore();
    getInput(newRecord->name, 100);
    cout << "Enter Employee Father's Name: ";
    getInput(newRecord->fatherName, 100);
    cout << "Enter Employee Mother's Name: ";
    getInput(newRecord->motherName, 100);
    cout << "Enter Employee Position: ";
    getInput(newRecord->position, 100);
    cout << "Enter Employee Department: ";
    getInput(newRecord->department, 100);
    while (true) 
    {
        cout << "Enter Date of Joining (DDMMYYYY): ";
        newRecord->doj = getIntegerInput();
        int day = newRecord->doj / 1000000;
        int month = (newRecord->doj / 10000) % 100;
        int year = newRecord->doj % 10000;
        if( year == 2024 && month >=8 && day > 12){   // More than current date
        	cout << "Invalid date. Please try again." << endl;
		}
        else if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 2002 && year <= 2024) // Valid Dates
        {
            if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) 
            {
                cout << "Invalid date. Please try again." << endl;
            } 
            else if (month == 2)
            {
                if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) 
                {
                    if (day > 29)
					{
                        cout << "Invalid date. Please try again." << endl;
                    }
					else 
					{
                        break;
                    }
                } 
                else 
                {
                    if (day > 28)
                    {
                        cout << "Invalid date. Please try again." << endl;
                    } 
                    else
                    {
                        break;
                    }
                }
            } 
            else 
            {
                break;
            }
        } 
        else 
        {
            cout << "Invalid date or year less than 2002. Please try again." << endl;
        }
    }
    cout << "Employee Address... " << endl;
    cout << "Enter Home/House No: ";
    cin.ignore();
    getAll(newRecord->homeNo, 20);
    cout << "Enter Street Name: ";
    getAll(newRecord->street, 100);
    cout << "Enter City: ";
    getAll(newRecord->city, 50);
    cout << "Enter State: ";
    getAll(newRecord->state, 50);
    cout << "Enter Country: ";
    getAll(newRecord->country, 50);
    cout << "Enter Pin: ";
    newRecord->pin = getIntegerInput();
    newRecord->next = NULL;
    return newRecord;
}

// Function to insert a record into the database
void insertRecord(Employee** head) 
{
    Employee* newRecord = createRecord(*head); // Pass head to createRecord
    if (*head == NULL || (*head)->id > newRecord->id) 
    {
        newRecord->next = *head;
        *head = newRecord;
    } 
    else 
    {
        Employee* current = *head;
        while (current->next != NULL && current->next->id < newRecord->id)
        {
            current = current->next;
        }
        newRecord->next = current->next;
        current->next = newRecord;
    }
    logOutput("Record inserted successfully!", newRecord, "Insert_log.txt");
}

// Function to delete a record from the database
void deleteRecord(Employee** head, int id) 
{
    if (*head == NULL) 
    {
        cout << "Record not found!" << endl;
        return;
    }
    if ((*head)->id == id) 
    {
        Employee* temp = *head;
        *head = (*head)->next;
        logOutput("Record deleted successfully!", temp, "Delete_log.txt");
        delete temp;
        cout << "Record deleted successfully" << endl;
        return;
    }
    Employee* current = *head;
    while (current->next != NULL && current->next->id != id) 
    {
        current = current->next;
    }
    if (current->next == NULL) 
    {
        cout << "Record not found!" << endl;
        return;
    }
    Employee* temp = current->next;
    current->next = current->next->next;
    logOutput("Record deleted successfully!", temp, "Delete_log.txt");
    delete temp;
    cout << "Record deleted successfully" << endl;
}

// Function to find a record in the database
void findRecord(Employee* head, int id) 
{
    while (head != NULL) 
    {
        if (head->id == id) 
        {
            cout << "Record found!" << endl;
            cout << "Employee Id: " << head->id << endl;
            cout << "Employee Name: " << head->name << endl;
            cout << "Employee Father's Name: " << head->fatherName << endl;
            cout << "Employee Mother's Name: " << head->motherName << endl;
            cout << "Employee Position: " << head->position << endl;
            cout << "Employee Department: " << head->department << endl;
            cout << "Date of Joining: ";
            cout << std::setw(2) << std::setfill('0') << head->doj / 1000000 << "/";
            cout << std::setw(2) << std::setfill('0') << head->doj / 10000 % 100 << "/";
            cout << std::setw(2) << std::setfill('0') << head->doj % 10000 << endl;
            cout << "Employee Address... " << endl;
            cout << "Home/House No: " << head->homeNo << endl;
            cout << "Street Name: " << head->street << endl;
            cout << "City: " << head->city << endl;
            cout << "State: " << head->state << endl;
            cout << "Country: " << head->country << endl;
            cout << "Pin: " << head->pin << endl;
            logOutput("Record founded successfully!", head, "Found_log.txt");
            return;
        }
        head = head->next;
    }
    cout << "Record not found!" << endl;
}

// Function to update a record in the database
void updateRecord(Employee* head, int id) 
{
    while (head != NULL) 
    {
        if (head->id == id) 
        {
            cout << "Enter new Employee Name: ";
            cin.ignore();
            getInput(head->name, 100);
            cout << "Enter new Employee Father's Name: ";
            getInput(head->fatherName, 100);
            cout << "Enter new Employee Mother's Name: ";
            getInput(head->motherName, 100);
            cout << "Enter new Employee Position: ";
            getInput(head->position, 100);
            cout << "Enter new Employee Department: ";
            getInput(head->department, 100);
            while (true) 
            {
                cout << "Enter new Date of Joining (DDMMYYYY): ";
                head->doj = getIntegerInput();
                int day = head->doj / 1000000;
                int month = (head->doj / 10000) % 100;
                int year = head->doj % 10000;
                if( year == 2024 && month >=8 && day > 12){   // More than current date
                	cout << "Invalid date. Please try again." << endl;
				}
                else if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 2002 && year <= 2024) // Valid Dates
                {
                    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) 
                    {
                        cout << "Invalid date. Please try again." << endl;
                    } 
                    else if (month == 2)
                    {
                        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) 
                        {
                            if (day > 29)
                            {
                                cout << "Invalid date. Please try again." << endl;
                            }
                            else 
                            {
                                break;
                            }
                        } 
                        else 
                        {
                            if (day > 28)
                            {
                                cout << "Invalid date. Please try again." << endl;
                            } 
                            else
                            {
                                break;
                            }
                        }
                    } 
                    else 
                    {
                        break;
                    }
                } 
                else 
                {
                    cout << "Invalid date or year less than 2002. Please try again." << endl;
                }
            }
            cout << "Employee Address... " << endl;
            cout << "Enter new Home/House No: ";
            cin.ignore();
            getAll(head->homeNo, 20);
            cout << "Enter new Street Name: ";
            getAll(head->street, 100);
            cout << "Enter new City: ";
            getAll(head->city, 50);
            cout << "Enter new State: ";
            getAll(head->state, 50);
            cout << "Enter new Country: ";
            getAll(head->country, 50);
            cout << "Enter new Pin: ";
            head->pin = getIntegerInput();
            logOutput("Record updated successfully!", head, "Update_log.txt");
            return;
        }
        head = head->next;
    }
    cout << "Record not found!" << endl;
}

// Function to display records of employees belonging to a particular location
void displayLocationWiseRecords(Employee* head) 
{
    cout << "Enter the location type (city/state/country/pin): ";
    string locationType;
    cin >> locationType;

    if (locationType == "pin") 
    {
        int locationValue;
        cout << "Enter the location value (pin): ";
        locationValue = getIntegerInput();;

        bool found = false;
        Employee* temp = head;
        while (temp != NULL) 
        {
            if (temp->pin == locationValue) 
            {
                cout << "Employee Id: " << temp->id << endl;
                cout << "Employee Name: " << temp->name << endl;
                cout << "Father's Name: " << temp->fatherName << endl;
                cout << "Mother's Name: " << temp->motherName << endl;
                cout << "Position: " << temp->position << endl;
                cout << "Department: " << temp->department << endl;
                cout << "Date of Joining: ";
                cout << std::setw(2) << std::setfill('0') << temp->doj / 1000000 << "/";
                cout << std::setw(2) << std::setfill('0') << temp->doj / 10000 % 100 << "/";
                cout << std::setw(2) << std::setfill('0') << temp->doj % 10000 << endl;
                cout << "Address... " << endl;
                cout << "Home/House No: " << temp->homeNo << endl;
                cout << "Street Name: " << temp->street << endl;
                cout << "City: " << temp->city << endl;
                cout << "State: " << temp->state << endl;
                cout << "Country: " << temp->country << endl;
                cout << "Pin: " << temp->pin << endl;
                cout << endl;
                logOutput("Record displayed successfully by pin!", temp, "Display_log.txt");

                found = true;
            }
            temp = temp->next;
        }

        if (!found) 
        {
            cout << "No records found for the specified location." << endl;
        }
    } 
    else 
    {
        string locationValue;
        cout << "Enter the location value: ";
        cin >> locationValue;

        bool found = false;
        Employee* temp = head;
        while (temp != NULL) 
        {
            if ((locationType == "city" && temp->city == locationValue) ||
                (locationType == "state" && temp->state == locationValue) ||
                (locationType == "country" && temp->country == locationValue)) 
            {
                cout << "Employee Id: " << temp->id << endl;
                cout << "Employee Name: " << temp->name << endl;
                cout << "Father's Name: " << temp->fatherName << endl;
                cout << "Mother's Name: " << temp->motherName << endl;
                cout << "Position: " << temp->position << endl;
                cout << "Department: " << temp->department << endl;
                cout << "Date of Joining: ";
                cout << std::setw(2) << std::setfill('0') << temp->doj / 1000000 << "/";
                cout << std::setw(2) << std::setfill('0') << temp->doj / 10000 % 100 << "/";
                cout << std::setw(2) << std::setfill('0') << temp->doj % 10000 << endl;
                cout << "Address... " << endl;
                cout << "Home/House No: " << temp->homeNo << endl;
                cout << "Street Name: " << temp->street << endl;
                cout << "City: " << temp->city << endl;
                cout << "State: " << temp->state << endl;
                cout << "Country: " << temp->country << endl;
                cout << "Pin: " << temp->pin << endl;
                cout << endl;
                logOutput("Record displayed successfully by location!", temp, "Display_log.txt");
                found = true;
            }
            temp = temp->next;
        }

        if (!found) 
        {
            cout << "No records found for the specified location." << endl;
        }
    }
}

// Function to generate city-wise report
void cityWiseReport(Employee* head) 
{
    cout << "City-wise Employee Report:" << endl;
    if (head == NULL) 
    {
        cout << "No records found." << endl;
        return;
    }

    char currentCity[50];
    strcpy(currentCity, head->city);
    cout << "\n" << "City: " << currentCity << endl;
    cout << "-------------------------" << endl;
    Employee* temp = head;
    while (temp != NULL) 
    {
        if (strcmp(temp->city, currentCity) == 0) 
        {
            cout << "Employee Id: " << temp->id << endl;
            cout << "Employee Name: " << temp->name << endl;
            cout << endl;
        } 
        else 
        {
            strcpy(currentCity, temp->city);
            cout << "\n" << "City: " << currentCity << endl;
            cout << "-------------------------" << endl;
            cout << "Employee Id: " << temp->id << endl;
            cout << "Employee Name: " << temp->name << endl;
            cout << endl;
        }
        temp = temp->next;
    }
}

// Function to generate department-wise report
void departmentWiseReport(Employee* head) 
{
    cout << "Department-wise Employee Report:" << endl;
    if (head == NULL) 
    {
        cout << "No records found." << endl;
        return;
    }

    string currentDepartment = head->department;
    cout << "\n" << "Department: " << currentDepartment << endl;
    cout << "-------------------------" << endl;
    Employee* temp = head;
    while (temp != NULL) 
    {
        if (temp->department == currentDepartment) 
        {
            cout << "Employee Id: " << temp->id << endl;
            cout << "Employee Name: " << temp->name << endl;
            cout << endl;
        } 
        else 
        {
            currentDepartment = temp->department;
            cout << "\n" << "Department: " << currentDepartment << endl;
            cout << "-------------------------" << endl;
            cout << "Employee Id: " << temp->id << endl;
            cout << "Employee Name: " << temp->name << endl;
            cout << endl;
        }
        temp = temp->next;
    }
}

// Function to generate position-wise report
void positionWiseReport(Employee* head) 
{
    cout << "Position-wise Employee Report:" << endl;
    if (head == NULL) 
    {
        cout << "No records found." << endl;
        return;
    }

    string currentPosition = head->position;
    cout << "\n" << "Position: " << currentPosition << endl;
    cout << "-------------------------" << endl;
    Employee* temp = head;
    while (temp != NULL) 
    {
        if (temp->position == currentPosition) 
        {
            cout << "Employee Id: " << temp->id << endl;
            cout << "Employee Name: " << temp->name << endl;
            cout << endl;
        } 
        else 
        {
            currentPosition = temp->position;
            cout << "\n" << "Position: " << currentPosition << endl;
            cout << "-------------------------" << endl;
            cout << "Employee Id: " << temp->id << endl;
            cout << "Employee Name: " << temp->name << endl;
            cout << endl;
        }
        temp = temp->next;
    }
}

// Function to generate a report
void generateReport(Employee* head) 
{
    int choice;
    cout << "Generate Report:" << endl;
    cout << "1. Employee City wise" << endl;
    cout << "2. Employee Department wise" << endl;
    cout << "3. Employee Position wise" << endl;
    cout << "Enter choice: ";
    choice = getIntegerInput();;
    switch (choice) 
    {
        case 1:
            cityWiseReport(head);
            logOutput("Report generated successfully by city!", head, "Report_log.txt");
            break;
        case 2:
            departmentWiseReport(head);
            logOutput("Report generated successfully by deparment!", head, "Report_log.txt");
            break;
        case 3:
            positionWiseReport(head);
            logOutput("Report generated successfully by position!", head, "Report_log.txt");
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

int main() 
{
    Employee* head = NULL;
    while (true) 
    {
    	system("cls");
        cout << "Employee Management System" << endl;
        cout << "1. Insert Record" << endl;
        cout << "2. Delete Record" << endl;
        cout << "3. Find Record" << endl;
        cout << "4. Update Record" << endl;
        cout << "5. Display Records" << endl;
        cout << "6. Generate Report" << endl;
        cout << "7. Log File" << endl;
        cout << "8. Exit" << endl;
        int choice;
        cout << "Enter choice :- ";
        choice = getIntegerInput();
        switch (choice) 
        {
            case 1:
                insertRecord(&head);
                cout << "Record inserted successfully!" << endl;
                break;
            case 2:
                int id;
                cout << "Enter Employee Id to delete: ";
                id = getIntegerInput();
                deleteRecord(&head, id);
                break;
            case 3:
                cout << "Enter Employee Id to find: ";
                id = getIntegerInput();
                findRecord(head, id);
                break;
            case 4:
                cout << "Enter Employee Id to update: ";
                id = getIntegerInput();
                updateRecord(head, id);
                break;
            case 5:
                displayLocationWiseRecords(head);
                break;
            case 6:
                generateReport(head);
                break;
            case 7:
                displayLogFile();
                cout << "LogFile Displayed!" << endl;
                break;
            case 8:
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout << "Press any key to continue...";
        getch();
    }
    return 0;
}
