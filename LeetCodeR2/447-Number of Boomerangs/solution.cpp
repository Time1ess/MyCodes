class Solution {
public:
    int distance(pair<int, int> &a, pair<int, int> &b)
    {
        int x = a.first - b.first;
        int y = a.second - b.second;
        return x * x + y * y;
    }
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        unordered_map<int, int> dists;
        int n = points.size();
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(i == j)
                    continue;
                int dist = distance(points[i], points[j]);
                dists[dist]++;
            }
            for(auto cnt: dists)
                ans += cnt.second * (cnt.second - 1);
            dists.clear();
        }
        return ans;
    }
};
