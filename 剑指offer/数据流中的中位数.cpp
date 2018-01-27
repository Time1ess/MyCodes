#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<int> min_heap, max_heap;
    int cnt = 0;
public:
    void adjust_heap(vector<int> &h, bool is_max_heap)
    {
        if(!is_max_heap)
            std::push_heap(h.begin(), h.end(), greater<int>());
        else
            std::push_heap(h.begin(), h.end());
    }
    void push_heap(vector<int> &h, int num, bool is_max_heap=true)
    {
        h.push_back(num);
        adjust_heap(h, is_max_heap);
    }
    void pop_heap(vector<int> &h, bool is_max_heap=true)
    {
        std::pop_heap(h.begin(), h.end());
        h.pop_back();
        adjust_heap(h, is_max_heap);
    }
    void Insert(int num)
    {
        if(cnt == 0)
            push_heap(max_heap, num);
        else if(cnt & 0x1)
        {
            push_heap(max_heap, num);
            push_heap(min_heap, max_heap[0], false);
            pop_heap(max_heap);
        }
        else
        {
            push_heap(min_heap, num, false);
            push_heap(max_heap, min_heap[0]);
            pop_heap(min_heap, false);
        }
        cnt++;
    }

    double GetMedian()
    { 
    	if(cnt & 0x1)
			return max_heap[0];
        else
            return (double)(max_heap[0] + min_heap[0]) / 2;
    }

};

int main()
{
    vector<int> s{5,2,3,4,1,6,7,0,8};
    Solution sol;
    for(auto x: s)
    {
        sol.Insert(x);
        cout<<sol.GetMedian()<<endl;
    }
    return 0;
}
