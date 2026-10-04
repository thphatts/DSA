#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

vector<long long> a;
long long maxSubarray(int left, int right)
{
    if (left == right)
    {
        return a[left];
    }
    int mid = left + (right - left) / 2;

    // truong hop neu nam hoan toan ben trai
    long long bestLeft = maxSubarray(left, mid);

    // truong hop nam ben phai
    long long bestRight = maxSubarray(mid + 1, right);

    long long sum = 0;
    long long leftSuffix = LLONG_MIN;
    for (int i = mid; i >= left; i--)
    {
        sum += a[i];
        leftSuffix = max(leftSuffix, sum);
    }

    sum = 0;
    long long rightPrefix = LLONG_MIN;

    for (int i = mid + 1; i <= right; i++)
    {
        sum += a[i];
        rightPrefix = max(rightPrefix, sum);
    }
    long long bestCross = leftSuffix + rightPrefix;
    return max({bestLeft, bestRight, bestCross});
}

int main()
{
    int n;
    cin >> n;
    a.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << maxSubarray(0, n - 1);
    return 0;
}