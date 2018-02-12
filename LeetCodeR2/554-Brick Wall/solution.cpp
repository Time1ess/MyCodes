class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int, int> endings;
        int n = wall.size();
        int least = n;
        int wall_width;
        for(auto row: wall)
        {
            int sum = 0;
            for(auto x: row)
            {
                sum += x;
                endings[sum]++;
            }
            wall_width = sum;
        }
        for(auto end: endings)
            if((n - end.second) < least && end.first != wall_width)
                least = n - end.second;
        return least;
    }
};
