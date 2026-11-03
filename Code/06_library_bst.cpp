// C++17. Moi tep co main rieng, bien dich tung tep doc lap.
// Thay NOI DUNG giua begin your code va end your code.
// Cac gia tri tra ve tam thoi KHONG phai dap an.
#include <iostream>
using namespace std;

struct Book
{
    int id;
    char title[81];
    char author[61];
    int year;
    int quantity;
};
struct Node
{
    Book book;
    Node *left;
    Node *right;
};

bool validQuantity(int quantity) { return quantity >= 0 && quantity <= 10000; }
bool validBook(const Book &b)
{
    return b.id >= 1 && b.id <= 9999 && b.title[0] != '\0' && b.author[0] != '\0' && b.year >= 1450 && b.year <= 2100 && validQuantity(b.quantity);
}
Node *createNode(const Book &b)
{
    Node *node = new Node;
    node->book = b;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}
void clearTree(Node *&root)
{
    if (root == nullptr)
        return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
    root = nullptr;
}
void printBook(const Book &b)
{
    cout << b.id << " | " << b.title << " | " << b.author;
    cout << " | " << b.year << " | " << b.quantity << '\n';
}
void createSample(Node *&root)
{
    clearTree(root);
    Book data[7] = {
        {50, "Cau truc du lieu", "Nguyen An", 2022, 3},
        {30, "Lap trinh C++", "Le Binh", 2021, 5},
        {70, "Co so du lieu", "Tran Chi", 2020, 2},
        {20, "Mang may tinh", "Pham Dung", 2023, 4},
        {40, "He dieu hanh", "Vo Hanh", 2019, 1},
        {60, "Tri tue nhan tao", "Do Khoa", 2024, 6},
        {80, "Xu ly tin hieu", "Bui Lam", 2022, 2}};
    root = createNode(data[0]);
    root->left = createNode(data[1]);
    root->right = createNode(data[2]);
    root->left->left = createNode(data[3]);
    root->left->right = createNode(data[4]);
    root->right->left = createNode(data[5]);
    root->right->right = createNode(data[6]);
}

Node *searchBook(Node *root, int id)
{
    if (root == nullptr || root->book.id == id)
    {
        return root;
    }
    if (id < root->book.id)
    {
        return searchBook(root->left, id);
    }
    return searchBook(root->right, id);
}

bool insertBook(Node *&root, const Book &b)
{
    if (!validBook(b))
        return false;

    if (root == nullptr)
    {
        root = createNode(b);
        return true;
    }

    if (b.id == root->book.id)
    {
        return false;
    }
    else if (b.id < root->book.id)
    {
        return insertBook(root->left, b);
    }
    else
    {
        return insertBook(root->right, b);
    }
}

Node *minNode(Node *root)
{
    if (root == nullptr)
        return nullptr;
    Node *curr = root;
    while (curr->left != nullptr)
    {
        curr = curr->left;
    }
    return curr;
}

bool removeBook(Node *&root, int id)
{
    if (root == nullptr)
        return false;

    if (id < root->book.id)
    {
        return removeBook(root->left, id);
    }
    else if (id > root->book.id)
    {
        return removeBook(root->right, id);
    }
    else
    {
        if (root->left == nullptr)
        {
            Node *temp = root;
            root = root->right;
            delete temp;
            return true;
        }
        else if (root->right == nullptr)
        {
            Node *temp = root;
            root = root->left;
            delete temp;
            return true;
        }
        else
        {
            Node *successor = minNode(root->right);
            root->book = successor->book;
            return removeBook(root->right, successor->book.id);
        }
    }
}

bool updateQuantity(Node *root, int id, int quantity)
{
    if (!validQuantity(quantity))
        return false;
    Node *target = searchBook(root, id);
    if (target == nullptr)
        return false;
    target->book.quantity = quantity;
    return true;
}

void inorder(Node *root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    printBook(root->book);
    inorder(root->right);
}

int countTitles(Node *root)
{
    if (root == nullptr)
        return 0;
    return 1 + countTitles(root->left) + countTitles(root->right);
}

int totalCopies(Node *root)
{
    if (root == nullptr)
        return 0;
    return root->book.quantity + totalCopies(root->left) + totalCopies(root->right);
}

bool readBook(Book &b)
{
    cout << "Ma sach: ";
    if (!(cin >> b.id))
        return false;
    cin.ignore(10000, '\n');
    cout << "Ten sach (toi da 80 ky tu): ";
    cin.getline(b.title, 81);
    if (!cin)
        return false;
    cout << "Tac gia (toi da 60 ky tu): ";
    cin.getline(b.author, 61);
    if (!cin)
        return false;
    cout << "Nam xuat ban: ";
    if (!(cin >> b.year))
        return false;
    cout << "So ban sach: ";
    return static_cast<bool>(cin >> b.quantity);
}

int main()
{
    Node *root = nullptr;
    createSample(root);
    cout << "THU VIEN BST - du lieu mau 7 dau sach, 23 ban sach\n";
    while (true)
    {
        cout << "\n1 Inorder  2 Them  3 Tim  4 Cap nhat so ban\n";
        cout << "5 Xoa  6 Thong ke  7 Tao rong  8 Nap lai mau  0 Thoat\nChon: ";
        int choice;
        if (!(cin >> choice) || choice == 0)
            break;
        if (choice == 1)
        {
            cout << "Ma | Ten | Tac gia | Nam | So ban\n";
            if (root == nullptr)
                cout << "Cay rong\n";
            inorder(root);
        }
        else if (choice == 2)
        {
            Book b;
            if (!readBook(b))
                break;
            cout << (insertBook(root, b) ? "Them thanh cong\n" : "Khong them duoc\n");
        }
        else if (choice == 3)
        {
            int id;
            cout << "Ma can tim: ";
            if (!(cin >> id))
                break;
            Node *p = searchBook(root, id);
            if (p != nullptr)
                printBook(p->book);
            else
                cout << "Khong tim thay\n";
        }
        else if (choice == 4)
        {
            int id, quantity;
            cout << "Ma, so ban moi: ";
            if (!(cin >> id >> quantity))
                break;
            cout << (updateQuantity(root, id, quantity) ? "Cap nhat thanh cong\n" : "Khong cap nhat duoc\n");
        }
        else if (choice == 5)
        {
            int id;
            cout << "Ma can xoa: ";
            if (!(cin >> id))
                break;
            cout << (removeBook(root, id) ? "Xoa thanh cong\n" : "Khong xoa duoc\n");
        }
        else if (choice == 6)
        {
            cout << "So dau sach = " << countTitles(root);
            cout << "; tong so ban = " << totalCopies(root) << '\n';
        }
        else if (choice == 7)
            clearTree(root);
        else if (choice == 8)
            createSample(root);
        else
            cout << "Lua chon khong hop le\n";
    }
    clearTree(root);
    return 0;
}