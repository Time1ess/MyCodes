class Solution {
public:
    /**
     * @param A: an integer array
     * @param target: An integer
     * @param k: An integer
     * @return: an integer array
     */
    vector<int> kClosestNumbers(vector<int> &A, int target, int k) {
        // write your code here
        priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
        for(auto x: A) {
            pq.push({abs(x-target), x});
        }
        vector<int> ans;
        for(int i = 0; i < k && !A.empty(); i++) {
            auto p = pq.top();
            pq.pop();
            ans.push_back(p.second);
        }
        return ans;
    }
};
