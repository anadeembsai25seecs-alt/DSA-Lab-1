#include <iostream>
using namespace std;

int main() {

	int list[5] = { 3,6,9,12,15 };
	int* pArr = list;   //allocating pointer to list

	cout << "List: ";
	for (int i = 0;i < 5;i++) {
		cout << *(pArr + i) << " ";
	}
	/*here pArr gives the address of first element of list so we add i starting from 0
	  i then iterates to 1 and the pointer moves to next element and so on until for loop continues
	  '*' dereference variable prints the value at that memory address */ 
		                            
		                             
}
