class Solution {
public:
    /**
     * @param bottom: a string
     * @param allowed: a list of strings
     * @return: return a boolean
     */
    bool canBuild(unordered_map<string, vector<char>>& trans,
                  string current, int idx, int n, string next) {
        if(n == 1) {
            return true;
        } else if(idx == n - 1) {
            return canBuild(trans, next, 0, next.length(), "");
        }
        for(auto x : trans[current.substr(idx, 2)]) {
            next.push_back(x);
            if(canBuild(trans, current, idx+1, n, next)) {
                return true;
            }
            next.pop_back();
        }
        return false;
    }
    bool pyramidTransition(string &bottom, vector<string> &allowed) {
        // write your code here
        int n = bottom.length();
        if(n < 2) {
            return false;
        }
        unordered_map<string, vector<char>> transitions;
        for(auto x: allowed)
            transitions[x.substr(0, 2)].push_back(x[2]);
        return canBuild(transitions, bottom, 0, n, "");
    }
};
