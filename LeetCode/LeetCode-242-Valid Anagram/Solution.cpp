#include <map>
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length()!=t.length())
        return false;
        map<char,int> count_s,count_t;
        for(int i=0;i<s.length();i++)
        {
            count_s[s[i]]++;
            count_t[t[i]]++;
        }
        for(int i=0;i<s.length();i++)
        {
            if(count_s[s[i]]!=count_t[s[i]])
            return false;
        }
        return true;
        
    }
};
