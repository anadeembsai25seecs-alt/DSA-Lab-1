#include <iostream>
using namespace std;

int main(){

	int students = 0;
	int subjects = 0;
	do {
		cout << "Enter number of students: ";
		cin >> students;
		if (students <= 0) cout << "Must be positive.\n";
	} while (students <= 0);

	do {
		cout << "Enter number of subjects: ";
		cin >> subjects;
		if (subjects <= 0)
			cout << "Must be positive.\n";
	} while (subjects <= 0);

	int** marks = new int*[students];  // when we make pointer to pointer array, we use asterisk with new int also
	/*we used pointer to pointer beacuse marks array pointer will point at the students matrix which is also a pointer
	which will point to the rows of subjects*/
	
	for (int i = 0; i < students;i++) {
		marks[i] = new int[subjects];
		// array is also a pointer so it now points to rows of subjects for each student
	}
	int* total = new int[students]() ;  //paranthesis initializes the array with 0
	//storing subject marks
	cout << "Enter marks(0-100):";
	for (int i = 0;i < students;i++) {
		cout << "\n--------Student " << i + 1 << "--------\n";
		for (int j = 0;j < subjects;j++) {

			cout << "Subject " << j + 1 << ": ";
			cin >> *(*(marks + i) + j);
			
			/*first we add i in marks array to point to 1 position on students array
			and derefrenced it to select student 1 and then j is added so that
			the subjects array pointed to by the student array pointer is set to 
			1 subject and then so on and derefrenced it to add marks at that address.*/

			total[i] += *(*(marks + i) + j);

			/*we have made an array for storing total marks of every student
			so it is done in the same manner as input was taken*/
		}
	}
	int max_marks = total[0];
	int index = 0;
	for (int i = 1;i < students;i++) {
		if (total[i] > max_marks) {
			max_marks = total[i];
		}
	}
	for (int i = 0;i < students;i++) {  
		if (max_marks == total[i]) { /*here we match max_marks with every element of total array and with which it matches
			first, we note its index and then break the loop.In this way, the first person to get the total as max will be printed.*/
			index = i + 1;
			break;
		}
	}
	// prints matrix of marks
	cout << "Matrix of Marks: \n";
	for (int i = 0; i < students; i++) {
		for (int j = 0; j < subjects; j++) {
			cout << marks[i][j] << " ";
		}
		cout << endl;
	}

	cout << "Totals: ";
	for (int i = 0;i < students;i++) { //to print totals
		cout << total[i] << " ";
	}
	cout << "\nHighest total '" << max_marks << "' obtained by student " << index;

	for (int i = 0;i < students;i++) {
		delete[] marks[i]; //deletes rows
	}
	delete[]marks; // deletes row pointer array
	marks = nullptr;
	delete[]total;
}

