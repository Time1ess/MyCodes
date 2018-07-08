class Finder {
public:
    int findString(vector<string> str, int n, string x) {
        // write code here
        int l = 0, r = n;
        while(l < r) {
            while(l < r && str[l] == "")
                l++;
            while(l < r && str[r-1] == "")
                r--;
            if(l >= r)
                return -1;
            int m = l + (r - l) / 2;
            while(m > l && str[m] == "")
                m--;
            if(m == l) {
                m = l + (r - l) / 2;
                while(m < r && str[m] == "")
                    m++;
                if(m == r)
                    return -1;
            }
            if(str[m] == x)
                return m;
            else if(str[m] < x)
                l = m + 1;
            else
                r = m;
            
        }
        return l;
    }
};
