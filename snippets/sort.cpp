#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <ios>
#include <iomanip>

using namespace std;


int partition(vector<int> &a, int start, int end)
{
    int index = rand() % (end - start) + start;
    swap(a[index], a[end]);

    int small = start - 1;
    for(index = start; index < end; index++)
    {
        if(a[index] < a[end])
        {
            ++small;
            if(index != small)
                swap(a[index], a[small]);
        }
    }
    ++small;
    swap(a[small], a[end]);

    return small;
}

void quick_sort(vector<int> &a, int start, int end)
{
    if(start >= end || start < 0 || a.size() == 0)
        return;
    int index = partition(a, start, end);
    if(index > start)
        quick_sort(a, start, index - 1);
    if(index < end)
        quick_sort(a, index + 1, end);
}

void bubble_sort(vector<int> &a)
{
    int size = a.size();
    if(size == 0 || size == 1)
        return;
    for(int i = 0; i < size; i++)
        for(int j = i + 1; j < size; j++)
            if(a[i] > a[j])
                swap(a[i], a[j]);
}

void insertion_sort(vector<int> &a)
{
    int size = a.size();
    if(size == 0 || size == 1)
        return;
    for(int i = 1; i < size; i++)
    {
        int j = i;
        int tmp = a[i];
        while(j > 0 && tmp < a[j - 1])
        {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = tmp;
    }
}

void select_sort(vector<int> &a)
{
    int size = a.size();
    if(size == 0 || size == 1)
        return;
    for(int i = 0; i < size; i++)
    {
        int k = i;
        for(int j = i + 1; j < size; j++)
            if(a[j] < a[k])
                k = j;
        swap(a[i], a[k]);
    }
}

void heap_sort(vector<int> &a)  // Max-heap
{
    int size = a.size();
    if(size == 0 || size == 1)
        return;
    int unsorted = a.size();
    while(unsorted > 1)
    {
        // Adjust
        for(int i = unsorted / 2; i >= 1; i--) // Indices are zero-based
        {
            if(a[i - 1] < a[2 * i - 1])
                swap(a[i - 1], a[2 * i - 1]);
            if((2 * i + 1 - 1) < unsorted && a[i - 1] < a[2 * i + 1 - 1])
                swap(a[i - 1], a[2 * i + 1 - 1]);
        }
        // Pop and swap with last elem
        swap(a[0], a[unsorted - 1]);
        // Unsorted--
        unsorted--;
    }
}

void merge(vector<int> &a, int s, int m, int e)
{
    if(s >= m || m >= e)
        return;
    vector<int> tmp(e - s, 0);
    int ts = s, tm = m, i = 0;
    while(ts < m && tm < e)
        if(a[ts] < a[tm])
            tmp[i++] = a[ts++];
        else
            tmp[i++] = a[tm++];
    while(ts < m)
        tmp[i++] = a[ts++];
    while(tm < e)
        tmp[i++] = a[tm++];
    i = 0;
    while(s < e)
        a[s++] = tmp[i++];
}

void merge_sort(vector<int> &a, int start, int end)
{
    if(start + 1 >= end)
        return;
    int m = (end - start) / 2 + start;
    merge_sort(a, start, m);
    merge_sort(a, m, end);
    merge(a, start, m, end);
}

void cout_array(const vector<int> &a, bool sorted, string header="")
{
    if(header != "")
        cout<<left<<setw(20)<<header<<" ";
    if(sorted)
        cout<<" Sorted: ";
    for(unsigned long i = 0; i < a.size(); i++)
        cout<<a[i]<<" ";
    if(sorted)
        cout<<endl;
}


int main()
{
    vector<int> a = {1,7,6,5,2,3,4,6,8,9,2,3,4,1,9,0,4,5,3,2};
    vector<int> b;

    b = a;
    cout_array(b, false, "[Quick Sort]");
    quick_sort(b, 0, 19);
    cout_array(b, true);

    b = a;
    cout_array(b, false, "[Bubble Sort]");
    bubble_sort(b);
    cout_array(b, true);

    b = a;
    cout_array(b, false, "[Insertion sort]");
    insertion_sort(b);
    cout_array(b, true);

    b = a;
    cout_array(b, false, "[Select Sort]");
    select_sort(b);
    cout_array(b, true);

    b = a;
    cout_array(b, false, "[Heap Sort]");
    heap_sort(b);
    cout_array(b, true);

    b = a;
    cout_array(b, false, "[Merge Sort]");
    merge_sort(b, 0, b.size());
    cout_array(b, true);
    return 0;
}
