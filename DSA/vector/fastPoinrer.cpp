#include"iostream"
using namespace std;
#include "vector"
template <typename T>
vector<int> twoSum(vector<T> nums, int target)
{
    vector<int> res(2);
    int left = 0, right = nums.size() - 1;
    while (left < right)
    {
        int sum = nums[left] + nums[right];
        if (sum == target)
        {
            // 题目要求的索引是从 1 开始的
            res[0] = left+1;
            res[1] = right+1;
            return  {left + 1, right + 1};
            //return res;
        }
        else if (sum < target)
        {
            left++; // 让 sum 大一点
        }
        else if (sum > target)
        {
            right--; // 让 sum 小一点
        }
    }
    return {-1,-1};
}

int main() {
    vector<int> test = {1, 2,  4, 5, 6, 7, 9,11,21};
    int tar = 33;
    vector<int> ret = twoSum(test,tar);
    for(auto i = 0; i < ret.size();i++)
    {
        cout<<ret[i]<<" "<<endl;
    }

    return 0;
}