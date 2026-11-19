#include <iostream>
using namespace std;

class MaxHeap {
private:
    int* heap;
    int size;
    int capacity;

public:

    // Constructor: Creates a dynamic array for the heap.
    // Time Complexity: O(1)
    MaxHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new int[capacity];
    }

    // Insert a value and move it upward until the max heap property is restored.
    // Time Complexity: O(log n)
    void insert(int value) {

        if (size == capacity) {
            cout << "Heap full!" << endl;
            return;
        }

        heap[size] = value;
        int current = size;
        size++;

        int swaps = 0;

        while (current > 0) {
            int parent = (current - 1) / 2;

            if (heap[current] > heap[parent]) {
                int temp = heap[current];
                heap[current] = heap[parent];
                heap[parent] = temp;

                current = parent;
                swaps++;
            }
            else {
                break;
            }
        }

        cout << value << "\t\t" << swaps << "\t\t";

        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }

        cout << endl;
    }

    // Move a value downward to restore the max heap property.
    // Time Complexity: O(log n)
    void siftDown(int arr[], int n, int i) {

        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;

            siftDown(arr, n, largest);
        }
    }

    // Sort the array in ascending order using heap sort.
    // Time Complexity: O(n log n)
    void heapSort() {

        int originalSize = size;

        for (int i = size - 1; i > 0; i--) {
            int temp = heap[0];
            heap[0] = heap[i];
            heap[i] = temp;

            siftDown(heap, i, 0);
        }

        size = originalSize;
    }

    // Display the current heap array.
    // Time Complexity: O(n)
    void display() {
        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }

    // Destructor: Releases dynamically allocated memory.
    // Time Complexity: O(1)
    ~MaxHeap() {
        delete[] heap;
    }
};

int main() {

    int n;
    cout << "Enter number of elements to enter: ";
    cin >> n;

    MaxHeap h(n); //creating heap

    int* values = new int[n];

    cout << "\nEnter the values to insert: ";
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    cout << "Insert\t\tSwaps\t\tHeap after insertion" << endl;

    for (int i = 0; i < n; i++) {
        h.insert(values[i]);
    }
    /*Q1: The worst case is O(log n) swaps. A newly inserted element
    may move from the last level to the root, passing through 
    the height of the heap.*/

    cout << "\nFinal Max Heap: ";
    h.display();

    h.heapSort();

    /*Q2: Building through n individual insertions:O(nlog n).
    Heap sort: O(nlog n)*/
    cout << "Sorted output: ";
    h.display();

    delete[] values;
}
