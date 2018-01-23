
class Solution {
public:
    long long merge(vector<int> &data, int l, int m, int r)
    {
        int tm = m - 1, tr = r - 1;
        long long cnt = 0;
        int index = r - l;
		vector<int> tmp(r - l, 0);
        while(tm >= l && tr >= m)
        {
            if(data[tm] > data[tr])
            {
                tmp[--index] = data[tm--];
                cnt += tr - m + 1;
            }
            else
                tmp[--index] = data[tr--];
        }
        while(tm >= l)
            tmp[--index] = data[tm--];
        while(tr >= m)
            tmp[--index] = data[tr--];
        for(int i = 0; i < r - l; i++)
            data[l + i] = tmp[i];
        return cnt;
    }
    long long InversePairs(vector<int> &data, int l, int r)
    {
        if(l + 1 >= r)
            return 0;
        int m = l + (r - l) / 2;
        long long left_cnt = InversePairs(data, l, m);
        long long right_cnt = InversePairs(data, m, r);
        long long merge_cnt = merge(data, l, m, r);
        return left_cnt + right_cnt + merge_cnt;
    }
    long long InversePairs(vector<int> data) {
        int size = data.size();
        if(size <= 1)
            return 0;
        return  InversePairs(data, 0, size) % 1000000007;
    }
};


