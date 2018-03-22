class Solution {
public:
    bool dfs(unordered_set<string> &visited, string &ans, int total, int n, int k)
    {
        if(visited.size() == total)
            return true;
        string prev = ans.substr(ans.length() - n + 1);
        for(int i = 0; i < k; i++)
        {
            string next = prev;
            next.push_back('0' + i);
            if(visited.find(next) == visited.end())
            {
                visited.insert(next);
                ans.push_back('0' + i);
                if(dfs(visited, ans, total, n, k))
                    return true;
                ans.pop_back();
                visited.erase(next);
            }
        }
        return false;
    }
    string crackSafe(int n, int k) {
        string ans(n, '0');
        unordered_set<string> visited{ans};
        dfs(visited, ans, pow(k, n), n, k);
        return string(ans.begin(), ans.end());
    }
};
