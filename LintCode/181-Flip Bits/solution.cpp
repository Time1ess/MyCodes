class Solution {
public:
    /**
     * @param a: An integer
     * @param b: An integer
     * @return: An integer
     */
    int bitSwapRequired(int a, int b) {
        // write your code here
        int cnt = 0, t = a ^ b;
        while(t)
        {
            cnt++;
            t = t & (t - 1);
        }
        return cnt;
    }
};
