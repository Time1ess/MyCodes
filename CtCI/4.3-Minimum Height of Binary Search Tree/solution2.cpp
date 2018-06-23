#include <cmath>

class MinimalBST {
public:
    int buildMinimalBST(vector<int> vals) {
        // write code here
        int n = vals.size();
        return n == 0 ? 0 : (int)floor(log(n) / log(2)) + 1;
    }
};
