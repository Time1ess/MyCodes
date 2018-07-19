class Solution {
public:
    /**
     * @param S: a string
     * @param words: a list of strings
     * @return: return a integer
     */
    vector<pair<char, int>> compile(const string& S) {
        int n = S.length();
        vector<pair<char, int>> ans;
        int last_idx = 0;
        for(int i = 1; i < n; i++) {
            if(S[i] == S[last_idx]) {
                continue;
            }
            ans.push_back({S[last_idx], i-last_idx});
            last_idx = i;
        }
        ans.push_back({S[last_idx], n-last_idx});
        return ans;
    }
    bool equal(const vector<pair<char, int>> src, const vector<pair<char, int>>& tar) {
        int n = src.size();
        int m = tar.size();
        if(n != m) {
            return false;
        }
        for(int i = 0; i < n; i++) {
            if(src[i].first != tar[i].first) {
                return false;
            }
            if(src[i].second == tar[i].second) {
                continue;
            } else if(src[i].second > tar[i].second) {
                return false;
            }
            if(tar[i].second < 3) {
                return false;
            }
        }
        return true;
    }
    int expressiveWords(string &S, vector<string> &words) {
        // write your code here
        const vector<pair<char, int>> compiled_s = compile(S);
        int cnt = 0;
        for(auto s: words) {
            if(equal(compile(s), compiled_s)) {
                cnt++;
            }
        }
        return cnt;
    }
};
