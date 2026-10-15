#include <iostream>
using namespace std;

void inputIDs(int array[], int n) {

	for (int i = 0; i < n;i++) {
		cout << "Enter student Id: ";
		cin >> array[i];
	}
}

int linearSearch(int arr[], int n, int target) {

	for (int i = 0;i < n;i++) {
		if (arr[i] == target) {
			return i;
		}
	}
	return -1;
}

void displayResult(int index){

	if (index != -1) {
		cout << "Index: " << index;
	}
	else
		cout << "Not found";
}
int main() {
	int student_id[100];

	int n;
	cout << "Total Student IDs you want to enter:";
	cin >> n;

	if (n < 0) {
		cout << "Invalid Size";
		return 1;
	}
	else if (n == 0) {
		cout << "Empty array";
		return 1;
	}
	else {
		inputIDs(student_id, n);
	}

	char choice;
	do {
		int target;
		cout << "\nID you want to find:";
		cin >> target;

		if (target <= 0) {
			cout << "Inavalid ID";
			return 1;
		}
		else {
			int index;
			index = linearSearch(student_id, n, target);
			displayResult(index);
		}
		cout << "\nDo you to find more IDs (y/n): ";
		cin >> choice;
	} while (choice == 'y');

	return 0;
}
