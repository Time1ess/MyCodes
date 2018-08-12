class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int cur_height = 0;
        int l = 0, r = n - 1;
        int ans = 0;
        while (l <= r) {
            if (height[l] < height[r]) {
                cur_height = max(cur_height, height[l]);
                ans += max(0, cur_height - height[l]);
                l++;
            } else {
                cur_height = max(cur_height, height[r]);
                ans += max(0, cur_height - height[r]);
                r--;
            }
        }
        return ans;
    }
};
