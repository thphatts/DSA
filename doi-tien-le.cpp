/*
giả sử một người đến cửa hàng để đổi tiền:
người đó chuyển khoản cho nhân viên
nhân viên đưa lại tiền mặt cho người đó
cửa hàng có 3 loại tiền:
- 1k
- 2k
- 5k
hỏi: Với một số tiền nhất định, có bao nhiêu cách để đổi thành tiền lẻ?
vd: 8k = 5k + 2k + 1k = 5k + 1k + 1k + 1k = 2k + 2k + 2k + 2k = 2k + 2k + 2k + 1k + 1k = 2 + 2 + 1 + 1 + 1 + 1 = ...
*/

#include <iostream>

long long countWaysO1(long long n)
{
    if (n < 0)
        return 0;
    // Bảng cộng bù cho (n + 4)^2 tương ứng với n % 10
    static const int offset[10] = {4, 5, 4, 1, 16, 1, 16, 1, 4, 17};
    return ((n + 4) * (n + 4) + offset[n % 10]) / 20;
}

int main()
{
    long long n;
    std::cout << "Nhap so tien (k): ";
    if (std::cin >> n)
    {
        std::cout << "So cach doi (O(1)): " << countWaysO1(n) << "\n";
    }
    return 0;
}