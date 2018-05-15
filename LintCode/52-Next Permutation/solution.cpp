class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers
     */
    vector<int> nextPermutation(vector<int> &nums) {
        // write your code here
        vector<int>::iterator first = nums.begin(), last = nums.end();
        if(first == last)
            return nums;
        vector<int>::iterator i = last;
        if(first == --i)
            return nums;
        while(true)
        {
            vector<int>::iterator l1 = i;
            if(*--i < *l1)
            {
                vector<int>::iterator l2 = last;
                while(*i >= *--l2)
                    ;
                iter_swap(i, l2);
                reverse(l1, last);
                return nums;
            }
            if(i == first)
            {
                reverse(first, last);
                return nums;
            }
        }
    }
};
