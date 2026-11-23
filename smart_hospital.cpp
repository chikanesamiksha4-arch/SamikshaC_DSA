#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10; // Size of the Hash Table

// Linked List Node representing each Patient
struct Patient {
    int patientID;
    string name;
    int age;
    string disease;
    Patient* next;
};

Patient* hashTable[SIZE]; // Hash Table array of Linked List heads

// Hash Function: Maps Patient ID to an index (0 to 9)
int hashFunction(int id) {
    return id % SIZE;
}

// 1. Register a new patient (Insert into Linked List using Chaining)
void registerPatient(int id, string name, int age, string disease) {
    int index = hashFunction(id);
    Patient* newNode = new Patient();
    newNode->patientID = id;
    newNode->name = name;
    newNode->age = age;
    newNode->disease = disease;

    newNode->next = hashTable[index]; // Link to existing chain (handles collisions)
    hashTable[index] = newNode;       // Insert at head of bucket
    cout << "Registered: " << name << " (ID: " << id << ") at Hash Index " << index << endl;
}

// 2. Search / Retrieve patient information by Patient ID
void searchPatient(int id) {
    int index = hashFunction(id);
    Patient* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->patientID == id) {
            cout << "Found -> ID: " << temp->patientID << ", Name: " << temp->name
                 << ", Age: " << temp->age << ", Condition: " << temp->disease << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Patient ID " << id << " not found.\n";
}

// 3. Update patient information
void updatePatient(int id, string newDisease) {
    int index = hashFunction(id);
    Patient* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->patientID == id) {
            temp->disease = newDisease;
            cout << "Updated condition for Patient ID " << id << " to: " << newDisease << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Patient ID " << id << " not found.\n";
}

// 4. Discharge a patient (Delete node from Linked List)
void dischargePatient(int id) {
    int index = hashFunction(id);
    Patient* temp = hashTable[index];
    Patient* prev = NULL;

    while (temp != NULL && temp->patientID != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Patient ID " << id << " not found.\n";
        return;
    }

    if (prev == NULL)
        hashTable[index] = temp->next; // Discharging first node in bucket
    else
        prev->next = temp->next;       // Bypassing discharged node

    delete temp;
    cout << "Discharged Patient ID " << id << " successfully.\n";
}

// 5. Display all patient records
void displayAllPatients() {
    cout << "\n--- Hospital Patient Records (Hash Table + Chaining) ---\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "Bucket [" << i << "]: ";
        Patient* temp = hashTable[i];
        while (temp != NULL) {
            cout << "[ID:" << temp->patientID << " - " << temp->name
                 << ", Age:" << temp->age << ", " << temp->disease << "] -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

int main() {
    // Initialize all hash table buckets to NULL
    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = NULL;
    }

    // 1. Register Patients (IDs 104 and 204 collide at index 4 to show Chaining)
    registerPatient(104, "Rahul Verma", 45, "Fever");
    registerPatient(107, "Sneha Patil", 30, "Fracture");
    registerPatient(204, "Amit Joshi", 62, "Hypertension");

    // 2. Display All Records
    displayAllPatients();

    // 3. Search & Update Patient Info
    cout << endl;
    searchPatient(204);
    updatePatient(104, "Recovered - Observation");

    // 4. Discharge a Patient
    dischargePatient(107);

    // 5. Display Final Records
    displayAllPatients();

    return 0;
}
