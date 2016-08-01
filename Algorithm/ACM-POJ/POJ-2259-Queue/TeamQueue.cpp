/*
# Author: David - youchen.du@gmail.com
# QQ : 449195172
# Last modified:    2015-07-18 14:49
# Filename:     TeamQueue.cpp
# Description: 
*/
#include <iostream>
#include <string>
#include <queue>
#include <map>
using namespace std;
int caseNum,teamNum;
queue<long> teams[1001];	//each queue indicates the members now in the que
queue<int> que;			//top value means the next team to dequeue
int members[1000000];	//value indicates which team belongs to
bool hasMember[1001];	//value means if there are team members in the que 

void solve()
{
	string cmd;
	long elem;
	cout<<"Scenario #"<<++caseNum<<endl;
	while(cin>>cmd&&cmd!="STOP")
	{
		if(cmd=="ENQUEUE")
		{
			cin>>elem;
			if(!hasMember[members[elem]])
			{
				hasMember[members[elem]]=true;
				que.push(members[elem]);
			}
			teams[members[elem]].push(elem);
		}
		else if(cmd=="DEQUEUE")
		{
			int curTeamIndex=que.front();
			cout<<teams[curTeamIndex].front()<<endl;
			teams[curTeamIndex].pop();
			if(teams[curTeamIndex].empty())
			{
				que.pop();
				hasMember[curTeamIndex]=false;
			}
		}
	}
	cout<<endl;
}
void init()
{
	for(int i=0;i!=teamNum;i++)
	{
		hasMember[i]=false;
		while(!teams[i].empty())
			teams[i].pop();
	}
	while(!que.empty())
		que.pop();
}
void input()
{
	int elem,elemNum;
	for(int i=0;i<teamNum;i++)
	{
		cin>>elemNum;
		for(int j=0;j<elemNum;j++)
		{
			cin>>elem;
			members[elem]=i;
		}
	}
}
int main()
{
	caseNum=0;
	while(cin>>teamNum,teamNum)
	{
		init();
		input();
		solve();
	}
	return 0;
}
