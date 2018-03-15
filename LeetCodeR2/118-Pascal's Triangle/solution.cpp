class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        if(numRows == 0)
            return ans;
        ans.push_back({1});
        if(numRows == 1)
            return ans;
        for(int i = 2; i <= numRows; i++)
        {
            vector<int> row;
            row.push_back(1);
            for(int k = 1; k < i-1; k++)
                row.push_back(ans[i-2][k-1] + ans[i-2][k]);
            row.push_back(1);
            ans.push_back(row);
        }
        return ans;
    }
};
