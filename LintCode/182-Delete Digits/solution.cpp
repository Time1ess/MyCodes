class Solution {
public:
    /**
     * @param A: A positive integer which has N digits, A is a string
     * @param k: Remove k digits
     * @return: A string
     */
    string DeleteDigits(string &A, int k) {
        // write your code here
        int n = A.length();
        string ans = "";
        for(int i = 0; i < n; i++)
        {
            while(!ans.empty() && k > 0 && ans.back() > A[i])
            {
                ans.pop_back();
                k--;
            }
            if(A[i] != '0' || !ans.empty())
                ans.push_back(A[i]);
        }
        while(k-- > 0)
            ans.pop_back();
        return ans;
    }
};
