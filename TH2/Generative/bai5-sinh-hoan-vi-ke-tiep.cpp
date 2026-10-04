/*
# thuật toán sinh:
Cho một hoán vị P của các số từ 1 đến n, P chưa phải hoán vị giảm dần. Hãy sinh hoán vị đứng ngay sau P theo thứ tự từ điển bằng quy tắc: tìm điểm tăng từ bên phải, đổi chỗ với phần tử phù hợp và đảo phần đuôi.
Input: Dòng 1 chứa n (2 ≤ n ≤ 100). Dòng 2 chứa n số nguyên của hoán vị P.
Output: In hoán vị kế tiếp trên một dòng.
*/

#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin >> n;

    int a[100];
    for (int k = 0; k < n; k++)
    {
        cin >> a[k];
    }

    int i = n - 2; // bắt đầu từ vị trí gần cuối để so sánh với phần từ cuối
    while (i >= 0 && a[i] > a[i + 1])
    {
        i--;
    }

    int j = n - 1; // tìm phần tử thay từ phần tử cuối
    while (a[j] < a[i])
    {
        j--;
    }

    swap(a[i], a[j]);

    int left = i + 1;
    int right = n - 1;

    while (left < right)
    {
        swap(a[left], a[right]);
        left++;
        right--;
    }
    for (int k = 0; k < n; k++)
    {
        if (k > 0)
        {
            cout << ' ';
        }
        cout << a[k];
    }
    return 0;
}