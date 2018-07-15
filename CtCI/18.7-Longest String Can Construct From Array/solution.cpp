#include <unordered_map>

bool cmp(const string& a, const string& b) {
    return a.length() > b.length();
}
class LongestString {
public:
    bool can_construct(unordered_map<string, bool>& words, const string s, bool original) {
        if(words.find(s) != words.end() && !original) {
            return words[s];
        }
        int n = s.length();
        for(int i = 1; i < n; i++) {
            const string left = s.substr(0, i);
            const string right = s.substr(i);
            if(words.find(left) != words.end() && words[left] == true
               && can_construct(words, right, false)) {
                return true;
            }
        }
        words[s] = false;
        return false;
    }
    int getLongest(vector<string> str, int n) {
        // write code here
        unordered_map<string, bool> words;
        for(auto x: str) {
            words[x] = true;
        }
        sort(str.begin(), str.end(), cmp);
        for(auto s: str) {
            if(can_construct(words, s, true)) {
                return s.length();
            }
        }
        return -1;
    }
};
