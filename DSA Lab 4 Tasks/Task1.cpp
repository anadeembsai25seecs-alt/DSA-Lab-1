#include <iostream>
#include <string>
using namespace std;

// Node of the doubly linked list
struct Node
{
    int songID;
    string songName;
    string duration;

    Node* prev;
    Node* next;
};

// Head and tail of playlist
Node* head = NULL;
Node* tail = NULL;

// Current song for Play Next / Previous
Node* current = NULL;


// 1. Add Song
void addSong()
{
    Node* newNode = new Node;

    cout << "Enter Song ID: ";
    cin >> newNode->songID;

    cout << "Enter Song Name: ";
    cin.ignore();
    getline(cin, newNode->songName);

    cout << "Enter Duration (mm:ss): ";
    cin >> newNode->duration;

    newNode->prev = NULL;
    newNode->next = NULL;

    // If playlist is empty
    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
        current = head;
    }
    else
    {
        // Add at the end
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    cout << "Song added successfully!\n";
}


// 2. Delete Song
void deleteSong()
{
    int id;
    cout << "Enter Song ID to delete: ";
    cin >> id;

    Node* temp = head;

    while (temp != NULL)
    {
        if (temp->songID == id)
        {
            // If deleting the first node
            if (temp == head)
            {
                head = temp->next;

                if (head != NULL)
                    head->prev = NULL;
            }
            else
            {
                temp->prev->next = temp->next;

                if (temp->next != NULL)
                    temp->next->prev = temp->prev;
            }

            // If deleting the last node
            if (temp == tail)
            {
                tail = temp->prev;
            }

            // If current song is deleted
            if (current == temp)
            {
                if (temp->next != NULL)
                    current = temp->next;
                else
                    current = temp->prev;
            }

            delete temp;

            cout << "Song deleted successfully!\n";
            return;
        }

        temp = temp->next;
    }

    cout << "Song not found!\n";
}


// 3. Display Playlist Forward
void displayForward()
{
    if (head == NULL)
    {
        cout << "Playlist is empty!\n";
        return;
    }

    Node* temp = head;

    cout << "\n--- Playlist Forward ---\n";

    while (temp != NULL)
    {
        cout << "ID: " << temp->songID
            << " | Name: " << temp->songName
            << " | Duration: " << temp->duration << endl;

        temp = temp->next;
    }
}


// 4. Display Playlist Backward
void displayBackward()
{
    if (tail == NULL)
    {
        cout << "Playlist is empty!\n";
        return;
    }

    Node* temp = tail;

    cout << "\n--- Playlist Backward ---\n";

    while (temp != NULL)
    {
        cout << "ID: " << temp->songID
            << " | Name: " << temp->songName
            << " | Duration: " << temp->duration << endl;

        temp = temp->prev;
    }
}


// 5. Search Song
void searchSong()
{
    int id;

    cout << "Enter Song ID to search: ";
    cin >> id;

    Node* temp = head;

    while (temp != NULL)
    {
        if (temp->songID == id)
        {
            cout << "\nSong Found!\n";
            cout << "Song ID: " << temp->songID << endl;
            cout << "Song Name: " << temp->songName << endl;
            cout << "Duration: " << temp->duration << endl;

            return;
        }

        temp = temp->next;
    }

    cout << "Song not found!\n";
}


// 6. Play Next Song
void playNext()
{
    if (current == NULL)
    {
        cout << "Playlist is empty!\n";
        return;
    }

    if (current->next != NULL)
    {
        current = current->next;

        cout << "\nPlaying Next Song:\n";
        cout << "ID: " << current->songID << endl;
        cout << "Name: " << current->songName << endl;
        cout << "Duration: " << current->duration << endl;
    }
    else
    {
        cout << "Already at the last song!\n";
    }
}


// 7. Play Previous Song
void playPrevious()
{
    if (current == NULL)
    {
        cout << "Playlist is empty!\n";
        return;
    }

    if (current->prev != NULL)
    {
        current = current->prev;

        cout << "\nPlaying Previous Song:\n";
        cout << "ID: " << current->songID << endl;
        cout << "Name: " << current->songName << endl;
        cout << "Duration: " << current->duration << endl;
    }
    else
    {
        cout << "Already at the first song!\n";
    }
}


// 8. Reverse Playlist
void reversePlaylist()
{
    if (head == NULL)
    {
        cout << "Playlist is empty!\n";
        return;
    }

    Node* temp = head;
    Node* swapNode;

    while (temp != NULL)
    {
        // Swap next and previous pointers
        swapNode = temp->prev;
        temp->prev = temp->next;
        temp->next = swapNode;

        // Move to the next node
        // Since pointers were swapped, move using prev
        temp = temp->prev;
    }

    // Swap head and tail
    swapNode = head;
    head = tail;
    tail = swapNode;

    // Keep current song the same
    cout << "Playlist reversed successfully!\n";
}


// Main function
int main()
{
    int choice;

    do
    {
        cout << "\n\tPLAYLIST\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Search Song\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Reverse Playlist\n";
        cout << "9. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addSong();
            break;

        case 2:
            deleteSong();
            break;

        case 3:
            displayForward();
            break;

        case 4:
            displayBackward();
            break;

        case 5:
            searchSong();
            break;

        case 6:
            playNext();
            break;

        case 7:
            playPrevious();
            break;

        case 8:
            reversePlaylist();
            break;

        case 9:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 9);

    return 0;
}