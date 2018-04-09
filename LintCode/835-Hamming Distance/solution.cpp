class Solution {
public:
    /**
     * @param x: an integer
     * @param y: an integer
     * @return: return an integer, denote the Hamming Distance between two integers
     */
    int hammingDistance(int x, int y) {
        // write your code here
        int cnt = 0;
        int t = x ^ y;
        while(t)
        {
            cnt++;
            t = t & (t-1);
        }
        return cnt;
    }
};
