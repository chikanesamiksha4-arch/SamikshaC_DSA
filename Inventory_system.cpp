#include <iostream>
#include <string>
using namespace std;



// Structure representing each Product node in the Linked List
struct Product {
    int id;                 // Unique Product ID
    string name;            // Product Name
    double price;           // Product Price
    int stock;              // Available Quantity
    Product* next;          // Pointer to the next product in the chain
};

// Hash Table: Array of Linked List head pointers
Product* hashTable[TABLE_SIZE];

// Initialize all buckets in the hash table to NULL
void initTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

// Hash Function: Maps Product ID to an index (0 to TABLE_SIZE - 1)
int hashFunction(int id) {
    return id % TABLE_SIZE;
}

// 1. Add a new product (Insert at head of chain - resolves collisions via Chaining)
void addProduct() {
    Product* newNode = new Product();
    cout << "Enter Product ID: ";
    cin >> newNode->id;
    cin.ignore(); // Clear input buffer before reading string
    cout << "Enter Product Name: ";
    getline(cin, newNode->name);
    cout << "Enter Price: ";
    cin >> newNode->price;
    cout << "Enter Stock Quantity: ";
    cin >> newNode->stock;

    int index = hashFunction(newNode->id);
    newNode->next = hashTable[index]; // Link new node to existing chain
    hashTable[index] = newNode;       // Make new node the head of that bucket
    cout << "Product added at Hash Index " << index << "!\n";
}

// 2. Search / Retrieve a product using Hash Table
void searchProduct() {
    int id;
    cout << "Enter Product ID to search: ";
    cin >> id;

    int index = hashFunction(id);
    Product* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->id == id) {
            cout << "Found -> ID: " << temp->id << " | Name: " << temp->name
                 << " | Price: " << temp->price << " | Stock: " << temp->stock << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Product not found!\n";
}

// 3. Update existing product details
void updateProduct() {
    int id;
    cout << "Enter Product ID to update: ";
    cin >> id;

    int index = hashFunction(id);
    Product* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->id == id) {
            cin.ignore();
            cout << "Enter New Name: ";
            getline(cin, temp->name);
            cout << "Enter New Price: ";
            cin >> temp->price;
            cout << "Enter New Stock: ";
            cin >> temp->stock;
            cout << "Product updated successfully!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Product not found!\n";
}

// 4. Remove a discontinued product (Delete node from Linked List)
void removeProduct() {
    int id;
    cout << "Enter Product ID to remove: ";
    cin >> id;

    int index = hashFunction(id);
    Product* temp = hashTable[index];
    Product* prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Product not found!\n";
        return;
    }

    if (prev == NULL) {
        hashTable[index] = temp->next; // Deleting the first node in chain
    } else {
        prev->next = temp->next;       // Bypass the deleted node
    }
    delete temp;                       // Free memory
    cout << "Product removed successfully!\n";
}

// 5. Display all available products across all Hash Table buckets
void displayCatalog() {
    cout << "\n--- Product Catalog (Hash Table + Chaining) ---\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Bucket [" << i << "]: ";
        Product* temp = hashTable[i];
        if (temp == NULL) {
            cout << "Empty";
        }
        while (temp != NULL) {
            cout << "[ID:" << temp->id << ", " << temp->name
                 << ", Rs." << temp->price << ", Qty:" << temp->stock << "] -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

int main() {
    initTable();
    int choice;
    do {
        cout << "\n=== E-Commerce Inventory Menu ===\n";
        cout << "1. Add Product\n2. Search Product\n3. Update Product\n4. Remove Product\n5. Display All Products\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: searchProduct(); break;
            case 3: updateProduct(); break;
            case 4: removeProduct(); break;
            case 5: displayCatalog(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
