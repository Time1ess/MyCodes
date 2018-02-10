class Solution {
public:
    int romanToInt(string s) {
        int n = s.length();
        if(n == 0)
            return 0;
        unordered_map<char, int> mapping = {{'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}};
        int ans = mapping[s.back()];
        for(int i = n - 2; i >= 0; i--)
            if(mapping[s[i]] < mapping[s[i+1]])
                ans -= mapping[s[i]];
            else
                ans += mapping[s[i]];
        return ans;
    }
};
