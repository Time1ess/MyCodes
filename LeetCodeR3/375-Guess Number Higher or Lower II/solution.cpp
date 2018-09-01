class Solution {
public:
    int getMoney(vector<vector<int>>& mem, int l, int r) {
        if (l >= r) {
            return 0;
        } else if (l + 1 == r) {
            return l;
        } else if (mem[l][r] != 0) {
            return mem[l][r];
        }
        mem[l][r] = INT_MAX;
        for (int x = l; x <= r; x++) {
            mem[l][r] = min(mem[l][r], x + max(getMoney(mem, l, x-1), getMoney(mem, x+1, r)));
        }
        return mem[l][r];
    }
    int getMoneyAmount(int n) {
        vector<vector<int>> mem(n+1, vector<int>(n+1, 0));
        return getMoney(mem, 1, n);
    }
};
