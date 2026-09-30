#include <iostream>
using namespace std;

// Node for circular linked list
struct Node
{
    int personID;
    Node* next;
};

Node* head = NULL;


// 1. Create Circle
void createCircle(int N)
{
    Node* newNode;
    Node* temp;

    // Create first person
    head = new Node;
    head->personID = 1;
    head->next = head;

    temp = head;

    // Create remaining people
    for (int i = 2; i <= N; i++)
    {
        newNode = new Node;
        newNode->personID = i;

        newNode->next = head;
        temp->next = newNode;

        temp = newNode;
    }
}


// 2. Elimination Process
void eliminationProcess(int N, int k)
{
    Node* current = head;
    Node* previous = NULL;

    cout << "\nEliminated Order: ";

    // Continue until only one person remains
    while (current->next != current)
    {
        // Move k-1 times
        for (int count = 1; count < k; count++)
        {
            previous = current;
            current = current->next;
        }

        // Display eliminated person
        cout << current->personID << " ";

        // Remove current person
        previous->next = current->next;

        delete current;

        // Move to the next person
        current = previous->next;
    }

    // The remaining person is the survivor
    head = current;

    cout << endl;
}


// 3. Display Survivor
void displaySurvivor()
{
    cout << "Survivor: Person " << head->personID << endl;
}


// Main function
int main()
{
    int N, k;

    cout << "Enter number of people (N): ";
    cin >> N;

    cout << "Enter step count (k): ";
    cin >> k;

    // Create circular linked list
    createCircle(N);

    // Perform elimination
    eliminationProcess(N, k);

    // Display survivor
    displaySurvivor();

    return 0;
}