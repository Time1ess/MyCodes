class Solution {
public:
    int compress(vector<char>& chars) {
        int size = chars.size();
        if(size <= 1)
            return size;
        char cur = chars[0];
        int cnt = 1;
        int index = 0;
        for(int i = 1; i <= size; i++)
        {
            if(i == size || cur != chars[i])
            {
                chars[index++] = cur;
                if(cnt != 1)
                {
                    string s = to_string(cnt);
                    for(int j = 0; j < s.length(); j++)
                        chars[index++] = s[j];
                }
                if(i == size)
                    return index;
                cur = chars[i];
                cnt = 1;
            }
            else
                cnt++;
        }
    }
};
