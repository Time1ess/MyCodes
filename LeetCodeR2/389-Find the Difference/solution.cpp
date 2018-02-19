class Solution {
public:
    char findTheDifference(string s, string t) {
        char ans = 0;
        for(auto c: s)
            ans ^= c;
        for(auto c: t)
            ans ^= c;
        return ans;
    }
};
