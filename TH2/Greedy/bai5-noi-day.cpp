#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n;
    cin >> n;

    priority_queue<long long, vector<long long>, greater<long long>> pq;

    for (int i = 0; i < n; i++)
    {
        long long length;
        cin >> length;
        pq.push(length);
    }
    long long total = 0;
    while (pq.size() > 1)
    {
        long long a = pq.top();
        pq.pop();

        long long b = pq.top();
        pq.pop();

        long long sum = a + b;
        total += sum;
        pq.push(sum);
    }
    cout << total;
    return 0;
}