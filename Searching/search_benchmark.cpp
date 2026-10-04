#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <numeric>
#include <iomanip>
using namespace std;

int sequentialSearch(const vector<int> arr, int x)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == x)
        {
            return i;
        }
    }
    return -1;
}

int binarySearch(const vector<int> arr, int x)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x)
        {
            return mid;
        }
        if (arr[mid] < x)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

int jumpSearch(const vector<int> arr, int x)
{
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < x)
    {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
        {
            return -1;
        }
    }
    while (arr[prev] < x)
    {
        prev++;
        if (prev == min(step, n))
            return -1;
    }
    if (arr[prev] == x)
        return prev;

    return -1;
}

template <typename Func>
double benchmark(Func searchFunc, const std::vector<int> &arr, int target, int runs = 1000)
{
    // Warm-up cache
    searchFunc(arr, target);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < runs; ++i)
    {
        volatile int res = searchFunc(arr, target); // volatile tránh compiler tối ưu bỏ qua vòng lặp
        (void)res;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> elapsed = end - start;
    return elapsed.count() / runs; // Thời gian trung bình mỗi lần chạy (nanosecond)
}

int main()
{
    const int N = 1000000; // 1 triệu phần tử
    const int RUNS = 1000; // Lặp 1000 lần để đo trung bình chính xác

    // Khởi tạo mảng có thứ tự và phân bố đều: 0, 2, 4, 6, ..., 1999998
    std::cout << "Dang khoi tao mang " << N << " phan tu...\n";
    std::vector<int> arr(N);
    for (int i = 0; i < N; ++i)
    {
        arr[i] = i * 2;
    }

    // Giá trị cần tìm nằm ở khoảng 70% mảng (phần tử thứ 700000)
    int target = arr[700000];
    std::cout << "Gia tri can tim: " << target << " (tai index 700000)\n\n";

    // 1. Chạy kiểm tra tính đúng đắn trước
    std::cout << "[Kiem tra vi tri tra ve]\n";
    std::cout << "  Linear Search:        index = " << sequentialSearch(arr, target) << "\n";
    std::cout << "  Binary Search:        index = " << binarySearch(arr, target) << "\n";
    std::cout << "  Jump Search:          index = " << jumpSearch(arr, target) << "\n";

    // 2. Đo đạc thời gian
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "============================================================\n";
    std::cout << std::left << std::setw(25) << "Thuat toan"
              << std::setw(20) << "Thoi gian trung binh (ns)"
              << "Do phuc tap ly thuyet\n";
    std::cout << "============================================================\n";

    // Đo Linear Search (vì Linear Search chạy chậm trên 1M phần tử, giảm số lần lặp để tránh chờ lâu)
    double t_linear = benchmark(sequentialSearch, arr, target, 50);
    std::cout << std::left << std::setw(25) << "Linear Search"
              << std::setw(20) << t_linear
              << "O(n)\n";

    // Đo Jump Search
    double t_jump = benchmark(jumpSearch, arr, target, RUNS);
    std::cout << std::left << std::setw(25) << "Jump Search"
              << std::setw(20) << t_jump
              << "O(sqrt(n))\n";

    // Đo Binary Search
    double t_binary = benchmark(binarySearch, arr, target, RUNS);
    std::cout << std::left << std::setw(25) << "Binary Search"
              << std::setw(20) << t_binary
              << "O(log n)\n";

    // Đo Interpolation Search

    std::cout << "============================================================\n";
    std::cout << "* Chu thich: 1 microsecond (us) = 1,000 nanoseconds (ns)\n";

    return 0;
}