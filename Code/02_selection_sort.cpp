// C++17. Moi tep co main rieng, bien dich tung tep doc lap.
// Thay NOI DUNG giua begin your code va end your code.
// Cac gia tri tra ve tam thoi KHONG phai dap an.
#include <iostream>
using namespace std;
const int MAX_N = 100;

void printArray(const int a[], int n)
{
    if (n == 0)
        cout << "(rong)";
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    cout << '\n';
}
void copyArray(const int source[], int destination[], int n)
{
    for (int i = 0; i < n; ++i)
        destination[i] = source[i];
}
bool sameArray(const int a[], const int b[], int n)
{
    for (int i = 0; i < n; ++i)
        if (a[i] != b[i])
            return false;
    return true;
}

void selectionSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[minIdx])
            {
                minIdx = j;
            }
        }
        if (a[minIdx] != i)
        {
            int temp = a[i];
            a[i] = a[minIdx];
            a[minIdx] = temp;
        }
    }
}

void check(const char label[], const int input[], const int expected[], int n)
{
    int a[MAX_N];
    copyArray(input, a, n);
    selectionSort(a, n);
    cout << label << ": ";
    printArray(a, n);
    cout << (sameArray(a, expected, n) ? "[DAT]\n" : "[CHUA DAT]\n");
}
int main()
{
    int input[] = {29, -4, 10, 29, 0, 7};
    int sorted[] = {-4, 0, 7, 10, 29, 29};
    int reversed[] = {5, 4, 3, 2, 1};
    int ascending[] = {1, 2, 3, 4, 5};
    int equal[] = {8, 8, 8, 8};
    int one[] = {42};
    check("Hon hop", input, sorted, 6);
    check("Da sap xep", sorted, sorted, 6);
    check("Giam dan", reversed, ascending, 5);
    check("Bang nhau", equal, equal, 4);
    check("Mot phan tu", one, one, 1);
    check("Mang rong", one, one, 0);
    return 0;
}
/*
- sau lượt lặp thứ i thì tất cả các phần tử từ vị trí 0 đến a[i] đều được cố định tại vị trí đó và không duyệt lần nữa
- selection sort vẫn thực hiện bậc 2 phép so sánh cho dù mảng được sắp xếp
*/
