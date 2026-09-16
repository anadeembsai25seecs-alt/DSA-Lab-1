#include <iostream>
using namespace std;

int main(){

       int n;
       do {
           cout << "Enter number of marks (1-10): ";
           cin >> n;

           if (n < 1 || n > 10)
               cout << "Enter a number between 1 and 10.\n";

       } while (n < 1 || n > 10);

 
       int* marks = new int[n];  // first we allocate memory for original n values

       cout << "Enter " << n << " marks:\n";

       for (int i = 0; i < n; i++) {
           cin >> *(marks + i);
       }

       int* newMarks = new int[n + 1]; // then we allocate a second block for n+1 integers

       for (int i = 0; i < n; i++) { // for loop is used for copying original n values into second block
           *(newMarks + i) = *(marks + i); /*newMarks + i moves the index from 0 to last in second alloacted block of n + 1 values
           and '*' derefrence operator gives the value at that address and same happens with marks+i one*/
       }

       // Read the new mark into the final position
       cout << "Enter new mark: ";
       cin >> *(newMarks + n); // adding n to newMarks moves the pointer to last index

       delete[] marks;  // deletes the old block

       // Make original pointer refer to the new block
       marks = newMarks;

       // Update the stored size
       n = n + 1;

       // Display all values
       cout << "All marks: ";
       for (int i = 0; i < n; i++) {
           cout << *(marks + i) << " ";
       }            
       cout << endl;

       delete[] marks; // Release the final block
       marks = nullptr;
   }
 
