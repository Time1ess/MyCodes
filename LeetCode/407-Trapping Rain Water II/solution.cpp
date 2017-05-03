// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-03 09:07
// Last modified: 2017-05-03 09:07
// Filename: solution.cpp
// Description:
class Block
{
public:
    int row;
    int col;
    int height;
    Block()
    {
        row = -1;
        col = -1;
        height = 0;
    }
    Block(int r, int c, int h):row(r), col(c), height(h)
    {
    }
};
class Compare
{
public:
    bool operator()(Block a, Block b)
    {
        return a.height > b.height;
    }
};
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        if(m == 0)
            return 0;
        int n = heightMap[0].size();
        priority_queue<Block, vector<Block>, Compare> pq;
        bool visited[m][n] = {false};
        for(int i = 0; i < m; i++)
        {
            visited[i][0] = visited[i][n-1] = true;
            pq.push(Block(i, 0, heightMap[i][0]));
            pq.push(Block(i, n-1, heightMap[i][n-1]));
        }
        for(int j = 0; j < n; j++)
        {
            visited[0][j] = visited[m-1][j] = true;
            pq.push(Block(0, j, heightMap[0][j]));
            pq.push(Block(m-1, j, heightMap[m-1][j]));
        }
        int water = 0;
        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while(!pq.empty())
        {
            Block blk = pq.top();
            pq.pop();
            for(int i = 0; i < 4; i++)
            {
                int row = blk.row + dirs[i][0];
                int col = blk.col + dirs[i][1];
                if(row >= 0 && row < m && col >= 0 && col < n && !visited[row][col])
                {
                    visited[row][col] = true;
                    water += max(0, blk.height - heightMap[row][col]);
                    pq.push(Block(row, col, max(blk.height, heightMap[row][col])));
                }
            }
        }
        return water;
    }
};
