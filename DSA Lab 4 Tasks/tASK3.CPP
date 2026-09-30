#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int bit;
    Node* next;
    Node* prev;
};

Node* createNode(int bit)
{
    Node* newNode = new Node;

    newNode->bit = bit;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}
// INSERTION AT END 

void insertAtEnd(Node*& head, Node*& tail, int bit)
{
    Node* newNode = createNode(bit);

    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}
//INSERTION AT FRONT

void insertAtFront(Node*& head, Node*& tail, int bit)
{
    Node* newNode = createNode(bit);

    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}
//  DELETING LIST 

void freeList(Node*& head)
{
    while (head != NULL)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
// CHECKING BINARY INPUT

bool isValidBinary(string binary)
{
    if (binary.empty())
        return false;

    for (int i = 0; i < binary.length(); i++)
    {
        if (binary[i] != '0' && binary[i] != '1')
            return false;
    }

    return true;
}
// PADDING TO 8 BITS 

void padToBytes(Node*& head, Node*& tail)
{
    int count = 0;
    Node* temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    int zeros = (8 - (count % 8)) % 8;

    for (int i = 0; i < zeros; i++)
    {
        insertAtFront(head, tail, 0);
    }
}
//STORING BINARY

void storeBinary(Node*& head, Node*& tail, string binary)
{
    head = NULL;
    tail = NULL;

    for (int i = 0; i < binary.length(); i++)
    {
        insertAtEnd(head, tail, binary[i] - '0');
    }

    // Make the number a multiple of 8 bits
    padToBytes(head, tail);
}
// DISPLAYING BINARY

void displayGroups(Node* head)
{
    Node* temp = head;

    int count = 0;

    while (temp != NULL)
    {
        cout << temp->bit;

        count++;

        if (count % 8 == 0 && temp->next != NULL)
        {
            cout << " ";
        }

        temp = temp->next;
    }

    cout << endl;
}
// - 1'S COMPLEMENT -

void onesComplement(Node* head)
{
    Node* temp = head;

    while (temp != NULL)
    {
        temp->bit = 1 - temp->bit;

        temp = temp->next;
    }
}


// ADD 1 

void addOne(Node* tail)
{
    Node* temp = tail;
    int carry = 1;

    while (temp != NULL && carry == 1)
    {
        if (temp->bit == 0)
        {
            temp->bit = 1;
            carry = 0;
        }
        else
        {
            temp->bit = 0;
            carry = 1;
        }

        temp = temp->prev;
    }

    // Carry is discarded if it goes beyond
    // the fixed number of bits.
}


// -2'S COMPLEMENT -

void twosComplement(Node* head, Node* tail)
{
    // Step 1: 1's complement
    onesComplement(head);

    // Step 2: Add 1
    addOne(tail);
}

//BINARY ADDITION 

Node* binaryAddition(
    Node* tail1,
    Node* tail2,
    Node*& resultTail)
{
    Node* p = tail1;
    Node* q = tail2;

    int carry = 0;

    Node* resultHead = NULL;
    resultTail = NULL;

    // Start from the rightmost bits

    while (p != NULL || q != NULL || carry != 0)
    {
        int sum = carry;

        if (p != NULL)
        {
            sum = sum + p->bit;
            p = p->prev;
        }

        if (q != NULL)
        {
            sum = sum + q->bit;
            q = q->prev;
        }

        int resultBit = sum % 2;

        carry = sum / 2;

        // Insert result at the beginning

        insertAtFront(resultHead, resultTail, resultBit);
    }

    return resultHead;
}
//  LEFT SHIFT

void leftShift(Node*& head, Node*& tail)
{
    insertAtEnd(head, tail, 0);
}


// REMOVE LEADING ZEROS

void removeLeadingZeros(Node*& head, Node*& tail)
{
    while (head != NULL &&
        head->bit == 0 &&
        head->next != NULL)
    {
        Node* temp = head;

        head = head->next;

        head->prev = NULL;

        delete temp;
    }

    // Update tail

    tail = head;

    while (tail != NULL && tail->next != NULL)
    {
        tail = tail->next;
    }
}

// BINARY MULTIPLICATION 

Node* binaryMultiplication(
    Node* head1,
    Node* tail1,
    Node* tail2,
    Node*& resultTail)
{
    // Result starts from 0

    Node* resultHead = NULL;

    resultTail = NULL;

    insertAtEnd(resultHead, resultTail, 0);


    // Start from the rightmost bit of the multiplier

    Node* multiplier = tail2;

    while (multiplier != NULL)
    {
        // If multiplier bit is 1, add multiplicand to result

        if (multiplier->bit == 1)
        {
            Node* newTail = NULL;

            Node* newResult = binaryAddition(
                resultTail,
                tail1,
                newTail
            );

            // Delete old result

            freeList(resultHead);

            // Store new result
            resultHead = newResult;
            resultTail = newTail;
        }
        // Shift multiplicand left
        leftShift(head1, tail1);

        // Move to previous multiplier bit
        multiplier = multiplier->prev;
    }
    // Remove unnecessary zeros
    removeLeadingZeros(resultHead, resultTail);

    return resultHead;
}
//BINARY TO DECIMAL

long long binaryToDecimal(Node* head)
{
    long long decimal = 0;
    Node* temp = head;

    while (temp != NULL)
    {
        decimal = decimal * 2 + temp->bit;
        temp = temp->next;
    }

    return decimal;
}
//READ BINARY
string readBinary(string message){
    string binary;

    while (true)
    {
        cout << message;
        cin >> binary;
        if (isValidBinary(binary))
        {
            return binary;
        }
        cout << "Invalid input! Enter only 0 and 1.\n";
    }
}

int main()
{
    string binary1;
    string binary2;

    // Read input
    binary1 = readBinary("Enter first binary number: ");
    binary2 = readBinary("Enter second binary number: ");

    // FIRST NUMBER
    Node* head1 = NULL;
    Node* tail1 = NULL;

    storeBinary(head1, tail1, binary1);

    //SECOND NUMBER 
    Node* head2 = NULL;
    Node* tail2 = NULL;

    storeBinary(head2, tail2, binary2);

    // Display numbers
    cout << "\nFirst Binary Number:  ";
    displayGroups(head1);

    cout << "Second Binary Number: ";
    displayGroups(head2);

    //  1'S COMPLEMENT
    Node* onesHead = NULL;
    Node* onesTail = NULL;

    storeBinary(onesHead, onesTail, binary1);
    onesComplement(onesHead);

    cout << "\n1's Complement of First Number: ";
    displayGroups(onesHead);

    // 2'S COMPLEMENT 

    Node* twosHead = NULL;
    Node* twosTail = NULL;

    storeBinary(twosHead, twosTail, binary1);
    twosComplement(twosHead, twosTail);

    cout << "2's Complement of First Number: ";
    displayGroups(twosHead);

    //  ADDITION
    Node* additionTail = NULL;
    Node* additionHead = binaryAddition(
        tail1,
        tail2,
        additionTail
    );

    // Make addition result a multiple of 8 bits
    padToBytes(additionHead, additionTail);

    cout << "\nBinary Addition: ";
    displayGroups(additionHead);


    // MULTIPLICATION 

    // Make a fresh copy of first number because multiplication changes it
    // through left shifting.
    Node* multiplyHead1 = NULL;
    Node* multiplyTail1 = NULL;

    storeBinary(
        multiplyHead1,
        multiplyTail1,
        binary1
    );
    // Make a fresh copy of second number
    Node* multiplyHead2 = NULL;
    Node* multiplyTail2 = NULL;

    storeBinary(
        multiplyHead2,
        multiplyTail2,
        binary2
    );
    Node* multiplicationTail = NULL;
    Node* multiplicationHead =
        binaryMultiplication(
            multiplyHead1,
            multiplyTail1,
            multiplyTail2,
            multiplicationTail
        );


    cout << "Binary Multiplication: ";
    displayGroups(multiplicationHead);


    // DECIMAL CONVERSION

    cout << "\nDecimal value of first number: "
        << binaryToDecimal(head1) << endl;

    cout << "Decimal value of second number: "
        << binaryToDecimal(head2) << endl;

    cout << "Decimal value of addition result: "
        << binaryToDecimal(additionHead) << endl;

    cout << "Decimal value of multiplication result: "
        << binaryToDecimal(multiplicationHead) << endl;


    // FREEING MEMORY

    freeList(head1);
    freeList(head2);

    freeList(onesHead);
    freeList(twosHead);

    freeList(additionHead);

    freeList(multiplyHead1);
    freeList(multiplyHead2);

    freeList(multiplicationHead);

}