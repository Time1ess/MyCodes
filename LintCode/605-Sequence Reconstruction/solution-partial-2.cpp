class Solution {
public:
    bool seq_equal(const vector<int>& v1, const vector<int>& v2) {
        int n = v1.size();
        int m = v2.size();
        if(n != m) {
            return false;
        }
        for(int i = 0; i < n; i++) {
            if(v1[i] != v2[i]) {
                return false;
            }
        }
        return true;
    }
    /**
     * @param org: a permutation of the integers from 1 to n
     * @param seqs: a list of sequences
     * @return: true if it can be reconstructed only one or false
     */
    bool sequenceReconstruction(vector<int> &org, vector<vector<int>> &seqs) {
        // write your code here
        unordered_map<int, int> in_degrees;
        unordered_map<int, unordered_multiset<int>> constraints;
        int m = org.size();
        unordered_set<int> elems;
        for(int i = 1;i <= m; i++) {
            in_degrees[i] = 0;
        }
        for(auto p: seqs) {
            int len = p.size();
            if(len == 0) {
                continue;
            }
            elems.insert(p[0]);
            for(int i = 1; i < len; i++) {
                elems.insert(p[i]);
                for(int j = i - 1; j >= 0; j--) {
                    in_degrees[p[i]]++;
                    constraints[p[j]].insert(p[i]);
                }
            }
        }
        if(elems.size() != m) {
            return false;
        }
        vector<int> ans;
        while(true) {
            int pickable_cnt = 0;
            int pick = 0;
            for(auto p: in_degrees) {
                if(p.second == 0) {
                    pickable_cnt++;
                    pick = p.first;
                    if(pickable_cnt > 1) {
                        return false;
                    }
                }
            }
            if(pickable_cnt == 0) {
                break;
            }
            in_degrees.erase(pick);
            ans.push_back(pick);
            for(auto x: constraints[pick]) {
                in_degrees[x]--;
            }
            constraints.erase(pick);
        }
        return seq_equal(org, ans);
    }
};
