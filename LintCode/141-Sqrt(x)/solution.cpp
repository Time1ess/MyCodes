class Solution {
public:
    /**
     * @param x: An integer
     * @return: The sqrt of x
     */
    int sqrt(int x) {
        // write your code here
        if(x <= 0)
            return 0;
        int l = 1, r = x / 2 + 1;
        while(l < r)
        {
            long long m = l + (r - l) / 2;
            long long t1 = m * m;
            long long t2 = (m + 1) * (m + 1);
            if(t1 <= x && x < t2)
                return m;
            else if(x < t1)
                r = m;
            else
                l = m + 1;
        }
        return l;
    }
};
