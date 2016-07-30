/*
磁盘移臂调度算法SSTF及SCAN模拟
*/
#include <iostream>
#include <cstring>
#include <cmath>
#pragma warning(disable:4996)
using namespace std;

class SSTF
{
private:
	struct indexDistance
	{
		int distance;
		int index;
	};
	int nowindex;
	int size;
	int maxSize;
	indexDistance *list;
	int total;
	int *seq;
	double average;
	int outNumber;
	int inNumber;
public:
	SSTF(int s, int n)
	{
		size = s;
		maxSize = s;
		list = new indexDistance[size];
		seq = new int[size];
		memset(list, 0, sizeof(indexDistance)*size);
		memset(seq, 0, sizeof(int)*size);
		total = 0;
		outNumber = 0;
		inNumber = 0;
		average = 0;
		nowindex = n;
	}
	~SSTF()
	{
		delete[] list;
		delete[] seq;
	}
	void push(int index)
	{
		list[inNumber++].index = index;
	}
	int getTotal(void)
	{
		return total;
	}

	void printSequence(void)
	{
		cout << "Output Sequence:";
		for (int i = 0; i < maxSize - size; i++)
			cout << seq[i] << " ";
		cout << endl;
	}
	void setDistance()
	{
		for (int i = 0; i < size; i++)
			list[i].distance = abs(list[i].index - nowindex);
	}



	bool out()
	{
		if (size == 0)return false;
		int low = 0;
		for (int i = 0; i < size; i++)
		{
			if (list[low].distance>list[i].distance)
				low = i;
		}
		seq[outNumber++] = list[low].index;
		total += list[low].distance;
		nowindex = list[low].index;
		list[low].index = list[size - 1].index;
		size--;
		average = 1.0*total / (maxSize - size);
		cout << endl << "Next Visit Number:";
		cout.width(3);
		cout << nowindex << "\tDistance:";
		cout.width(3);
		cout << list[low].distance;
		cout << "\tAverage Finding Length:";
		cout.width(3);
		cout.precision(3);
		cout << average << endl;
		for (int i = 0; i < size; i++)
		{
			list[i].distance = abs(list[i].index - nowindex);
		}
		return true;
	}

};

class SCAN
{
private:
	struct indexDistance
	{
		int distance;
		int index;
	};
	int nowindex;
	int size;
	int maxSize;
	indexDistance *list, *start;
	int total;
	int *seq;
	double average;
	int outNumber;
	int inNumber;
public:
	SCAN(int s, int n)
	{
		size = s;
		maxSize = s;
		list = new indexDistance[size];
		start = list;
		seq = new int[size];
		memset(list, 0, sizeof(list)*size);
		memset(seq, 0, sizeof(seq)*size);
		total = 0;
		outNumber = 0;
		inNumber = 0;
		average = 0;
		nowindex = n;
	}
	~SCAN()
	{
		delete[] start;
		delete[] seq;
	}
	void push(int index)
	{
		list[inNumber++].index = index;
	}
	int getTotal(void)
	{
		return total;
	}

	void printSequence(void)
	{
		cout << "Output Sequence:";
		for (int i = 0; i < maxSize - size; i++)
			cout << seq[i] << " ";
		cout << endl;
	}

	void setDistance()
	{
		for (int i = 0; i < size; i++)
			list[i].distance = abs(list[i].index - nowindex);
	}

	void sort()
	{
		int tmp;
		int i = 0, j = size - 1;
		while (i < j)
		{
			if (list[i].index > nowindex)i++;
			if (list[j].index < nowindex)j--;
			tmp = list[i].index;
			list[i].index = list[j].index;
			list[j].index = tmp;
		}
		int key = 0;
		while (list[key].index>nowindex)key++;
		//??0~k-1?°?????ò
		for (i = 0; i < key; i++)
		for (j = i + 1; j < key; j++)
		{
			if (list[i].index>list[j].index)
			{
				tmp = list[i].index;
				list[i].index = list[j].index;
				list[j].index = tmp;
			}
		}
		//??k~size-1?°?????ò
		for (i = key; i < size; i++)
		for (j = i + 1; j < size; j++)
		{
			if (list[i].index<list[j].index)
			{
				tmp = list[i].index;
				list[i].index = list[j].index;
				list[j].index = tmp;
			}
		}
		setDistance();
	}

	bool out()
	{
		if (size == 0)
			return false;
		cout << endl << "Next Visit Number:";
		cout.width(3);
		cout << list[0].index << "\tDistance:";
		cout.width(3);
		cout << list[0].distance;
		total += list[0].distance;
		seq[outNumber++] = list[0].index;
		size--;
		average = 1.0*total / (maxSize - size);
		cout << "\tAverage Finding Length:";
		cout.width(3);
		cout.precision(3);
		cout << average << endl;
		nowindex = list[0].index;
		list = list + 1;
		sort();
		return true;
	}

};

int main()
{
	freopen("in.txt", "r", stdin);
	cout << "Please enter the total number:";
	int t;
	cin >> t;
	cout << t << endl;
	cout << "Please enter the start number:";
	int n;
	cin >> n;
	cout << n << endl;
	SCAN scan(t, n);
	SSTF sstf(t, n);
	for (int i = 0; i < t; i++)
	{
		cin >> n;
		cout << "Please enter the " << i + 1 << "th number:";
		scan.push(n);
		sstf.push(n);
		cout << n << endl;
	}
	scan.sort();
	sstf.setDistance();
	cout << endl << "SCAN:" << endl;
	while (scan.out());
	cout << endl << "Total:" << scan.getTotal() << endl;
	scan.printSequence();

	cout << endl << "SSTF:" << endl;
	while (sstf.out());
	cout << endl << "Total:" << sstf.getTotal() << endl;
	sstf.printSequence();
	
	return 0;
}