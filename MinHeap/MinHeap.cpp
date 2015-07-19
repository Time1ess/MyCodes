#include <iostream>
using namespace std;
#define SIZE 1000

int heap[SIZE];
int hLength=0;
void Down(int p)
{
	int q=p*2;
	int a=heap[p];
	while(q<=hLength)
	{
		if(q<hLength&&heap[q]>heap[q+1])
			q++;
		if(heap[q]>=a)
			break;
		else
		{
			heap[p]=heap[q];
			p=q;
			q=p*2;
		}
	}
	heap[p]=a;
}

int DeleteMin()
{
	int r=heap[1];
	heap[1]=heap[hLength--];
	Down(1);
	return r;
}

void Up(int p)
{
	int q=p/2;
	int a=heap[p];
	while(q>=1&&a<heap[q])
	{
		heap[p]=heap[q];
		p=q;
		q=p/2;
	}
	heap[p]=a;
}

void Insert(int a)
{
	heap[++hLength]=a;
	Up(hLength);
}

void IncreaseKey(int p,int a)
{
	if(heap[p]>a)
		return;
	heap[p]=a;
	Up(p);
}

void Build()
{
	for(int i=hLength/2;i>0;i--)
		Down(i);
}

void ShowHeap()
{
	for(int i=1;i<=hLength;i++)
		cout<<heap[i]<<" ";
	cout<<endl;
}
int main()
{
	int p;
	while(cin>>p&&p!=-1)
	{
		heap[++hLength]=p;
	}
	ShowHeap();
	Build();
	ShowHeap();
	for(int i=0;i<3;i++)
	{
		DeleteMin();
		ShowHeap();
	}
	for(int i=0;i<3;i++)
	{
		cin>>p;
		Insert(p);
		ShowHeap();
	}
	while(hLength>1)
	{
		DeleteMin();
		ShowHeap();
	}
}
