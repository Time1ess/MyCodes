class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        int chars[256] = {0};
        int size = str.size();
        for(int i = 0; i < size; i++)
            chars[str[i]]++;
        for(int i = 0; i < size; i++)
            if(chars[str[i]] == 1)
                return i;
        return -1;
    }
};
