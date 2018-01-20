class Solution {
public:
    void _Permutation(vector<string> &ans, vector<char> &current, int index)
    {
        int size = current.size();
        if(index == size)
        {
            ans.push_back(string(current.begin(), current.end()));
            return;
        }
        else
        {
            unordered_set<char> us;
            for(int i = index; i < size; i++)
            {
                if(us.find(current[i]) != us.end())
                    continue;
                us.insert(current[i]);
                swap(current[index], current[i]);
                _Permutation(ans, current, index + 1);
                swap(current[index], current[i]);
            }
        }
    }
    vector<string> Permutation(string str) {
    	vector<string> ans;
        if(str == "")
            return ans;
        vector<char> current;
        for(int i = 0; i < str.size(); i++)
            current.push_back(str[i]);
        sort(current.begin(), current.end());
        _Permutation(ans, current, 0);
        sort(ans.begin(), ans.end());
        return ans;
    }
};
