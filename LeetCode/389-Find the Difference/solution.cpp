// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-09-07 10:43
// Last modified: 2016-09-07 11:00
// Filename: solution.cpp
// Description:
char findTheDifference(char* s, char* t) {
    int cnt[26];
    char ans;
    for(int i=0; i<26; i++)
        cnt[i] = 0;
    for(char *p=s; *p!='\0'; p++)
        cnt[*p-'a']++;
    for(char *p=t; *p!='\0'; p++)
        cnt[*p-'a']--;
    for(int i=0; i<26; i++)
        if(cnt[i]!=0)
        {
            ans = 'a'+i;
            break;
        }
    return ans;
}
