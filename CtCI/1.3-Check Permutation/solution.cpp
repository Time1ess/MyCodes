class Same {
public:
    bool checkSam(string stringA, string stringB) {
        // write code here
        vector<int> cnts(256, 0);
        for(auto c: stringA)
            cnts[c]++;
        for(auto c: stringB)
            if(cnts[c] == 0)
                return false;
            else
                cnts[c]--;
        return true;
    }
};
