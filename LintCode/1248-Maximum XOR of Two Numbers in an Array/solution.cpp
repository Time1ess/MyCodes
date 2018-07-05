class Solution {
public:
    /**
     * @param nums: 
     * @return: the maximum result of ai XOR aj, where 0 â‰¤ i, j < n
     */
    int findMaximumXOR(vector<int>& v1, vector<int>& v0, int offset) {
        if(offset < 0 || v1.size() == 0 || v0.size() == 0) {
            return 0;
        }
        int mask = 1 << offset;
        vector<int> v11, v10, v01, v00;
        for(auto x: v1) {
            if(x & mask)
                v11.push_back(x);
            else
                v10.push_back(x);
        }
        for(auto x: v0) {
            if(x & mask)
                v01.push_back(x);
            else
                v00.push_back(x);
        }
        int cnt_v11 = v11.size(), cnt_v10 = v10.size();
        int cnt_v01 = v01.size(), cnt_v00 = v00.size();
        if((cnt_v11 == 0 && cnt_v01 == 0) || (cnt_v10 == 0 && cnt_v00 == 0)) {
            // Same second bit, XOR = 0
            return findMaximumXOR(v1, v0, offset-1);
        }
        else {
            int a = findMaximumXOR(v01, v10, offset-1);
            int b = findMaximumXOR(v11, v00, offset-1);
            return mask + max(a, b);
        }
    }
    int findMaximumXOR(vector<int> &nums) {
        int max_num = 0;
        for(auto x : nums) {
            max_num = max(x, max_num);
        }
        int offset = 0;
        while(max_num) {
            offset++;
            max_num >>= 1;
        }
        vector<int> v1, v0;
        int ans = 0;
        for(; offset >= 0 ; offset--) {
            int mask = 1 << offset;
            for(auto x: nums) {
                if(x & mask)
                    v1.push_back(x);
                else
                    v0.push_back(x);
            }
            if(v1.size() != 0 && v0.size() != 0) {
                ans = 1 << offset;
                break;
            }
            v1.clear();
            v0.clear();
        }
        return ans + findMaximumXOR(v1, v0, offset-1);
    }
};
