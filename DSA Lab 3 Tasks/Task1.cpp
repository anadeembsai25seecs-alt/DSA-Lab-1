#include <iostream>
#include<string>  // for getline() function
#include <cctype>  // library imported to use tolower() function
using namespace std;

bool check_palindrome(string palindrome) {  //function to check if the word is a palindrome

    string text = "";

    for (int i = 0;i < palindrome.length();i++) {
        if (isalnum(palindrome[i])) {  // this function isalnum() checks if the letter is alphanumeric meaning ignores spaces and punctuation
            text += tolower(palindrome[i]);  // tolower() lowers all letters of palindrome
        }
    }
    int n = text.length();

    for (int i = 0; i < n/2; i++) {

        if (text[i] != text[n - 1 - i]) {  //checks for atleast 1 pair to be unmatched and returns false
            return false;  
        }

    }
    return true;  //if 'if' condition is not fulfilled then the function returns true
}
int main() {

    string palindrome;

    cout << "Enter the word you want to check: ";
    getline(cin,palindrome);

    bool check = check_palindrome(palindrome);

    if (check) {
        cout << "The text '" << palindrome << "'is a palindrome";
    }
    else
        cout << "The text '" << palindrome << "'is not a palindrome";
}
