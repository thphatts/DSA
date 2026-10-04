#include <iostream>
#include <vector>

using namespace std;
using Mask = unsigned long long;

Mask adj[45] = {};
vector<int> current;
vector<int> best;

void search(Mask candidates)
{
    int remaining = __builtin_popcountll(candidates);

    if ((int)current.size() + remaining <= (int)best.size())
    {
        return;
    }
    if (candidates == 0)
    {
        best = current;
        return;
    }

    int v = __builtin_ctzll(candidates);
    Mask bit = 1ULL << v;

    Mask rest = candidates & ~bit;

    current.push_back(v + 1);

    search(rest & ~adj[v]);

    current.pop_back();

    search(rest);
}

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;

        --u;
        --v;

        adj[u] |= 1ULL << v;
        adj[v] |= 1ULL << u;
    }

    Mask all = (1ULL << n) - 1;
    search(all);

    cout << best.size() << '\n';

    for (int i = 0; i < (int)best.size(); ++i)
    {
        if (i > 0)
            cout << ' ';
        cout << best[i];
    }
    cout << '\n';

    return 0;
}