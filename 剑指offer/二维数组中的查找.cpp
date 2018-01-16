class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        int m = array.size();
        if(m == 0)
            return false;
        int n = array[0].size();
        if(n == 0)
            return false;
        if(target < array[0][0] || target > array[m-1][n-1])
            return false;
        int r = 0, c = n - 1;
        while(r < m && c >= 0)
        {
            if(array[r][c] == target)
                return true;
            else if(array[r][c] > target)
                c--;
            else
                r++;
        }
        return false;
    }
};
