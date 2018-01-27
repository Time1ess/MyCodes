class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        vector<int> ans;
        int nums_size = num.size();
        if(nums_size == 0 || size <= 0 || nums_size < size)
            return ans;
        deque<int> dq;
        int i = 0;
        while(i < size)
        {
            while(!dq.empty() && num[dq.back()] <= num[i])
                dq.pop_back();
            dq.push_back(i);
            i++;
        }
        while(i < nums_size)
        {
            ans.push_back(num[dq.front()]);
            while(!dq.empty() && num[dq.back()] <= num[i])
                dq.pop_back();
            while(!dq.empty() && (i - size) >= dq.front())
                dq.pop_front();
            dq.push_back(i);
            i++;
        }
        ans.push_back(num[dq.front()]);
        return ans;
    }
};
