class Solution {
public:
    int Fibonacci(int n) {
        if(n <= 1)
            return n;
		int fm2 = 0, fm1 = 1, f;
        for(int i = 2; i <= n; i++)
        {
            f = fm1 + fm2;
            fm2 = fm1;
            fm1 = f;
        }
        return f;
    }
};
