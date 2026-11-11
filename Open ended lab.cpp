#include <iostream>
#include <string>
using namespace std;

/*BST was used to store the student records beacuse
we need to store the roll numbers in a sequence and
using BST we can do that efficiently. Also in reasonably 
balanced BST, it becomes more easy to search for an element
(worst-case time complexity = O(n))
*/
/*We have used the queue beacuse it allows to add the requests 
at end and pop the requests from front so that the requests that
arrived first can be processed first*/
/*instead of BST, linked lists could also be used to store the 
student records and its implementation is much easier than BST
but the seraching becomes more complex and you also need to sort the
array before display.*/

//BST

struct student {
    string name;
    int roll_no;
    student* left;
    student* right;

    student(int rollno, string n) :
        roll_no(rollno), name(n),
        left(nullptr), right(nullptr) {
    }
};


student* insert(student* root, int rollno, string n) {

    if (root == nullptr) {
        return new student(rollno, n);
    }

    if (rollno < root->roll_no) {
        root->left = insert(root->left, rollno, n);
    }
    else if (rollno > root->roll_no) {
        root->right = insert(root->right, rollno, n);
    }

    return root;
}

/*in this search function, we find the roll no.
First we compare with root. 
If not matched and the roll no is greater than the 
root, we move right else we move left.*/
student* search(student* root, int rollno) {

    if (root == nullptr) {
        return nullptr;
    }

    if (rollno == root->roll_no) {
        return root;
    }

    if (rollno < root->roll_no) {
        return search(root->left, rollno);
    }

    return search(root->right, rollno);
}


void inorder(student* root) {

    if (root == nullptr) {
        return;
    }

    inorder(root->left);

    cout << "Roll Number: " << root->roll_no << endl;
    cout << "Name: " << root->name << endl;

    inorder(root->right);
}

//freeing memory
void destroy(student* root) {

    if (root == nullptr) {
        return;
    }

    destroy(root->left);
    destroy(root->right);

    delete root;
}

// QUEUE 

struct node {
    int roll_no;
    node* next;

    node(int no) : roll_no(no), next(nullptr) {
    }
};

node* front = nullptr;
node* rear = nullptr;


void enqueue(int no) {

    node* q = new node(no);

    if (rear == nullptr) {
        front = rear = q;
    }
    else {
        rear->next = q;
        rear = q;
    }

    cout << "Help request added successfully!" << endl;
}

// Serve earliest help request
int dequeue() {

    if (front == nullptr) {
        return -1;
    }

    node* temp = front;

    int r = temp->roll_no;

    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;

    return r;
}


bool isEmpty() {
    return front == nullptr;
}

// freeing memory
void destroyQueue() {

    while (front != nullptr) {

        node* temp = front;

        front = front->next;

        delete temp;
    }

    rear = nullptr;
}


int main() {

    student* root = nullptr;

    int choice;
    int rollno;
    string name;

    do {

        cout << "\nSTUDENT HELP DESK:" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Search Student" << endl;
        cout << "3. Display All Students" << endl;
        cout << "4. Add Help Request" << endl;
        cout << "5. Serve Help Request" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            cout << "Enter Roll Number: ";
            cin >> rollno;

            // checking for duplicate roll number
            /*although bst handles it but we need to
            show the user a clear mssg*/
            if (search(root, rollno) != nullptr) {

                cout << "Error! Roll number already exists." << endl;
            }
            else {

                cout << "Enter Student Name: ";
                cin >> ws;
                getline(cin, name);

                root = insert(root, rollno, name);

                cout << "Student added successfully!" << endl;
            }

            break;

        case 2:

            if (root == nullptr) {

                cout << "No students registered yet!" << endl;
                break;
            }

            cout << "Enter Roll Number to search: ";
            cin >> rollno;

            {
                student* result = search(root, rollno);

                if (result == nullptr) {

                    cout << "Student not found!" << endl;
                }
                else {

                    cout << "Student Found!" << endl;
                    cout << "Roll Number: "
                        << result->roll_no << endl;

                    cout << "Name: "
                        << result->name << endl;
                }
            }

            break;

        case 3:

            if (root == nullptr) {

                cout << "No students to display!" << endl;
            }
            else {

                cout << "\nREGISTERED STUDENTS:" << endl;

                inorder(root);
            }

            break;

        case 4:

            if (root == nullptr) {

                cout << "No registered students available!" << endl;
                break;
            }

            cout << "Enter Roll Number for help request: ";
            cin >> rollno;

            if (search(root, rollno) == nullptr) {

                cout << "Student is not registered!" << endl;
            }
            else {

                enqueue(rollno);
            }

            break;

        case 5:

            if (isEmpty()) {

                cout << "No help requests waiting!" << endl;
            }
            else {

                int served = dequeue();

                student* s = search(root, served);

                cout << "(Serving Help Request)" << endl;
                cout << "Roll Number: " << served << endl;
                cout << "Student Name: " << s->name << endl;
            }

            break;

        case 6:

            cout << "(Exiting Student Help Desk)" << endl;
            break;

        default:

            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 6);

    // Release dynamically allocated memory
    destroy(root);
    destroyQueue();

    return 0;
}


