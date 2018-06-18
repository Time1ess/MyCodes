class SetOfStacks {
public:
    void pushStacks(vector<vector<int>>& stacks, int size, int val) {
        int n = stacks.size();
        if(n == 0 || int(stacks[n-1].size()) == size) {
            stacks.push_back({val});
        } else {
            stacks[n-1].push_back(val);
        }
    }
    void popStacks(vector<vector<int>>& stacks) {
        int n = stacks.size();
        if(n == 0)
            return;
        stacks[n-1].pop_back();
        if(stacks[n-1].empty())
            stacks.pop_back();
    }
    vector<vector<int> > setOfStacks(vector<vector<int> > ope, int size) {
        // write code here
        vector<vector<int>> stacks;
        for(auto x: ope) {
            bool isPush = x[0] == 1;
            int val = x[1];
            if(isPush) {
                pushStacks(stacks, size, val);
            } else {
                popStacks(stacks);
            }
        }
        return stacks;
    }
};
