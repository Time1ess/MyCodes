class Solution {
public:
    vector<int> count(string word)
    {
        vector<int> ans(26, 0);
        for(auto c: word)
        {
            int k = (c >= 'A' && c <= 'Z')? c - 'A': (c >= 'a' && c <= 'z')? c - 'a': -1;
            if(k != -1)
                ans[k]++;
        }
        return ans;
    }
    
    bool complete(vector<int> candidate, vector<int> &target)
    {
        for(int i = 0; i < 26; i++)
            if(candidate[i] < target[i])
                return false;
        return true;
    }
    
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        vector<int> plate_cnt = count(licensePlate);
        string ans = "";
        for(auto word: words)
            if((word.length() < ans.length() || ans.length() == 0) && complete(count(word), plate_cnt))
                ans = word;
        return ans;
    }
};
