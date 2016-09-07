// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-09-07 10:35
// Last modified: 2016-09-07 10:43
// Filename: solution.cpp
// Description:
char* reverseString(char* s) {
    if(s==0||*s=='\0')
        return 0;
    char tmp;
    char *prior, *last;
    prior = s;
    last = s;
    while(*last!='\0')
        last++;
    last--;
    while(prior<=last)
    {
        tmp = *prior;
        *prior = *last;
        *last = tmp;
        prior++;
        last--;
    }
    return s;
}
