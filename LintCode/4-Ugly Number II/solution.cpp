class Solution {
public:
    /**
     * @param n: An integer
     * @return: the nth prime number as description.
     */
    int nthUglyNumber(int n) {
        // write your code here
        if (n == 1)
            return 1;
        vector<int> uglies;
        uglies.push_back(1);
        int p2 = 0, p3 = 0, p5 = 0;
        int f2 = 2, f3 = 3, f5 = 5;
        for (int i = 2; i <= n; i++) {
            int cur = min(f2, min(f3, f5));
            uglies.push_back(cur);
            if (f2 == cur)
                f2 = 2 * uglies[++p2];
            if (f3 == cur)
                f3 = 3 * uglies[++p3];
            if (f5 == cur)
                f5 = 5 * uglies[++p5];
        }
        return uglies[n-1];
    }
};
