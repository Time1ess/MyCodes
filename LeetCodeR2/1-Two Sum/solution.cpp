class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> showups;
        for(int i = 0; i < nums.size(); i++)
            if(showups.find(target - nums[i]) != showups.end())
                return {i, showups[target-nums[i]]};
            else
                showups[nums[i]] = i;
    }
};
