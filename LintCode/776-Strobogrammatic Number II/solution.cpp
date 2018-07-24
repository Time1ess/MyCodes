class Solution {
public:
    /**
     * @param n: the length of strobogrammatic number
     * @return: All strobogrammatic numbers
     */
    void backtrack(vector<string>& ans, stack<char> s, int n, const int total_n) {
        static unordered_map<char, char> maps = {
            {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}, {'0', '0'}};
        static vector<char> sems = {'0', '1', '8'};
        if(n == 0) {
            string res;
            if((total_n & 0x1) != 0) {
                res.push_back(s.top());
                s.pop();
            }
            while(!s.empty()) {
                res.push_back(s.top());
                s.pop();
            }
            reverse(res.begin(), res.end());
            for(int i = total_n / 2 - 1; i >= 0; i--) {
                res.push_back(maps[res[i]]);
            }
            if(total_n == 1 || res[0] != '0') {
                ans.push_back(res);
            }
            return;
        }
        if(n == 1) {
            for(auto x: sems) {
                s.push(x);
                backtrack(ans, s, n-1, total_n);
                s.pop();
            }
            return;
        }
        for(auto p: maps) {
            s.push(p.first);
            backtrack(ans, s, n-2, total_n);
            s.pop();
        }
    }
    vector<string> findStrobogrammatic(int n) {
        // write your code here
        if(n <= 0) {
            return {""};
        }
        vector<string> ans;
        stack<char> s;
        backtrack(ans, s, n, n);
        return ans;
    }
};
