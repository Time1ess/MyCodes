class Solution {
public:
    /**
     * @param A: an integer array
     * @param target: An integer
     * @param k: An integer
     * @return: an integer array
     */
    vector<int> kClosestNumbers(vector<int> &A, int target, int k) {
        // write your code here
        int n = A.size();
        if(n == 0)
            return {};
        else if(A[0] >= target) {
            return vector<int>(A.begin(), A.begin() + k);
        } else if(A[n-1] <= target) {
            vector<int> ans(A.end() - k, A.end());
            reverse(ans.begin(), ans.end());
            return ans;
        }
        int idx = lower_bound(A.begin(), A.end(), target) - A.begin();
        int low = max(0, idx - k + 1), high = min(n - 1, idx + k - 1);
        while(high - low + 1 > k) {
            if(abs(A[low] - target) <= abs(A[high] - target))
                high--;
            else if(abs(A[low] - target) > abs(A[high] - target))
                low++;
        }
        vector<int> ans;
        while(low <= high) {
            if(abs(A[low] - target) > abs(A[high] - target)) {
                ans.push_back(A[low++]);
            } else {
                ans.push_back(A[high--]);
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
