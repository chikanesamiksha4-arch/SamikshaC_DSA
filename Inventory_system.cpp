
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

// Structure to store product information
struct Product
{
    int id;              // Stores unique product ID
    string name;         // Stores product name
    float price;         // Stores product price
    int quantity;        // Stores available quantity
};

// Node of Linked List
struct Node
{
    Product data;        // Stores product information
    Node* next;          // Points to the next node
};

// Class to manage the complete product system
class ProductSystem
{
    Node* head;          // Points to the first node of Linked List

    // Hash Table uses Chaining to handle collisions
    vector<list<Product*>> hashTable;

    int size;            // Stores hash table size

public:

    // Constructor initializes the system
    ProductSystem()
    {
        head = NULL;     // Initially Linked List is empty
        size = 10;       // Hash Table contains 10 positions
        hashTable.resize(size);
    }

    // Hash Function calculates the index
    int hashFunction(int id)
    {
        return id % size;  // Returns index using modulo operator
    }

    // Searches product using Product ID
    Product* searchProduct(int id)
    {
        int index = hashFunction(id); // Finds hash table index

        // Checks all products at that index
        for (Product* p : hashTable[index])
        {
            if (p->id == id) // Checks whether ID matches
                return p;    // Returns product if found
        }

        return NULL; // Returns NULL if product is not found
    }

    // Function to add a new product
    void addProduct()
    {
        Product p; // Creates a product variable

        cout << "Enter Product ID: ";
        cin >> p.id;

        // Checks whether Product ID already exists
        if (searchProduct(p.id) != NULL)
        {
            cout << "Product ID already exists!\n";
            return;
        }

        cin.ignore(); // Clears input buffer

        cout << "Enter Product Name: ";
        getline(cin, p.name);

        cout << "Enter Price: ";
        cin >> p.price;

        cout << "Enter Quantity: ";
        cin >> p.quantity;

        // Creates a new Linked List node
        Node* newNode = new Node;

        newNode->data = p; // Stores product information
        newNode->next = head; // Connects new node to old first node
        head = newNode; // Makes new node the first node

        // Inserts product into Hash Table
        int index = hashFunction(p.id);

        // Adds product to the bucket using Chaining
        hashTable[index].push_back(&newNode->data);

        cout << "Product Added Successfully!\n";
    }

    // Function to display all products
    void displayProducts()
    {
        Node* temp = head; // Starts from first node

        // Checks whether Linked List is empty
        if (temp == NULL)
        {
            cout << "No Products Available!\n";
            return;
        }

        cout << "\n--- Product List ---\n";

        // Traverses the complete Linked List
        while (temp != NULL)
        {
            cout << "ID: " << temp->data.id << endl;
            cout << "Name: " << temp->data.name << endl;
            cout << "Price: " << temp->data.price << endl;
            cout << "Quantity: " << temp->data.quantity << endl;

            cout << "-------------------\n";

            temp = temp->next; // Moves to next node
        }
    }

    // Function to update product details
    void updateProduct()
    {
        int id;

        cout << "Enter Product ID: ";
        cin >> id;

        // Searches product using Hash Table
        Product* p = searchProduct(id);

        // Checks whether product exists
        if (p == NULL)
        {
            cout << "Product Not Found!\n";
            return;
        }

        cin.ignore();

        cout << "Enter New Product Name: ";
        getline(cin, p->name);

        cout << "Enter New Price: ";
        cin >> p->price;

        cout << "Enter New Quantity: ";
        cin >> p->quantity;

        cout << "Product Updated Successfully!\n";
    }

    // Function to remove a product
    void removeProduct()
    {
        int id;

        cout << "Enter Product ID: ";
        cin >> id;

        Node* temp = head; // Starts from first node
        Node* prev = NULL; // Stores previous node

        // Searches for the product in Linked List
        while (temp != NULL && temp->data.id != id)
        {
            prev = temp;       // Saves current node
            temp = temp->next; // Moves to next node
        }

        // Checks whether product exists
        if (temp == NULL)
        {
            cout << "Product Not Found!\n";
            return;
        }

        // Finds the Hash Table index
        int index = hashFunction(id);

        // Removes product from Hash Table
        hashTable[index].remove(&temp->data);

        // If first node is deleted
        if (prev == NULL)
            head = temp->next;
        else
            prev->next = temp->next;

        delete temp; // Frees memory of deleted node

        cout << "Product Removed Successfully!\n";
    }

    // Function to search and display a product
    void search()
    {
        int id;

        cout << "Enter Product ID: ";
        cin >> id;

        // Searches product using Hash Table
        Product* p = searchProduct(id);

        if (p == NULL)
        {
            cout << "Product Not Found!\n";
        }
        else
        {
            cout << "\nProduct Found!\n";

            cout << "ID: " << p->id << endl;
            cout << "Name: " << p->name << endl;
            cout << "Price: " << p->price << endl;
            cout << "Quantity: " << p->quantity << endl;
        }
    }

    // Function to display menu
    void menu()
    {
        int choice;

        do
        {
            cout << "\n===== E-COMMERCE SYSTEM =====\n";

            cout << "1. Add Product\n";
            cout << "2. Update Product\n";
            cout << "3. Remove Product\n";
            cout << "4. Display Products\n";
            cout << "5. Search Product\n";
            cout << "6. Exit\n";

            cout << "Enter Choice: ";
            cin >> choice;

            // Executes operation according to user choice
            switch (choice)
            {
                case 1:
                    addProduct();
                    break;

                case 2:
                    updateProduct();
                    break;

                case 3:
                    removeProduct();
                    break;

                case 4:
                    displayProducts();
                    break;

                case 5:
                    search();
                    break;

                case 6:
                    cout << "Thank You!\n";
                    break;

                default:
                    cout << "Invalid Choice!\n";
            }

        } while (choice != 6); // Repeats until user selects Exit
    }

    // Destructor releases dynamically allocated memory
    ~ProductSystem()
    {
        while (head != NULL)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Main function: Program execution starts here
int main()
{
    ProductSystem obj; // Creates object of ProductSystem

    obj.menu();        // Calls menu function

    return 0;          // Ends program successfully
}
