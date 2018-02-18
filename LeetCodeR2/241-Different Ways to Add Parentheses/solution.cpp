class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> ans;
        int len = input.length();
        for(int i = 0; i < len; i++)
        {
            if(input[i] == '+' || input[i] == '-' || input[i] == '*')
            {
                vector<int> ans1 = diffWaysToCompute(input.substr(0, i));
                vector<int> ans2 = diffWaysToCompute(input.substr(i + 1, len - i - 1));
                for(auto x: ans1)
                    for(auto y: ans2)
                    {
                        if(input[i] == '+')
                            ans.push_back(x+y);
                        else if(input[i] == '-')
                            ans.push_back(x-y);
                        else
                            ans.push_back(x*y);
                    }
            }
        }
        if(ans.empty())
            ans.push_back(stoi(input));
        return ans;
    }
};
