class Solution {
public:
    string decodeString(string &s, const int &n, int &i)
    {
        string ans = "";
        while(i < n && s[i] != ']')
        {
            if(s[i] < '0' || s[i] > '9')
                ans += s[i++];
            else
            {
                int cnt = 0;
                while(i < n && s[i] >= '0' && s[i] <= '9')
                    cnt = cnt * 10 + s[i++] - '0';
                
                i++;
                string t = decodeString(s, n, i);
                i++;
                
                while(cnt--)
                    ans.append(t);
            }
        }
        return ans;
    }
    string decodeString(string s) {
        int i = 0;
        return decodeString(s, s.length(), i);
    }
};
