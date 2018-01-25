class Solution {
public:
    int LastRemaining_Solution(int n, int m)
    {
        if(n < 1 || m < 1)
            return -1;
        list<int> children;
        for(int i = 0; i < n; i++)
            children.push_back(i);
        list<int>::iterator it = children.begin(), next;
        while(children.size() > 1)
        {
            for(int i = 1; i < m; i++)
            {
                ++it;
                if(it == children.end())
                    it = children.begin();
            }
            next = ++it;
            if(next == children.end())
                next = children.begin();
            --it;
            children.erase(it);
            it = next;
        }
        return *it;
    }
};
