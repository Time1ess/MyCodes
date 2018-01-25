class Tmp
{
public:
    static int N;
    static int sum;
    
    Tmp()
    {
        ++N;
        sum += N;
    }
    
    static void Reset()
    {
        N = 0;
        sum = 0;
    }
};

int Tmp::N = 0;
int Tmp::sum = 0;

class Solution {
public:
    int Sum_Solution(int n) {
        Tmp::Reset();
        
        Tmp *a = new Tmp[n];
        delete[] a;
        a = NULL;
        return Tmp::sum;
    }
};
