class Solution {
public:
    string makeLargestSpecial(string S) {
        int n = S.length();
        int cnt = 0, s = 0;
        vector<string> segs;
        for(int i = 0; i < n; i++)
        {
            if(S[i] == '1')
                cnt++;
            else
                cnt--;
            if(cnt == 0)
            {
                segs.push_back('1' + makeLargestSpecial(S.substr(s + 1, i - s - 1)) + '0');
                s = i + 1;
            }
        }
        sort(segs.begin(), segs.end(), greater<string>());
        string ans = "";
        for(int i = 0; i < segs.size(); i++)
            ans += segs[i];
        return ans;
    }
};
