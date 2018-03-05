class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> cnts;
        for(auto x: nums1)
            cnts[x]++;
        vector<int> ans;
        for(auto x: nums2)
            if(cnts[x])
            {
                ans.push_back(x);
                cnts[x]--;
            }
        return ans;
    }
};
