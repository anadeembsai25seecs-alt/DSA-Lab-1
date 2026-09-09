void print_matrix(int A[][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << " ";
        }

        cout << endl;
    }
}


int main(){

    // Test 1: 2x2 matrix


    int A2[100][100] = {
        {1, 2},
        {3, 4}
    };

    int B2[100][100] = {
        {5, 6},
        {7, 8}
    };

    int C2_strassen[100][100] = {};
    int C2_standard[100][100] = {};

    strassen(A2, B2, C2_strassen, 2);
    standard_multiply(A2, B2, C2_standard, 2);

    cout << "Test 1 - 2x2 matrix:" << endl;

    cout << "Strassen result:" << endl;
    print_matrix(C2_strassen, 2);

    cout << "Standard result:" << endl;
    print_matrix(C2_standard, 2);

    cout << "Match: "
        << (compare_matrices(C2_strassen, C2_standard, 2) ? "Yes" : "No")
        << endl;



    // Test 2: 4x4 matrix
 

    int A4[100][100] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int B4[100][100] = {
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };

    int C4_strassen[100][100] = {};
    int C4_standard[100][100] = {};

    strassen(A4, B4, C4_strassen, 4);
    standard_multiply(A4, B4, C4_standard, 4);

    cout << endl;
    cout << "Test 2 - 4x4 matrix:" << endl;

    cout << "Match: "
        << (compare_matrices(C4_strassen, C4_standard, 4) ? "Yes" : "No")
        << endl;


  
    // Test 3: Random values


    int A_random[100][100] = {
        {2, 4, 1, 3},
        {5, 1, 2, 4},
        {3, 6, 2, 1},
        {4, 2, 5, 3}
    };

    int B_random[100][100] = {
        {1, 3, 2, 4},
        {2, 5, 1, 3},
        {4, 2, 3, 1},
        {3, 1, 4, 2}
    };

    int C_random_strassen[100][100] = {};
    int C_random_standard[100][100] = {};

    strassen(A_random, B_random, C_random_strassen, 4);
    standard_multiply(A_random, B_random, C_random_standard, 4);

    cout << endl;
    cout << "Test 3 - Random values:" << endl;

    cout << "Match: "
        << (compare_matrices(
            C_random_strassen,
            C_random_standard,
            4)
            ? "Yes"
            : "No")
        << endl;

    return 0;
}
