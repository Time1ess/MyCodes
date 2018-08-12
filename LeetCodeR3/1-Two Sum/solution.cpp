class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indices;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            int want = target - nums[i];
            if (indices.find(want) != indices.end()) {
                return {indices[want], i};
            }
            indices[nums[i]] = i;
        }
        return {-1, -1};
    }
};
