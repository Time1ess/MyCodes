bool cmp(const vector<int>& p1, const vector<int>& p2) {
    return p1[0] < p2[0];
}
bool cmp2(const vector<int>& p1, const vector<int>& p2) {
    return p1[1] < p2[1];
}
bool cmp3(const vector<int>& p1, const vector<int>& p2) {
    return p1[1] > p2[1];
}
class Solution {
public:
    /**
     * @param points: n points on a 2D plane
     * @return: if there is such a line parallel to y-axis that reflect the given points
     */
    bool same(float x, float y) {
        return abs(x-y) < 1e-6;
    }
    bool isReflected(vector<vector<int>> &points) {
        int n = points.size();
        if(n <= 1) {
            return true;
        }
        sort(points.begin(), points.end(), cmp);  // Sort x-axis asc
        int i = 0;
        while(i < n / 2) {  // For same x in the first half, sort y asc
            int j = i + 1;
            while(j < n / 2 && points[i][0] == points[j][0]) {
                j++;
            }
            sort(points.begin() + i, points.begin() + j, cmp2);
            i = j;
        }
        i = (n+1) / 2;
        while(i < n) {  // For same x in the second half, sort y desc
            int j = i + 1;
            while(j < n && points[i][0] == points[j][0]) {
                j++;
            }
            sort(points.begin() + i, points.begin() + j, cmp3);
            i = j;
        }
        int j = n - 1;
        i = 0;
        bool mid_set = false;
        float mid;
        while(points[i][0] < points[j][0]) {
            if(points[i][1] != points[j][1]) {
                return false;
            }
            float m = 1.0 * (points[i][0] + points[j][0]) / 2;
            if(!mid_set) {
                mid_set = true;
                mid = m;
            } else if(!same(mid, m)) {
                return false;
            }
            i++, j--;
        }
        if(!mid_set || i > j) {  // All with same x, or all points are calculated
            return true;
        }
        // Still some points not calculated, they have same x
        return same(points[i][0], mid);
    }
};
