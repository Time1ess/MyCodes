struct Cmp {
    bool operator()(const pair<string, int>& a, const pair<string, int>& b) const {
        return a.second < b.second || (a.second == b.second && a.first > b.first);
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> cnts;
        for (auto x : words) {
            cnts[x]++;
        }
        priority_queue<pair<string, int>, vector<pair<string, int>>, Cmp> pq;
        for (auto p : cnts) {
            pq.push(p);
        }
        vector<string> ans;
        while (k--) {
            auto top = pq.top();
            pq.pop();
            ans.push_back(top.first);
        }
        return ans;
    }
};
