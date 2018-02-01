class Solution {
public:
    /*
     * @param s: A string 
     * @param p: A string includes "?" and "*"
     * @return: is Match?
     */
    bool isMatch(string &s, string &p) {
        // write your code here
        int ssize = s.length(), psize = p.length();
        int sidx = 0, pidx = 0, last_star = -1, last_sidx = -1;
        while(sidx < ssize)
        {
            if(pidx < psize && (p[pidx] == '?' || s[sidx] == p[pidx]))  // Single match
            {
                sidx++, pidx++;
                continue;
            }
                
            if(pidx < psize && p[pidx] == '*')  // Current *, advancing pidx
            {
                last_star = pidx++;
                last_sidx = sidx;
                continue;
            }
            
            if(last_star != -1)  // No match, advancing sidx by using *
            {
                pidx = last_star+1;
                sidx = ++last_sidx;
                continue;
            }
            return false;
        }
        while(pidx < psize && p[pidx] == '*')
            pidx++;
        return pidx == psize;
    }
};
