class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> candidates;
        for(auto x: nums1)
            candidates.insert(x);
        vector<int> ans;
        for(auto y: nums2)
            if(candidates.find(y) != candidates.end())
            {
                ans.push_back(y);
                candidates.erase(y);
            }
        return ans;
    }
};
