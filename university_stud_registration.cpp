
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

// Structure to store course information
struct Course
{
    string courseName;  // Stores course name
    Course* next;       // Points to next course
};

// Structure to store student information
struct Student
{
    int roll;           // Stores unique roll number
    string name;        // Stores student name
    string department;  // Stores department name
    Course* courses;    // Points to student's course list
};

// Node of Student Linked List
struct Node
{
    Student data;       // Stores student information
    Node* next;         // Points to next student
};

// Class to manage student registration system
class StudentSystem
{
    Node* head;         // Points to first student node

    // Hash Table with Chaining
    vector<list<Student*>> hashTable;

    int size;           // Stores hash table size

public:

    // Constructor initializes the system
    StudentSystem()
    {
        head = NULL;     // Initially no students
        size = 10;       // Hash Table size is 10
        hashTable.resize(size);
    }

    // Hash Function calculates index using Roll Number
    int hashFunction(int roll)
    {
        return roll % size;
    }

    // Searches student using Roll Number
    Student* searchStudent(int roll)
    {
        int index = hashFunction(roll); // Finds hash index

        // Checks students present in that bucket
        for (Student* s : hashTable[index])
        {
            if (s->roll == roll)
                return s; // Returns student if found
        }

        return NULL; // Student not found
    }

    // Function to register a new student
    void registerStudent()
    {
        Student s;

        cout << "Enter Roll Number: ";
        cin >> s.roll;

        // Checks whether Roll Number already exists
        if (searchStudent(s.roll) != NULL)
        {
            cout << "Roll Number Already Exists!\n";
            return;
        }

        cin.ignore(); // Clears input buffer

        cout << "Enter Student Name: ";
        getline(cin, s.name);

        cout << "Enter Department: ";
        getline(cin, s.department);

        s.courses = NULL; // Initially no courses enrolled

        // Creates a new student node
        Node* newNode = new Node;

        newNode->data = s; // Stores student information
        newNode->next = head; // Connects to old first node
        head = newNode; // Makes new node first node

        // Inserts student into Hash Table
        int index = hashFunction(s.roll);

        // Chaining handles students with same hash index
        hashTable[index].push_back(&newNode->data);

        cout << "Student Registered Successfully!\n";
    }

    // Function to update student information
    void updateStudent()
    {
        int roll;

        cout << "Enter Roll Number: ";
        cin >> roll;

        // Searches student using Hash Table
        Student* s = searchStudent(roll);

        if (s == NULL)
        {
            cout << "Student Not Found!\n";
            return;
        }

        cin.ignore();

        cout << "Enter New Name: ";
        getline(cin, s->name);

        cout << "Enter New Department: ";
        getline(cin, s->department);

        cout << "Student Information Updated!\n";
    }

    // Function to enroll student in a course
    void enrollCourse()
    {
        int roll;
        string courseName;

        cout << "Enter Roll Number: ";
        cin >> roll;

        // Searches student using Roll Number
        Student* s = searchStudent(roll);

        if (s == NULL)
        {
            cout << "Student Not Found!\n";
            return;
        }

        cin.ignore();

        cout << "Enter Course Name: ";
        getline(cin, courseName);

        // Checks whether student is already enrolled
        Course* temp = s->courses;

        while (temp != NULL)
        {
            if (temp->courseName == courseName)
            {
                cout << "Already Enrolled in This Course!\n";
                return;
            }

            temp = temp->next; // Moves to next course
        }

        // Creates a new course node
        Course* newCourse = new Course;

        newCourse->courseName = courseName;
        newCourse->next = s->courses;

        // Adds course at beginning of course Linked List
        s->courses = newCourse;

        cout << "Course Enrollment Successful!\n";
    }

    // Function to withdraw student from a course
    void withdrawCourse()
    {
        int roll;
        string courseName;

        cout << "Enter Roll Number: ";
        cin >> roll;

        // Finds student using Roll Number
        Student* s = searchStudent(roll);

        if (s == NULL)
        {
            cout << "Student Not Found!\n";
            return;
        }

        cin.ignore();

        cout << "Enter Course Name to Withdraw: ";
        getline(cin, courseName);

        Course* temp = s->courses; // Starts from first course
        Course* prev = NULL;       // Stores previous course

        // Searches for the required course
        while (temp != NULL &&
               temp->courseName != courseName)
        {
            prev = temp;
            temp = temp->next;
        }

        // Course does not exist
        if (temp == NULL)
        {
            cout << "Course Not Found!\n";
            return;
        }

        // If first course is removed
        if (prev == NULL)
            s->courses = temp->next;
        else
            prev->next = temp->next;

        delete temp; // Frees memory of course node

        cout << "Course Withdrawal Successful!\n";
    }

    // Function to display all student records
    void displayStudents()
    {
        Node* temp = head; // Starts from first student

        if (temp == NULL)
        {
            cout << "No Student Records Available!\n";
            return;
        }

        cout << "\n===== STUDENT RECORDS =====\n";

        // Traverses all student nodes
        while (temp != NULL)
        {
            cout << "\nRoll Number: "
                 << temp->data.roll << endl;

            cout << "Name: "
                 << temp->data.name << endl;

            cout << "Department: "
                 << temp->data.department << endl;

            cout << "Courses Enrolled:\n";

            // Accesses the student's course Linked List
            Course* c = temp->data.courses;

            if (c == NULL)
                cout << "No Courses Enrolled\n";

            // Displays all enrolled courses
            while (c != NULL)
            {
                cout << "- " << c->courseName << endl;
                c = c->next;
            }

            temp = temp->next; // Moves to next student

            cout << "-----------------------\n";
        }
    }

    // Function to remove a student record
    void removeStudent()
    {
        int roll;

        cout << "Enter Roll Number: ";
        cin >> roll;

        Node* temp = head; // Starts from first student
        Node* prev = NULL; // Stores previous student

        // Searches for student using Roll Number
        while (temp != NULL &&
               temp->data.roll != roll)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Student Not Found!\n";
            return;
        }

        // Finds Hash Table index
        int index = hashFunction(roll);

        // Removes student from Hash Table
        hashTable[index].remove(&temp->data);

        // If first student is deleted
        if (prev == NULL)
            head = temp->next;
        else
            prev->next = temp->next;

        // Deletes all courses of that student
        Course* c = temp->data.courses;

        while (c != NULL)
        {
            Course* nextCourse = c->next;
            delete c;
            c = nextCourse;
        }

        delete temp; // Deletes student node

        cout << "Student Record Removed Successfully!\n";
    }

    // Function to search and display student
    void search()
    {
        int roll;

        cout << "Enter Roll Number: ";
        cin >> roll;

        // Searches student using Hash Table
        Student* s = searchStudent(roll);

        if (s == NULL)
        {
            cout << "Student Not Found!\n";
        }
        else
        {
            cout << "\nStudent Found!\n";

            cout << "Roll Number: " << s->roll << endl;
            cout << "Name: " << s->name << endl;
            cout << "Department: " << s->department << endl;
        }
    }

    // Function to display main menu
    void menu()
    {
        int choice;

        do
        {
            cout << "\n===== UNIVERSITY STUDENT SYSTEM =====\n";

            cout << "1. Register Student\n";
            cout << "2. Update Student Information\n";
            cout << "3. Enroll Student in Course\n";
            cout << "4. Withdraw Student from Course\n";
            cout << "5. Remove Student Record\n";
            cout << "6. Display All Students\n";
            cout << "7. Search Student\n";
            cout << "8. Exit\n";

            cout << "Enter Your Choice: ";
            cin >> choice;

            // Performs operation based on user choice
            switch (choice)
            {
                case 1:
                    registerStudent();
                    break;

                case 2:
                    updateStudent();
                    break;

                case 3:
                    enrollCourse();
                    break;

                case 4:
                    withdrawCourse();
                    break;

                case 5:
                    removeStudent();
                    break;

                case 6:
                    displayStudents();
                    break;

                case 7:
                    search();
                    break;

                case 8:
                    cout << "Thank You!\n";
                    break;

                default:
                    cout << "Invalid Choice!\n";
            }

        } while (choice != 8); // Repeats until Exit is selected
    }

    // Destructor frees all dynamically allocated memory
    ~StudentSystem()
    {
        while (head != NULL)
        {
            Node* temp = head;
            head = head->next;

            // Deletes all courses of current student
            Course* c = temp->data.courses;

            while (c != NULL)
            {
                Course* nextCourse = c->next;
                delete c;
                c = nextCourse;
            }

            delete temp; // Deletes student node
        }
    }
};

// Main function: Execution starts here
int main()
{
    StudentSystem obj; // Creates StudentSystem object

    obj.menu();        // Calls menu function

    return 0;          // Ends program
}
