class Solution {
public:
    /**
     * @param nums: a list of integers
     * @return: return a boolean
     */
    bool isPossible(vector<int> &nums) {
        // write your code here
        unordered_map<int, int> ending_cnts; // key: Slice end with key, cnt: cnt
        map<int, int> cnts;
        int min_num = INT_MAX, max_num = INT_MIN;
        for(auto x: nums) {
            cnts[x]++;
            min_num = min(min_num, x);
            max_num = max(max_num, x);
        }
            
            
        // Build shortest slices as many as possible.
        int x = min_num;
        while(x <= max_num - 2) {
            if(cnts[x] == 0) {
                x++;
                continue;
            }
            int cnt = min(cnts[x], min(cnts[x+1], cnts[x+2]));
            ending_cnts[x+2] += cnt;
            cnts[x] -= cnt;
            cnts[x+1] -= cnt;
            cnts[x+2] -= cnt;
            x++;
        }
        
        // Append remain nums
        for(int i = min_num; i <= max_num; i++) {
            if(ending_cnts[i-1] < cnts[i])
                return false;
            ending_cnts[i-1] -= cnts[i];
            ending_cnts[i] += cnts[i];
        }
        return true;
    }
};
