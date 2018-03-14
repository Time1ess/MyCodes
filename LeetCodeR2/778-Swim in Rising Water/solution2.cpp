struct GridPoint
{
    int cost, x, y;
    GridPoint(int _cost, int _x, int _y)
    {
        cost = _cost;
        x = _x;
        y = _y;
    }
    bool operator< (const GridPoint &other) const
    {
        return cost > other.cost;
    }
};
    
    
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        if(n == 0)
            return 0;
        priority_queue<GridPoint> pq;
        pq.push(GridPoint(grid[0][0], 0, 0));
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        visited[0][0] = true;
        int cost = 0;
        const static vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while(!pq.empty())
        {
            auto top = pq.top();
            pq.pop();
            cost = max(cost, top.cost);
            if(top.x == n - 1 && top.y == n - 1)
                return cost;
            
            for(auto d: directions)
            {
                int new_x = top.x + d.first;
                int new_y = top.y + d.second;
                if(new_x < 0 || new_x == n || new_y < 0 || new_y == n || visited[new_x][new_y])
                    continue;
                visited[new_x][new_y] = true;
                pq.push(GridPoint(grid[new_x][new_y], new_x, new_y));
            }
        }
        return 0;
    }
};
