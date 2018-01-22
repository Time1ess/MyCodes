class Solution {
public:
    int partition(vector<int> &numbers, int start, int end)
    {
        if(start >= end)
            return start;
        int pivot = start + rand() % (end - start);
        swap(numbers[pivot], numbers[end]);
        
        int small = start - 1;
        for(int i = start; i < end; i++)
        {
        	if(numbers[i] < numbers[end])
            {
            	++small;
                if(i != small)
                    swap(numbers[small], numbers[i]);
            }
        }
        ++small;
        swap(numbers[small], numbers[end]);
        return small;
    }
    
    bool more_than_half(vector<int> &numbers, int &res)
    {
        int cnt = 0;
        int size = numbers.size();
        for(int i = 0; i < size; i++)
            if(numbers[i] == res)
                cnt++;
        return (cnt * 2) > size;
    }
    
    int MoreThanHalfNum_Solution(vector<int> numbers) {
    	int size = numbers.size();
        if(size == 0)
            return 0;
        int mid = size >> 1;
        int start = 0, end = size - 1;
        int index = partition(numbers, start, end);
        while(index != mid)
        {
            if(index < mid)
            	start = index + 1;
            else
                end = index - 1;
            index = partition(numbers, start, end);
        }
        int res = numbers[mid];
        if(!more_than_half(numbers, res))
            return 0;
        return res;
    }
};
