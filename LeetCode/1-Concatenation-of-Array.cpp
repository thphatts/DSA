/*
You are given an integer array nums of length n. Create an array
ans of length 2n where ans[i] == nums[i] and ans[i + n] == nums[i]
for 0 <= i < n (0-indexed).
Specifically, ans is the concatenation of two nums arrays.
*/

#include <iostream>
using namespace std;
vector<int> getConcatenation(vector<int> &nums)
{
    vector<int> ans;
    for (int i = 0; i < 2; i++)
    {
        for (int num : nums)
        {
            ans.push_back(num);
        }
    }
    return ans;
};
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
    vector<int> ans = getConcatenation(nums);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans.at(i) << " ";
    }
}