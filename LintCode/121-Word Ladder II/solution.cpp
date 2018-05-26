class Solution {
public:
    /*
     * @param start: a string
     * @param end: a string
     * @param dict: a set of string
     * @return: a list of lists of string
     */
    vector<vector<string>> findLadders(string &start, string &end, unordered_set<string> &dict) {
        // write your code here
        dict.insert(end);
        unordered_map<string, vector<string>> nexts;
        unordered_map<string, int> levels;
        int len = start.length();
        int size = dict.size();
        queue<string> q;
        q.push(start);
        levels[start] = 0;
        while(!q.empty()) {
            auto s = q.front();
            q.pop();
            if(s == end)
                break;
            int level = levels[s];
            vector<string> next;
            for(int i = 0; i < len; i++) {
                string news = s;
                for(char c = 'a'; c <= 'z'; c++) {
                    news[i] = c;
                    if(c == s[i] || dict.find(news) == dict.end())
                        continue;
                    auto it = levels.find(news);
                    if(it == levels.end()) {
                        // The first time
                        q.push(news);
                        levels[news] = level + 1;
                    }
                    next.push_back(news);
                }
            }
            nexts[s] = next;
        }
        vector<string> path;
        path.push_back(start);
        vector<vector<string>> ans;
        dfs_path(ans, path, nexts, levels, start, end);
        return ans;
    }
    void dfs_path(vector<vector<string>>& ans, vector<string> &path,
                  unordered_map<string, vector<string>>& nexts,
                  unordered_map<string, int>& levels,
                  const string& now, const string& end) {
        if(now == end) {
            ans.push_back(path);
            return;
        }
        for(const string& news: nexts[now]) {
            if(levels[now] + 1 != levels[news])
                continue;
            path.push_back(news);
            dfs_path(ans, path, nexts, levels, news, end);
            path.pop_back();
        }
    }
};
