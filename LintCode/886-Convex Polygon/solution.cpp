class Solution {
public:
    /**
     * @param point: a list of two-tuples
     * @return: a boolean, denote whether the polygon is convex
     */
    int crossProduct(const vector<int>& p1,
                      const vector<int>& p2,
                      const vector<int>& p3) {
        int x1 = p1[0] - p2[0], x2 = p3[0] - p2[0];
        int y1 = p1[1] - p2[1], y2 = p3[1] - p2[1];
        return (x1 * y2 - x2 * y1);
    }
    bool isConvex(vector<vector<int>> &point) {
        // write your code here
        int n = point.size();
        int normDirection = 0;
        for(int i = 0; i < n; i++) {
            int t = crossProduct(point[i%n], point[(i+1)%n], point[(i+2)%n]);
            if(t == 0)
                continue;
            if(t * normDirection < 0)
                return false;
            normDirection = t;
        }
        return true;
    }
};
