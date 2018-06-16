class Solution {
public:
    /**
     * @param N: a positive number
     * @return: how many numbers X from 1 to N are good
     */
    int rotate(int digit) {
        if(digit == 0 || digit == 1 || digit == 8)
            return digit;
        else if(digit == 2)
            return 5;
        else if(digit == 5)
            return 2;
        else if(digit == 6)
            return 9;
        else if(digit == 9)
            return 6;
        return -1;
    }
    bool isGoodNumber(int x) {
        vector<int> vx;
        while(x) {
            vx.push_back(x%10);
            x /= 10;
        }
        vector<int> rotated = vx;
        for(int i = 0; i < rotated.size(); i++) {
            if(rotate(rotated[i]) == -1)
                return false;
            rotated[i] = rotate(rotated[i]);
        }
        bool sameNumber = true;
        for(int i = 0; i < rotated.size(); i++) {
            sameNumber = sameNumber && vx[i] == rotated[i];
        }
        return !sameNumber;
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
