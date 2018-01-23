#include <iostream>
#include <string>

using namespace std;


class Solution
{
public:
    string transform(string source)
    {
        int length = source.length();
        int cnt_a = 0, cnt_b = 0;
        for(int i = 0; i < length; i++)
            if(source[i] == 'A')
                cnt_a++;
            else if(source[i] == 'B')
                cnt_b++;
        int target_len = length - cnt_a + cnt_b;
        if(target_len > length)
            throw new exception();
        int i = 0, j = 0;
        while(j < length && source[j] == 'A')
            j++;
        while(i < target_len && j < length)
        {
            source[i++] = source[j++];
            while(j < length && source[j] == 'A')
                j++;
        }
        i = length - cnt_a - 1;
        j = target_len - 1;
        while(i >= 0 && j >= 0)
        {
            source[j--] = source[i];
            if(source[i] == 'B')
                source[j--] = 'B';
            i--;
        }
        source.resize(target_len);
        return source;
    }
};


void judge(string source, string target, bool raise=false)
{
    Solution sol;
    cout<<source<<" --> "<<target<<" ";
    bool succeed = false;
    try
    {
        string ans = sol.transform(source);
        cout<<"[Got "<<ans<<"] ";
        if(ans == target && !raise)
            succeed = true;
        else
            succeed = false;
    }
    catch(...)
    {
        cout<<"[Raise exception] ";
        if(raise)
            succeed = true;
        else
            succeed = false;
    }
    if(succeed)
        cout<<"Succeed"<<endl;
    else
        cout<<"Failed"<<endl;
}
int main()
{
    judge("AAA", "");
    judge("BB", "", true);
    judge("ABB", "", true);
    judge("CABB", "", true);
    judge("CAABB", "CBBBB");
    judge("CAABAB", "CBBBB");
    judge("CCBAABC", "CCBBBBC");
    judge("CABCABC", "CBBCBBC");
    judge("CBCABCAABCAA", "CBBCBBCBBC");
    judge("AB", "BB");
    judge("ABAA", "BB");
    judge("ABCCABBBACACA", "BBCCBBBBBBCC");
    return 0;
}
