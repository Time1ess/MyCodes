class Solution {
public:
    int get_bit_one(int x)
    {
        int ans = 0;
        while(x)
        {
            ans++;
            x &= (x-1);
        }
        return ans;
    }
    vector<string> readBinaryWatch(int num) {
        vector<string> ans;
        for(int i = 0; i < 12; i++)
            for(int j = 0; j < 60; j++)
                if(get_bit_one(i) + get_bit_one(j) == num)
                    ans.push_back(to_string(i) + ":" + (j < 10 ? "0": "") + to_string(j));
        return ans;
    }
};
