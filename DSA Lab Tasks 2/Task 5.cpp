#include <iostream>
using namespace std;

int temp = 0;

void swap1(int* pa, int* pb) {   //part a
	temp = *pa;     //temp variable is used for swapping
	*pa = *pb;
	*pb = temp;
	cout << "a = " << *pa << endl;
	cout << "b = " << *pb << endl;
}

void swap2(int** pa, int** pb) {    //part b
	temp = **pa;     
	**pa = **pb;
	**pb = temp;
	cout << "a = " << **pa << endl;
	cout << "b = " << **pb << endl;
}

int main() {

	int a = 5, b = 10;
	int* pa = &a; //pa and pb are pointer variables of type int. 
	int* pb = &b;

	int** ppa = &pa; //ppa and ppb are called double pointers or pointers-to-pointers.
	int** ppb = &pb;

	cout << "Before Swapping:\n";
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	cout << "After Swapping (part a):\n";
	swap1(pa, pb);  //address of a, address of b

	swap(a, b); // again swapping to test part b

	cout << "After Swapping (part b):\n";
	swap2(ppa, ppb);  //address of a, address of b
	

}


