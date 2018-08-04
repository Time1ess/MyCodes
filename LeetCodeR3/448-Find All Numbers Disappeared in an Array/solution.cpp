class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> ans;
        for(auto x: nums) {
            int v = abs(x);
            if(nums[v-1] > 0) {
                nums[v-1] = -(nums[v-1]);
            }
        }
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            if(nums[i] > 0) {
                ans.push_back(i+1);
            }
        }
        return ans;
    }
};
