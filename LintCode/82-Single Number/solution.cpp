class Solution {
public:
    /**
     * @param A: An integer array
     * @return: An integer
     */
    int singleNumber(vector<int> &A) {
        // write your code here
        int x = 0;
        for(auto k: A)
            x ^= k;
        return x;
    }
};
