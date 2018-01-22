class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> ans;
        int size = input.size();
        if(size < k || k == 0)
            return ans;
        else if(size == k)
            return input;
        priority_queue<int> pq;
        for(int i = 0; i < size; i++)
        {
			if(pq.size() < k)
                pq.push(input[i]);
            else if(pq.top() > input[i])
            {
                pq.pop();
                pq.push(input[i]);
            }
        }
        while(!pq.empty())
        {
        	ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }
};
