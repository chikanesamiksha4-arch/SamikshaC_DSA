#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10; // Size of the Hash Table

// Structure representing each Student node in the Linked List
struct Student {
    int rollNo;             // Unique Student Roll Number
    string name;            // Student Name
    string course;          // Enrolled Course (e.g., "Data Structures" or "None")
    Student* next;          // Pointer to next student in collision chain
};

// Hash Table: Array of Linked List head pointers
Student* hashTable[TABLE_SIZE];

// Initialize all buckets to NULL
void initTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

// Hash Function: Maps Roll Number to an index (0 to TABLE_SIZE - 1)
int hashFunction(int rollNo) {
    return rollNo % TABLE_SIZE;
}

// Helper function to locate a student node by Roll Number
Student* findStudent(int rollNo) {
    int index = hashFunction(rollNo);
    Student* temp = hashTable[index];
    while (temp != NULL) {
        if (temp->rollNo == rollNo) return temp;
        temp = temp->next;
    }
    return NULL;
}

// 1. Register a new student (Insert into Hash Table using Chaining)
void registerStudent() {
    Student* newNode = new Student();
    cout << "Enter Roll Number: ";
    cin >> newNode->rollNo;
    cin.ignore();
    cout << "Enter Student Name: ";
    getline(cin, newNode->name);
    newNode->course = "Not Enrolled"; // Default status before course enrollment

    int index = hashFunction(newNode->rollNo);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    cout << "Student registered at Hash Index " << index << "!\n";
}

// 2. Update student information
void updateStudent() {
    int roll;
    cout << "Enter Roll Number to update: ";
    cin >> roll;

    Student* s = findStudent(roll);
    if (s == NULL) {
        cout << "Student not found!\n";
        return;
    }
    cin.ignore();
    cout << "Enter Updated Name: ";
    getline(cin, s->name);
    cout << "Student details updated!\n";
}

// 3. Enroll student in a course
void enrollCourse() {
    int roll;
    cout << "Enter Roll Number to enroll: ";
    cin >> roll;

    Student* s = findStudent(roll);
    if (s == NULL) {
        cout << "Student not found!\n";
        return;
    }
    cin.ignore();
    cout << "Enter Course Name to enroll: ";
    getline(cin, s->course);
    cout << s->name << " enrolled in " << s->course << "!\n";
}

// 4. Withdraw student from a course
void withdrawCourse() {
    int roll;
    cout << "Enter Roll Number to withdraw from course: ";
    cin >> roll;

    Student* s = findStudent(roll);
    if (s == NULL) {
        cout << "Student not found!\n";
        return;
    }
    s->course = "Withdrawn / None";
    cout << "Course withdrawn for " << s->name << "!\n";
}

// 5. Remove student record completely (Delete node from Linked List)
void removeStudent() {
    int roll;
    cout << "Enter Roll Number to remove record: ";
    cin >> roll;

    int index = hashFunction(roll);
    Student* temp = hashTable[index];
    Student* prev = NULL;

    while (temp != NULL && temp->rollNo != roll) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Student not found!\n";
        return;
    }

    if (prev == NULL) {
        hashTable[index] = temp->next;
    } else {
        prev->next = temp->next;
    }
    delete temp;
    cout << "Student record deleted!\n";
}

// 6. Search or Display all student records
void displayAll() {
    cout << "\n--- University Student Records (Hash Table + Chaining) ---\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Bucket [" << i << "]: ";
        Student* temp = hashTable[i];
        if (temp == NULL) {
            cout << "Empty";
        }
        while (temp != NULL) {
            cout << "[Roll:" << temp->rollNo << ", " << temp->name
                 << ", Course:" << temp->course << "] -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

int main() {
    initTable();
    int choice;
    do {
        cout << "\n=== University Registration Menu ===\n";
        cout << "1. Register Student\n2. Update Student Info\n3. Enroll in Course\n";
        cout << "4. Withdraw from Course\n5. Remove Student Record\n6. Display All Records\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: updateStudent(); break;
            case 3: enrollCourse(); break;
            case 4: withdrawCourse(); break;
            case 5: removeStudent(); break;
            case 6: displayAll(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}
