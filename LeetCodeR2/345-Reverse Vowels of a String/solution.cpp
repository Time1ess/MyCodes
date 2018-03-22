class Solution {
public:
    string reverseVowels(string s) {
        unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        int l = 0, r = s.length() - 1;
        while(l < r)
        {
            while(l < r && vowels.find(s[l]) == vowels.end())
                l++;
            if(l >= r)
                break;
            while(l < r && vowels.find(s[r]) == vowels.end())
                r--;
            if(l >= r)
                break;
            swap(s[l++], s[r--]);
        }
        return s;
    }
};
