class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
    	int size = A.size();
        vector<int> ans;
        if(size == 0)
            return ans;
        vector<int> prefix_mul(size + 1, 1), suffix_mul(size, 1);
        for(int i = 1; i <= size; i++)
        	prefix_mul[i] = prefix_mul[i-1] * A[i-1];  // prefix[0, i) = A[0] * A[1] * ... * A[i - 1]
        for(int i = size - 2; i >= 0; i--)
            suffix_mul[i] = suffix_mul[i+1] * A[i+1];  // suffix(i, n) = A[i+1] * ... * A[n - 1]
        for(int i = 0; i < size; i++)
            ans.push_back(prefix_mul[i] * suffix_mul[i]);
        return ans;
    }
};
