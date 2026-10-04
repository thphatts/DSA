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

// sắp xếp theo thứ tự giảm dần các giá trị của vật phẩm theo cthuc (v/w) giá trị của sản phẩm
// đáng giá nhất trên đơn vị cân nặng
bool compare(Item a, Item b)
{
    return (double)a.value / a.weight > (double)b.value / b.weight;
}

// hàm tính cận trên: từ node hiện tại duyệt tham lam và nhét đầy balo thì thu được tối đa bao nhiêu giá trị
double getBound(Node node, int n, int capacity, const vector<Item> &items)
{

    // nếu túi đầy không thể nhét thêm thì bound chính bằng giá trị hiện có
    if (node.weight >= capacity)
        return node.value;

    double bound = node.value;
    int totalWeight = node.weight;
    int i = node.level + 1;

    // duyệt từ vật phẩm kế tiếp nếu còn đủ chỗ thì cộng dồn giá trị và khối lượng vào
    while (i < n && totalWeight + items[i].weight <= capacity)
    {
        totalWeight += items[i].weight;
        bound += items[i].value;

        // tăng i để duyệt vật phẩm tiếp theo thỏa yêu cầu
        i++;
    }

    // Fractional: lấy một phần vật phẩm và tính upper bound
    // nếu còn chỗ trống mà không đủ chứ trọn vẹn khối lượng của vật phẩm thứ i
    if (i < n)
    {
        // vì là bài toán 0/1 nên khi nhét một phần giá trị vật phẩm thì bound >= kết quả tối ưu thật tế
        int remaining = capacity - totalWeight;
        bound += (double)remaining * items[i].value / items[i].weight;
    }
    // Upper bound
    return bound;
}

int knapsack(int capacity, vector<Item> items)
{
    int n = items.size();

    sort(items.begin(), items.end(), compare);

    queue<Node> q;
    Node root;
    root.level = -1; // chưa xét món nào
    root.weight = 0;
    root.value = 0;

    root.bound = getBound(root, n, capacity, items);
    q.push(root); // đưa root(-1) và duyệt theo cơ chế FIFO
    int best = 0; // lưu giá trị lớn nhất tìm thấy tính đến thời điểm hiện tại
    while (!q.empty())
    {
        Node current = q.front(); // lấy node ở đầu hàng đợi
        q.pop();

        // nếu bound của node hiện tại nhỏ hơn best thì cắt bỏ
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
                best = take.value; // cập nhật giá trị best của node hiện tại

            take.bound = getBound(take, n, capacity, items); // tính bound của nhánh nếu lấy node đó

            if (take.bound > best)
                q.push(take); // nếu nhánh có triển vọng thì duyệt tiếp
        }
        Node skip;
        skip.level = nextLevel;
        // nếu skip thì giá trị cũ được giữ nguyên
        skip.weight = current.weight;
        skip.value = current.value;

        skip.bound = getBound(skip, n, capacity, items); // tính bound của nhánh
        if (skip.bound > best)
            q.push(skip); // nếu nhánh có triển vọng thì duyệt tiếp
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