
#include <iostream>  // Used for input and output (cin and cout)
#include <queue>     // Used to implement Queue
#include <stack>     // Used to implement Stack
#include <string>    // Used to store customer names and categories
using namespace std;

// Structure is used to store customer details together
struct Customer
{
    int token;          // Stores the customer's token number
    string name;        // Stores the customer's name
    string category;    // Stores whether customer is Normal or Priority
};

int main()
{
    // Queue stores normal customers in FIFO order
    // FIFO means First In First Out
    queue<Customer> normalQueue;

    // This queue stores senior citizens and differently-abled customers
    // They are given priority over normal customers
    queue<Customer> priorityQueue;

    // Stack stores the history of recently served customers
    // Stack follows LIFO (Last In First Out)
    stack<Customer> history;

    int choice;          // Stores the menu choice entered by the user
    int tokenNumber = 1; // Token numbering starts from 1

    // do-while loop displays the menu repeatedly
    do
    {
        cout << "\n===== BANK TOKEN MANAGEMENT SYSTEM =====";

        // Displaying all available operations
        cout << "\n1. Register Customer";
        cout << "\n2. Serve Customer";
        cout << "\n3. Display Waiting Customers";
        cout << "\n4. Display Served Customer History";
        cout << "\n5. Exit";

        cout << "\nEnter your choice: ";
        cin >> choice; // Takes the user's choice

        // Switch selects the operation according to user's choice
        switch(choice)
        {
            case 1:
            {
                Customer c; // Creates a customer variable

                // Assigns a unique token number to the customer
                c.token = tokenNumber++;

                // Clears the input buffer before reading a name
                cin.ignore();

                cout << "Enter customer name: ";
                getline(cin, c.name); // Reads the complete customer name

                // Displays customer categories
                cout << "\n1. Normal";
                cout << "\n2. Senior Citizen";
                cout << "\n3. Differently-Abled";
                cout << "\nEnter category: ";

                int categoryChoice;
                cin >> categoryChoice; // Takes customer category

                // If customer selects Normal
                if(categoryChoice == 1)
                {
                    c.category = "Normal";

                    // push() inserts customer at the end of normal queue
                    normalQueue.push(c);
                }

                // If customer selects Senior Citizen
                else if(categoryChoice == 2)
                {
                    c.category = "Senior Citizen";

                    // Inserts senior citizen into priority queue
                    priorityQueue.push(c);
                }

                // If customer selects Differently-Abled
                else if(categoryChoice == 3)
                {
                    c.category = "Differently-Abled";

                    // Inserts differently-abled customer into priority queue
                    priorityQueue.push(c);
                }

                else
                {
                    // Displays message for an invalid category
                    cout << "\nInvalid category!";
                    tokenNumber--; // Reuses the token number
                    break;
                }

                // Displays registration confirmation
                cout << "\nCustomer registered successfully!";
                cout << "\nToken Number: " << c.token;

                break;
            }

            case 2:
            {
                // First check whether priority queue contains customers
                if(!priorityQueue.empty())
                {
                    // front() accesses the first priority customer
                    Customer c = priorityQueue.front();

                    // pop() removes the served customer from the queue
                    priorityQueue.pop();

                    // push() stores the served customer in history stack
                    history.push(c);

                    // Displays served customer details
                    cout << "\nServing Priority Customer";
                    cout << "\nToken: " << c.token;
                    cout << "\nName: " << c.name;
                    cout << "\nCategory: " << c.category;
                }

                // If no priority customer is waiting
                // then check the normal queue
                else if(!normalQueue.empty())
                {
                    // Accesses the first normal customer
                    Customer c = normalQueue.front();

                    // Removes the customer from normal queue
                    normalQueue.pop();

                    // Stores the served customer in history stack
                    history.push(c);

                    cout << "\nServing Normal Customer";
                    cout << "\nToken: " << c.token;
                    cout << "\nName: " << c.name;
                }

                else
                {
                    // Displays message if both queues are empty
                    cout << "\nNo customers waiting!";
                }

                break;
            }

            case 3:
            {
                cout << "\n--- PRIORITY CUSTOMERS ---";

                // Creates a temporary copy of priority queue
                // This allows us to display customers without deleting them
                queue<Customer> temp = priorityQueue;

                // Checks whether priority queue is empty
                if(temp.empty())
                    cout << "\nNo priority customers.";

                // Displays all priority customers
                while(!temp.empty())
                {
                    // Gets the first customer from temporary queue
                    Customer c = temp.front();

                    cout << "\nToken: " << c.token;
                    cout << " Name: " << c.name;

                    // Removes customer only from temporary queue
                    temp.pop();
                }

                cout << "\n--- NORMAL CUSTOMERS ---";

                // Copies normal queue into temporary queue
                temp = normalQueue;

                if(temp.empty())
                    cout << "\nNo normal customers.";

                // Displays all normal customers
                while(!temp.empty())
                {
                    Customer c = temp.front();

                    cout << "\nToken: " << c.token;
                    cout << " Name: " << c.name;

                    temp.pop(); // Moves to the next customer
                }

                break;
            }

            case 4:
            {
                cout << "\n--- SERVED CUSTOMER HISTORY ---";

                // Checks whether history stack is empty
                if(history.empty())
                {
                    cout << "\nNo history available.";
                }

                else
                {
                    // Creates a temporary copy of history stack
                    stack<Customer> temp = history;

                    // Displays recently served customers first
                    while(!temp.empty())
                    {
                        // top() accesses the most recently served customer
                        Customer c = temp.top();

                        cout << "\nToken: " << c.token;
                        cout << " Name: " << c.name;
                        cout << " Category: " << c.category;

                        // Removes customer from temporary stack
                        temp.pop();
                    }
                }

                break;
            }

            case 5:
                // Exits the program
                cout << "\nThank you for using Bank Token System!";
                break;

            default:
                // Executes when user enters an invalid menu choice
                cout << "\nInvalid choice!";
        }

    }
    // Repeats menu until user selects option 5
    while(choice != 5);

    return 0; // Successfully ends the program
}

