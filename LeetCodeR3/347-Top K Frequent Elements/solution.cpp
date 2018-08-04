struct Cmp {
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) {
        return p1.second > p2.second;
    }
};
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnts;
        for(auto x: nums) {
            cnts[x]++;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> pq;
        for(auto p: cnts) {
            pq.push(p);
            if(pq.size() > k) {
                pq.pop();
            }
        }
        vector<int> ans;
        while(!pq.empty()) {
            ans.push_back(pq.top().first);
            pq.pop();
        }
        return ans;
    }
};
