class Middle {
public:
    vector<int> getMiddle(vector<int> A, int n) {
        // write code here
        priority_queue<int> max_heap;
        priority_queue<int, vector<int>, std::greater<int>> min_heap;
        vector<int> ans;
        for(int i = 0; i < n; i++) {
            if((i & 0x1) == 1) {
                max_heap.push(A[i]);
                min_heap.push(max_heap.top());
                max_heap.pop();
            } else {
                min_heap.push(A[i]);
                max_heap.push(min_heap.top());
                min_heap.pop();
            }
            ans.push_back(max_heap.top());
        }
        return ans;
    }
};
