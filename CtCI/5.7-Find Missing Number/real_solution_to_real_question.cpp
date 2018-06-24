class Finder {
public:
    int findMissingInternal(vector<vector<int>>& numbers, const int col) {
        if(col >= 32)
            return 0;
        vector<vector<int>> oneBits, zeroBits;
        for(int i = 0; i < numbers.size(); i++) {
            if(int(numbers[i].size()) >= col + 1 && numbers[i][col] == 1)
                oneBits.push_back(numbers[i]);
            else
                zeroBits.push_back(numbers[i]);
        }
        int oneBitsSize = oneBits.size();
        int zeroBitsSize = zeroBits.size();
        if(zeroBitsSize <= oneBitsSize) {
            int v = findMissingInternal(zeroBits, col+1);
            return (v << 1) | 0;
        } else {
            int v = findMissingInternal(oneBits, col+1);
            return (v << 1) | 1;
        }
    }
    int findMissing(vector<vector<int> > numbers, int n) {
        // write code here
        return findMissingInternal(numbers, 0);
    }
};
