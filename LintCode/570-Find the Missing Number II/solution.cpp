class Solution {
public:
    /*
     * @param n: An integer
     * @param str: a string with number from 1-n in random order and miss one number
     * @return: An integer
     */
    void dfs(bool *nums, int &ans, int n, string &str, int idx)
    {
        if(ans != 0)
            return;
        int len = str.length();
        if(idx == len)
        {
            int cnt = 0;
            for(int i = 1; i <= n; i++)
                if(nums[i] == false)
                    cnt++;
            if(cnt == 1)
                for(int i = 1; i <= n; i++)
                    if(nums[i] == false)
                        ans = i;
            return;
        }
        if(idx < len - 1)
        {
            int num = (str[idx] - '0') * 10 + str[idx+1] - '0';
            if(num <= n && nums[num] == false)  // Two digits
            {
                nums[num] = true;
                dfs(nums, ans, n, str, idx+2);
                nums[num] = false;
            }
        }
        int num = str[idx] - '0';  // Only one digit
        if(nums[num] == false)
        {
            nums[num] = true;
            dfs(nums, ans, n, str, idx+1);
            nums[num] = false;
        }
    }
    int findMissing2(int n, string &str) {
        // write your code here
        int ans = 0;
        bool nums[31] = {false};
        dfs(nums, ans, n, str, 0);
        return ans;
    }
};
