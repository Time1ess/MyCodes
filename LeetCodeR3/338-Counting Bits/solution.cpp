class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> cnts(num+1, 0);
        int base = 1;
        int cnt = 1;
        for(int i = 1; i <= num; i++) {
            if(cnt == 0) {
                base *= 2;
                cnt = base;
                cnts[i] = 1;
            } else {
                cnts[i] = cnts[i-base] + 1;
            }
            cnt--;
        }
        return cnts;
    }
};
