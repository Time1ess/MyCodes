class Solution {
public:
    /**
     * @param arr: a permutation of N
     * @return: the most number of chunks
     */
    int maxChunksToSorted(vector<int> &arr) {
        // write your code here
        int n = arr.size();
        int cnt = 0;
        int max_idx = -1;
        for(int i = 0; i < n; i++) {
            max_idx = max(max_idx, arr[i]);
            if(i == max_idx) {
                cnt++;
            }
        }
        return cnt;
    }
};
