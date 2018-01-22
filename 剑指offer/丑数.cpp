class Solution {
public:
    int GetUglyNumber_Solution(int index) {
    	if(index <= 0)
            return 0;
        int *ugly_numbers = new int[index];
        int *u2 = ugly_numbers, *u3 = ugly_numbers, *u5 = ugly_numbers;
        ugly_numbers[0] = 1;
        int next_index = 1;
        while(next_index < index)
        {
            int nu2 = (*u2) * 2, nu3 = (*u3) * 3, nu5 = (*u5) * 5;
            int m = min(nu2, min(nu3, nu5));
            ugly_numbers[next_index] = m;
            while(*u2 * 2 <= m)
                u2++;
            while(*u3 * 3 <= m)
                u3++;
            while(*u5 * 5 <= m)
                u5++;
            next_index++;
        }
        int ans = ugly_numbers[next_index - 1];
        delete[] ugly_numbers;
        return ans;
    }
};
