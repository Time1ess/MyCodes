class Finder {
public:
    int findMissing(vector<vector<int> > numbers, int n) {
        // write code here
        int x = n;
        for(int i = 0; i < n; i++) {
            x ^= i;
            for(int j = 0; j < numbers[i].size(); j++) {
                x ^= numbers[i][j] << j;
            }
        }
        return x;
    }
};
