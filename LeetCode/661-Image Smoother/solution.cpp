// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-22 15:31
// Last modified: 2017-08-22 15:31
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        vector<vector<int>> ans(M.size(), vector<int>(M[0].size(), 0));
        int tot = 0, cnt = 0;
        for(int i = 0; i < M.size(); i++)
        {
            for(int j = 0; j < M[i].size(); j++)
            {
                tot = M[i][j], cnt = 1;
                if(j > 0)
                    tot += M[i][j-1], cnt++;
                if(j < M[i].size()-1)
                    tot += M[i][j+1], cnt++;
                if(i > 0)
                {
                    tot += M[i-1][j], cnt++;
                    if(j > 0)
                        tot += M[i-1][j-1], cnt++;
                    if(j < M[i].size()-1)
                        tot += M[i-1][j+1], cnt++;
                }
                if(i+1 < M.size())
                {
                    tot += M[i+1][j], cnt++;
                    if(j > 0)
                        tot += M[i+1][j-1], cnt++;
                    if(j < M[i].size()-1)
                        tot += M[i+1][j+1], cnt++;
                }
                ans[i][j] = int(tot / cnt);
            }
        }
        return ans;
    }
};
