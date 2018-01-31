class Solution {
public:
    /*
     * @param nums: A list of integers
     * @return: the median of numbers
     */
    vector<int> medianII(vector<int> &nums) {
        // write your code here
        vector<int> ans;
        int size = nums.size();
        if(size == 0)
            return ans;
        priority_queue<int> max_pq;
        priority_queue<int, vector<int>, greater<int>> min_pq;
    
        for(int i = 0; i < size; i++)
        {
            if((i & 0x1) == 0) // even
            {
                min_pq.push(nums[i]);
                int tmp = min_pq.top();
                min_pq.pop();
                max_pq.push(tmp);
            }
            else  // odd
            {
                max_pq.push(nums[i]);
                int tmp = max_pq.top();
                max_pq.pop();
                min_pq.push(tmp);
            }
            ans.push_back(max_pq.top());
        }
        return ans;
    }
};
