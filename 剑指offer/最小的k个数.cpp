class Solution {
public:
    int partition(vector<int> &input, int start, int end)
    {
        if(start >= end)
            return start;
        int index = start + rand() % (end - start);
        swap(input[index], input[end]);
        int small = start - 1;
        for(index = start; index < end; index++)
            if(input[index] < input[end])
            {
                ++small;
                if(small != index)
                    swap(input[index], input[small]);
            }
        ++small;
        swap(input[small], input[end]);
        return small;
    }
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        int size = input.size();
        vector<int> ans;
        if(size < k)
            return ans;
        else if(size == k)
            return input;
        int start = 0, end = size - 1;
        int index = partition(input, start, end);
        while(index != k)
        {
            if(index > k)
                end = index - 1;
            else
                start = index + 1;
            index = partition(input, start, end);
        }
        for(int i = 0; i < index; i++)
            ans.push_back(input[i]);
        return ans;
    }
};
