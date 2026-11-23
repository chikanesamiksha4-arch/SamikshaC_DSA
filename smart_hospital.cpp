
#include <iostream>  // Used for input and output
#include <string>    // Used to store names and diseases
using namespace std;

// Structure to store patient information
struct Patient
{
    int id;             // Stores patient ID
    string name;        // Stores patient name
    int age;            // Stores patient age
    string disease;     // Stores patient disease

    Patient* next;      // Pointer to connect the next patient
};

// Structure to create Hash Table nodes
struct HashNode
{
    int id;              // Stores patient ID
    Patient* patient;    // Points to patient information
    HashNode* next;      // Connects nodes during collision
};

class Hospital
{
private:

    Patient* head;       // Points to the first patient in Linked List

    static const int SIZE = 10; // Hash Table size is 10

    HashNode* table[SIZE]; // Creates Hash Table

    // Hash function calculates index using patient ID
    int hashFunction(int id)
    {
        return id % SIZE; // Returns remainder as index
    }

public:

    // Constructor initializes the Linked List and Hash Table
    Hospital()
    {
        head = NULL; // Initially Linked List is empty

        // Makes every Hash Table location empty
        for(int i = 0; i < SIZE; i++)
        {
            table[i] = NULL;
        }
    }

    // Function to search patient using ID
    Patient* searchPatient(int id)
    {
        int index = hashFunction(id); // Calculates Hash Table index

        HashNode* temp = table[index]; // Starts searching at that index

        // Checks every node in the chain
        while(temp != NULL)
        {
            if(temp->id == id) // Checks whether ID matches
            {
                return temp->patient; // Returns patient record
            }

            temp = temp->next; // Moves to next node
        }

        return NULL; // Patient not found
    }

    // Function to insert patient into Hash Table
    void insertHash(Patient* p)
    {
        int index = hashFunction(p->id); // Calculates index

        HashNode* newNode = new HashNode; // Creates new Hash Table node

        newNode->id = p->id; // Stores patient ID
        newNode->patient = p; // Stores patient pointer

        // Connects new node to existing nodes
        // This is called Collision Resolution using Chaining
        newNode->next = table[index];

        table[index] = newNode; // Updates Hash Table index
    }

    // Function to register a new patient
    void registerPatient()
    {
        Patient* p = new Patient; // Creates new patient dynamically

        cout << "\nEnter Patient ID: ";
        cin >> p->id; // Takes patient ID

        // Checks whether patient ID already exists
        if(searchPatient(p->id) != NULL)
        {
            cout << "\nPatient ID already exists!";
            delete p; // Deletes newly created node
            return;   // Stops function
        }

        cin.ignore(); // Clears input buffer

        cout << "Enter Patient Name: ";
        getline(cin, p->name); // Takes complete patient name

        cout << "Enter Patient Age: ";
        cin >> p->age; // Takes patient age

        cin.ignore(); // Clears input buffer

        cout << "Enter Disease: ";
        getline(cin, p->disease); // Takes disease name

        // Inserts patient at beginning of Linked List
        p->next = head;

        head = p; // Makes new patient the first node

        insertHash(p); // Inserts patient into Hash Table

        cout << "\nPatient registered successfully!";
    }

    // Function to update patient information
    void updatePatient()
    {
        int id;

        cout << "\nEnter Patient ID to update: ";
        cin >> id; // Takes patient ID

        Patient* p = searchPatient(id); // Searches patient

        if(p == NULL) // Checks if patient does not exist
        {
            cout << "\nPatient not found!";
            return;
        }

        cin.ignore(); // Clears input buffer

        cout << "Enter new patient name: ";
        getline(cin, p->name); // Updates patient name

        cout << "Enter new age: ";
        cin >> p->age; // Updates patient age

        cin.ignore();

        cout << "Enter new disease: ";
        getline(cin, p->disease); // Updates disease

        cout << "\nPatient information updated successfully!";
    }

    // Function to discharge and delete a patient
    void dischargePatient()
    {
        int id;

        cout << "\nEnter Patient ID to discharge: ";
        cin >> id; // Takes patient ID

        Patient* temp = head; // Starts from first Linked List node

        Patient* prev = NULL; // Stores previous node

        // Searches patient in Linked List
        while(temp != NULL && temp->id != id)
        {
            prev = temp;       // Stores current node
            temp = temp->next; // Moves to next patient
        }

        if(temp == NULL) // Checks if patient is not found
        {
            cout << "\nPatient not found!";
            return;
        }

        // If patient is the first node
        if(prev == NULL)
        {
            head = temp->next; // Updates head pointer
        }
        else
        {
            // Connects previous node to next node
            prev->next = temp->next;
        }

        // Calculates Hash Table index
        int index = hashFunction(id);

        HashNode* h = table[index]; // Starts searching in Hash Table

        HashNode* hPrev = NULL; // Stores previous Hash Table node

        // Searches patient in Hash Table chain
        while(h != NULL && h->id != id)
        {
            hPrev = h; // Stores previous node
            h = h->next; // Moves to next node
        }

        // Deletes patient from Hash Table
        if(h != NULL)
        {
            if(hPrev == NULL)
            {
                table[index] = h->next; // Updates first node
            }
            else
            {
                hPrev->next = h->next; // Connects remaining nodes
            }

            delete h; // Deletes Hash Table node
        }

        delete temp; // Deletes patient record from memory

        cout << "\nPatient discharged successfully!";
    }

    // Function to display all patients
    void displayPatients()
    {
        Patient* temp = head; // Starts from first patient

        if(head == NULL) // Checks whether Linked List is empty
        {
            cout << "\nNo patient records available!";
            return;
        }

        cout << "\n===== ALL PATIENT RECORDS =====";

        // Traverses the complete Linked List
        while(temp != NULL)
        {
            cout << "\n\nPatient ID: " << temp->id;
            cout << "\nPatient Name: " << temp->name;
            cout << "\nPatient Age: " << temp->age;
            cout << "\nDisease: " << temp->disease;

            temp = temp->next; // Moves to next patient
        }
    }

    // Function to search and display a patient
    void searchAndDisplay()
    {
        int id;

        cout << "\nEnter Patient ID to search: ";
        cin >> id; // Takes patient ID

        Patient* p = searchPatient(id); // Searches patient

        if(p == NULL)
        {
            cout << "\nPatient not found!";
        }
        else
        {
            // Displays patient details if found
            cout << "\nPatient Found!";
            cout << "\nPatient ID: " << p->id;
            cout << "\nName: " << p->name;
            cout << "\nAge: " << p->age;
            cout << "\nDisease: " << p->disease;
        }
    }

    // Function to display Hash Table
    void displayHashTable()
    {
        cout << "\n===== HASH TABLE =====";

        // Visits all Hash Table indexes
        for(int i = 0; i < SIZE; i++)
        {
            cout << "\nIndex " << i << ": ";

            HashNode* temp = table[i]; // Starts at current index

            // Displays all nodes in the chain
            while(temp != NULL)
            {
                cout << temp->id << " -> ";

                temp = temp->next; // Moves to next node
            }

            cout << "NULL"; // Shows end of chain
        }
    }

    // Destructor frees dynamically allocated memory
    ~Hospital()
    {
        // Deletes all Hash Table nodes
        for(int i = 0; i < SIZE; i++)
        {
            HashNode* temp = table[i];

            while(temp != NULL)
            {
                HashNode* nextNode = temp->next;

                delete temp; // Deletes current Hash Table node

                temp = nextNode; // Moves to next node
            }
        }

        // Deletes all patient nodes
        Patient* temp = head;

        while(temp != NULL)
        {
            Patient* nextPatient = temp->next;

            delete temp; // Deletes current patient

            temp = nextPatient; // Moves to next patient
        }
    }
};

// Main function: Program execution starts here
int main()
{
    Hospital h; // Creates Hospital object

    int choice; // Stores user's menu choice

    // Repeats menu until user selects Exit
    do
    {
        cout << "\n\n===== SMART HOSPITAL PATIENT RECORD SYSTEM =====";

        cout << "\n1. Register New Patient";
        cout << "\n2. Update Patient Information";
        cout << "\n3. Discharge Patient";
        cout << "\n4. Display All Patients";
        cout << "\n5. Search Patient";
        cout << "\n6. Display Hash Table";
        cout << "\n7. Exit";

        cout << "\nEnter your choice: ";
        cin >> choice; // Takes user's choice

        // Executes function according to user's choice
        switch(choice)
        {
            case 1:
                h.registerPatient(); // Registers patient
                break;

            case 2:
                h.updatePatient(); // Updates patient
                break;

            case 3:
                h.dischargePatient(); // Discharges patient
                break;

            case 4:
                h.displayPatients(); // Displays all patients
                break;

            case 5:
                h.searchAndDisplay(); // Searches patient
                break;

            case 6:
                h.displayHashTable(); // Displays Hash Table
                break;

            case 7:
                cout << "\nThank you!";
                break;

            default:
                cout << "\nInvalid choice!";
        }

    }
    while(choice != 7); // Repeats until choice is 7

    return 0; // Ends program successfully
}
