class Solution {
public:
    void reOrderArray(vector<int> &array) {
        int size = array.size();
        if(size == 0)
            return;
        int odd_cnt = 0;
        for(int i = 0; i < size; i++)
            if(array[i] & 0x1 == 1)
                odd_cnt ++;
        int index_odd = 0, index_even = odd_cnt;
        vector<int> tmp(size, 0);
        for(int i = 0; i < size; i++)
        {
            if(array[i] & 0x1 == 1)
                tmp[index_odd++] = array[i];
            else
                tmp[index_even++] = array[i];
        }
        for(int i = 0; i < size; i++)
            array[i] = tmp[i];
    }
};
