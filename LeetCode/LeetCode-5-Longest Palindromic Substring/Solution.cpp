class Solution {
public:
    string longestPalindrome(string s) {
        int len=s.length();
        if(s.empty())
            return "";
        if(len==1)
            return s;
        int start=0,str_len=1;
        for(int i=0;i<len;)
        {
            if(len-i<=str_len/2)break;
            int j=i,k=i;
            while(k<len-1&&s[k]==s[k+1])k++;
            i=k+1;
            while(k<len-1&&j>0&&s[k+1]==s[j-1])
            {
                k++;
                j--;
            }
            int new_len=k-j+1;
            if(new_len>str_len)
            {
                start=j;
                str_len=new_len;
            }
        }
        return s.substr(start,str_len);

    }
};
