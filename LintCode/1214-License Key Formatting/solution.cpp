class Solution {
public:
    /**
     * @param S: a string
     * @param K: a integer
     * @return: return a string
     */
    string licenseKeyFormatting(string &S, int K) {
        // write your code here
        int n = S.length();
        string ans = "";
        int idx = n - 1;
        int cnt = K;
        while (idx >= 0) {
            if (S[idx] == '-') {
                idx--;
                continue;
            }
            if (cnt == 0) {
                ans.push_back('-');
                cnt = K;
            }
            ans.push_back(S[idx] >= 'a' && S[idx] <= 'z' ? S[idx] - 'a' + 'A' : S[idx]);
            cnt--;
            idx--;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
