class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        int ans = N;
        vector<int> nums;
        while(N)
        {
            nums.push_back(N%10);
            N/=10;
        }
        reverse(nums.begin(), nums.end());
        int n = nums.size();
        int inverse_idx = -1;
        for(int j = 1; j < n; j++)
        {
            if(nums[j] < nums[j-1])
            {
                inverse_idx = j-1;
                while(inverse_idx >= 1 && nums[inverse_idx] == nums[inverse_idx-1])
                    inverse_idx--;
                break;
            }
        }
        if(inverse_idx == -1)
            return ans;
        ans = 0;
        for(int i = 0; i < inverse_idx; i++)
            ans = ans * 10 + nums[i];
        ans = ans * 10 + nums[inverse_idx] - 1;
        for(int i = inverse_idx + 1; i < n; i++)
            ans = ans * 10 + 9;
        return ans;
    }
};
