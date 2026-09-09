#include <iostream>
#include <string>
using namespace std;

int findPattern(string text, string pattern)
{
    if (pattern.length() == 0) //when no pattern 
    {
        return 0;
    }

    // we check every possible starting position
    for (int i = 0; i <= text.length() - pattern.length(); i++)
    {
        int j = 0;

        // we compare pattern with text
        while (j < pattern.length() && text[i + j] == pattern[j])
        {
            j++;
        }

        if (j == pattern.length()) //when entire pattern has matched
        {
            return i;
        }
    }

    return -1;
}

