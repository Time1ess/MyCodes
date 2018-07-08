class Stack {
public:
    int getHeight(vector<int> men, int n) {
        // write code here
        vector<int> lis;
        int ans = 0;
        for(auto x: men) {
            auto it = lower_bound(lis.begin(), lis.end(), x);
            if(it == lis.end())
                lis.push_back(x);
            else
                *it = x;
            ans = max(static_cast<int>(lis.size()), ans);
        }
        return ans;
    }
};
