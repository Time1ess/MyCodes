class Solution {
public:
    bool IsContinuous( vector<int> numbers ) {
        int size = numbers.size();
        if(size != 5)
            return false;
        sort(numbers.begin(), numbers.end());
        int cnt_joker = 0, cnt_gap = 0;
        int small = 0;
        while(small < size && numbers[small] == 0)
            cnt_joker++, small++;
        int big = small+1;
        while(big < size)
        {
            if(numbers[small] == numbers[big])
                return false;
            cnt_gap += numbers[big] - numbers[small] - 1;
            small = big;
            big++;
        }
        return cnt_joker >= cnt_gap;
    }
};
