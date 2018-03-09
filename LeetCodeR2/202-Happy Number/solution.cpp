class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> used;
        while(n != 1)
        {
            if(used.find(n) != used.end())
                return false;
            else
                used.insert(n);
            int t = 0, p = 0;
            while(n)
            {
                p = n % 10;
                t += p * p;
                n /= 10;
            }
            n = t;
            cout<<n<<endl;
        }
        return true;
    }
};
