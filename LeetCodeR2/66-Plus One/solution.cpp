class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        reverse(digits.begin(), digits.end());
        int c = 1;
        for(int i = 0; i < digits.size(); i++)
        {
            int x = digits[i] + c;
            if(x == 10)
            {
                c = 1;
                x = 0;
            }
            else
                c = 0;
            digits[i] = x;
        }
        if(c == 1)
            digits.push_back(1);
        reverse(digits.begin(), digits.end());
        return digits;
    }
};
