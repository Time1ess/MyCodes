class Count2 {
public:
    int count2sAtDigit(int n, int d) {
        int power10 = pow(10, d);
        int next_power10 = pow(10, d+1);
        int cnt_more_than_power10 = n % power10;
        
        int round_down = n - n % next_power10;
        int round_up = round_down + next_power10;
        
        int digit = (n / power10) % 10;
        if(digit < 2) {
            return round_down / 10;
        } else if(digit > 2) {
            return round_up / 10;
        } else {
            return round_down / 10 + cnt_more_than_power10 + 1;
        }
    }
    int countNumberOf2s(int n) {
        // write code here
        int cnt = 0;
        int d = 0;
        for(int base = 1; base < n; base *= 10) {
            cnt += count2sAtDigit(n, d++);
        }
        return cnt;
    }
};
