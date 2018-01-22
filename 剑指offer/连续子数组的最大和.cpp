class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
    	int current_max = INT_MIN, current = 0, size = array.size();
        if(size == 0)
            return current;
        for(int i = 0; i < size; i++)
        {
            if(current < 0)
                current = array[i];
            else
            	current += array[i];
            current_max = max(current_max, current);
        }
        return current_max;
    }
};
