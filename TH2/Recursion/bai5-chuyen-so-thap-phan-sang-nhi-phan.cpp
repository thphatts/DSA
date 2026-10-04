#include <iostream>
using namespace std;

void doiNhiPhan(long long n)
{
    if (n < 2)
    {
        cout << n;
        return;
    }
    doiNhiPhan(n / 2);
    cout << n % 2;
}

int main()
{
    long long n;
    cin >> n;

    doiNhiPhan(n);
    return 0;
}