class Solution {
public:
    /**
     * @param gas: An array of integers
     * @param cost: An array of integers
     * @return: An integer
     */
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        // write your code here
        int n = gas.size();
        int start = 0;
        int remain = 0;
        while(start < n)
        {
            remain = gas[start];
            int next = start;
            do
            {
                // cost[next] to get to next stop
                remain -= cost[next];
                next = (next + 1) % n;
                if(remain < 0)
                    break;
                // Gain gas[next] at new stop
                remain += gas[next];
            } while(next != start);
            if(remain < 0)
            {
                // Can't get to next, then start from next
                if(next <= start)
                    return -1;
                start = next;
                continue;
            }
            if(next == start)
                break;
        }
        return start;
    }
};
