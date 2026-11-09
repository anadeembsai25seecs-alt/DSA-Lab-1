#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Linked List Node
struct ListNode
{
    int val;
    ListNode* next;

    ListNode(int x)
    {
        val = x;
        next = NULL;
    }
};

// Comparator for Min-Heap
struct Compare
{
    bool operator()(ListNode* a, ListNode* b)
    {
        return a->val > b->val;
    }
};

// Function to merge K sorted linked lists
ListNode* mergeKLists(vector<ListNode*>& lists)
{
    priority_queue<ListNode*, vector<ListNode*>, Compare> pq;

    // Insert first node of every list into heap
    for (int i = 0; i < lists.size(); i++)
    {
        if (lists[i] != NULL)
        {
            pq.push(lists[i]);
        }
    }

    // Create dummy node
    ListNode* dummy = new ListNode(0);
    ListNode* tail = dummy;

    // Merge the lists
    while (!pq.empty())
    {
        // Get smallest node
        ListNode* smallest = pq.top();
        pq.pop();

        // Attach node to result
        tail->next = smallest;
        tail = tail->next;

        // Insert next node from same list
        if (smallest->next != NULL)
        {
            pq.push(smallest->next);
        }
    }

    tail->next = NULL;

    return dummy->next;
}

// Function to print linked list
void printList(ListNode* head)
{
    while (head != NULL)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}


int main()
{
    int k;

    cout << "Enter number of linked lists: ";
    cin >> k;

    vector<ListNode*> lists(k);

    // Input linked lists
    for (int i = 0; i < k; i++)
    {
        int n;

        cout << "Enter number of nodes in list " << i + 1 << ": ";
        cin >> n;

        ListNode* head = NULL;
        ListNode* tail = NULL;

        cout << "Enter sorted elements: ";

        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;

            ListNode* newNode = new ListNode(x);

            if (head == NULL)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }

        lists[i] = head;
    }

  
    ListNode* result = mergeKLists(lists);

    
    cout << "\nMerged linked list: ";
    printList(result);

    return 0;
}

