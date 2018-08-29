class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        set<vector<int>> ans;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n - 3; i++) {
            for (int j = i + 1; j < n - 2; j++) {
                int k = j + 1, l = n - 1;
                while (k < l) {
                    int s = nums[i] + nums[j] + nums[k] + nums[l];
                    if (s == target) {
                        ans.insert({nums[i], nums[j], nums[k], nums[l]});
                        k++;
                        l--;
                    } else if (s > target) {
                        l--;
                    } else {
                        k++;
                    }
                }
            }
        }
        return vector<vector<int>>(ans.begin(), ans.end());
    }
};
