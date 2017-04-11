// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-11 10:17
// Last modified: 2017-04-11 10:17
// Filename: solution.cpp
// Description:
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        int height = wall.size();
        int least = height;
        unordered_map<int, int> edges;
        for(auto row: wall)
        {
            int width = 0;
            for(int i = 0; i < row.size()-1; i++)
            {
                width += row[i];
                edges[width]++;
                least = min(least, height - edges[width]);
            }
        }
        return least;
    }
};
