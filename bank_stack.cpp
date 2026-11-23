#include <iostream>                 // Include input/output stream library
using namespace std;                // Use standard namespace for cout and cin

int main() {                        // Main function where program execution begins
    int stack[5];                   // Declare an array of size 5 to act as a stack
    int top = -1;                   // Initialize top to -1 (indicates stack is empty)

    // --- PUSH: Store 5 recently served customer tokens ---
    cout << "Enter 5 served customer token numbers (oldest to newest):\n"; // Prompt user
    for (int i = 0; i < 5; i++) {                   // Loop 5 times to push 5 tokens
        top++;                                      // Increment top pointer to next empty slot
        cin >> stack[top];                          // Insert token at the top of the stack
    }

    // --- POP / DISPLAY: Show service history in LIFO (Last-In, First-Out) order ---
    cout << "\nService History (Most Recent First):\n"; // Display history heading
    while (top >= 0) {                              // Loop from top down to index 0
        cout << "Token: " << stack[top] << endl;    // Display most recently served token first
        top--;                                      // Decrement top pointer to move down the stack
    }

    return 0;                       // End program and return 0 to OS
}
