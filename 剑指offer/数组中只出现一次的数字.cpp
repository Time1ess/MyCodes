class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
		int xor_all = 0;
        int size = data.size();
        for(int i = 0; i < size; i++)
            xor_all ^= data[i];
        int group_0 = 0, group_1 = 0;
        int mask = 0;
        int cnt = 0;
        while(!(mask & xor_all))
            mask = 1 << (cnt++);
        for(int i = 0; i < size; i++)
            if(data[i] & mask)
                group_1 ^= data[i];
            else
                group_0 ^= data[i];
        *num1 = group_0;
        *num2 = group_1;
    }
};
