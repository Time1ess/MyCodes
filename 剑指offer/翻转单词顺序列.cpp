class Solution {
public:
    void Reverse(string &str, int s, int e)
    {
        int size = str.size();
        if(size == 0 || s >= size || e < 0)
            return;
        while(s < e)
        {
            swap(str[s], str[e]);
            s++, e--;
        }
    }
    string ReverseSentence(string str) {
        int size = str.size();
        int i = 0, j = 0;
        Reverse(str, 0, size - 1);
        while(i != size)
        {
            if(str[i] == ' ')
            {
                i++;
                j++;
            }
            else if(str[j] == ' ' || j == size)
            {
                Reverse(str, i, j - 1);
                i = j;
            }
            else
                j++;
        }
        return str;
    }
};
