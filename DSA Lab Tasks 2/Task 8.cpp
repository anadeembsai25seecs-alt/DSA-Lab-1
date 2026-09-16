#include <iostream>
using namespace std;

int main() {
    int n = 3;  // length of array
    int* values = new int[n]; // dynamic memory allocation for the array

    cout << "Enter 3 integers: ";
    for (int i = 0; i < n; i++) {  // taking in values from user in array
        cin >> values[i];
    }

    cout << "Array: ";
    for (int i = 0; i < n; i++) {  // prints out the values stored in array
        cout << values[i] << " ";
    }

    delete[] values;   // deletes the array and free the memory allocated

}
