#include <iostream>
using namespace std;


void inputSortedIDs(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

bool isSorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}


int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (target < arr[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    return -1;
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    if (n < 0) {
        cout << "Invalid array size.";
        return 0;
    }
    else if (n == 0) {
        cout << "Empty array.";
        return 0;
    }

    int* arr = new int[n];

    cout << "Enter registration IDs in ascending order: ";
    inputSortedIDs(arr, n);

    if (!isSorted(arr, n)) {
        cout << "Error: IDs are not sorted.";
        delete[] arr;
        return 0;
    }
    int result;
    char choice;
    do {
        int target;
        cout << "\nEnter registration ID to search: ";
        cin >> target;

        if (target <= 0) {
            cout << "Inavalid ID";
            return 1;
        }
        else {
            result = binarySearch(arr, 0, n - 1, target);
        }
        if (result != -1) {
            cout << "Found at index " << result;
        }
        else {
            cout << "Registration ID not found.";
        }

        cout << "\nDo you to find more IDs (y/n): ";
        cin >> choice;
    } while (choice == 'y');
    delete[] arr;
    return 0;
}
