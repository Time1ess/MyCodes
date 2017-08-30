// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-30 10:59
// Last modified: 2017-08-30 10:59
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> ans(m, vector<int>(n, -1));
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
            {
                queue<pair<int, int>> smap;
                smap.push(make_pair(i, j));
                while(!smap.empty())
                {
                    pair<int, int> tmp = smap.front();
                    smap.pop();
                    if(matrix[tmp.first][tmp.second] == 0)
                    {
                        ans[i][j] = abs(i - tmp.first) + abs(j - tmp.second);
                        break;
                    }
                    if(tmp.first > 0)
                        smap.push(make_pair(tmp.first-1, tmp.second));
                    if(tmp.first < m - 1)
                        smap.push(make_pair(tmp.first+1, tmp.second));
                    if(tmp.second > 0)
                        smap.push(make_pair(tmp.first, tmp.second-1));
                    if(tmp.second < n - 1)
                        smap.push(make_pair(tmp.first, tmp.second+1));
                }
            }
        return ans;
    }
};
