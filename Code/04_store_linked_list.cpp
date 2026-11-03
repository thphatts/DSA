// C++17. Moi tep co main rieng, bien dich tung tep doc lap.
// Thay NOI DUNG giua begin your code va end your code.
// Cac gia tri tra ve tam thoi KHONG phai dap an.
#include <iostream>
using namespace std;

struct Product
{
    int id;
    char name[61];
    long long price;
    int stock;
};
struct Node
{
    Product item;
    Node *next;
};
bool validPriceStock(long long price, int stock)
{
    return price >= 0 && price <= 100000000LL && stock >= 0 && stock <= 100000;
}
bool validProduct(const Product &p)
{
    return p.id >= 1 && p.id <= 9999 && p.name[0] != '\0' && validPriceStock(p.price, p.stock);
}
Node *createNode(const Product &p)
{
    Node *node = new Node;
    node->item = p;
    node->next = nullptr;
    return node;
}
void clearList(Node *&head)
{
    while (head != nullptr)
    {
        Node *old = head;
        head = head->next;
        delete old;
    }
}
void printProduct(const Product &p)
{
    cout << p.id << " | " << p.name << " | " << p.price << " | " << p.stock << '\n';
}
void display(Node *head)
{
    cout << "Ma | Ten | Don gia VND | Ton kho\n";
    if (head == nullptr)
        cout << "Danh sach rong\n";
    for (Node *p = head; p != nullptr; p = p->next)
        printProduct(p->item);
}
void createSample(Node *&head)
{
    clearList(head);
    Product data[3] = {{20, "But bi", 5000, 100},
                       {10, "Vo A5", 12000, 50},
                       {30, "Thuoc ke", 8000, 30}};
    Node *a = createNode(data[0]);
    Node *b = createNode(data[1]);
    Node *c = createNode(data[2]);
    a->next = b;
    b->next = c;
    head = a;
}

Node *findProduct(Node *head, int id)
{
    Node *currentNode = head;
    while (currentNode != nullptr)
    {
        if (currentNode->item.id == id)
        {
            return currentNode;
        }
        currentNode = currentNode->next;
    }
    return nullptr;
}

bool addHead(Node *&head, const Product &p)
{
    if (!(validProduct(p)))
    {
        return false;
    }
    if (findProduct(head, p.id) != nullptr)
    {
        return false;
    }

    Node *newNode = createNode(p);
    newNode->next = head;
    head = newNode;
    return true;
}

bool addTail(Node *&head, const Product &p)
{
    if (!(validProduct(p)))
        return false;
    if (findProduct(head, p.id) != nullptr)
        return false;

    Node *newNode = createNode(p);
    if (head == nullptr)
    {
        head = newNode;
        return true;
    }
    Node *currentNode = head;
    while (currentNode->next != nullptr)
    {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
    return true;
}

bool removeProduct(Node *&head, int id)
{
    if (head == nullptr)
        return false;
    if (head->item.id == id)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    Node *curr = head;
    while (curr->next != nullptr && curr->next->item.id != id)
    {
        curr = curr->next;
    }
    if (curr->next != nullptr)
    {
        Node *temp = curr->next;
        curr->next = temp->next;
        delete temp;
        return true;
    }
    return false;
}

bool updateProduct(Node *head, int id, long long price, int stock)
{
    if (!(validPriceStock(price, stock)))
        return false;

    Node *p = findProduct(head, id);
    if (p == nullptr)
        return false;
    p->item.price = price;
    p->item.stock = stock;
    return true;
}

long long inventoryValue(Node *head)
{
    long long total = 0;
    Node *curr = head;
    while (curr != nullptr)
    {
        total += curr->item.price * curr->item.stock;
        curr = curr->next;
    }
    return total;
}

bool readProduct(Product &p)
{
    cout << "Ma san pham: ";
    if (!(cin >> p.id))
        return false;
    cin.ignore(10000, '\n');
    cout << "Ten san pham (toi da 60 ky tu): ";
    cin.getline(p.name, 61);
    if (!cin)
        return false;
    cout << "Don gia: ";
    if (!(cin >> p.price))
        return false;
    cout << "Ton kho: ";
    return static_cast<bool>(cin >> p.stock);
}
int main()
{
    Node *head = nullptr;
    createSample(head);
    cout << "QUAN LY CUA HANG - du lieu mau: 20, 10, 30\n";
    while (true)
    {
        cout << "\n1 Xuat  2 Them dau  3 Them cuoi  4 Tim\n";
        cout << "5 Cap nhat gia va ton  6 Xoa  7 Tong gia tri\n";
        cout << "8 Tao rong  9 Nap lai mau  0 Thoat\nChon: ";
        int choice;
        if (!(cin >> choice) || choice == 0)
            break;
        if (choice == 1)
            display(head);
        else if (choice == 2 || choice == 3)
        {
            Product p;
            if (!readProduct(p))
                break;
            bool ok = choice == 2 ? addHead(head, p) : addTail(head, p);
            cout << (ok ? "Them thanh cong\n" : "Khong them duoc\n");
        }
        else if (choice == 4)
        {
            int id;
            cout << "Ma can tim: ";
            if (!(cin >> id))
                break;
            Node *p = findProduct(head, id);
            if (p != nullptr)
                printProduct(p->item);
            else
                cout << "Khong tim thay\n";
        }
        else if (choice == 5)
        {
            int id, stock;
            long long price;
            cout << "Ma, gia moi, ton moi: ";
            if (!(cin >> id >> price >> stock))
                break;
            cout << (updateProduct(head, id, price, stock) ? "Cap nhat thanh cong\n" : "Khong cap nhat duoc\n");
        }
        else if (choice == 6)
        {
            int id;
            cout << "Ma can xoa: ";
            if (!(cin >> id))
                break;
            cout << (removeProduct(head, id) ? "Xoa thanh cong\n" : "Khong xoa duoc\n");
        }
        else if (choice == 7)
            cout << "Tong gia tri = " << inventoryValue(head) << " VND\n";
        else if (choice == 8)
            clearList(head);
        else if (choice == 9)
            createSample(head);
        else
            cout << "Lua chon khong hop le\n";
    }
    clearList(head);
    return 0;
}

/*
- hàm đổi node đầu phải nhận (Node*& head)để cho phép thao tác và thay đổi trực tiếp đến con trỏ nguyên bản
- cần kiểm tra mã trùng trước khi cấp phát node mới để tránh tốn bộ nhớ và tránh cấp phát và giải phóng bộ nhớ cho biến không hợp lệ
*/