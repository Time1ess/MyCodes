class Solution {
public:
    /*
     * @param A: An integer array
     * @return: An integer array
     */
    vector<int> singleNumberIII(vector<int> &A) {
        // write your code here
        int x = 0;
        for(auto k: A)
            x ^= k;
        x = (x&(x-1)) ^ x;
        int first = 0, second = 0;
        for(auto k: A)
            if(x & k)
                first ^= k;
            else
                second ^= k;
        return {first, second};
    }
};
