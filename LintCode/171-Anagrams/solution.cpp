class Solution {
public:
    /**
     * @param strs: A list of strings
     * @return: A list of strings
     */
    vector<string> anagrams(vector<string> &strs) {
        // write your code here
        map<vector<int>, vector<string>> anas;
        for(auto str: strs)
        {
            vector<int> cnt(26, 0);
            for(auto c: str)
                cnt[c-'a']++;
            anas[cnt].push_back(str);
        }
        vector<string> ans;
        for(auto x: anas)
        {
            if(int(x.second.size()) > 1)
                for(auto _x: x.second)
                    ans.push_back(_x);
        }
        return ans;
    }
};
