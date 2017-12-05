class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        vector<int> digits;
        while(N)
        {
            digits.push_back(N%10);
            N /= 10;
        }
        reverse(digits.begin(), digits.end());
        bool consistency;
        int n = digits.size();
        while(true)
        {
            consistency = true;
            for(int i = n - 1; i > 0; i--)
            {
                if(digits[i] < digits[i-1])
                {
                    consistency = false;
                    digits[i-1]--;
                    for(int j = i; j < n; j++)
                        digits[j] = 9;
                    break;
                }
            }
            if(consistency)
                break;
        }
        int ans = 0;
        for(int i = 0; i < n; i++)
            ans = ans * 10 + digits[i];
        return ans;
    }
};
