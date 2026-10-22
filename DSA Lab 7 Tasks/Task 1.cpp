#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;


struct Node {
    char data;
    Node* left;
    Node* right;
};

Node* createNode(char value) {
    Node* n = new Node;
    n->data = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}


Node* buildTree(string s, int& i) {
   
    if (i >= (int)s.length() || s[i] == ',' || s[i] == ')') {
        return NULL;
    }

    Node* root = createNode(s[i]);
    i++;

    if (i < (int)s.length() && s[i] == '(') {
        i++;                        
        root->left = buildTree(s, i);   
        if (i < (int)s.length() && s[i] == ',') {
            i++;                     
        }
        root->right = buildTree(s, i);  
        if (i < (int)s.length() && s[i] == ')') {
            i++;                   
        }
    }
    return root;
}


void preorderString(Node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data;
    if (root->left != NULL || root->right != NULL) {
        cout << "(";
        preorderString(root->left);          
        cout << ",";
        preorderString(root->right);          
        cout << ")";
    }
}


void preorderPlain(Node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    preorderPlain(root->left);
    preorderPlain(root->right);
}


void inorderIterative(Node* root) {
    stack<Node*> st;
    Node* current = root;

    while (current != NULL || !st.empty()) {
       
        while (current != NULL) {
            st.push(current);
            current = current->left;
        }
        current = st.top();
        st.pop();
        cout << current->data << " ";
       
        current = current->right;
    }
}


void postorderIterative(Node* root) {
    if (root == NULL) {
        return;
    }
    stack<Node*> s1;
    stack<Node*> s2;

    s1.push(root);
    while (!s1.empty()) {
        Node* temp = s1.top();
        s1.pop();
        s2.push(temp);             

        if (temp->left != NULL) {
            s1.push(temp->left);
        }
        if (temp->right != NULL) {
            s1.push(temp->right);
        }
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

bool isValidTreeString(string s) {
    if (s.length() == 0) {
        return false;
    }

    int depth = 0;                  
    int commas[100];                
    commas[0] = 0;

    for (int i = 0; i < (int)s.length(); i++) {
        char c = s[i];
        char prev;
        if (i == 0) {
            prev = ' ';
        }
        else {
            prev = s[i - 1];
        }

        if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9') {
            if (i == 0 || prev == '(' || prev == ',') { 
            }
            else {
                return false;
            }
        }
        else if (c == '(') {
            if (i == 0 || prev == '(' || prev == ')' || prev == ',') {
                return false;
            }
            depth++;
            commas[depth] = 0;
        }
        else if (c == ',') {
            if (depth == 0) {
                return false;
            }
            commas[depth]++;
            if (commas[depth] > 1) {
                return false;
            }
        }
        else if (c == ')') {
            if (depth == 0) {
                return false;       
            }
            if (prev == '(') {
                return false;       
            }
            depth--;
        }
        else {
            return false;           
        }

        if (depth == 0 && i < (int)s.length() - 1 && c == ')') {
            return false;
        }
    }

    if (depth != 0) {
        return false;
    }
    char last = s[s.length() - 1];
    if (last == '(' || last == ',') {
        return false;
    }
    return true;
}


int getHeight(Node* root) {
    if (root == NULL) {
        return -1;
    }
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    if (lh > rh) {
        return lh + 1;
    }
    else {
        return rh + 1;
    }
}


void printDepths(Node* root, int depth) {
    if (root == NULL) {
        return;
    }
    cout << "Node " << root->data << " -> depth " << depth << endl;
    printDepths(root->left, depth + 1);
    printDepths(root->right, depth + 1);
}


struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
};

BSTNode* insertBST(BSTNode* root, int value) {
    if (root == NULL) {
        BSTNode* n = new BSTNode;
        n->data = value;
        n->left = NULL;
        n->right = NULL;
        return n;
    }
    if (value < root->data) {
        root->left = insertBST(root->left, value);
    }
    else {
        root->right = insertBST(root->right, value);
    }
    return root;
}

BSTNode* buildBST(vector<int> numbers) {
    BSTNode* root = NULL;          
    for (int i = 0; i < (int)numbers.size(); i++) {
        root = insertBST(root, numbers[i]);
    }
    return root;
}

void inorderBST(BSTNode* root) {
    if (root == NULL) {
        return;
    }
    inorderBST(root->left);
    cout << root->data << " ";
    inorderBST(root->right);
}


int main() {
    string treeString = "a(b(d,e),c(,f(g,)))";
    cout << "Given string: " << treeString << endl << endl;

    cout << "Validation:" << endl;
    if (isValidTreeString(treeString)) {
        cout << "The string is a VALID binary tree." << endl;
    }
    else {
        cout << "The string is NOT valid." << endl;
        return 0;
    }
  
    string tests[4] = { "a(b,c", "a(b,c))", "a(,,b)", "a(b)c" };
    for (int i = 0; i < 4; i++) {
        cout << "Test \"" << tests[i] << "\" -> ";
        if (isValidTreeString(tests[i])) {
            cout << "valid" << endl;
        }
        else {
            cout << "invalid" << endl;
        }
    }
    cout << endl;

    int index = 0;
    Node* root = buildTree(treeString, index);
    cout << "Tree built successfully." << endl << endl;

    cout << "Preorder (recursive):" << endl;
    cout << "String form : ";
    preorderString(root);
    cout << endl;
    cout << "Node order  : ";
    preorderPlain(root);
    cout << endl << endl;

    cout << "Inorder (iterative, stack):" << endl;
    inorderIterative(root);
    cout << endl << endl;

    cout << "Postorder (iterative, stack):" << endl;
    postorderIterative(root);
    cout << endl << endl;

    cout << "Height and Depth:" << endl;
    cout << "Height of tree = " << getHeight(root) << endl;
    printDepths(root, 0);
    cout << endl;

    cout << "BST from integers:" << endl;
    vector<int> numbers;
    numbers.push_back(50);
    numbers.push_back(30);
    numbers.push_back(70);
    numbers.push_back(20);
    numbers.push_back(40);
    numbers.push_back(60);
    numbers.push_back(80);
    BSTNode* bstRoot = buildBST(numbers);
    cout << "Inorder of BST: ";
    inorderBST(bstRoot);
    cout << endl;

    return 0;
}
