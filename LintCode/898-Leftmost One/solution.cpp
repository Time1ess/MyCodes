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
        for(int j = 0; j < m; j++)
            for(int i = 0; i < n; i++)
                if(arr[i][j] == 1)
                    return j;
    }
};
