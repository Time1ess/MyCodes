class Solution {
public:
    string originalDigits(string s) {
        vector<int> cnts(26, 0);
        for(auto c: s)
            cnts[c-'a']++;
        string ans = "";
        static vector<pair<char, string>> uniques{{'z', "zero"},{'x', "six"},{'g', "eight"},{'s', "seven"},
                                                  {'v', "five"},{'f', "four"},{'w', "two"},{'t', "three"},
                                                  {'o', "one"},{'i', "nine"}};
        static vector<int> nums{0,6,8,7,5,4,2,3,1,9};
        for(int i = 0; i < 10; i++)
        {
            int k = cnts[uniques[i].first-'a'];
            for(auto c: uniques[i].second)
                cnts[c-'a'] -= k;
            ans.append(k, nums[i]+'0');
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};
