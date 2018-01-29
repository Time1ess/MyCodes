class Solution {
public:
    /**
     * @param words: a list of unique words
     * @return: all pairs of distinct indices
     */
    bool is_palindrome(string &s)
    {
        int i = 0, j = s.length() - 1;
        while(i < j)
            if(s[i++] != s[j--])
                return false;
        return true;
    }
    vector<vector<int>> palindromePairs(vector<string> &words) {
        unordered_map<string, int> reversed;
        vector<vector<int>> ans;
        int n = words.size();
        if(n == 0)
            return ans;
        int empty_str_index = -1;
        for(int i = 0; i < n; i++)
        {
            string s = words[i];
            if(s == "")
                empty_str_index = i;
            reverse(s.begin(), s.end());
            reversed[s] = i;
        }
        if(empty_str_index != -1)
        {
            for(int i = 0; i < n; i ++)
            {
                if(i == empty_str_index)
                    continue;
                if(is_palindrome(words[i]))
                {
                    ans.push_back({empty_str_index, i});
                }
            }
        }
        for(int i = 0; i < n; i++)
        {
            int length = words[i].length();
            for(int j = 0; j < length; j++)
            {
                string left = words[i].substr(0, j);
                string right = words[i].substr(j, length - j);
                if(reversed.find(left) != reversed.end()
                        && is_palindrome(right)
                        && reversed[left] != i)
                    ans.push_back({i, reversed[left]});
                if(reversed.find(right) != reversed.end()
                        && is_palindrome(left)
                        && reversed[right] != i)
                    ans.push_back({reversed[right], i});
            }
        }
        return ans;
    }
};
