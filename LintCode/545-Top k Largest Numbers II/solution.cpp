class Solution {
private:
    priority_queue<int, vector<int>, greater<int>> pq;
    int k;
public:
    /*
    * @param k: An integer
    */Solution(int k) {
        // do intialization if necessary
        this->k = k;
    }

    /*
     * @param num: Number to be added
     * @return: nothing
     */
    void add(int num) {
        if(k <= 0)
            return;
        if(pq.size() < k)
            pq.push(num);
        else if(pq.size() == k && pq.top() < num)
        {
            pq.pop();
            pq.push(num);
        }
        // write your code here
    }

    /*
     * @return: Top k element
     */
    vector<int> topk() {
        // write your code here
        priority_queue<int, vector<int>, greater<int>> tmp(pq);
        vector<int> ans;
        while(!tmp.empty())
        {
            ans.push_back(tmp.top());
            tmp.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
