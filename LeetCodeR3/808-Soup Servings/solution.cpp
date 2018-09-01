class Solution {
public:
    double solve(vector<vector<double>>& mem, int A, int B) {
        if (A <= 0 && B <= 0) {
            return 0.5;
        }
        if (A <= 0) {
            return 1;
        }
        if (B <= 0) {
            return 0;
        }
        if (mem[A][B] > 0) {
            return mem[A][B];
        }
        mem[A][B] = 0.25 * (solve(mem, A - 4, B) +
                            solve(mem, A - 3, B - 1) +
                            solve(mem, A - 2, B - 2) +
                            solve(mem, A - 1, B - 3));
        return mem[A][B];
    }
    double soupServings(int N) {
        vector<vector<double>> mem(200, vector<double>(200, 0));
        return N >= 4800 ? 1 : solve(mem, (N + 24) / 25, (N + 24) / 25);
    }
};
