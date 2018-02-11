class Solution {
public:
    bool isAnagram(string s, string t) {
        int cnts[26] = {0};
        for(auto c:s)
            cnts[c-'a']++;
        for(auto c:t)
            cnts[c-'a']--;
        for(int i = 0; i < 26; i++)
            if(cnts[i] != 0)
                return false;
        return true;
    }
};
