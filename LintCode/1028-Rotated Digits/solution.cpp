class Solution {
public:
    /**
     * @param N: a positive number
     * @return: how many numbers X from 1 to N are good
     */
    bool isGoodNumber(int x) {
        bool flag = false;
        while(x) {
            int t = x % 10;
            x /= 10;
            if(t == 2 || t == 5 || t == 6 || t == 9)
                flag = true;
            else if(t == 3 || t == 4 || t == 7)
                return false;
        }
        return flag;
    }
    int rotatedDigits(int N) {
        // write your code here
        int cnt = 0;
        for(int i = 1; i <= N; i++)
            if(isGoodNumber(i))
                cnt++;
        return cnt;
    }
};
