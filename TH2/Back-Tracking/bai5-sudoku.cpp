#include <iostream>
using namespace std;
int a[4][4];

bool hopLe(int row, int col, int value)
{
    for (int k = 0; k < 4; k++)
    {
        if (a[row][k] == value)
        {
            return false;
        }
        if (a[k][col] == value)
        {
            return false;
        }

        int startRow = (row / 2) * 2;
        int startCol = (col / 2) * 2;
        for (int r = startRow; r < startRow + 2; r++)
        {
            for (int c = startCol; c < startCol + 2; c++)
            {
                if (a[r][c] == value)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool giaiSudoku()
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (a[row][col] != 0)
            {
                continue;
            }
            for (int value = 1; value <= 4; value++)
            {
                if (hopLe(row, col, value))
                {
                    a[row][col] = value;
                    if (giaiSudoku())
                    {
                        return true;
                    }
                    a[row][col] = 0;
                }
            }
            return false;
        }
    }
    return true;
}

int main()
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            cin >> a[row][col];
        }
    }
    if (giaiSudoku())
    {
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                cout << a[row][col] << ' ';
            }
            cout << '\n';
        }
    }
}