class Solution {
public:
    /**
     * @param org: a permutation of the integers from 1 to n
     * @param seqs: a list of sequences
     * @return: true if it can be reconstructed only one or false
     */
    bool sequenceReconstruction(vector<int> &org, vector<vector<int>> &seqs) {
        vector<unordered_map<int, unordered_set<int>>> constraints;
        unordered_map<int, int> cons_cnt;
        unordered_set<int> elems;
        int n = seqs.size();
        int m = org.size();
        for(int i = 1; i <= m; i++) {
            cons_cnt[i] = 0;
        }
        for(int i = 0; i < n; i++) {
            int len = seqs[i].size();
            if(len == 0) {
                continue;
            }
            elems.insert(seqs[i][0]);
            unordered_map<int, unordered_set<int>> cons;
            for(int j = 1; j < len; j++) {
                elems.insert(seqs[i][j]);
                for(int k = j - 1; k >= 0; k--) {
                    cons[seqs[i][j]].insert(seqs[i][k]);
                    cons_cnt[seqs[i][j]]++;
                }
            }
            constraints.push_back(cons);
        }
        if(elems.size() != m) {
            return false;
        }
        while(true) {
            int pickable_cnt = 0;
            int pick = 0;
            for(auto p: cons_cnt) {
                if(p.second == 0) {
                    pickable_cnt++;
                    pick = p.first;
                    if(pickable_cnt > 1) {
                        return false;
                    }
                }
            }
            cons_cnt.erase(pick);
            if(pickable_cnt == 0) {  // No more nums without constraints
                break;
            }
            m--;
            for(auto cons: constraints) {
                for(auto p: cons) {  // For constraints of each num
                    if(p.second.find(pick) != p.second.end()) {
                        cons_cnt[p.first]--;
                    }
                }
            }
        }
        return m == 0;
    }
};
