class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int cnt = 0;
        int i = 0;
        int n = arr.size();
        while(i < n)
        {
            if(arr[i] == i)
            {
                cnt++;
                i++;
            }
            else
            {
                int mmax = arr[i];
                int j = i;
                for(;j <= mmax; j++)
                    mmax = max(mmax, arr[j]);
                cnt++;
                i = mmax + 1;
            }
        }
        return cnt;
    }
};
