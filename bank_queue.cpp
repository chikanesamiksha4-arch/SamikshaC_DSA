#include <iostream>                 // Include input/output stream library
using namespace std;                // Use standard namespace for cout and cin

int main() {                        // Main function where program execution begins
    int queue[5];                   // Declare an array of size 5 to act as a queue
    int front = 0, rear = -1;       // Initialize front to 0 and rear to -1 (empty queue)

    // --- ENQUEUE: Store 5 customer tokens ---
    cout << "Enter 5 customer token numbers:\n";  // Prompt user to enter 5 tokens
    for (int i = 0; i < 5; i++) {                   // Loop 5 times to read 5 tokens
        rear++;                                     // Move rear pointer forward by 1
        cin >> queue[rear];                         // Store entered token at rear position
    }

    // --- DEQUEUE: Serve customers in FIFO (First-In, First-Out) order ---
    cout << "\nServing customers in order:\n";      // Display heading for serving
    while (front <= rear) {                         // Loop until all elements from front to rear are served
        cout << "Serving Token: " << queue[front] << endl; // Print token at front
        front++;                                    // Move front pointer to the next customer
    }

    return 0;                       // End program and return 0 to OS
}
