class Solution {
public:
    int find_dist(vector<int>& nums, vector<int>& dists, vector<bool>& visited, int i) {
        if (visited[i] == true) {
            return 0;
        } else if (dists[i] != 0) {
            return dists[i];
        }
        visited[i] = true;
        dists[i] = 1 + find_dist(nums, dists, visited, nums[i]);
        visited[i] = false;
        return dists[i];
    }
    int arrayNesting(vector<int>& nums) {
        int n = nums.size();
        vector<int> dists(n, 0);
        vector<bool> visited(n, false);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, find_dist(nums, dists, visited, i));
        }
        return ans;
    }
};
