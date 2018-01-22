class Solution {
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        int base = 1, ans = 0, mod = 0, t = n;
        while(t)
        {
            mod = t % 10;
            t = t / 10;
            ans += t * base;
            if(mod == 1)
                ans += n % base + 1;
            else if(mod > 1)
                ans += base;
            base *= 10;
        }
        return ans;
    }
};
