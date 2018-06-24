class Finder {
public:
    int findMissing(vector<vector<int> > numbers, int n) {
        // write code here
        for(int i = 0; i < n; i++) {
            if(i % 2 != numbers[i][0])
                return i;
        }
        return n;
    }
};
