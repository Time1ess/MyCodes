class Solution {
public:
    /**
     * @param length: the length of the array
     * @param updates: update operations
     * @return: the modified array after all k operations were executed
     */
    vector<int> getModifiedArray(int length, vector<vector<int>> &updates) {
        // Write your code here
        vector<int> ans;
        map<int, int> changes;
        for(auto x: updates) {
            changes[x[0]] += x[2];
            changes[x[1]+1] -= x[2];
        }
        auto it = changes.begin();
        int cur = 0;
        for(int i = 0; i < length; i++) {
            if(it != changes.end() && it->first == i) {
                cur += it->second;
                it++;
            }
            ans.push_back(cur);
        }
        return ans;
    }
};
