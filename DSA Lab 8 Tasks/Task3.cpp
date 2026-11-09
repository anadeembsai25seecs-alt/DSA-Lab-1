#include <iostream>
using namespace std;

struct Node
{
    int data;
    int height;
    Node* left;
    Node* right;
};

int height(Node* root)
{
    if (root == NULL)
        return 0;

    return root->height;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

Node* createNode(int value)
{
    Node* newNode = new Node();

    newNode->data = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int getBalance(Node* root)
{
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

Node* rightRotate(Node* y)
{
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x)
{
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


Node* insert(Node* root, int value)
{
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);

    else if (value > root->data)
        root->right = insert(root->right, value);

    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

    // RR Case
    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    // LR Case
    if (balance > 1 && value > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 && value < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


Node* findMin(Node* root)
{
    Node* current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}


Node* deleteNode(Node* root, int value)
{
    if (root == NULL)
        return root;

    if (value < root->data)
        root->left = deleteNode(root->left, value);

    else if (value > root->data)
        root->right = deleteNode(root->right, value);

    else
    {
       
        if (root->left == NULL || root->right == NULL)
        {
            Node* temp;

            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;

            if (temp == NULL)
            {
                delete root;
                return NULL;
            }
            else
            {
                Node* oldRoot = root;
                root = temp;
                delete oldRoot;
            }
        }

        else
        {
            Node* temp = findMin(root->right);

            root->data = temp->data;

            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void printTree(Node* root)
{
    if (root == NULL)
        return;

    printTree(root->left);
    cout << root->data << " ";
    printTree(root->right);
}


void printStructure(Node* root, int space = 0)
{
    if (root == NULL)
        return;

    space = space + 5;

    printStructure(root->right, space);

    cout << endl;

    for (int i = 5; i < space; i++)
        cout << " ";

    cout << root->data << endl;

    printStructure(root->left, space);
}


void topMaximum(Node* root, int k, int result[], int& count)
{
    if (root == NULL || count == k)
        return;

    topMaximum(root->right, k, result, count);

    if (count < k)
    {
        result[count] = root->data;
        count++;
    }

    topMaximum(root->left, k, result, count);
}

void topMinimum(Node* root, int k, int result[], int& count)
{
    if (root == NULL || count == k)
        return;

    topMinimum(root->left, k, result, count);

    if (count < k)
    {
        result[count] = root->data;
        count++;
    }

    topMinimum(root->right, k, result, count);
}


int sumTopK(Node* root, int k, int& count)
{
    if (root == NULL || count == k)
        return 0;

    int sum = sumTopK(root->right, k, count);

    if (count < k)
    {
        sum = sum + root->data;
        count++;
    }

    sum = sum + sumTopK(root->left, k, count);

    return sum;
}


void deleteTopK(Node*& root, int k)
{
    int result[1000];
    int count = 0;

    topMaximum(root, k, result, count);

    for (int i = 0; i < count; i++)
    {
        root = deleteNode(root, result[i]);

        cout << "\nAfter deleting " << result[i] << ":\n";
        printTree(root);
        cout << endl;

        cout << "Tree structure:";
        printStructure(root);
    }
}

int main()
{
    Node* root = NULL;

    int n, value;

    cout << "Enter number of elements: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter value: ";
        cin >> value;

        root = insert(root, value);

        cout << "\nTree after insertion of " << value << ":\n";

        cout << "Sorted values: ";
        printTree(root);

        cout << "\nTree structure:";
        printStructure(root);

        cout << "\n----------------------\n";
    }

    int k;

    cout << "\nEnter K: ";
    cin >> k;

    if (k < 0)
    {
        cout << "K cannot be negative.\n";
        return 0;
    }

    if (k > n)
        k = n;

    int result[1000];
    int count = 0;

    // Maximum K elements
    topMaximum(root, k, result, count);

    cout << "\nTop " << k << " maximum elements: ";

    for (int i = 0; i < count; i++)
        cout << result[i] << " ";

    // Minimum K elements
    count = 0;

    topMinimum(root, k, result, count);

    cout << "\nTop " << k << " minimum elements: ";

    for (int i = 0; i < count; i++)
        cout << result[i] << " ";

    // Sum of maximum K elements
    count = 0;

    int sum = sumTopK(root, k, count);

    cout << "\nSum of top " << k << " maximum elements: " << sum;

    // Delete maximum K elements
    cout << "\n\nDeleting top " << k << " maximum elements...\n";

    deleteTopK(root, k);

    cout << "\nFinal AVL tree: ";
    printTree(root);

    cout << endl;

    return 0;
}

