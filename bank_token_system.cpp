#include <iostream>                 // Include input/output stream library
using namespace std;                // Use standard namespace for cout and cin

#define MAX 50                      // Maximum size of the bank token queue

int main() {                        // Main function where execution starts
    int queue[MAX];                 // Array to store customer token numbers
    int front = -1, rear = -1;      // Initialize front and rear to -1 (empty queue)
    int choice;                     // Variable to store user's menu selection
    int token = 100;                // Starting token counter (first token will be 101)

    do {                            // Loop to repeatedly display the menu
        cout << "\n--- Bank Token Management System ---\n";
        cout << "1. Issue a Token\n";
        cout << "2. Display All Tokens\n";
        cout << "3. Serve a Customer\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;              // Read user's choice

        switch (choice) {           // Execute block matching user's choice
            case 1:                 // Issue a new token (Enqueue)
                if (rear == MAX - 1) {                      // Check if queue is full
                    cout << "Queue is Full! Cannot issue more tokens.\n";
                } else {
                    if (front == -1) front = 0;             // Set front to 0 for the first customer
                    token++;                                // Increment token number
                    rear++;                                 // Move rear pointer forward
                    queue[rear] = token;                    // Store new token at rear
                    cout << "Token Issued: " << token << endl;
                }
                break;

            case 2:                 // Display all waiting tokens
                if (front == -1 || front > rear) {          // Check if queue is empty
                    cout << "No tokens waiting in the queue.\n";
                } else {
                    cout << "Waiting Tokens: ";
                    for (int i = front; i <= rear; i++) {   // Print from front to rear
                        cout << queue[i] << " ";
                    }
                    cout << endl;
                }
                break;

            case 3:                 // Serve the next customer (Dequeue)
                if (front == -1 || front > rear) {          // Check if queue is empty
                    cout << "No customers left to serve.\n";
                } else {
                    cout << "Serving Customer with Token: " << queue[front] << endl;
                    front++;                                // Move front pointer to next customer
                }
                break;

            case 4:                 // Exit the program
                cout << "Exiting Bank Token System...\n";
                break;

            default:                // Handle invalid menu input
                cout << "Invalid choice! Please enter 1 to 4.\n";
        }
    } while (choice != 4);          // Keep running until user selects Exit (4)

    return 0;                       // End program successfully
}
