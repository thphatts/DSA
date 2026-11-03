// C++17. Moi tep co main rieng, bien dich tung tep doc lap.
// Thay NOI DUNG giua begin your code va end your code.
// Cac gia tri tra ve tam thoi KHONG phai dap an.
#include <iostream>
using namespace std;

int binarySearchFirst(const int a[], int n, int x)
{
    int left = 0;
    int right = n - 1;
    int result = -1;

    while (left <= right)
    {
        // tránh lỗi tràn số khi left và right quá lơns
        int mid = left + (right - left) / 2;
        if (a[mid] < x)
        {
            left = mid + 1;
        }
        else if (a[mid] > x)
        {
            right = mid - 1;
        }
        else
        {
            result = mid;
            right = mid - 1;
        }
    }

    return result;
}

void check(const char label[], const int a[], int n, int x, int expected)
{
    int result = binarySearchFirst(a, n, x);
    cout << label << ": thuc te = " << result << ", mong doi = " << expected;
    cout << (result == expected ? " [DAT]\n" : " [CHUA DAT]\n");
}
int main()
{
    int a[] = {-7, 0, 3, 3, 3, 12, 20};
    int one[] = {5};
    check("Gia tri lap", a, 7, 3, 2);
    cout << "test";
    check("Khong ton tai", a, 7, 9, -1);
    check("Dau mang", a, 7, -7, 0);
    check("Cuoi mang", a, 7, 20, 6);
    check("Mang rong", a, 0, 3, -1);
    check("Mot phan tu", one, 1, 5, 0);
    return 0;
}

/*
- không được trả về ngay khi a[mid] == x vì trong vài trường hợp trùng sẽ tìm sai vị trí xuất hiện đầu tiên
- nếu mảng chưa được sắp xếp thì điều kiện của mid sẽ sai vì không biết được x nằm khoảng right hay left
*/
