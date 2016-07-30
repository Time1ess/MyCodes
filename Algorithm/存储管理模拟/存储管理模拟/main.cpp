#include <iostream>
#pragma warning(disable:4996)
using namespace std;


class FIFO
{
private:
	int size;
	int missCnt;
	int Cnt;
	double missPercent;
	int *data;
public:
	FIFO(int s)
	{
		size = s;
		missCnt = 0;
		Cnt = 0;
		missPercent = 0;
		data = new int[size];
		memset(data, -1, size*sizeof(int));
	}
	~FIFO()
	{
		delete[] data;
	}
	void showdata(void)
	{
		for (int i = 0; i < size; i++)
		{
			cout.width(2);
			cout << data[i] << " ";
		}
		cout << endl;
	}

	bool find(int elem)
	{
		cout << "置换前:";
		showdata();
		for (int i = 0; i < size; i++)
		if (data[i] == elem)
		{
			Cnt++;
			missPercent = 1.0*missCnt / Cnt;
			cout << "置换后:";
			showdata();
			return true;
		}
		for (int i = size - 1; i >0; i--)
			data[i] = data[i - 1];
		data[0] = elem;
		Cnt++;
		missCnt++;
		missPercent = 1.0*missCnt / Cnt;
		cout << "置换后:";
		showdata();
		return false;
	}


	int getCnt(void)
	{
		return Cnt;
	}
	int getMissCnt(void)
	{
		return missCnt;
	}
	double getMissPercent(void)
	{
		return missPercent;
	}
};

class LRU
{
private:
	int size;
	int *data;
	int missCnt;
	int Cnt;
	double missPercent;

public:
	LRU(int s)
	{
		size = s;
		data = new int[size];
		missCnt = 0;
		Cnt = 0;
		missPercent = 0;
		memset(data, -1, size*sizeof(int));
	}
	~LRU()
	{
		delete[] data;
	}
	void showdata(void)
	{
		for (int i = 0; i < size; i++)
		{
			cout.width(2);
			cout << data[i] << " ";
		}
		cout << endl;
	}

	bool find(int elem)
	{
		cout << "置换前:";
		showdata();
		for (int i = 0; i < size; i++)
		if (data[i] == elem)
		{
			Cnt++;
			for (int j = i; j>0; j--)
			{
				data[j] = data[j - 1];
			}
			data[0] = elem;
			missPercent = 1.0*missCnt / Cnt;
			cout << "置换后:"; 
			showdata();
			return true;
		}
		for (int j = size-1; j > 0; j--)
			data[j] = data[j - 1];
		data[0] = elem;
		Cnt++;
		missCnt++;
		missPercent = 1.0*missCnt / Cnt;
		cout << "置换后:";
		showdata();
		return false;
	}
	
	int getCnt(void)
	{
		return Cnt;
	}
	int getMissCnt(void)
	{
		return missCnt;
	}
	double getMissPercent(void)
	{
		return missPercent;
	}

};

int main()
{
	freopen("in.txt", "r", stdin);
	int t;
	cout << "请输入页面内存大小:";
	cin >> t;
	cout << t << endl;
	LRU lru(t);
	FIFO fifo(t);
	cout << endl << "请输入要查询的值:";
	while (cin >> t&&t != -1)
	{
		cout << t << endl << "LRU:" << endl;
		if (lru.find(t))
			cout << t << " 在页面中被命中\t";
		else
			cout << t << " 在页面中未命中\t";
		cout << "当前总共查询次数 " << lru.getCnt() << " 缺页次数 " << lru.getMissCnt()
			<< " 缺页率 ";
		cout.precision(3);
		cout<<lru.getMissPercent()*100<<"%" << endl;
		cout << endl << "FIFO:" << endl;
		if (fifo.find(t))
			cout << t << " 在页面中被命中\t";
		else
			cout << t << " 在页面中未命中\t";
		cout << "当前总共查询次数 " << fifo.getCnt() << " 缺页次数 " << fifo.getMissCnt()
			<< " 缺页率 ";
		cout.precision(3);
		cout << fifo.getMissPercent() * 100 << "%" << endl;
		cout << endl << "请输入要查询的值:";
	}
	return 0;
}