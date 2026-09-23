#include <iostream>
using namespace std;

class StringPool {

private:
    string* stringPool;
    int currentSize;
    int maxSize;

public:
    StringPool() {

        currentSize = 0;
        maxSize = 5;
        stringPool = new string[maxSize];  //dynamic array created
    }
    void addString(string str) {  //method to add string to string pool
        if (currentSize < maxSize) {
            stringPool[currentSize] = str;  //adds string to string pool
            currentSize++;
            cout << str << " added.\n";
        }
        else {
            cout << str << " cannot be added. The pool is out of space.\n";
        }
    }
    //removes string without freeing memory
    void removeString(int location) {
        if (location > 0 && location <= currentSize) {

            cout << endl << stringPool[location - 1] << " removed.";

            // shift every string after the removed one back by one slot
            for (int i = location - 1; i < currentSize - 1; i++) {
                stringPool[i] = stringPool[i + 1];
            }

            stringPool[currentSize - 1] = "";  //clear the now-unused last slot
            currentSize--;
        }
        else {
            cout << "Invalid location: " << location << ".\n";
        }
    }
    // Display pool status
    void displayPool() {

        cout << "\n--Pool Status:--" << endl;

        for (int i = 0; i < currentSize; i++) {
            cout << i << ": " << stringPool[i] << endl;
        }

        cout << "Current size: " << currentSize << endl;
        cout << "Maximum size: " << maxSize << endl;
    }

    ~StringPool() {  // it is a destructor it fixes the memory leak
        delete[] stringPool;
        stringPool = nullptr;

        cout << "\nMemory released. Pool deleted." << endl;
    }
};


int main() {

    StringPool pool; //object created

    pool.addString("Apple");
    pool.addString("Banana");
    pool.addString("Watermelon");
    pool.addString("Grapes");
    pool.addString("Orange");
    pool.addString("Strawberry");  // this wont be added beacuse the max limit is 5

    pool.displayPool();

    pool.removeString(5);
    pool.removeString(3);
    pool.removeString(9); //this line will give error because out of range

    pool.displayPool();

    /*when the main ends, the pool function gets out of scope and
    then the destructor runs and free the memory preventing memory leak*/

}
