class Solution {
public:
    int bulbSwitch(int n) {
        int cnt = 0;
        for(int i = 1; i <= n; i++)
        {
            int sqrt_i = sqrt(i);
            if(sqrt_i * sqrt_i == i)
                cnt++;
        }
        return cnt;
    }
};
