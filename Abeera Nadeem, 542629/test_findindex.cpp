int main() {

	// test module 1 (multiple occurences)
	int x[5] = { 1,9,6,5,9 };

	int indices1[5];

	cout << "TEST MODULE 1 (multiple occurences):\n";
	find_index(x, 5, 9, indices1);  //calling function

	// test module 2 (no occurence)
	int y[5] = { 1,9,6,5,9 };

	int indices2[5];

	cout << "\nTEST MODULE 2 (no occurence):\n";
	find_index(y, 5, 2, indices2);  //calling function

	// test module 3 (empty array)
	int z[5] = {};

	int indices3[5];

	cout << "\nTEST MODULE 3 (empty array):\n";
	find_index(z, 0, 9, indices3);  //calling function

	return 0;
}