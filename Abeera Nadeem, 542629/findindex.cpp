#include <iostream>
#include <array>
using namespace std;

void find_index(int array[], int array_size, int target, int index[]) {

	if (array_size == 0) {
		cout << "The array is empty.\n";
	}

	int count = 0;

	for (int i = 0; i < array_size; i++) {   //we use for loop to check all elements of array for target

		if (array[i] == target) {   //if element matches the target
			index[count] = i;       /*the array of indices stores that index at as first element of array as count is 0
									  count is then incremented and if the target is also at some other index at array it stores that index
									  at second element of array.*/
			count++;
		}

	}
	if (count == 0) {
		cout << "Element was not found.\n";
	}
	for (int i = 0; i < count; i++) {
		cout << "Element was found at index " << index[i] << endl;
	}

}

