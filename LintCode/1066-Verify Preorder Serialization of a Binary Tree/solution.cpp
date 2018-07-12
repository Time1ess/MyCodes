class Solution {
public:
    /**
     * @param preorder: a string
     * @return: return a bool
     */
    bool hasVal(const string& preorder, int& idx, const int n) {
        if(preorder[idx] == '#') {
            idx += 2;
            return false;
        }
        while(idx < n && preorder[idx] != ',')
            idx++;
        idx++;
        return true;
    }
    bool isValidSerialization(const string& preorder, int& idx, const int n) {
        if(idx >= n)
            return false;
        bool isVal = hasVal(preorder, idx, n);
        // If it's a null node
        if(!isVal)
            return true;
        return isValidSerialization(preorder, idx, n) && isValidSerialization(preorder, idx, n);
    }
    bool isValidSerialization(string &preorder) {
        // write your code here
        int n = preorder.size();
        int idx = 0;
        return isValidSerialization(preorder, idx, n) && idx == n+1 ;
    }
};
