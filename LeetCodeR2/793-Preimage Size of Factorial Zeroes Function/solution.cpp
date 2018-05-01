class Solution {
public:
    int cnt_zeros(long long x)
    {
        int cnt = 0;
        for(; x > 0; x /= 5)
            cnt += x / 5;
        return cnt;
    }
    int bsearch(int k)
    {
        int l = 0, r = 5 * (k + 1);
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(cnt_zeros(m) <= k)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }
    int preimageSizeFZF(int K) {
        return bsearch(K) - bsearch(K-1);
    }
};
