#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f)  //node constructor
    {
        ch = c;
        freq = f;
        left = NULL;
        right = NULL;
    }
};

// Compare frequencies for Min-Heap
struct Compare
{
    bool operator()(Node* a, Node* b)  //overloaded function tells the priority queue to act min-heap
    {
        return a->freq > b->freq;
    }
};


void preorder(Node* root, string code)
{
    if (root == NULL)
        return;

    // if it is a leaf node
    if (root->left == NULL && root->right == NULL)
    {
        cout << root->ch << " : " << code << endl;
        return;
    }

    preorder(root->left, code + "0");   //add 0 for left
    preorder(root->right, code + "1");  //add 1 for right
}

// Huffman Tree
void buildHuffman(string S, int f[], int N)
{
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Insert all characters into Min-Heap
    for (int i = 0; i < N; i++)
    {
        Node* newNode = new Node(S[i], f[i]);
        pq.push(newNode);
    }

    // Build the tree
    while (pq.size() > 1) //runs until only 1 (max) element is left
    {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node('$', left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    
    Node* root = pq.top();  //we make the left element the root of huffman tree

    preorder(root, "");
}

int main()
{
    int N;
    cout << "Enter the length of string: ";
    cin >> N;

    string S;
    cout << "Enter the string: ";
    cin >> S;

    int* f = new int[N];

    cout << "Enter the frequencies: ";
    for (int i = 0; i < N; i++)
    {
        cin >> f[i];
    }

    buildHuffman(S, f, N);

    return 0;
}

