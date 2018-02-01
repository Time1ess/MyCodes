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
        int cnt = 0;
        priority_queue<int, vector<int>, greater<int>> pq;
        unordered_set<int> visited;
        pq.push(1);
        int top;
        while(cnt++ < n)
        {
            top = pq.top();
            pq.pop();
            for(int i = 0; i < size; i++)
            {
                int t = primes[i] * top;
                if(t / primes[i] != top)
                    continue;
                if(visited.find(t) != visited.end())
                    continue;
                visited.insert(t);
                pq.push(t);
            }
        }
        return top;
    }
};
