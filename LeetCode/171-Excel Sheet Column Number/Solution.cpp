class Solution {
public:
    int titleToNumber(string s) {
        int weight=1;
        int ans=0;
        for(int i=s.length()-1;i>=0;i--)
        {
            int cur=s[i]-'A'+1;
            ans+=cur*weight;
            weight*=26;
        }
        return ans;
    }
};
