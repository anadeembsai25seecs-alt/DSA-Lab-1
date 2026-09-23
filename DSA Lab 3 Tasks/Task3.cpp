#include <iostream>
using namespace std;

struct Node { //creating nodes
    int data;
    Node* next;
};

Node* head = nullptr; // head pointer

//Task 1 : Insert at head
void insertAtHead(int value) {

    Node* newNode = new Node(); //a node is created in heap and newNode points to it

    newNode->data = value;  //this line first derefrences the newNode to access the node in heap and then adds data to it
                             //can also be written as (*newNode).data = value;
    newNode->next = head;  //this line stores in the pointer part of node the address that was stored in head
    head = newNode;  // now the newNode is called the head

    cout << "Inserted " << value << " at head.\n";
}

// Task 2. Insert a new node at 3rd position
void insertAtThird(int value) {
    Node* newNode = new Node();
    newNode->data = value;

    // Case 1: empty list

    if (head == nullptr) {
        cout << "List is empty. The node will be stored at head.\n";
        newNode->next = nullptr; //newNode now points to null as it is only one element 
        head = newNode;
        return;
    }

    // Case 2: only 1 node

    if (head->next == nullptr) { // it checks if the head node points to null which will mean there is only 1 element
        cout << "List has less than 2 nodes. The node will be inserted at the end.\n";
        newNode->next = nullptr; //as the last element will always point to nullptr
        head->next = newNode; //head now stores the pointer to next node
        return;
    }

    // Case 3: insert at 3rd position
    Node* temp = head;
    temp = temp->next; // we point temp to 2nd element so that we can insert at the next position
    newNode->next = temp->next; /*2nd element stores the address of 3rd element but when we will store
                                 the newNode as 3rd element so this address will point to 4th element so
                                 we stored it in our 3rd element so that it points to 4th element*/
    temp->next = newNode;        //here we stored in the 2nd element the address of 3rd element(newNode)
    cout << "Inserted " << value << " at the 3rd position.\n";
}

// Task 3. Display the contents of the linked list
void displayList() {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    Node* temp = head;
    cout << "List: ";
    while (temp != nullptr) {  //the loop will work until it reaches nullptr because it is what is pointed to by last element
        cout << temp->data << " -> ";
        temp = temp->next;   //iterates through the list
    }
    cout << "NULL\n";
}

//Task 4. Delete the last node of linked list

void deleteLast() {
    if (head == nullptr) {
        cout << "List is empty.So no last element.\n";
        return;
    }

    // Case: only one node yes
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        cout << "Deleted the only node in the list.\n";
        return;
    }

    // Traverse to the second-last node
    Node* temp = head;
    while (temp->next->next != nullptr) { //on 2nd last element the address stored in the one pointed to by 2nd last element will be null
        temp = temp->next; //keeps on traversing until 2nd last element achieved
    }
    delete temp->next; //temp now points to 2nd last element and the node stored at that address is deleted
    temp->next = nullptr;
    cout << "Deleted the last node.\n";
}

// Task 5. Count the number of nodes in the list

int countNodes() {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Task 6. Reverse the linked list iteratively

void reverseList() {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next; // store next node
        current->next = prev; // reverse the link
        prev = current;       // move prev forward
        current = next;       // move current forward
    }
    head = prev; // update head to the new first node
    cout << "List reversed successfully.\n";
}

// Task 7. Search for a given value in the list
void searchValue(int value) {
    Node* temp = head;
    int position = 0;
    bool found = false;

    while (temp != nullptr) {
        if (temp->data == value) {
            found = true;
            break;
        }
        temp = temp->next;
        position++;
    }

    if (found)
        cout << "Value " << value << " found at position " << position << " (0-indexed).\n";
    else
        cout << "Value " << value << " not found in the list.\n";
}

// Free all remaining nodes before program exit
void freeList() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
}

//Task 8. Menu-driven interface
int main() {
    int choice, value;

    do {
        cout << "\n---- Singly Linked List Menu ----\n";
        cout << "1. Insert at Head\n";
        cout << "2. Insert at 3rd Position\n";
        cout << "3. Display List\n";
        cout << "4. Delete Last Node\n";
        cout << "5. Count Nodes\n";
        cout << "6. Reverse List\n";
        cout << "7. Search for a Value\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert at head: ";
            cin >> value;
            insertAtHead(value);
            displayList();
            break;

        case 2:
            cout << "Enter value to insert at 3rd position: ";
            cin >> value;
            insertAtThird(value);
            displayList();
            break;

        case 3:
            displayList();
            break;

        case 4:
            deleteLast();
            displayList();
            break;

        case 5:
            cout << "Number of nodes in the list: " << countNodes() << "\n";
            break;

        case 6:
            reverseList();
            displayList();
            break;

        case 7:
            cout << "Enter value to search: ";
            cin >> value;
            searchValue(value);
            break;

        case 8:
            cout << "Exiting program. Freeing allocated memory...\n";
            freeList();
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}

