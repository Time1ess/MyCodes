class Solution {
public:
    /*
     * @param : the given number
     * @param : another number
     * @return: the last digit of B! / A! 
     */
    int computeLastDigit(long long A, long long B) {
        // write your code here
        long long diff = B - A;
        int base = A % 10;
        if(diff >= 10)
            return 0;
        int res = 1;
        for(int i = 1; i <= diff; i++)
            res *= (base + i);
        return res % 10;
    }
};
