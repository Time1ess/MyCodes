class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> appears;
        for(auto x: nums)
        {
            if(appears.find(x) != appears.end())
                return true;
            appears.insert(x);
        }
        return false;
    }
};
