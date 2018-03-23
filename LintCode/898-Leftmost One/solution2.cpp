class Solution {
public:
    /**
     * @param arr: The 2-dimension array
     * @return: Return the column the leftmost one is located
     */
    int getColumn(vector<vector<int>> &arr) {
        // Write your code here
        int n = arr.size();
        int m = arr[0].size();
        int ans = INT_MAX;
        for(int i = 0; i < n; i++)
        {
            int l = 0, r = m - 1;
            while(l < r)
            {
                int k = l + (r-l) / 2;
                if(arr[i][k] == 1)
                    r = k;
                else
                    l = k+1;
            }
            ans = min(l, ans);
        }
        return ans;
    }
};
