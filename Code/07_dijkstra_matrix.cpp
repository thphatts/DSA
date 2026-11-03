// C++17. Moi tep co main rieng, bien dich tung tep doc lap.
// Thay NOI DUNG giua begin your code va end your code.
// Cac gia tri tra ve tam thoi KHONG phai dap an.
#include <iostream>
using namespace std;

const int MAX_V = 50;
const long long INF = (1LL << 60);

struct Graph
{
    int n;
    long long weight[MAX_V + 1][MAX_V + 1];
};

void createSample(Graph &g)
{
    g.n = 6;
    for (int i = 1; i <= g.n; ++i)
        for (int j = 1; j <= g.n; ++j)
            g.weight[i][j] = (i == j ? 0 : INF);
    g.weight[1][2] = 4;
    g.weight[1][3] = 1;
    g.weight[3][2] = 2;
    g.weight[2][4] = 1;
    g.weight[3][4] = 5;
    g.weight[3][5] = 8;
    g.weight[4][5] = 3;
    g.weight[2][5] = 0;
}

int selectMinVertex(const long long distance[], const bool visited[], int n)
{
    int minVertex = -1;
    long long minDist = INF;

    for (int v = 1; v <= n; ++v)
    {
        if (!visited[v] && distance[v] < minDist)
        {
            minDist = distance[v];
            minVertex = v;
        }
    }
    return minVertex;
}

void dijkstra(const Graph &g, int source, long long distance[], int parent[])
{
    bool visited[MAX_V + 1] = {};
    for (int v = 1; v <= g.n; ++v)
    {
        distance[v] = INF;
        parent[v] = -1;
    }
    distance[source] = 0;
    parent[source] = source;
    for (int step = 1; step <= g.n; ++step)
    {
        int u = selectMinVertex(distance, visited, g.n);
        if (u == -1)
            break;

        visited[u] = true;

        for (int v = 1; v <= g.n; ++v)
        {
            if (!visited[v] && g.weight[u][v] < INF)
            {
                if (distance[u] + g.weight[u][v] < distance[v])
                {
                    distance[v] = distance[u] + g.weight[u][v];
                    parent[v] = u;
                }
            }
        }
    }
}

void printRoute(const int parent[], int n, int source, int target)
{
    int route[MAX_V + 1], length = 0, v = target;
    while (v >= 1 && v <= n && length < n)
    {
        route[length++] = v;
        if (v == source)
            break;
        v = parent[v];
    }
    if (length == 0 || route[length - 1] != source)
    {
        cout << "(chuoi cha chua hop le)";
        return;
    }
    for (int i = length - 1; i >= 0; --i)
    {
        cout << route[i];
        if (i != 0)
            cout << " -> ";
    }
}

int main()
{
    Graph g;
    createSample(g);
    const int source = 1;
    long long distance[MAX_V + 1];
    int parent[MAX_V + 1];
    dijkstra(g, source, distance, parent);
    long long expected[] = {INF, 0, 3, 1, 4, 3, INF};
    cout << "Dijkstra tu nguon 1 - do thi co huong\n";
    for (int v = 1; v <= g.n; ++v)
    {
        cout << "Dinh " << v << ": ";
        if (distance[v] == INF)
            cout << "INF (khong co duong)";
        else
        {
            cout << distance[v] << "; duong: ";
            printRoute(parent, g.n, source, v);
        }
        cout << (distance[v] == expected[v] ? " [DAT]\n" : " [CHUA DAT]\n");
    }
    return 0;
}