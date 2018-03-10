class Solution {
public:
    double dfs(unordered_map<string, vector<string>> &rels, map<pair<string, string>, double> &rel_values,
               unordered_map<string, bool> &visited, bool &found, string num, string den)
    {
        if(rel_values.find({num, den}) != rel_values.end())
        {
            found = true;
            return rel_values[{num, den}];
        }
        if(visited[num])
            return -1;
        visited[num] = true;
        for(auto new_den: rels[num])
        {
            double res = dfs(rels, rel_values, visited, found, new_den, den);
            if(found)
            {
                visited[num] = false;
                return res * rel_values[{num, new_den}];
            }
        }
        visited[num] = false;
        return -1;
    }
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string, vector<string>> rels;
        unordered_map<string, bool> visited;
        map<pair<string, string>, double> rel_values;
        int n = equations.size();
        for(int i = 0; i < n; i++)
        {
            rels[equations[i].first].push_back(equations[i].second);
            rels[equations[i].second].push_back(equations[i].first);
            rel_values[equations[i]] = values[i];
            rel_values[{equations[i].second, equations[i].first}] = 1.0 / values[i];
        }
        vector<double> ans;
        for(auto query: queries)
        {
            bool found = false;
            double res = dfs(rels, rel_values, visited, found, query.first, query.second);
            ans.push_back(found ? res : -1);
        }
        return ans;
    }
};
