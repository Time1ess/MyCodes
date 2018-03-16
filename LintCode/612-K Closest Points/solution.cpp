/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * }; * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
 
struct DistPoint
{
    Point p;
    int dist;
    DistPoint(Point _p, double _d)
    {
        p = _p;
        dist = _d;
    }
    bool operator<(const DistPoint &other) const
    {
        if(dist < other.dist)
            return true;
        else if(dist == other.dist)
        {
            if(p.x < other.p.x)
                return true;
            else if(p.x == other.p.x && p.y < other.p.y)
                return true;
            else
                return false;
        }
        else
            return false;
    }
};

double calc_dist(const Point &a, const Point &b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

class Solution {
public:
    /**
     * @param points: a list of points
     * @param origin: a point
     * @param k: An integer
     * @return: the k closest points
     */
    vector<Point> kClosest(vector<Point> &points, Point &origin, int k) {
        // write your code here
        priority_queue<DistPoint> pq;
        for(auto p: points)
        {
            int dist = calc_dist(p, origin);
            DistPoint dp(p, dist);
            if(pq.size() < k)
                pq.push(dp);
            else if(pq.size() == k && dp < pq.top())
            {
                pq.pop();
                pq.push(dp);
            }
        }
        vector<Point> ans;
        while(!pq.empty())
        {
            ans.push_back(pq.top().p);
            pq.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
