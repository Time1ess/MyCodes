class Frequency {
public:
    int getFrequency(vector<string> article, int n, string word) {
        // write code here
        int ans = 0;
        for(auto _word : article) {
            if(_word == word)
                ans++;
        }
        return ans;
    }
};
