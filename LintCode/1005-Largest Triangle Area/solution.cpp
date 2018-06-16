class Solution {
public:
    /**
     * @param points: List[List[int]]
     * @return: return a double
     */
    double area(const vector<int>& p1, const vector<int>& p2, const vector<int>& p3) {
        return 0.5 * (p1[0] * (p2[1] - p3[1])
                      + p2[0] * (p3[1] - p1[1])
                      + p3[0] * (p1[1] - p2[1]));
    }
    double largestTriangleArea(vector<vector<int>> &points) {
        // write your code here
        double ans = 0;
        for(auto p1 : points)
            for(auto p2 : points)
                for(auto p3: points)
                    ans = max(ans, area(p1, p2, p3));
        return ans;
    }
};
