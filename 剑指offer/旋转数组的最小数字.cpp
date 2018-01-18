class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int size = rotateArray.size();
        if(size == 0)
            return 0;
        int s = 0, e = size - 1;
        while(s < e)
        {
        	int m = (e - s) / 2 + s;
            if(rotateArray[m] < rotateArray[e])
                e = m;
            else if(rotateArray[m] > rotateArray[e])
                s = m + 1;
            else
                e--;
        }
        return rotateArray[s];
    }
};


