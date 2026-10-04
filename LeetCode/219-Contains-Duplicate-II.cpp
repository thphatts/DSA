#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

bool containsNearbyDuplicate(vector<int> &nums, int k)
{
  // unordered_map lưu [giá trị : chỉ số xuất hiện gần nhất]
  unordered_map<int, int> seen;

  for (int i = 0; i < nums.size(); i++)
  {
    // Hàm count() trả về 1 nếu phần tử tồn tại trong map, 0 nếu không
    if (seen.count(nums[i]) && i - seen[nums[i]] <= k)
    {
      return true;
    }

    // Cập nhật lại chỉ số mới nhất cho phần tử nums[i]
    seen[nums[i]] = i;
  }

  return false;
}
int main()
{
  vector<int> nums;
  int n;
  cout << "Nhap so luong phan tu: ";
  cin >> n;
  cout << "Nhap cac phan tu: ";
  for (int i = 0; i < n; i++)
  {
    int temp;
    cin >> temp;
    nums.push_back(temp);
  }
  int k;
  cout << "Nhap k: ";
  cin >> k;
  if (containsNearbyDuplicate(nums, k))
    cout << "True\n";
  else
    cout << "False\n";
  return 0;
}