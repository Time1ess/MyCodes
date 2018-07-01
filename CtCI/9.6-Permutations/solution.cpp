class Permutation {
public:
    static bool cmp(const string& a, const string& b) {
        return (a + b) >= (b + a);
    }
    void permutations(string& s, vector<string>& ans, int idx, int n) {
        if(idx == n) {
            ans.push_back(s);
            return;
        }
        for(int i = idx; i < n; i++) {
            swap(s[i], s[idx]);
            permutations(s, ans, idx + 1, n);
            swap(s[i], s[idx]);
        }
    }
    vector<string> getPermutation(string A) {
        // write code here
        vector<string> ans;
        permutations(A, ans, 0, A.length());
        sort(ans.begin(), ans.end(), cmp);
        return ans;
    }
};
