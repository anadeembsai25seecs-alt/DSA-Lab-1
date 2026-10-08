#include <iostream>
#include <string>
using namespace std;


class Node {
public:
    int data;
    Node* next;
};


class Stack {
private:
    Node* topNode;

public:
    
    Stack() {
        topNode = NULL;
    }


    ~Stack() {
        clear();
    }

    void push(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = topNode;
        topNode = newNode;
    }


    int pop() {
        Node* temp = topNode;
        int value = temp->data;
        topNode = topNode->next;
        delete temp;
        return value;
    }

    int top() {
        return topNode->data;
    }

    bool isEmpty() {
        return topNode == NULL;
    }

   
    void clear() {
        while (topNode != NULL) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
};



bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}


int precedence(char op) {
    if (op == '*' || op == '/' || op == '%') {
        return 2;
    }
    if (op == '+' || op == '-') {
        return 1;
    }
    return 0;   // for '('
}


void checkOperators(string expr) {
    int length = expr.length();
    int i = 0;

    cout << "Operands : ";
    while (i < length) {
        if (isDigit(expr[i])) {
            while (i < length && isDigit(expr[i])) {
                cout << expr[i];
                i++;
            }
            cout << " ";
        }
        else {
            i++;
        }
    }
    cout << endl;

    cout << "Operators: ";
    for (i = 0; i < length; i++) {
        if (isOperator(expr[i])) {
            cout << expr[i] << " ";
        }
    }
    cout << endl;
}


bool infixToPostfix(string infix, string& postfix, string& error) {
    Stack s;                    // operators wait here
    postfix = "";
    bool expectOperand = true;  // true when a number or '(' must come next
    int tokens = 0;             

    int length = infix.length();
    int i = 0;

    while (i < length) {
        char c = infix[i];

        if (c == ' ') {
            i++;                                    
        }
        else if (isDigit(c)) {
            if (!expectOperand) {
                error = "missing operator between operands";
                return false;
            }
           
            while (i < length && isDigit(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += ' ';
            expectOperand = false;
            tokens++;
        }
        else if (c == '(') {
            if (!expectOperand) {
                error = "missing operator before '('";
                return false;
            }
            s.push(c);
            i++;
            tokens++;
        }
        else if (c == ')') {
            if (expectOperand) {
                error = "missing operand before ')'";
                return false;
            }
        
            while (!s.isEmpty() && s.top() != '(') {
                postfix += (char)s.pop();
                postfix += ' ';
            }
            if (s.isEmpty()) {
                error = "mismatched parentheses (extra ')')";
                return false;
            }
            s.pop();                                
            i++;
            tokens++;
        }
        else if (isOperator(c)) {
            if (expectOperand) {
                error = "missing operand before operator '" + string(1, c) + "'";
                return false;
            }
           
            while (!s.isEmpty() && s.top() != '(' && precedence(s.top()) >= precedence(c)) {
                postfix += (char)s.pop();
                postfix += ' ';
            }
            s.push(c);
            expectOperand = true;
            i++;
            tokens++;
        }
        else {
            error = "invalid character '" + string(1, c) + "'";
            return false;
        }
    }

    if (tokens == 0) {
        error = "empty expression";
        return false;
    }
    if (expectOperand) {
        error = "expression is incomplete (ends with an operator or '(')";
        return false;
    }

 
    while (!s.isEmpty()) {
        char op = (char)s.pop();
        if (op == '(') {
            error = "mismatched parentheses (missing ')')";
            return false;
        }
        postfix += op;
        postfix += ' ';
    }
    return true;
}


bool evaluatePostfix(string postfix, int& result, string& error) {
    Stack s;                    
    int length = postfix.length();
    int i = 0;

    while (i < length) {
        char c = postfix[i];

        if (c == ' ') {
            i++;
        }
        else if (isDigit(c)) {
            
            int number = 0;
            while (i < length && isDigit(postfix[i])) {
                number = number * 10 + (postfix[i] - '0');
                i++;
            }
            s.push(number);
        }
        else {
           
            if (s.isEmpty()) {
                error = "not enough operands";
                return false;
            }
            int b = s.pop();        
            if (s.isEmpty()) {
                error = "not enough operands";
                return false;
            }
            int a = s.pop();        

            if ((c == '/' || c == '%') && b == 0) {
                error = "division by zero";
                return false;
            }

            int answer = 0;
            if (c == '+') answer = a + b;
            if (c == '-') answer = a - b;
            if (c == '*') answer = a * b;
            if (c == '/') answer = a / b;
            if (c == '%') answer = a % b;

            s.push(answer);         
            i++;
        }
    }

    result = s.pop();               
    return true;
}


void processExpression(string expr) {
    string postfix;
    string error;
    int result = 0;

 
    cout << "\n*Infix expression  : \"" << expr << "\"" << endl;

    checkOperators(expr);

    if (!infixToPostfix(expr, postfix, error)) {
        cout << "Error: " << error << endl;
        return;
    }

 
    cout << "*Postfix expression: " << postfix << endl;

    if (!evaluatePostfix(postfix, result, error)) {
        cout << "Error: " << error << endl;
        return;
    }

    cout << "Result: " << result << endl;
}

int main() {
    string tests[12] = {
        "2 + 3 * 4",
        "(2 + 3) * 4",
        "10 + 2 * 6",
        "(10 + 2) * (6 - 3)",
        "20 / 5 + 3",
        "((2 + 3) * (4 - 1)) / 5",      
        "100 - 20 / 4 * 2 + 7 % 4",     
        "",                             
        "(2 + 3 * 4",                   
        "2 + 3) * 4",                   
        "10 / (5 - 5)",                
        "2 + * 3"                    
    };

    cout << "*Test Cases" << endl;
    for (int i = 0; i < 12; i++) {
        processExpression(tests[i]);
    }
}