// C++17. Moi tep co main rieng, bien dich tung tep doc lap.
// Thay NOI DUNG giua begin your code va end your code.
// Cac gia tri tra ve tam thoi KHONG phai dap an.
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};
struct Stack
{
    Node *top;
};
struct Queue
{
    Node *front;
    Node *rear;
};

void initStack(Stack &s) { s.top = nullptr; }
void initQueue(Queue &q)
{
    q.front = nullptr;
    q.rear = nullptr;
}
bool stackEmpty(const Stack &s) { return s.top == nullptr; }
bool queueEmpty(const Queue &q) { return q.front == nullptr; }

Node *createNode(int x)
{
    Node *node = new Node;
    node->data = x;
    node->next = nullptr;
    return node;
}

void clearStack(Stack &s)
{
    while (s.top != nullptr)
    {
        Node *old = s.top;
        s.top = s.top->next;
        delete old;
    }
}

void clearQueue(Queue &q)
{
    while (q.front != nullptr)
    {
        Node *old = q.front;
        q.front = q.front->next;
        delete old;
    }
    q.rear = nullptr;
}

bool push(Stack &s, int x)
{
    Node *newNode = createNode(x);
    newNode->next = s.top;
    s.top = newNode;
    return true;
}

bool pop(Stack &s, int &out)
{
    if (s.top == nullptr)
    {
        return false;
    }
    Node *old = s.top;
    out = old->data;
    s.top = s.top->next;
    delete old;
    return true;
}

bool peek(const Stack &s, int &out)
{
    if (s.top == nullptr)
    {
        return false;
    }
    out = s.top->data;
    return true;
}

bool enqueue(Queue &q, int x)
{
    Node *newNode = createNode(x);
    if (q.front == nullptr)
    {
        q.front = newNode;
        q.rear = newNode;
    }
    else
    {
        q.rear->next = newNode;
        q.rear = newNode;
    }
    return true;
}

bool dequeue(Queue &q, int &out)
{
    if (q.front == nullptr)
    {
        return false;
    }
    Node *old = q.front;
    out = old->data;
    q.front = q.front->next;

    if (q.front == nullptr)
    {
        q.rear = nullptr;
    }

    delete old;
    return true;
}

bool frontValue(const Queue &q, int &out)
{
    if (q.front == nullptr)
    {
        return false;
    }
    out = q.front->data;
    return true;
}

void show(const Stack &s, const Queue &q)
{
    cout << "Stack (dinh -> day): ";
    if (s.top == nullptr)
        cout << "(rong)";
    for (Node *p = s.top; p != nullptr; p = p->next)
        cout << p->data << ' ';
    cout << '\n';
    cout << "Queue (dau -> cuoi): ";
    if (q.front == nullptr)
        cout << "(rong)";
    for (Node *p = q.front; p != nullptr; p = p->next)
        cout << p->data << ' ';
    cout << " | front = ";
    if (q.front != nullptr)
        cout << q.front->data;
    else
        cout << "nullptr";
    cout << ", rear = ";
    if (q.rear != nullptr)
        cout << q.rear->data;
    else
        cout << "nullptr";
    cout << '\n';
}

int main()
{
    Stack s;
    Queue q;
    initStack(s);
    initQueue(q);
    cout << "STACK VA QUEUE BANG CON TRO LIEN KET\n";
    while (true)
    {
        cout << "\n1 Push  2 Pop  3 Peek  4 Enqueue  5 Dequeue\n";
        cout << "6 Front  7 Xem trang thai  8 Tao rong  0 Thoat\nChon: ";
        int choice;
        if (!(cin >> choice) || choice == 0)
            break;
        int x = 0, out = 0;
        bool ok = false;
        if (choice == 1 || choice == 4)
        {
            cout << "Gia tri: ";
            if (!(cin >> x))
                break;
            ok = choice == 1 ? push(s, x) : enqueue(q, x);
            cout << (ok ? "Them thanh cong\n" : "Khong them duoc\n");
        }
        else if (choice == 2 || choice == 3 || choice == 5 || choice == 6)
        {
            if (choice == 2)
                ok = pop(s, out);
            if (choice == 3)
                ok = peek(s, out);
            if (choice == 5)
                ok = dequeue(q, out);
            if (choice == 6)
                ok = frontValue(q, out);
            if (ok)
                cout << "Gia tri = " << out << '\n';
            else
                cout << "Khong lay duoc phan tu\n";
        }
        else if (choice == 7)
            show(s, q);
        else if (choice == 8)
        {
            clearStack(s);
            clearQueue(q);
        }
        else
            cout << "Lua chon khong hop le\n";
    }
    clearStack(s);
    clearQueue(q);
    return 0;
}