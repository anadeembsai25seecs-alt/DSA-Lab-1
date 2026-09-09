int main()
{
    // Test 1 (Pattern at the beginning)
    cout << "Test 1: ";
    cout << findPattern("anaya", "ana");
    


    // Test 2 (Pattern at the end)
    cout << "\nTest 2: ";
    cout << findPattern("replicate", "cate");
    


    // Test 3 (Pattern not present)
    cout << "\nTest 3: ";
    cout << findPattern("force", "cat");
   


    // Test 4 (Empty pattern)
    cout << "\nTest 4: ";
    cout << findPattern("ridiculous", "");
    

    return 0;
}
