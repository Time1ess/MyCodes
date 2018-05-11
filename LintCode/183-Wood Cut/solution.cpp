class Solution {
public:
    /**
     * @param L: Given n pieces of wood with length L[i]
     * @param k: An integer
     * @return: The maximum length of the small pieces
     */
    int woodCut(vector<int> &L, int k) {
        // write your code here
        int n = L.size();
        int min_len = 1, max_len = INT_MIN;
        for(auto x: L)
            max_len = max(max_len, x);
        while(min_len < max_len)
        {
            int cnt = 0;
            int cur_len = min_len + (max_len - min_len) / 2;
            for(auto x: L)
                cnt += x / cur_len;
            if(cnt >= k)
                min_len = cur_len + 1;
            else
                max_len = cur_len;
        }
        if(min_len == 1)
            return 0;
        return min_len - 1;
    }
};
