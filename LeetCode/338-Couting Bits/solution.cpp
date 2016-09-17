// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-09-17 11:08
// Last modified: 2016-09-17 11:08
// Filename: solution.cpp
// Description:
class Solution {
    public:
        vector<int> countBits(int num) {
            vector<int> ans;
            ans.push_back(0);
            if(num == 0)
                return ans;
            ans.push_back(1);
            int cnt = 1, idx = 2, tmp;
            while(idx < num+1)
            {
                cnt <<= 1;
                tmp = idx;
                while(idx < (tmp+cnt)&&idx < (num+1))
                {
                    ans.push_back(ans[idx-tmp]+1);
                    idx += 1;
                }
            }
            return ans;
        }
};

