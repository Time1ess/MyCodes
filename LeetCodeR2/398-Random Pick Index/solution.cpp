class Solution {
private:
    vector<int> nums;
    int n;
public:
    Solution(vector<int> nums) {
        this->nums = nums;
        this->n = nums.size();
    }
    
    int pick(int target) {
        int idx = -1, cnt = 1, i;
        for(i = 0; i < n; i ++)
            if(nums[i] == target)
            {
                idx = i;
                break;
            }
        for(int i = idx + 1; i < n; i++)
        {
            if(nums[i] == target)
            {
                cnt++;
                if(rand() % cnt == (cnt - 1))
                    idx = i;
            }
        }
        return idx;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
 */
