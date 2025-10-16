#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <ctime>
using namespace std;
struct Employee {
    char id[20];         // ID will be assigned after sorting
    char name[50];
    char registeredDate[20];
    float salary;
    char phone[20];
    char Email[30];
    char Gender[2];
    char position[20];
    Employee* next;
};
Employee* head = NULL;

void linearSearchByName() {
    if (head == NULL) {
        cout << "No employees to search.\n";
        return;
    }
 char searchName[50];
    cout << "Enter name to search: ";
    cin.ignore();
    cin.getline(searchName, 50);
    Employee* temp = head;
    bool found = false;
    while (temp != NULL) {
        if (strcmp(temp->name, searchName) == 0) {
            cout << "\n--- Employee Found ---\n";
            cout << "ID: " << temp->id << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Gender: "<< temp->Gender<<endl;
            cout << "Salary: " << temp->salary << endl;
            cout << "Position: "<< temp->position<<endl; 
            cout << "Registered Date: " << temp->registeredDate << endl;
            cout << "___________________________________\n";
            found = true;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "No employee found with that name.\n";
    }
}
int compareIDs(const void* a, const void* b) {
    Employee* emp1 = *(Employee**)a;
    Employee* emp2 = *(Employee**)b;
    return strcmp(emp1->id, emp2->id);
}
void binarySearchByID() {
    if (head == NULL) {
        cout << "No employees to search.\n";
        return;
    }
    // Count employees
    int count = 0;
    Employee* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    // Copy to array
    Employee** empArray = new Employee*[count];
    temp = head;
    for (int i = 0; i < count; i++) {
        empArray[i] = temp;
        temp = temp->next;
    }
 // Sort array by ID
    qsort(empArray, count, sizeof(Employee*), compareIDs);
    // Input ID to search
    char searchID[20];
    cout << "Enter ID to search (e.g. EMP/2025/001): ";
    cin.ignore();
    cin.getline(searchID, 20);
    // Binary search
    int low = 0, high = count - 1, mid;
    bool found = false;
    while (low <= high) {
        mid = (low + high) / 2;
        int cmp = strcmp(empArray[mid]->id, searchID);
        if (cmp == 0) {
            cout << "\n--- Employee Found ---\n";
            cout << "ID: " << empArray[mid]->id << endl;
            cout << "Gender:"<<empArray[mid]->Gender<<endl;
            cout << "Name: " << empArray[mid]->name << endl;
            cout << "Salary: " << empArray[mid]->salary << endl;
            cout << "Position: "<<empArray[mid]->position<<endl;
            cout << "Registered Date: " << empArray[mid]->registeredDate << endl;
            cout << "________________________________\n";
            found = true;
            break;
        } else if (cmp < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    if (!found) {
        cout << "No employee found with that ID.\n";
    }
    delete[] empArray;
}
// Function to display all employee records
void displayEmployees(Employee* head) {
    if (head == nullptr) {
        cout << "\nNo employees to display.\n";
        return;
    }
    Employee* temp = head;
    cout << "\n\t\t\tEmployee List\n";
    cout << "_________________________________________________________________________________________________________________________\n";
    cout << "ID\t\tName\t\tGender\t\tSalary\t\tPhone\t\tEmail\t\tDate\t\tposition\n";
    cout << "__________________________________________________________________________________________________________________________________________\n";
    while (temp != nullptr) {
        cout << temp->id << "\t\t" 
             << temp->name << "\t\t"<<temp->Gender
             << "\t" 
             << temp->salary << "\t\t" 
             << temp->phone << "\t\t" 
             << temp->Email <<"\t\t"<<temp->registeredDate<<"\t\t"<<temp->position<< endl;
        temp = temp->next;
    }
    cout << "_____________________________________________________________________________________________________________\n";
}
void insertionSortByName(Employee*& head) {
    if (!head || !head->next) return;

Employee* sorted = nullptr;
    while (head) {
        Employee* current = head;
        head = head->next;
        if (!sorted || strcmp(current->name, sorted->name) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            Employee* temp = sorted;
            while (temp->next && strcmp(current->name, temp->next->name) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
    head = sorted;
    std::cout << "Employees sorted by name using insertion sort.\n";
}
// Get current system date as string (DD-MM-YYYY)
void getCurrentDate(char dataStr[]) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    sprintf(dataStr, "%02d-%02d-%04d", ltm->tm_mday, ltm->tm_mon + 1, 1900 + ltm->tm_year);
}
void assignIDs() {
    Employee* temp = head;
    int count = 1;
    // First, assign a number to only those with empty ID
    while (temp != NULL) {
        if (strlen(temp->id) == 0) {
            // Find next available number that is not already used
            Employee* check = head;
            char newID[20];
            do {
                sprintf(newID, "EMP/2025/%03d", count);
                bool exists = false;
                // Check if this ID is already taken
                check = head;
                while (check != NULL) {
                    if (strcmp(check->id, newID) == 0) {
                        exists = true;
                        break;
                    }
                    check = check->next;
                }
                if (!exists) break;
                count++;
            } while (true);
            strcpy(temp->id, newID);
        }
        temp = temp->next;
    }
}
bool isValidName(const char name[]) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ')
            return false;
    }
    return true;
}
bool isValidEmail(const char email[]) {
    int atPos = -1, dotPos = -1;
    int len = strlen(email);
    if (len == 0) return true; // Allow empty, handled as "NULL"
    for (int i = 0; i < len; ++i) {
        if (email[i] == '@') atPos = i;
        else if (email[i] == '.' && atPos != -1) dotPos = i;
    }
    return atPos > 0 && dotPos > atPos + 1 && dotPos<len-1;}
bool isValidPhone(const char phone[]) {
    int len = strlen(phone);
    if (len == 0) return true; // Allow empty, we'll handle it as "NULL"
    int start = 0;
    if (phone[0] == '+') start = 1;
    for (int i = start; i < len; ++i) {
        if (!isdigit(phone[i])) return false;
    }
    return true;
}
bool isPositiveInteger(const char str[]) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return strlen(str) > 0;
}
bool isValidFloat(const char str[]) {
    int dotCount = 0;
    int len = strlen(str);
    if (len == 0) return false;
    for (int i = 0; i < len; i++) {
        if (str[i] == '.') {
            dotCount++;
            if (dotCount > 1) return false;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
Employee* createEmployee() {
    Employee* newEmp = new Employee;
    strcpy(newEmp->id, "");
getCurrentDate(newEmp->registeredDate);
    while (true) {
        cout << "Enter name (letters only): ";
        cin.ignore();
        cin.getline(newEmp->name, 50);
        if (strlen(newEmp->name) == 0)
            cout << "Name cannot be empty.\n";
        else if (!isValidName(newEmp->name))
            cout << "Invalid name. Use only letters and spaces.\n";
        else
            break;
    }
while (true) {
    cout << "Enter gender (M/F): ";
    cin.getline(newEmp->Gender, 2);
    if (strcmp(newEmp->Gender, "M") == 0 || strcmp(newEmp->Gender, "F") == 0 ||
        strcmp(newEmp->Gender, "m") == 0 || strcmp(newEmp->Gender, "f") == 0) {
        break;
    } else {
        cout << "Invalid input. Please enter M or F.\n";
    }
}
   while (true) {
    cout << "Enter position: ";
    cin.getline(newEmp->position, 10);
    if (strlen(newEmp->position) == 0)
        cout << "Position cannot be empty.\n";
    else
        break;
}  
    char salaryStr[20];
    while (true) {
        cout << "Enter salary (numeric only): ";
        cin.getline(salaryStr, 20);
        if (isValidFloat(salaryStr)) {
            newEmp->salary = atof(salaryStr);
            if (newEmp->salary > 0)
                break;
            else
                cout << "Salary must be greater than 0.\n";
        } else {
            cout << "Invalid input. Enter numbers only (e.g. 2500.50).\n";
}
    } 
    while (true) {
    cout << "Enter phone number (starts with + and digits only): ";
    cin.getline(newEmp->phone, 20);
    if (strlen(newEmp->phone) == 0) {
        cout << "Phone number cannot be empty.\n";
    } else if (isValidPhone(newEmp->phone)) {
        break;
    } else {
        cout << "Invalid phone number. Only '+' at the beginning and digits allowed.\n";
    }
}
    while (true) {
        cout << "Enter email (optional): ";
        cin.getline(newEmp->Email, 50);
        if (strlen(newEmp->Email) == 0) {
            strcpy(newEmp->Email, "NULL");
            break;
        } else if (isValidEmail(newEmp->Email)) {
            break;
        } else {
            cout << "Invalid email format. Example: user@example.com\n";
        }
    }
    // Registered Date
//    getCurrentDate(newEmp->registeredDate);
    newEmp->next = NULL;
    return newEmp;
}
void addEmployee() {
    Employee* newEmp = createEmployee();
    if (head == NULL) {
        head = newEmp;
    } else {
        Employee* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newEmp;
    }
    cout << "Employee added successfully. ID will be assigned after sorting.\n";
}
void editEmployee() {
    if (head == NULL) {
        cout << "No employees available to edit.\n";
        return;
    }
    char empID[20];
    cout << "Enter Employee ID to edit: ";
    cin.ignore();
    cin.getline(empID, 20);

    Employee* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->id, empID) == 0) {
            int choice;
            do {
                cout << "\nEditing Employee: " << empID << endl;
                cout << "1. Edit Name\n";
                cout << "2. Edit Gende\n";
                cout << "3. Edit Salary\n";
                cout << "4. Edit Position\n";
                cout << "5. Back to Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();
                switch (choice) {
                    case 1: {
                        char newName[50];
                        while (true) {
                            cout << "Enter new name (letters only): ";
                            cin.getline(newName, 50);
                            if (strlen(newName) == 0)
                                cout << "Name cannot be empty.\n";
                            else if (!isValidName(newName))
                                cout << "Invalid name. Use only letters and spaces.\n";
                            else
                                break;
                        }
                        strcpy(temp->name, newName);
                        cout << "Name updated successfully.\n";
                        break;
                    }
                    case 2: {
    char newGender[2];
    while (true) {
        cout << "Enter new gender (M/F): ";
        cin.getline(newGender, 2);
        if (strcmp(newGender, "M") == 0 || strcmp(newGender, "F") == 0 ||
            strcmp(newGender, "m") == 0 || strcmp(newGender, "f") == 0) {
            strcpy(temp->Gender, newGender);
            cout << "Gender updated successfully.\n";
            break;
        } else {
            cout << "Invalid input. Please enter M or F.\n";
        }
    }
    break;
}
                    case 3: {
                        char salaryStr[20];
                        while (true) {
                            cout << "Enter new salary (numeric only): ";
                            cin.getline(salaryStr, 20);
                            if (isValidFloat(salaryStr)) {
                                float newSalary = atof(salaryStr);
                                if (newSalary > 0) {
                                    temp->salary = newSalary;
                                    cout << "Salary updated successfully.\n";
                                    break;
                                } else {
                                    cout << "Salary must be greater than 0.\n";
                                }
                            } else {
                                cout << "Invalid input. Enter numbers only (e.g. 2500.50).\n";
                            }
                        }
                        break;
                    }
                    case 4: {
                        char newPosition[20];
                        while (true) {
                            cout << "Enter new position (e.g. Manager): ";
                            cin.getline(newPosition, 20);
                            if (strlen(newPosition) == 0)
                                cout << "Position cannot be empty.\n";
                            else
                                break;
                        }
                        strcpy(temp->position, newPosition);
                        cout << "Position updated successfully.\n";
                        break;
                    }
                    case 5:
                        cout << "Returning to main menu.\n";
                        break;
                    default:
                        cout << "Invalid option.\n";
                }
            } while (choice != 5);
            return;
        }
        temp = temp->next;
    }
    cout << "Employee with ID " << empID << " not found.\n";
}
void bubbleSortByID() {
    if (head == nullptr || head->next == nullptr) {
        cout << "List is too short to sort.\n";
        return;
    }
    bool swapped;
    Employee* ptr1;
    Employee* lptr = nullptr;
    do {
        swapped = false;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->id, ptr1->next->id) >0){
                std::swap(ptr1->salary, ptr1->next->salary);
                std::swap(ptr1->name, ptr1->next->name);
                std::swap(ptr1->id, ptr1->next->id);
                std::swap(ptr1->registeredDate, ptr1->next->registeredDate);
                std::swap(ptr1->phone, ptr1->next->phone);
                std::swap(ptr1->Email, ptr1->next->Email);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1; // Reduce the range for optimization
    } while (swapped);
    cout << "Employees sorted by ID using Bubble Sort.\n";
}
void deleteAll() {
    while (head != NULL) {
        Employee* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "All employees deleted successfully.\n";
}
void deleteByID() {
    if (head == NULL) {
        cout << "No employees to delete.\n";
        return;
    }
    char idToDelete[20];
    cout << "Enter the ID of the employee to delete: ";
    cin.ignore();
    cin.getline(idToDelete, 20);
    Employee* temp = head;
    Employee* prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->id, idToDelete) == 0) {
            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            cout << "Employee with ID " << idToDelete << " deleted.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Employee with ID " << idToDelete << " not found.\n";
}
void deleteMenu() {
    int choice;
    do {
        cout << "\n--- Delete Menu ---\n";
        cout << "1. Delete All Employees\n";
        cout << "2. Delete Single Employee by ID\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: deleteAll(); break;
            case 2: deleteByID(); break;
            case 3: cout << "Returning to main menu...\n"; break;
default: cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}
void updateSalaryByPercentage() {
    if (head == NULL) {
        cout << "No employees available to update.\n";
        return;
    }
    char targetPosition[20];
    cout << "Enter position to update salaries for: ";
    cin.ignore();  // Clear input buffer
    cin.getline(targetPosition, 20);
    float percentage;
    cout << "Enter percentage to increase salary (e.g. 10 for 10%): ";
    cin >> percentage;
    if (percentage < 0) {
        cout << "Percentage cannot be negative.\n";
        return;
    }
    bool found = false;
    Employee* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->position, targetPosition) == 0) {
            float oldSalary = temp->salary;
            temp->salary += (temp->salary * percentage / 100.0);
            cout << "? Updated " << temp->name << "'s salary from " 
                 << oldSalary << " to " << temp->salary << endl;
            found = true;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "? No employees found with position: " << targetPosition << endl;
    }
}
void swapEmployees(Employee* a, Employee* b) {
    Employee temp;
    strcpy(temp.id, a->id);
    strcpy(temp.name, a->name);
    strcpy(temp.registeredDate, a->registeredDate);
    temp.salary = a->salary;
    strcpy(temp.phone, a->phone);
    strcpy(temp.Email, a->Email);
    strcpy(temp.Gender, a->Gender);
    strcpy(temp.position, a->position);
    strcpy(a->id, b->id);
    strcpy(a->name, b->name);
    strcpy(a->registeredDate, b->registeredDate);
    a->salary = b->salary;
    strcpy(a->phone, b->phone);
    strcpy(a->Email, b->Email);
    strcpy(a->Gender, b->Gender);
    strcpy(a->position, b->position);
    strcpy(b->id, temp.id);
    strcpy(b->name, temp.name);
    strcpy(b->registeredDate, temp.registeredDate);
    b->salary = temp.salary;
    strcpy(b->phone, temp.phone);
    strcpy(b->Email, temp.Email);
    strcpy(b->Gender, temp.Gender);
    strcpy(b->position, temp.position);
}
void selectionSortByPosition() {
    if (head == NULL || head->next == NULL) {
        cout << "Not enough employees to sort.\n";
        return;
    }
    Employee* i = head;
    while (i != NULL) {
        Employee* minNode = i;
        Employee* j = i->next;

        while (j != NULL) {
            if (strcmp(j->position, minNode->position) < 0) {
                minNode = j;
            }
            j = j->next;
        }
        if (minNode != i) {
            swapEmployees(i, minNode);
        }
        i = i->next;
    }
    cout << "Employees sorted by position using selection sort.\n";
}
void sortByNameAndAssignIDs() {
    if (head == NULL || head->next == NULL) {
        cout << "Not enough employees to sort.\n";
        return;
    }
    bool swapped;
    do {
        swapped = false;
        Employee* current = head;
        while (current->next != NULL) {
            if (strcmp(current->name, current->next->name) > 0) {
                swapEmployees(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    assignIDs();
    cout << "Employees sorted by name and IDs assigned.\n";
}
void menu() {
    int choice;
    do {
        cout << "\n--- Employee Management System ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Sort by Name and Assign IDs\n";
        cout << "4. Delete employee\n";
        cout << "5. Update salary by percentage\n";
        cout << "6. Edit Employee\n";
        cout << "7. Linear Search by Name\n";
        cout << "8. Binary Search by ID\n";
        cout << "9. Bubble sort by id\n";
        cout << "10. Insertion sort by name\n ";
        cout << "11. Selection sort by position\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(head); 
            break;
            case 3: sortByNameAndAssignIDs(); 
            break;
            case 4: deleteMenu();
            break;
            case 5: updateSalaryByPercentage();
            break;
            case 6: editEmployee(); break;
            case 7: linearSearchByName(); break;
            case 8: binarySearchByID(); break;
             case 9: // Or whichever case you want
        bubbleSortByID();
   // displayEmployees(head);
    break;
    case 10: // Choose an available number
    insertionSortByName(head);
    break;
         case 11: selectionSortByPosition(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}
int main() {
    menu();
    return 0;
}