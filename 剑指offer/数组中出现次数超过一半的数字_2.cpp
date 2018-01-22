class Solution {
public:
    bool more_than_half(vector<int> &numbers, int number)
    {
        int cnt = 0, size = numbers.size();
        for(int i = 0; i < size; i++)
        	if(numbers[i] == number)
                cnt++;
        return cnt * 2 > size;
    }
    int MoreThanHalfNum_Solution(vector<int> numbers) {
    	int size = numbers.size();
        if(size == 0)
            return 0;
        int number = numbers[0];
        int cnt = 1;
        for(int i = 1; i < size; i++)
            if(cnt == 0)
            {
                cnt = 1;
                number = numbers[i];
            }
        	else
                cnt += number == numbers[i] ? 1 : -1;
        if(!more_than_half(numbers, number))
            return 0;
        return number;
    }
};
