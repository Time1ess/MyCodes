class Solution {
public:
    pair<int, int> parse_fraction(const string &frac, int s, int e)
    {
        // [-/+]\d+/\d+
        pair<int, int> ans = {0, 0};
        bool neg = false;
        if(frac[s] == '-')
        {
            neg = true;
            s++;
        }
        else if(frac[s] == '+')
        {
            s++;
        }
        while(s < e && frac[s] != '/')
        {
            ans.first = ans.first * 10 + frac[s] - '0';
            s++;
        }
        if(neg)
            ans.first = -ans.first;
        s++;  // Skip slash
        while(s < e)
        {
            ans.second = ans.second * 10 + frac[s] - '0';
            s++;
        }
        return ans;
    }
    
    int gcd(int a, int b)
    {
        if(b == 0)
            return a;
        return gcd(b, a % b);
    }
    
    void merge_fraction(pair<int, int> &current, pair<int, int> &other)
    {
        if(current.second == 0)  // initialize
        {
            current = other;
            return;
        }
        else if(current.second == other.second)
        {
            current.first += other.first;
            if(current.first == 0)
                current.second = 0;
        }
        else
        {
            current.first = current.first * other.second + current.second * other.first;
            current.second *= other.second;
        }
        if(current.first == 0)
        {
            current.second = 0;
            return;
        }
        int g = gcd(abs(current.first), current.second);
        current.first /= g;
        current.second /= g;
    }
    
    string fractionAddition(string expression) {
        int length = expression.length();
        int s = 0;
        pair<int, int> current = {0, 0};
        while(s < length)
        {
            int e = s + 1;
            while(e < length && expression[e] != '+' && expression[e] != '-')
                e++;
            pair<int, int> tmp = parse_fraction(expression, s, e);
            merge_fraction(current, tmp);
            s = e;
        }
        if(current.first == 0)
            current.second = 1;
        string ans = to_string(current.first) + "/" + to_string(current.second);
        return ans;
    }
};
