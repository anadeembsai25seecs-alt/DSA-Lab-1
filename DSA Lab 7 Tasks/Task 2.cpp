#include <iostream>
#include <string>
using namespace std;

struct Student {
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;
};

Student* createStudent(int id, string name, float gpa) {
    Student* s = new Student;
    s->studentID = id;
    s->name = name;
    s->GPA = gpa;
    s->left = NULL;
    s->right = NULL;
    return s;
}

Student* Insert(Student* root, int id, string name, float gpa) {
    if (root == NULL) {
        return createStudent(id, name, gpa);
    }
    if (id < root->studentID) {
        root->left = Insert(root->left, id, name, gpa);
    }
    else if (id > root->studentID) {
        root->right = Insert(root->right, id, name, gpa);
    }
    else {
        cout << "Student with ID " << id << " already exists!" << endl;
    }
    return root;
}


Student* Search(Student* root, int id) {
    if (root == NULL || root->studentID == id) {
        return root;
    }
    if (id < root->studentID) {
        return Search(root->left, id);
    }
    return Search(root->right, id);
}


Student* findMin(Student* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Student* Delete(Student* root, int id) {
    if (root == NULL) {
        return NULL;                         
    }
    if (id < root->studentID) {
        root->left = Delete(root->left, id);
    }
    else if (id > root->studentID) {
        root->right = Delete(root->right, id);
    }
    else {

        // Case 1: no children
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        // Case 2: only right child
        if (root->left == NULL) {
            Student* temp = root->right;
            delete root;
            return temp;
        }
        // Case 2: only left child
        if (root->right == NULL) {
            Student* temp = root->left;
            delete root;
            return temp;
        }
        // Case 3: two children
        Student* temp = findMin(root->right);
        root->studentID = temp->studentID;
        root->name = temp->name;
        root->GPA = temp->GPA;
        root->right = Delete(root->right, temp->studentID);
    }
    return root;
}


void Inorder(Student* root) {
    if (root == NULL) {
        return;
    }
    Inorder(root->left);
    cout << "ID: " << root->studentID << " |Name: " << root->name << " |GPA: " << root->GPA << endl;
    Inorder(root->right);
}

int countStudents(Student* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countStudents(root->left) + countStudents(root->right);
}

Student* findHighestGPA(Student* root) {
    if (root == NULL) {
        return NULL;
    }
    Student* best = root;
    Student* leftBest = findHighestGPA(root->left);
    Student* rightBest = findHighestGPA(root->right);
    if (leftBest != NULL && leftBest->GPA > best->GPA) {
        best = leftBest;
    }
    if (rightBest != NULL && rightBest->GPA > best->GPA) {
        best = rightBest;
    }
    return best;
}

Student* findLowestGPA(Student* root) {
    if (root == NULL) {
        return NULL;
    }
    Student* low = root;
    Student* leftLow = findLowestGPA(root->left);
    Student* rightLow = findLowestGPA(root->right);
    if (leftLow != NULL && leftLow->GPA < low->GPA) {
        low = leftLow;
    }
    if (rightLow != NULL && rightLow->GPA < low->GPA) {
        low = rightLow;
    }
    return low;
}


int displayAboveThreshold(Student* root, float threshold) {
    if (root == NULL) {
        return 0;
    }
    int found = 0;
    found += displayAboveThreshold(root->left, threshold);
    if (root->GPA > threshold) {
        cout << "ID: " << root->studentID << " |Name: " << root->name << " |GPA: " << root->GPA << endl;
        found++;
    }
    found += displayAboveThreshold(root->right, threshold);
    return found;
}

void printStudent(Student* s) {
    cout << "ID: " << s->studentID << "|Name: " << s->name << " |GPA: " << s->GPA << endl;
}


int main() {
    Student* root = NULL;

    cout << "   STUDENT RECORD MANAGEMENT (BST)   " << endl;

    cout << "1.INSERTING STUDENTS" << endl;
    root = Insert(root, 50, "Ali", 3.2);
    root = Insert(root, 30, "Sara", 3.8);
    root = Insert(root, 70, "Ahmed", 2.5);
    root = Insert(root, 20, "Fatima", 3.5);
    root = Insert(root, 40, "Usman", 2.9);
    root = Insert(root, 60, "Ayesha", 3.9);
    root = Insert(root, 80, "Hamza", 2.1);
    cout << "  7 students inserted." << endl << endl;

    
    cout << "2.ALL STUDENTS (Inorder, sorted by ID)" << endl;
    Inorder(root);
    cout << endl;

  
    cout << "3.TOTAL NUMBER OF STUDENTS" << endl;
    cout << "  Total = " << countStudents(root) << endl << endl;

    
    cout << "4.SEARCH" << endl;
    cout << "  (Searching for ID 40)" << endl;
    Student* found = Search(root, 40);
    if (found != NULL) {
        cout << "  Found:" << endl;
        printStudent(found);
    }
    else {
        cout << "  Student not found." << endl;
    }
    cout << "  (Searching for ID 99)" << endl;
    found = Search(root, 99);
    if (found != NULL) {
        cout << "  Found:" << endl;
        printStudent(found);
    }
    else {
        cout << "  Student not found." << endl;
    }
    cout << endl;

    
    cout << "5. DELETE" << endl;
    cout << "  (Deleting student with ID 30)" << endl;
    root = Delete(root, 30);
    cout << "  Students after deletion:" << endl;
    Inorder(root);
    cout << "  Total now = " << countStudents(root) << endl << endl;

   
    cout << "6. HIGHEST AND LOWEST GPA" << endl;
    cout << "  Highest GPA:" << endl;
    printStudent(findHighestGPA(root));
    cout << "  Lowest GPA:" << endl;
    printStudent(findLowestGPA(root));
    cout << endl;

   
    cout << "7. STUDENTS ABOVE A GPA THRESHOLD" << endl;
    float threshold;
    cout << "  Enter GPA threshold (e.g. 3.0): ";
    cin >> threshold;
    cout << "  Students with GPA above " << threshold << ":" << endl;
    int count = displayAboveThreshold(root, threshold);
    if (count == 0) {
        cout << "  No student found." << endl;
    }

    return 0;
}