class Solution {
public:
    int count(int mid, int m, int n)
    {
        int ans = 0;
        for(int i = 1; i <= m; i++)
            ans += min(mid / i, n);
        return ans;
    }
    int findKthNumber(int m, int n, int k) {
        int l = 1, r = m * n + 1;
        while(l < r)
        {
            int mid = l + (r - l) / 2;
            int c = count(mid, m, n);
            if(c < k)
                l = mid + 1;
            else
                r = mid;
        }
        return l;
    }
};
