class Solution {
public:
    /**
     * @param nums: an array
     * @return: the Next Greater Number for every element
     */
    vector<int> nextGreaterElements(vector<int> &nums) {
        // Write your code here
        int n = nums.size();
        stack<int> s;
        vector<int> next(n, -1);
        for(int i = 0; i < 2 * n; i++) {
            while(!s.empty() && nums[i%n] > nums[s.top()]) {
                next[s.top()] = nums[i%n];
                s.pop();
            }
            if(i < n)
                s.push(i);
        }
        return next;
    }
};
