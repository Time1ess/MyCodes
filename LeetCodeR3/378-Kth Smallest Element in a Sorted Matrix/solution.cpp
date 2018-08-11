struct cmp {
    bool operator()(const vector<int>& v1, const vector<int>& v2) {
        return v1[2] > v2[2];
    }
};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        if (m == 0) {
            return -1;
        }
        int n = matrix[0].size();
        if (n == 0) {
            return -1;
        }
        if (m * n < k) {
            return -1;
        }
        priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
        for(int j = 0; j < n; j++) {
            pq.push({0, j, matrix[0][j]});
        }
        int ans = -1;
        while(k--) {
            auto top = pq.top();
            pq.pop();
            ans = top[2];
            if(top[0] < m - 1) {
                pq.push({top[0] + 1, top[1], matrix[top[0]+1][top[1]]});
            }
        }
        return ans;
    }
};
