class Solution {
public:
    /**
     * @param points: a 2D array
     * @return: the number of boomerangs
     */
    int distance(const vector<int>& p, const vector<int>& q) {
        return (p[0] - q[0]) * (p[0] - q[0]) + (p[1] - q[1]) * (p[1] - q[1]);
    }
    int numberOfBoomerangs(vector<vector<int>> &points) {
        int n = points.size();
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            unordered_map<int, int> cnts;
            for(int j = 0; j < n; j++)
                cnts[distance(points[i], points[j])]++;
            for (auto x: cnts)
                cnt += x.second * (x.second - 1);
        }
        return cnt;
    }
};
