// Đề bài: Nhập số nguyên n, với 1 ≤ n ≤ 15. In tất cả chuỗi nhị phân độ dài n theo thứ tự tăng dần.

#include <iostream>
#include <vector>

using namespace std;
bool sinhNhiPhan(vector<int> &a)
{
    int i = a.size() - 1;

    // đi từ phải sang trái nếu gặp 1 thì đổi thành 0 và đi tiếp
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
int main()
{
    int n;
    cin >> n;
    vector<int> a(n, 0);
    do
    {
        for (int bit : a)
        {
            cout << bit;
        }
        cout << '\n';
    } while (sinhNhiPhan(a));
    return 0;
}