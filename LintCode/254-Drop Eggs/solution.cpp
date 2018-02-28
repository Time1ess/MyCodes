class Solution {
public:
    /**
     * @param n: An integer
     * @return: The sum of a and b
     */
    int dropEggs(int n) {
        // write your code here
        return ceil((sqrt(1+8*(long long)n)-1)/2);
    }
};
