#include <iostream>
using namespace std;

void merge(int arr[], int low, int mid, int high, int n) {

	//setting limits for temporary arrays
	int n1 = mid - low + 1;
	int n2 = high - mid;

	//forming temporary arrays
	int* l = new int[n1];
	int* r = new int[n2];

	//saving elements in left and then in right array
	for (int i = 0;i < n1;i++) {
		l[i] = arr[low + i];
	}

	for (int j = 0;j < n2;j++) {
		r[j] = arr[mid + 1 + j];
	}

	int i = 0, j = 0, k = low;

	//comparing values from both arrays and adding them to main array
	while (i < n1 && j < n2) {

		if (l[i] <= r[j]) {
			arr[k] = l[i];
			i++;
		}
		else {
			arr[k] = r[j];
			j++;
		}
		k++;
	}

	//adding remaining elements into array
	while (i < n1) {
		arr[k] = l[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = r[j];
		j++;
		k++;
	}

	cout << "Merged range [" << low << ".." << high << "]: ";

	for (int x = 0; x < n; x++) {
		cout << arr[x] << " ";
	}

	cout << endl;

	// deleting temporary memory
	delete[] l;
	delete[] r;

}

void mergeSort(int arr[], int low, int high, int n) {

	// base case
	if (low >= high) {
		return;
	}

	// middle index
	int mid = low + (high - low) / 2;

	// dividing left half
	mergeSort(arr, low, mid,n);

	// dividing right half
	mergeSort(arr, mid + 1, high,n);

	// merging both sorted halves
	merge(arr, low, mid, high,n);
}

int main() {

	int arr[] = { 35, 12, 43, 8, 51, 27, 19 };

	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "Original Array: ";

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	cout << endl << endl;

	mergeSort(arr, 0, n - 1, n);


	cout << endl << "Final Sorted Array: ";

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	// Test 1: Already sorted
	int arr1[] = { 1, 2, 4, 5, 8 };
	int n1 = sizeof(arr1) / sizeof(arr1[0]);

	cout << "\nAlready Sorted Array:" << endl;
	mergeSort(arr1, 0, n1 - 1, n1);

	cout << "Final Array: ";
	for (int i = 0; i < n1; i++) {
		cout << arr1[i] << " ";
	}
	cout << endl;


	// Test 2: Reverse sorted
	int arr2[] = { 8, 5, 4, 2, 1 };
	int n2 = sizeof(arr2) / sizeof(arr2[0]);

	cout << "\nReverse Sorted Array:" << endl;
	mergeSort(arr2, 0, n2 - 1, n2);

	cout << "Final Array: ";
	for (int i = 0; i < n2; i++) {
		cout << arr2[i] << " ";
	}
	cout << endl;


	// Test 3: Repeated values
	int arr3[] = { 5, 2, 5, 1, 2 };
	int n3 = sizeof(arr3) / sizeof(arr3[0]);

	cout << "\nRepeated Values Array:" << endl;
	mergeSort(arr3, 0, n3 - 1, n3);

	cout << "Final Array: ";
	for (int i = 0; i < n3; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;


	// Test 4: Single element
	int arr4[] = { 7 };
	int n4 = sizeof(arr4) / sizeof(arr4[0]);

	cout << "\nSingle Element Array:" << endl;
	mergeSort(arr4, 0, n4 - 1, n4);

	cout << "Final Array: ";
	for (int i = 0; i < n4; i++) {
		cout << arr4[i] << " ";
	}
	cout << endl;


	// Test 5: Empty array
	int arr5[1];
	int n5 = 0;

	cout << "\nEmpty Array:" << endl;
	mergeSort(arr5, 0, n5 - 1, n5);

	cout << "Array is empty." << endl;

	return 0;
}
