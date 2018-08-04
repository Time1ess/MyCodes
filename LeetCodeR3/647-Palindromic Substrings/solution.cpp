class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length();
        int ans = 0;
        for(int i = 0; i < n; i++) {
            ans++;
            int j = i - 1, k = i + 1;
            while(j >= 0 && k < n && s[j] == s[k]) {
                ans++;
                j--;
                k++;
            }
            j = i, k = i + 1;
            while(j >= 0 && k < n && s[j] == s[k]) {
                ans++;
                j--;
                k++;
            }
        }
        return ans;
    }
};
