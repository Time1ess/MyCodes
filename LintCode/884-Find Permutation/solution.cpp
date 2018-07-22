class Solution {
public:
    /**
     * @param s: a string
     * @return: return a list of integers
     */
    vector<int> findPermutation(string &s) {
        // write your code here
        int n = s.length();
        vector<int> ans;
        for(int i = 1; i <= n + 1; i++) {
            ans.push_back(i);
        }
        int i = 0;
        while(i < n) {
            int j = i;
            while(j < n && s[j] == 'D') {
                j++;
            }
            if(i == j) {  // No D
                i++;
                continue;
            }
            reverse(ans.begin() + i, ans.begin() + j + 1);
            i = j + 1;
        }
        return ans;
    }
};
