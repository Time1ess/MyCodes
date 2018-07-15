#include <unordered_set>

class Change {
public:
    int edit_distance(const string& s1, const string& s2) {
        int dist = 0;
        int m = s1.length();
        int n = s2.length();
        if(m != n) {
            return -1;
        }
        for(int i = 0; i < m; i++) {
            if(s1[i] != s2[i]) {
                dist++;
            }
        }
        return dist;
    }
    int countChanges(vector<string> dic, int n, string s, string t) {
        // write code here
        int m = s.length();
        queue<pair<string ,int>> q;
        unordered_set<string> visited;
        q.push({s, 0});
        while(!q.empty()) {
            auto front = q.front();
            q.pop();
            const string cur = front.first;
            const int cost = front.second;
            if(cur == t) {
                return cost;
            }
            for(int i = 0; i < m; i++) {
                for(auto x: dic) {
                    if(edit_distance(cur, x) == 1 && visited.find(x) == visited.end()) {
                        q.push({x, cost + 1});
                        visited.insert(x);
                    }
                }
            }
        }
        return -1;
    }
};
