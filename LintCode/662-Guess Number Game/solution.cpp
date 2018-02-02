// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    /**
     * @param n an integer
     * @return the number you guess
     */
    int guessNumber(int n) {
        // Write your code here
        int l = 1, r = n;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            int g = guess(m);
            if(g == 0)
                return m;
            else if(g > 0)
                l = m + 1;
            else
                r = m - 1;
        }
        return l;
    }
};
