class Solution {
public:
    /**
     * @param A: An integer array
     * @return: An integer
     */
    int singleNumberII(vector<int> &A) {
        // write your code here
        vector<int> cnts(32, 0);
        for(auto x: A)
        {
            int t = x, k = 0;
            while(t && k < 32)
            {
                if(t & 1)
                    cnts[k]++;
                t >>= 1;
                k++;
            }
        }
        int x = 0;
        for(int i = 0; i < 32; i++)
            if(cnts[i] % 3 != 0)
                x |= (1 << i);
        return x;
    }
};
