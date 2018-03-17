class Solution {
public:
    /**
     * @param nums: an integer array
     * @param k: An integer
     * @return: the top k largest numbers in array
     */
    vector<int> topk(vector<int> &nums, int k) {
        // write your code here
        priority_queue<int, vector<int>, greater<int>> pq;
        for(auto num: nums)
        {
            if(pq.size() < k)
                pq.push(num);
            else if(pq.size() == k && pq.top() < num)
            {
                pq.pop();
                pq.push(num);
            }
        }
        vector<int> ans;
        while(!pq.empty())
        {
            ans.push_back(pq.top());
            pq.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
