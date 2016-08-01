/*
# Author: David - youchen.du@gmail.com
# QQ : 449195172
# Last modified:    2015-07-18 14:10
# Filename:     main.cpp
# Description: 
*/
#include <iostream>
#include <string>
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;
stack<string> forward,backward;

int main()
{
	string cmd,site="http://www.acm.org/";
	
	while(cin>>cmd)
	{
		if(cmd=="QUIT")
			break;
		else if(cmd=="VISIT")
		{
			backward.push(site);
			cin>>site;
			cout<<site<<endl;
			while(!forward.empty())
				forward.pop();
		}
		else if(cmd=="BACK")
		{
			if(backward.empty())
			{
				cout<<"Ignored"<<endl;
			}
			else
			{
				forward.push(site);
				site=backward.top();
				cout<<site<<endl;
				backward.pop();
			}
		}
		else if(cmd=="FORWARD")
		{
			if(forward.empty())
			{
				cout<<"Ignored"<<endl;
			}
			else
			{
				backward.push(site);
				site=forward.top();
				cout<<site<<endl;
				forward.pop();
			}
		}
	}
	return 0;
}
