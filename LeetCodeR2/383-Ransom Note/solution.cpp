class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int cnt[26] = {0};
        for(auto ch: magazine)
            cnt[ch-'a']++;
        for(auto ch: ransomNote)
            if(--cnt[ch-'a'] < 0)
                return false;
        return true;
    }
};
