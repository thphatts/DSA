/*
Đề bài: Nhập n và k, với 1 ≤ n ≤ 15, 0 ≤ k ≤ n. In tất cả chuỗi nhị phân độ dài n có đúng k bit bằng 1, theo thứ tự tăng dần.
*/

#include <iostream>
#include <vector>
using namespace std;

bool sinhNhiPhan(vector<int> &a)
{
    int i = a.size() - 1;
    while (i >= 0 && a[i] == 1)
    {
        a[i] = 0;
        i--;
    }

    if (i < 0)
    {
        return false;
    }
    a[i] = 1;
    return true;
}

bool coDungKBit1(const vector<int> &a, int k)
{
    int dem = 0;
    for (int bit : a)
    {
        if (bit == 1)
        {
            dem++;
        }
    }
    if (dem == k)
    {
        return true;
    }
    return false;
}
int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n, 0);
    do
    {
        if (coDungKBit1(a, k))
        {
            for (int bit : a)
            {
                cout << bit;
            }
            cout << '\n';
        }
    } while (sinhNhiPhan(a));
    return 0;
}