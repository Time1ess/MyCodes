class Solution {
public:
    /*
     * @param digits: a number represented as an array of digits
     * @return: the result
     */
    vector<int> plusOne(vector<int> &digits) {
        // write your code here
        vector<int> ans = digits;
        int c = 1;
        int size = ans.size();
        if(size == 0)
            return ans;
        reverse(ans.begin(), ans.end());
        for(int i = 0; i < size; i++)
        {
            ans[i] += c;
            if(ans[i] >= 10)
            {
                ans[i] %= 10;
                c = 1;
            }
            else
                c = 0;
        }
        if(c == 1)
            ans.push_back(1);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
