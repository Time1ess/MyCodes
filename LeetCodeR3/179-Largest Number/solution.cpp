bool cmp(const string& a, const string& b) {
    return (a + b) > (b + a);
}

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> cands;
        for (auto x: nums) {
            cands.push_back(to_string(x));
        }
        sort(cands.begin(), cands.end(), cmp);
        string ans = "";
        for (auto s: cands) {
            ans.append(s);
        }
        int leading_zero_idx = 0;
        while (leading_zero_idx < ans.length() - 1 && ans[leading_zero_idx] == '0') {
            leading_zero_idx++;
        }
        return ans.substr(leading_zero_idx);
    }
};
