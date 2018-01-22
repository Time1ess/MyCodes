class Solution {
public:
    static bool cmp(const vector<char> &a, const vector<char> &b)
    {
        int i = a.size() - 1, j = b.size() - 1;
        while(i >= 0 && j >= 0)
        {
            if(a[i] > b[j])
                return false;
            if(i == 0 && j == 0)
                break;
            if(i > 0)
                i--;
            if(j > 0)
                j--;
        }
        return true;
    }
    string PrintMinNumber(vector<int> numbers) {
        if(numbers.empty())
            return "";
        vector<vector<char>> char_numbers;
        int size = numbers.size();
        for(int i = 0; i < size; i++)
        {
            vector<char> tmp;
            int _t = numbers[i];
            while(_t)
            {
                tmp.push_back(_t % 10 + '0');
                _t /= 10;
            }
            char_numbers.push_back(tmp);
        }
        sort(char_numbers.begin(), char_numbers.end(), cmp);
        int csize = char_numbers.size();
        string ans = "";
        for(int i = 0; i < csize; i++)
        {
            reverse(char_numbers[i].begin(), char_numbers[i].end());
            ans += string(char_numbers[i].begin(), char_numbers[i].end());
        }
        return ans;
    }
};
