/*
# Author: David - youchen.du@gmail.com
# QQ : 449195172
# Last modified:    2015-07-19 15:59
# Filename:     Argus.cpp
# Description: 
*/
#include <iostream>
#include <string>
using namespace std;
struct Node{
	int now;
	int id;
	int period;
};
Node node[3010];
int K;
int nLength=0;
void Down(int p)
{
	int q=p*2;
	Node a=node[p];
	while(q<=nLength)
	{
		if(q<nLength&&node[q].now>node[q+1].now)
			q++;
		else if(q<nLength&&node[q].now==node[q+1].now&&node[q].id>node[q+1].id)
			q++;
		if(node[q].now>a.now||
				((a.now==node[q].now)&&node[q].id>a.id))
			break;
		node[p]=node[q];
		p=q;
		q=p*2;
	}
	node[p]=a;
}
void Build()
{
	for(int i=nLength/2;i>0;i--)
		Down(i);
}

int main()
{
	string str;
	while(cin>>str&&str!="#")
	{
		cin>>node[++nLength].id;
		cin>>node[nLength].period;
	}
	for(int i=1;i<=nLength;i++)
	{
		node[i].now+=node[i].period;
	}
	cin>>K;
	Build();
	for(int i=1;i<=K;i++)
	{
		cout<<node[1].id<<endl;
		node[1].now+=node[1].period;
		Down(1);
	}
	return 0;
			
}
