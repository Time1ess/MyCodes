#include <iostream>
#include <string>
using namespace std;

int main()
{
    bool chars[26] = {false};
    string blocks;
    cin>>blocks;
    int cnt = 0;
    for(int i = 0; i < blocks.length(); i++)
    {
        if(chars[blocks[i]-'A'] == false)
        {
            cnt++;
            if(cnt == 3)
                break;
            chars[blocks[i]-'A'] = true;
        }
    }
    if(cnt == 1 || cnt == 2)
        cout<<cnt<<endl;
    else
        cout<<0<<endl;
    return 0;
}
