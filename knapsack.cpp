#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Item
{
    int weight;
    int value;
};

struct Node
{
    int level;
    int weight;
    int value;
    double bound;
};

bool compare(Item a, Item b)
{
    return (double)a.value / a.weight > (double)b.value / b.weight;
}

double getBound(Node node, int n, int capacity, const vector<Item> &items)
{
    if (node.weight >= capacity)
        return node.value;
    double bound = node.value;

    int totalWeight = node.weight;
    int i = node.level + 1;

    while (i < n && totalWeight + items[i].weight <= capacity)
    {
        totalWeight += items[i].weight;
        bound += items[i].value;

        i++;
    }
    if (i < n)
    {
        int remaining = capacity - totalWeight;
        bound += (double)remaining * items[i].value / items[i].weight;
    }
    return bound;
}

int knapsack(int capacity, vector<Item> items)
{
    int n = items.size();

    sort(items.begin(), items.end(), compare);

    queue<Node> q;
    Node root;
    root.level = -1;
    root.weight = 0;
    root.value = 0;

    root.bound = getBound(root, n, capacity, items);
    q.push(root);
    int best = 0;
    while (!q.empty())
    {
        Node current = q.front();
        q.pop();
        if (current.bound <= best)
            continue;

        int nextLevel = current.level + 1;

        if (nextLevel >= n)
            continue;
        Node take;
        take.level = nextLevel;
        take.value = current.value + items[nextLevel].value;
        take.weight = current.weight + items[nextLevel].weight;

        if (take.weight <= capacity)
        {
            if (take.value > best)
                best = take.value;

            take.bound = getBound(take, n, capacity, items);

            if (take.bound > best)
                q.push(take);
        }
        Node skip;
        skip.level = nextLevel;
        skip.weight = current.weight;
        skip.value = current.value;

        skip.bound = getBound(skip, n, capacity, items);
        if (skip.bound > best)
            q.push(skip);
    }
    return best;
}

int main()
{
    vector<Item> items = {
        {2, 40}, {3, 50}, {4, 65}, {5, 70}, {3, 30}};
    int capacity = 10;
    cout << "Maximum value = " << knapsack(capacity, items) << endl;
}