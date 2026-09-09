int main()
{
    int mode;


    // Test 1: Unique mode
    int array1[] = { 1, 2, 2, 3, 4 };

    if (histogram(array1, 5, mode))
    {
        cout << "Test 1 - Mode: " << mode << endl;
    }



    // Test 2: Multiple modes
    int array2[] = { 1, 1, 2, 2, 3 };

    if (histogram(array2, 5, mode))
    {
        cout << "Test 2 - Mode: " << mode << endl;
    }




    // Test 3: Empty array
    int array3[1];

    if (!histogram(array3, 0, mode))
    {
        cout << "Test 3 - Array is empty." << endl;
    }

    return 0;
}
