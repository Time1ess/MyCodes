#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;


const long long N = pow(2, 32);


vector<int> find_nums(vector<int> &nums)
{
    vector<int> ans;
    vector<int> bits(N / 32 * 2, 0);
    for(auto x: nums)
    {
        int base = x / 16;
        int offset = x % 16 * 2;
        if(((1 << offset) & bits[base]))  // 11, appears more than once
            continue;
        else if(((1 << (offset+1)) & bits[base])) // 01 -> 11, Second appears
            bits[base] |= 1 << offset;
        else  // 00 -> 01
            bits[base] |= 1 << (offset+1);
    }
    for(int i = 0; i < N / 32 * 2; i++)  // No need to iterate all nums in simulation
    {
        int base = i / 16;
        int offset = i % 16 * 2;
        if(!((1 << offset) & bits[base]) && ((1 << (offset+1)) & bits[base]))
            ans.push_back(i);
    }
    return ans;
}


int main()
{
    // 模拟海量数据
    vector<int> nums{0,1,2,3,4,5,6,7,8,9,2,5,6,7,8,9,3257863};
    vector<int> ans = find_nums(nums);
    for(auto x: ans)
        cout<<x<<endl;
    sort(nums.begin(), nums.end());
    for(auto x: nums)
        cout<<x<<" ";
    cout<<endl;
    return 0;
}
