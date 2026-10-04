// Đề bài: Cho các số từ 1 đến n. In tất cả cách chọn k số khác nhau theo thứ tự từ điển, với 1 ≤ k ≤ n ≤ 15.
#include <iostream>
#include <vector>
using namespace std;

bool sinhToHop(vector<int> &a, int n)
{
    int k = a.size();
    int i = k - 1;

    // tim vi tri con tang duoc
    while (i >= 0 && a[i] == n - k + i + 1)
    {
        i--;
    }
    if (i < 0)
    {
        return false;
    }
    a[i]++;

    // phan duoi nho nhat, van tang dan
    for (int j = i + 1; j < k; j++)
    {
        a[j] = a[j - 1] + 1;
    }
    return true;
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(k);
    for (int i = 0; i < k; i++)
    {
        a[i] = i + 1;
    }
    do
    {
        for (int i = 0; i < k; i++)
        {
            if (i > 0)
            {
                cout << ' ';
            }
            cout << a[i];
        }
        cout << '\n';
    } while (sinhToHop(a, n));
    return 0;
}