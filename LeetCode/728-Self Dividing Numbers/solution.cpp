class Solution {
public:
    bool can_self_divide(int x)
    {
        int origin_x = x;
        while(x)
        {
            int k = x % 10;
            if(k == 0 || origin_x % k != 0)
                return false;
            x /= 10;
        }
        return true;
    }
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> ans;
        for(int i = left; i <= right; i++)
            if(can_self_divide(i))
                ans.push_back(i);
        return ans;
    }
};
