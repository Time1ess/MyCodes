// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-09-07 11:01
// Last modified: 2016-09-07 11:04
// Filename: solution2.cpp
// Description:
char findTheDifference(char* s, char* t) {
    char ans=0;
    for(char *p=s; *p!='\0'; p++)
        ans^= *p;
    for(char *p=t; *p!='\0'; p++)
        ans^= *p;
    return ans;
}
