class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        map<int, int> cnts;
        for (auto x: hand) {
            cnts[x]++;
        }
        for (auto p: cnts) {
            int s = p.first;
            int cnt = p.second;
            if (cnt == 0) {
                continue;
            }
            for (int i = 1 ; i < W; i++) {
                cnts[s+i] -= cnt;
                if (cnts[s+i] < 0) {
                    return false;
                }
            }    
        }
        return true;
    }
};
