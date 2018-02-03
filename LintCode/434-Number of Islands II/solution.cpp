/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */


class Solution {
public:
    /*
     * @param n: An integer
     * @param m: An integer
     * @param operators: an array of point
     * @return: an integer array
     */
    int find(map<int, int> &parents, int x)
    {
        if(parents[x] != x)
            parents[x] = find(parents, parents[x]);
        return parents[x];
    }
    vector<int> numIslands2(int n, int m, vector<Point> &operators) {
        // write your code here
        vector<int> ans;
        int size = operators.size();
        if(size == 0)
            return ans;
        map<int, int> parents;
        for(int i = 0; i < size; i++)
        {
            int s = operators[i].x * m + operators[i].y;
            parents[s] = s;
        }
        vector<pair<int, int>> directions({{0, -1}, {0, 1}, {-1, 0}, {1, 0}});
        map<pair<int, int>, int> islands;
        int cnt = 0;
        for(int i = 0; i < size; i++)
        {
            Point p = operators[i];
            int s = operators[i].x * m + operators[i].y;
            if(islands[{p.x, p.y}] != 1) // skip processed
                cnt ++;
            islands[{p.x, p.y}] = 1;
            int pi = find(parents, s);
           
            for(auto dir: directions)
            {
                pair<int, int> t = make_pair(p.x+dir.first, p.y+dir.second);
                if(islands[t] == 0)
                    continue;
                int st = t.first * m + t.second;
                int pt = find(parents, st);
                if(pi == pt)
                    continue;
                parents[pt] = pi;
                cnt --;
            }
            ans.push_back(cnt);
        }
        return ans;
    }
};
