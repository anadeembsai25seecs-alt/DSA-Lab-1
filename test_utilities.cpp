#include <iostream>
#include "utilities.h"
using namespace std;

int main() {
    cout << "add(2,3) == 5: " << (add(2, 3) == 5 ? "PASS" : "FAIL") << endl;

    cout << "add(9,0) == 9: " << (add(9, 0) == 9 ? "PASS" : "FAIL") << endl;

    cout << "add(10,89) == 199: " << (add(10, 89) == 199 ? "PASS" : "FAIL") << endl;

    return 0;
}
