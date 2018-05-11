/**
 * class SVNRepo {
 *     public:
 *     static bool isBadVersion(int k);
 * }
 * you can use SVNRepo::isBadVersion(k) to judge whether 
 * the kth code version is bad or not.
*/


class Solution {
public:
    /*
     * @param n: An integer
     * @return: An integer which is the first bad version.
     */
    int findFirstBadVersion(int n) {
        // write your code here
        int l = 1, r = n;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(SVNRepo::isBadVersion(m) == true)
                r = m;
            else
                l = m + 1;
        }
        return l;
    }
};
