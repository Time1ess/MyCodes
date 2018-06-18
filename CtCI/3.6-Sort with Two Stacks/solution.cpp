class TwoStacks {
public:
    vector<int> twoStacksSort(vector<int> numbers) {
        // write code here
        vector<int> ans;
        while(!numbers.empty()) {
            int x = numbers.back();
            numbers.pop_back();
            while(!ans.empty() && ans.back() < x) {
                int y = ans.back();
                ans.pop_back();
                numbers.push_back(y);
            }
            ans.push_back(x);
        }
        return ans;
    }
};
