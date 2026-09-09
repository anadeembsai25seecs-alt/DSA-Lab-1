#include <iostream>
using namespace std;

void pascal_triangle(int n)
{
    if (n == 0)
    {
        cout << "Empty triangle." << endl;
        return;
    }

    int tri[100][100] = {};

    for (int i = 0; i < n; i++)
    {
        tri[i][0] = 1;
        tri[i][i] = 1;

        for (int j = 1; j < i; j++)
        {
            tri[i][j] = tri[i - 1][j - 1]
                + tri[i - 1][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << tri[i][j] << " ";
        }

        cout << endl;
    }
}
