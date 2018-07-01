class Queens {
public:
    bool checkValid(vector<pair<int, int>>& queens, int x, int y) {
        for(auto q: queens) {
            if(q.first == x || q.second == y || abs(q.first - x) == abs(q.second - y))
                return false;
        }
        return true;
    }
    int nQueens(vector<pair<int, int>>& queens, int x, int n) {
        if(x == n)
            return 1;
        int ways = 0;
        for(int y = 0; y < n; y++) {
            if(!checkValid(queens, x, y))
                continue;
            queens.push_back({x, y});
            ways += nQueens(queens, x+1, n);
            queens.pop_back();
        }
        return ways;
    }
    int nQueens(int n) {
        // write code here
        vector<pair<int, int>> queens;
        return nQueens(queens, 0, n);
    }
};
