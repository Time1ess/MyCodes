class Solution {
public:
    /**
     * @param gas: An array of integers
     * @param cost: An array of integers
     * @return: An integer
     */
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        // write your code here
        int n = gas.size(), remain = 0, start = 0, total = 0;
        for(int i = 0; i < n; i++)
        {
            remain += gas[i] - cost[i];
            if(remain < 0)
            {
                start = i + 1;
                total += remain;
                remain = 0;
            }
        }
        return total + remain >= 0 ? start : -1;
    }
};
