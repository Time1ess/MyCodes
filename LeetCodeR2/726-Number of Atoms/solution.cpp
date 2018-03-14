class Solution {
public:
    int parse_count(string &formula, int &s, int e, int base)
    {
        int count = 0;
        while(s <= e && formula[s] >= '0' && formula[s] <= '9')
            count = count * 10 + formula[s++] - '0';
        if(count == 0)
            count = 1;
        return count;
    }
    void countOfAtoms(map<string, int> &cnts, string &formula, int &s, int e, int base)
    {
        while(s <= e)
        {
            if(formula[s] >= 'A' && formula[s] <= 'Z')
            {
                // [A-Z][a-z]*\d*
                string key = "";
                key += formula[s++];
                while(s <= e && formula[s] >= 'a' && formula[s] <= 'z')
                    key.push_back(formula[s++]);
                cnts[key] += parse_count(formula, s, e, base);
            }
            else if(formula[s] == '(')
            {
                map<string, int> tmp_cnts;
                s++;
                countOfAtoms(tmp_cnts, formula, s, e, 1);
                // s should be at ')'
                s++;
                // Parse count
                int count = parse_count(formula, s, e, base);
                for(auto x: tmp_cnts)
                    cnts[x.first] += x.second * count;
            }
            else if(formula[s] == ')')
                return;
        }
    }
    string countOfAtoms(string formula) {
        int s = 0, e = formula.size() - 1;
        map<string, int> cnts;
        countOfAtoms(cnts, formula, s, e, 1);  // Atom-Cnt pair
        string ans = "";
        for(auto x: cnts)
            ans += x.first + (x.second != 1 ? to_string(x.second) : "");
        return ans;
    }
};
