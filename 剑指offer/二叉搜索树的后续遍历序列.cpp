class Solution {
public:
    bool is_binary_post_order(vector<int> &sequence, int start, int end)
    {
        if(start >= end)
            return true;
        int k = start;
        while(k < end && sequence[k] < sequence[end])
            k++;  // [start, k - 1]
        int j = k;
        while(j < end && sequence[j] > sequence[end])
            j++;  // [k, j - 1]
        if(j != end)
            return false;
        return is_binary_post_order(sequence, start, k - 1) && is_binary_post_order(sequence, k, j - 1);
    }
    bool VerifySquenceOfBST(vector<int> sequence) {
		int size = sequence.size();
        if(size == 0)
            return false;
        else if(size == 1)
            return true;
        else
            return is_binary_post_order(sequence, 0, size - 1);
    }
};
