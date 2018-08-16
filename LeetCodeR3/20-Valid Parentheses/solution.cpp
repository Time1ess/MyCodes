class Solution {
public:
    bool isValid(string s) {
        stack<char> ss;
        unordered_set<char> left = {'(', '[', '{'};
        unordered_map<char, char> to_left = {{')', '('}, {']', '['}, {'}', '{'}};
        for(auto c: s) {
            if (left.find(c) != left.end()) {
                ss.push(c);
            } else if (ss.empty() || to_left[c] != ss.top()) {
                return false;
            } else {
                ss.pop();
            }
        }
        return ss.size() == 0;
    }
};
