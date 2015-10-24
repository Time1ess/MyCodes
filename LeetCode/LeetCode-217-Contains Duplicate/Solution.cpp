#include <map>
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        map<int,int> maps;
        for(auto num:nums)
        {
            if(maps[num]!=0)
            return true;
            maps[num]++;
        }
        return false;
    }
};
