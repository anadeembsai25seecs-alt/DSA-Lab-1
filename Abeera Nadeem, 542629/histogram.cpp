#include <iostream>
using namespace std;


bool histogram(int array[], int size, int& mode)
{
    if (size == 0)
    {
        return false;
    }

    int highest_count = 0;

    for (int i = 0; i < size; i++)
    {
        int count = 0;

        for (int j = 0; j < size; j++)
        {
            if (array[i] == array[j])
            {
                count++;
            }
        }

        if (count > highest_count)
        {
            highest_count = count;
            mode = array[i];
        }
    }

    return true;
}
