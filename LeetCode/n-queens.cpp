#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n;
int totalSolutions = 0;
vector<int> col_pos;   // col_pos[i] lưu chỉ số cột của quân hậu ở hàng i
vector<bool> used_col; // Đánh dấu cột đã có hậu
vector<bool> diag1;    // Đánh dấu đường chéo xuôi (i - j + n)
vector<bool> diag2;    // Đánh dấu đường chéo ngược (i + j)

void printSolution()
{
    totalSolutions++;
    cout << "--- Cach xep thu " << totalSolutions << " ---" << '\n';
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (col_pos[i] == j)
                cout << " Q ";
            else
                cout << " . ";
        }
        cout << '\n';
    }
    cout << '\n';
}

void backtrack(int row)
{
    // Nếu đã đặt thành công N quân hậu từ hàng 1 đến hàng n
    if (row > n)
    {
        printSolution();
        return;
    }

    // Thử đặt quân hậu ở hàng 'row' vào từng cột 'c'
    for (int c = 1; c <= n; c++)
    {
        int d1 = row - c + n; // Chuyển về chỉ số dương
        int d2 = row + c;

        // Nếu cột và hai đường chéo đều an toàn
        if (!used_col[c] && !diag1[d1] && !diag2[d2])
        {
            // Đặt hậu & đánh dấu
            col_pos[row] = c;
            used_col[c] = true;
            diag1[d1] = true;
            diag2[d2] = true;

            // Đệ quy sang hàng tiếp theo
            backtrack(row + 1);

            // Quay lui: Trả lại trạng thái cũ
            used_col[c] = false;
            diag1[d1] = false;
            diag2[d2] = false;
        }
    }
}

int main()
{
    cout << "Nhap N: ";
    if (!(cin >> n) || n <= 0)
        return 0;

    col_pos.resize(n + 1);
    used_col.assign(n + 1, false);
    diag1.assign(2 * n + 1, false);
    diag2.assign(2 * n + 1, false);

    backtrack(1);

    cout << "Tong so cach dat: " << totalSolutions << '\n';
    return 0;
}