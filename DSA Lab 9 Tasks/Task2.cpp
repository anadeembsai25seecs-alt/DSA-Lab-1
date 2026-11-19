#include <iostream>
using namespace std;

class Heap {
private:
    int* arr;
    int size;
    int capacity;
    bool isMax;

public:

    // Constructor: Creates a heap.
    // Time Complexity: O(1)
    Heap(int cap, bool maxHeap) {
        capacity = cap;
        size = 0;
        isMax = maxHeap;
        arr = new int[capacity];
    }

    // Checks whether one value has higher priority than another.
    // Time Complexity: O(1)
    bool higherPriority(int a, int b) {
        if (isMax)
            return a > b;
        else
            return a < b;
    }

    // Inserts a value and moves it upward.
    // Time Complexity: O(log n)
    void push(int value) {

        if (size == capacity)
            return;

        arr[size] = value;
        int current = size;
        size++;

        while (current > 0) {

            int parent = (current - 1) / 2;

            if (higherPriority(arr[current], arr[parent])) {

                int temp = arr[current];
                arr[current] = arr[parent];
                arr[parent] = temp;

                current = parent;
            }
            else {
                break;
            }
        }
    }

    // Moves a value downward to restore heap property.
    // Time Complexity: O(log n)
    void siftDown(int i) {

        int best = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size &&
            higherPriority(arr[left], arr[best])) {
            best = left;
        }

        if (right < size &&
            higherPriority(arr[right], arr[best])) {
            best = right;
        }

        if (best != i) {

            int temp = arr[i];
            arr[i] = arr[best];
            arr[best] = temp;

            siftDown(best);
        }
    }

    // Removes and returns the root element.
    // Time Complexity: O(log n)
    int pop() {

        if (size == 0)
            return -1;

        int root = arr[0];

        arr[0] = arr[size - 1];
        size--;

        if (size > 0)
            siftDown(0);

        return root;
    }

    // Returns the root without removing it.
    // Time Complexity: O(1)
    int top() {
        if (size == 0)
            return -1;

        return arr[0];
    }

    // Returns the number of elements.
    // Time Complexity: O(1)
    int getSize() {
        return size;
    }

    // Checks whether the heap is empty.
    // Time Complexity: O(1)
    bool empty() {
        return size == 0;
    }

    // Destructor: Releases memory.
    // Time Complexity: O(1)
    ~Heap() {
        delete[] arr;
    }
};


class MedianMonitor {

private:
    Heap maxHeap;
    Heap minHeap;

public:

    // Creates one max heap and one min heap.
    // Time Complexity: O(1)
    MedianMonitor(int capacity)
        : maxHeap(capacity, true),
        minHeap(capacity, false) {
    }

    // Inserts a new waiting time and balances both heaps.
    // Time Complexity: O(log n)
    void addWait(int x) {

        // Insert into the correct heap.
        if (maxHeap.empty() || x <= maxHeap.top()) {
            maxHeap.push(x);
        }
        else {
            minHeap.push(x);
        }

        // Max heap should have the extra element.
        if (maxHeap.getSize() > minHeap.getSize() + 1) {

            int value = maxHeap.pop();
            minHeap.push(value);
        }

        else if (minHeap.getSize() > maxHeap.getSize()) {

            int value = minHeap.pop();
            maxHeap.push(value);
        }

        // Print information.
        cout << x << "\t\t";

        if (maxHeap.empty())
            cout << "none\t\t";
        else
            cout << maxHeap.top() << "\t\t";

        if (minHeap.empty())
            cout << "none\t\t";
        else
            cout << minHeap.top() << "\t\t";

        double median = getMedian();

        cout << median << "\t\t";

        if (median > 35)
            cout << "ALERT: call extra staff";
        else
            cout << "Normal";

        cout << endl;
    }

    // Calculates the median using the two heap roots.
    // Time Complexity: O(1)
    double getMedian() {

        if (maxHeap.getSize() > minHeap.getSize()) {
            return maxHeap.top();
        }

        else {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }
};


int main() {

    MedianMonitor hospital(20);

    int waits[] = { 45, 20, 60, 15, 30, 90, 10, 55 };

    cout << "Arrival\tWait\tMax heap root\tMin heap root\t\tMedian\t\tStatus"<< endl;

    for (int i = 0; i < 8; i++) {
        cout << i + 1 << "\t";
        hospital.addWait(waits[i]);
    }
/*Q7: The median is better because it is less affected by extreme values. 
At arrival 6, the waiting times are:45, 20, 60, 15, 30, 90
  Average = 43.33 minutes
  Median = 37.5 minutes
The waiting time of 90 minutes increases the average significantly, 
whereas the median is less affected by this extreme value. 
Therefore, the median gives a better representation of the typical patient's waiting time.

Q8:If the heap sizes differ by two or more, the heaps are not properly balanced. 
Their roots may no longer represent the middle values of the complete dataset correctly. 
As a result, the calculated median can be incorrect.

Q9: Repeated sorting: Sorting after every arrival requires O(n^2log n) total time.
    Two heaps: Each insertion takes O(log n), and median lookup takes O(1). For n patients, total time is O(nlog n).*/
}
