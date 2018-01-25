class Solution {
public:
    static int terminator(int n)
    {
        return 0;
    }
    static int Sum(int n)
    {
        static int (*p[2])(int) = {terminator, Sum};
        return n + p[!!n](n-1);
    }
    int Sum_Solution(int n) {
        return Solution::Sum(n);
    }
};

