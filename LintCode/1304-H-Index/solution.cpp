class Solution {
public:
    /**
     * @param citations: a list of integers
     * @return: return a integer
     */
    int hIndex(vector<int> &citations) {
        // write your code here
        int n = citations.size();
        sort(citations.begin(), citations.end());
        for(int i = 0; i < n; i++) {
            int h = n - i;
            if(citations[i] >= h && (i == 0 || citations[i-1] <= h))
                return h;
        }
        return 0;
    }
};
