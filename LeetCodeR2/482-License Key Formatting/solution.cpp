class Solution {
public:
    string licenseKeyFormatting(string S, int K) {
        int n = S.length();
        string ans = "";
        int cnt = K;
        for(int j = n - 1; j >= 0; j--)
        {
            if(S[j] == '-')
                continue;
            if(cnt == 0)
            {
                ans.push_back('-');
                cnt = K - 1;
            }
            else
                cnt--;
            if(S[j] >= 'a' && S[j] <= 'z')
                ans.push_back(S[j] - 'a' + 'A');
            else
                ans.push_back(S[j]);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
