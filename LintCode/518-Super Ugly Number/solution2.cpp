class Solution {
public:
    /*
     * @param n: a positive integer
     * @param primes: the given prime list
     * @return: the nth super ugly number
     */
    int nthSuperUglyNumber(int n, vector<int> &primes) {
        // write your code here
        int size = primes.size();

        vector<int> indices(size, 0);
        vector<int> uglies(n, 0);
        uglies[0] = 1;
        int cnt = 1;
        while(cnt < n)
        {
            int mmin = 1e9;
            for(int i = 0; i < size; i++)
            {
                int t = primes[i] * uglies[indices[i]];
                if(t / primes[i] != uglies[indices[i]])
                    continue;
                mmin = min(mmin, t);
            }
            for(int i = 0; i < size; i++)
                if(mmin == primes[i] * uglies[indices[i]])
                    indices[i]++;
            uglies[cnt++] = mmin;
        }
        return uglies[cnt-1];
    }
};
