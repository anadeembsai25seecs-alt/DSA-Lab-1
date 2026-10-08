#include <iostream>
#include <string>
using namespace std;


class Node {
public:
    char data;
    Node* next;
};


class Stack {
private:
    Node* topNode;

public:

    Stack() {
        topNode = NULL;
    }

    // Destructor
    ~Stack() {
        clear();
    }


    void push(char c) {
        Node* newNode = new Node;   // make a new node
        newNode->data = c;          // store the character in it
        newNode->next = topNode;    // link it to the old top
        topNode = newNode;          // it is now the new top
    }


    char pop() {
        if (topNode == NULL) {
            cout << "Stack is empty, cannot pop." << endl;
            return '\0';
        }
        Node* temp = topNode;
        char c = temp->data;
        topNode = topNode->next;
        delete temp;
        return c;
    }


    char top() {
        if (topNode == NULL) {
            cout << "Stack is empty, no top element." << endl;
            return '\0';
        }
        return topNode->data;
    }


    bool isEmpty() {
        return topNode == NULL;
    }


    void display() {
        if (topNode == NULL) {
            cout << "Stack is empty." << endl;
            return;
        }
        cout << "Stack (top to bottom): ";
        Node* current = topNode;
        while (current != NULL) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Clear: delete every node
    void clear() {
        while (topNode != NULL) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
};


bool isOpening(char c) {
    if (c == '(' || c == '[' || c == '{') {
        return true;
    }
    return false;
}


bool isClosing(char c) {
    if (c == ')' || c == ']' || c == '}') {
        return true;
    }
    return false;
}


bool isMatch(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '[' && close == ']') return true;
    if (open == '{' && close == '}') return true;
    return false;
}


bool checkBalance(string expr) {
    Stack s;

    int length = expr.length();   // number of characters in the expression

    for (int i = 0; i < length; i++) {
        char c = expr[i];

        if (isOpening(c)) {

            s.push(c);
            cout << "   Push " << c << "  ->  ";
            s.display();               // show current contents of the stack
        }
        else if (isClosing(c)) {

            if (s.isEmpty()) {
                cout << "   Found extra " << c << "  ->  ";
                s.display();           // show current contents of the stack
                return false;
            }
            char openBracket = s.pop();
            cout << "   Pop  " << openBracket << "  ->  ";
            s.display();               // show current contents of the stack
            if (!isMatch(openBracket, c)) {
                return false;          // wrong type of bracket
            }
        }
        // any other character (letters, +, *, ...) is ignored
    }


    if (!s.isEmpty()) {
        return false;
    }

    return true;
}


int main() {
    string tests[7] = {
         "(A+B)",
         "{A+[B*C]}",
         "(A+B]",
         "((A+B)",
         "{[()]}",
         "A+B*C",
         "([A+B])"
    };

    cout << "Test Cases:" << endl;
    for (int i = 0; i < 7; i++) {
        cout << endl;
        cout << "Expression: " << tests[i] << endl;
        bool result = checkBalance(tests[i]);
        cout << "Result: ";
        if (result) {
            cout << "Balanced" << endl;
        }
        else {
            cout << "Not Balanced" << endl;
        }
    }
    cout << endl;

    return 0;
}