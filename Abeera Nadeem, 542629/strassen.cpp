#include <iostream>
using namespace std;

void add(int A[][100], int B[][100], int C[][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(int A[][100], int B[][100], int C[][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(int A[][100], int B[][100], int C[][100], int n)
{
    // Base case: 1x1 matrix
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;

    int A11[100][100] = {};
    int A12[100][100] = {};
    int A21[100][100] = {};
    int A22[100][100] = {};

    int B11[100][100] = {};
    int B12[100][100] = {};
    int B21[100][100] = {};
    int B22[100][100] = {};

    int P1[100][100] = {};
    int P2[100][100] = {};
    int P3[100][100] = {};
    int P4[100][100] = {};
    int P5[100][100] = {};
    int P6[100][100] = {};
    int P7[100][100] = {};

    int temp1[100][100] = {};
    int temp2[100][100] = {};

    // Divide A and B into four parts
    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // P1 = A11 * (B12 - B22)
    subtract(B12, B22, temp1, half);
    strassen(A11, temp1, P1, half);

    // P2 = (A11 + A12) * B22
    add(A11, A12, temp1, half);
    strassen(temp1, B22, P2, half);

    // P3 = (A21 + A22) * B11
    add(A21, A22, temp1, half);
    strassen(temp1, B11, P3, half);

    // P4 = A22 * (B21 - B11)
    subtract(B21, B11, temp1, half);
    strassen(A22, temp1, P4, half);

    // P5 = (A11 + A22) * (B11 + B22)
    add(A11, A22, temp1, half);
    add(B11, B22, temp2, half);
    strassen(temp1, temp2, P5, half);

    // P6 = (A12 - A22) * (B21 + B22)
    subtract(A12, A22, temp1, half);
    add(B21, B22, temp2, half);
    strassen(temp1, temp2, P6, half);

    // P7 = (A11 - A21) * (B11 + B12)
    subtract(A11, A21, temp1, half);
    add(B11, B12, temp2, half);
    strassen(temp1, temp2, P7, half);

    // Calculate result quadrants
    int C11[100][100] = {};
    int C12[100][100] = {};
    int C21[100][100] = {};
    int C22[100][100] = {};

    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            C11[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];

            C12[i][j] = P1[i][j] + P2[i][j];

            C21[i][j] = P3[i][j] + P4[i][j];

            C22[i][j] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
        }
    }

    // Combine four quadrants
    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }
}


// Standard matrix multiplication
void standard_multiply(int A[][100], int B[][100], int C[][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


// Compare two matrices
bool compare_matrices(int A[][100], int B[][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] != B[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

