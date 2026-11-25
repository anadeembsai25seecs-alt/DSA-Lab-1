#include <iostream>
using namespace std;


int comparisonCount = 0;
int arraySize = 0;

// partition function
int partition(int arr[], int low, int high) {

    int pivot = arr[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {

        comparisonCount++;

        if (arr[j] <= pivot) {

            i++;

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // placing pivot in its correct position
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    int pi = i + 1;

    // partition details
    cout << "Pivot: " << pivot << endl;
    cout << "Pivot index: " << pi << endl;

    cout << "Array: ";

    for (int x = 0; x < arraySize; x++) {
        cout << arr[x] << " ";
    }

    cout << endl << endl;

    return pi;
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {

    if (low < high) {

        int pi = partition(arr, low, high);

        // sort left side
        quickSort(arr, low, pi - 1);

        // sort right side
        quickSort(arr, pi + 1, high);
    }
}

int main() {

    // TEST 1: First given array
    int arr1[] = { 2, 1, 5, 4, 6, 3 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    arraySize = n1;
    comparisonCount = 0;

    cout << "TEST 1: First Array" << endl;

    quickSort(arr1, 0, n1 - 1);

    cout << "Sorted Array: ";
    for (int i = 0; i < n1; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;


    // TEST 2: Second given array
    int arr2[] = { 35, 12, 43, 8, 51, 27, 19 };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    arraySize = n2;
    comparisonCount = 0;

    cout << "\nTEST 2: Second Array" << endl;

    quickSort(arr2, 0, n2 - 1);

    cout << "Sorted Array: ";
    for (int i = 0; i < n2; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;


    // TEST 3: Random order
    int arr3[] = { 5, 1, 4, 2, 8 };
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    arraySize = n3;
    comparisonCount = 0;

    cout << "\nTEST 3: Random Order" << endl;

    quickSort(arr3, 0, n3 - 1);

    cout << "Total Comparisons: " << comparisonCount << endl;


    // TEST 4: Already sorted
    int arr4[] = { 1, 2, 4, 5, 8 };
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    arraySize = n4;
    comparisonCount = 0;

    cout << "\nTEST 4: Already Sorted" << endl;

    quickSort(arr4, 0, n4 - 1);

    cout << "Total Comparisons: " << comparisonCount << endl;


    // TEST 5: Reverse sorted
    int arr5[] = { 8, 5, 4, 2, 1 };
    int n5 = sizeof(arr5) / sizeof(arr5[0]);

    arraySize = n5;
    comparisonCount = 0;

    cout << "\nTEST 5: Reverse Sorted" << endl;

    quickSort(arr5, 0, n5 - 1);

    cout << "Total Comparisons: " << comparisonCount << endl;


    // TEST 6: Repeated values
    int arr6[] = { 7, 7, 7, 7, 7 };
    int n6 = sizeof(arr6) / sizeof(arr6[0]);

    arraySize = n6;
    comparisonCount = 0;

    cout << "\nTEST 6: Repeated Values" << endl;

    quickSort(arr6, 0, n6 - 1);

    cout << "Total Comparisons: " << comparisonCount << endl;


    // TEST 7: Empty array
    int arr7[1];
    int n7 = 0;

    arraySize = n7;
    comparisonCount = 0;

    cout << "\nTEST 7: Empty Array" << endl;

    quickSort(arr7, 0, n7 - 1);

    cout << "Total Comparisons: " << comparisonCount << endl;


    // TEST 8: Single element
    int arr8[] = { 7 };
    int n8 = sizeof(arr8) / sizeof(arr8[0]);

    arraySize = n8;
    comparisonCount = 0;

    cout << "\nTEST 8: Single Element" << endl;

    quickSort(arr8, 0, n8 - 1);

    cout << "Total Comparisons: " << comparisonCount << endl;

    return 0;
}
