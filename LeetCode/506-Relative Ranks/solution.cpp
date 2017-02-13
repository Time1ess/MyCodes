// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-13 14:56
// Last modified: 2017-02-13 14:56
// Filename: solution.cpp
// Description:
bool cmp(const pair<int, int>& a, const pair<int, int>& b)
{
    return a.first > b.first;
}
class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& nums) {
        vector<pair<int, int>> nis;
        vector<string> ranks;
        vector<string> results;
        results.resize(nums.size());
        for(int i=0; i < nums.size(); i++)
        {
            if(i == 0)
                ranks.push_back("Gold Medal");
            else if (i == 1)
                ranks.push_back("Silver Medal");
            else if (i == 2)
                ranks.push_back("Bronze Medal");
            else
                ranks.push_back(to_string(i+1));
        }
        for(int i=0; i < nums.size(); i++)
            nis.push_back(make_pair(nums[i], i));
        sort(nis.begin(), nis.end(), cmp);
        
        for(int i=0; i < nums.size(); i++)
        {
            results[nis[i].second] = ranks[i];
        }
        return results;
    }
};
