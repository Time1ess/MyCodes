class Solution {
public:
    /**
     * @param p: the point List
     * @return: the numbers of pairs which meet the requirements
     */
    int even(int x)
    {
        return (x & 0x1) == 0 ? 1 : 0;
    }
    int pairNumbers(vector<Point> &p) {
        // Write your code here
        vector<int> cnts(4, 0);
        // x:y
        // 0: odd:odd,
        // 1: odd:even
        // 2: even:odd
        // 3: even:even
        for(auto _p: p)
            cnts[even(_p.x)*2 + even(_p.y)]++;
        int ans = 0;
        for(int i = 0; i < 4; i++)
            ans += cnts[i] * (cnts[i] - 1);
        return ans / 2;
    }
};
