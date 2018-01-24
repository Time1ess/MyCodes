class Solution {
public:
    bool IsContinuous( vector<int> numbers ) {
        int size = numbers.size();
        if(size != 5)
            return false;
        sort(numbers.begin(), numbers.end());
        int cnt_joker = 0;
        int i = 0;
        bool expectation_set = false;
        int expectation = -1;
        while(i < size)
        {
            if(numbers[i] == 0)
                cnt_joker++;
            else
            {
                if(!expectation_set)
                {
                    expectation_set = true;
                    expectation = numbers[i];
                }
                else if(numbers[i] != expectation)
                    if(cnt_joker != 0)
                    {
                        cnt_joker--;
                        expectation++;
                        continue;
                    }
                    else
                        return false;
                expectation++;
            }
            i++;
        }
        return true;
    }
};
