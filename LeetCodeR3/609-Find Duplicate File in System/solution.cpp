class Solution {
public:
    string read_directory(const string& path, int& idx, int n) {
        string dir = "";
        while(idx < n && path[idx] != ' ') {
            dir.push_back(path[idx++]);
        }
        idx++;
        return dir;
    }
    pair<string, string> read_file(const string& path, int& idx, int n) {
        string content;
        string file_name;
        while(idx < n && path[idx] != '(') {
            file_name.push_back(path[idx++]);
        }
        idx++;
        while(idx < n && path[idx] != ')') {
            content.push_back(path[idx++]);
        }
        idx += 2;
        return {file_name, content};
    }
    vector<pair<string, string>> read_path(const string& path) {
        int idx = 0;
        int n = path.length();
        string dir = read_directory(path, idx, n);
        vector<pair<string, string>> files;
        while(idx < n) {
            auto p = read_file(path, idx, n);
            files.push_back({dir + "/" + p.first, p.second});
        }
        return files;
    }
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> duplicates;
        for(auto path: paths) {
            auto files = read_path(path);
            for(auto x: files) {
                duplicates[x.second].push_back(x.first);
            }
        }
        vector<vector<string>> ans;
        for(auto p: duplicates) {
            if(p.second.size() > 1) {
                ans.push_back(p.second);
            }
        }
        return ans;
    }
};
