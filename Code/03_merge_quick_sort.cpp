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

void merge(int a[], int left, int mid, int right, int temp[])
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (a[i] <= a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }

    while (i <= mid)
    {
        temp[k++] = a[i++];
    }

    while (j <= right)
    {
        temp[k++] = a[j++];
    }

    for (int p = left; p <= right; ++p)
    {
        a[p] = temp[p];
    }
}

void mergeSort(int a[], int left, int right, int temp[])
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid, temp);
    mergeSort(a, mid + 1, right, temp);
    merge(a, left, mid, right, temp);
}

int partition(int a[], int left, int right)
{
    int pivot = a[right];
    int i = left - 1;

    for (int j = left; j < right; ++j)
    {
        if (a[j] <= pivot)
        {
            i++;
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    int t = a[i + 1];
    a[i + 1] = a[right];
    a[right] = t;

    return i + 1;
}

void quickSort(int a[], int left, int right)
{
    if (left >= right)
        return;

    int p = partition(a, left, right);
    quickSort(a, left, p - 1);
    quickSort(a, p + 1, right);
}

void check(const char label[], const int input[], const int expected[], int n)
{
    int a[MAX_N], b[MAX_N], temp[MAX_N];
    copyArray(input, a, n);
    copyArray(input, b, n);
    mergeSort(a, 0, n - 1, temp);
    quickSort(b, 0, n - 1);
    cout << label << '\n';
    cout << "Merge Sort: ";
    printArray(a, n);
    cout << (sameArray(a, expected, n) ? "[DAT]\n" : "[CHUA DAT]\n");
    cout << "Quick Sort: ";
    printArray(b, n);
    cout << (sameArray(b, expected, n) ? "[DAT]\n" : "[CHUA DAT]\n");
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
