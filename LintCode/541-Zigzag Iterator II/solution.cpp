class ZigzagIterator2 {
private:
    vector<vector<int>::iterator> iters, iters_ends;
    int idx, n;
public:
    /*
    * @param vecs: a list of 1d vectors
    */ZigzagIterator2(vector<vector<int>>& vecs) {
        // do intialization if necessary
        idx = -1;
        n = vecs.size();
        for(int i = 0; i < n; i++) {
            iters.push_back(vecs[i].begin());
            iters_ends.push_back(vecs[i].end());
        }
    }

    /*
     * @return: An integer
     */
    int next() {
        // write your code here
        int x = 0;
        int cnt = 0;
        while(true) {
            if(cnt == 2 * n) {
                return -1;  // No valid value
            }
            cnt++;
            idx = (idx + 1) % n;
            if(iters[idx] != iters_ends[idx]) {
                x = *(iters[idx]);
                ++(iters[idx]);
                break;
            }
        }
        return x;
    }

    /*
     * @return: True if has next
     */
    bool hasNext() {
        // write your code here
        for(int i = 0; i < n; i++) {
            if(iters[i] != iters_ends[i]) {
                return true;
            }
        }
        return false;
    }
};

/**
 * Your ZigzagIterator2 object will be instantiated and called as such:
 * ZigzagIterator2 solution(vecs);
 * while (solution.hasNext()) result.push_back(solution.next());
 * Ouptut result
 */
