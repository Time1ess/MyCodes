// 快速排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

int RandomInRange(int start, int end)
{
	return rand() % (end - start) + start;
}

void Swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

//使用第一个数据作为基准数
void quick_sort(int *a, int start,int end)
{
	int size = end - start;
	if (a == NULL || size <= 0)
		return;
	int i=start, j=end-1, key=a[start];
	while (i<j)
	{
		while (i < j&&a[j] > key)--j;
		a[i] = a[j];
		while (i < j&&a[i] < key)++i;
		a[j] = a[i];
	}
	a[i] = key;
	quick_sort(a, start, i - 1);
	quick_sort(a, i + 1, end);
}


//使用随机数作为基准数
int Partition(int data[], int length, int start, int end)
{
	//抛出异常
	if (data == NULL || length <= 0 || start < 0 || end >= length)
		throw exception("Invalid Parameters");
	//产生一个随机位置
	int index = RandomInRange(start,end);

	//将该位置与最后一个元素交换
	Swap(&data[index], &data[end]);

	int small = start - 1;
	//++small指向上一次交换之后的下一个位置，若
	//data[index]小于data[end]则交换
	//small之前的全部都是小于data[end]的元素
	for (index = start; index < end; index++)
	{
		if (data[index] < data[end])
		{
			++small;
			if (small != index)
				Swap(&data[index], &data[small]);
		}
	}
	++small;
	Swap(&data[small], &data[end]);
	//完成了以上交换后，small之前全部为小于data[small]的元素
	//small之后全部为大于data[small]的元素

	return small;
}

void QuickSort(int data[], int length, int start, int end)
{
	if (start == end)
		return;

	int index = Partition(data, length, start, end);
	if (index > start)
		QuickSort(data, length, start, index - 1);
	if (index < end)
		QuickSort(data, length, index + 1, end);
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned)time(NULL));

	int a[] = { 2,3,1,8,6,7,4 };
	//quick_sort(a, 0, 5);
	QuickSort(a, 7, 0, 6);
	for (int i = 0; i < 7;i++)
		cout << a[i] << " ";
	cin.get();
	return 0;
}

