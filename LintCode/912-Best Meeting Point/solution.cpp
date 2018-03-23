class Solution {
public:
    /**
     * @param grid: a 2D grid
     * @return: the minimize travel distance
     */
    int distance(pair<int, int> &p1, pair<int, int> &p2)
    {
        return abs(p1.first-p2.first) + abs(p1.second-p2.second);
    }
    int minTotalDistance(vector<vector<int>> &grid) {
        // Write your code here
        vector<int> xs, ys;
        vector<pair<int, int>> points;
        int n = grid.size();
        if(n == 0)
            return 0;
        int m = grid[0].size();
        if(m == 0)
            return 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(grid[i][j] == 1)
                {
                    xs.push_back(i);
                    ys.push_back(j);
                    points.push_back({i, j});
                }
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        int k = xs.size();
        int x = round(1.0 * (xs[k/2] + xs[(k-1)/2])/2);
        int y = round(1.0 * (ys[k/2] + ys[(k-1)/2])/2);
        pair<int, int> c = {x, y};
        int dist = 0;
        for(auto p: points)
            dist += distance(p, c);
        return dist;
    }
};
