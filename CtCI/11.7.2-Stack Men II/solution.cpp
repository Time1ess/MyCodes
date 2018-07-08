bool cmp(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}

class Stack {
public:
    int getHeight(vector<vector<int> > actors, int n) {
        sort(actors.begin(), actors.end(), cmp);
        vector<int> lis;
        for(auto x: actors) {
            auto it = lower_bound(lis.begin(), lis.end(), x[1]);
            if(it == lis.end())
                lis.push_back(x[1]);
            else
                *it = x[1];
        }
        return static_cast<int>(lis.size());
    }
};
