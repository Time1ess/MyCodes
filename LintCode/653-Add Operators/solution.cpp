class Solution {
public:
    /*
     * @param num: a string contains only digits 0-9
     * @param target: An integer
     * @return: return all possibilities
     */
    void dfs(const string &num, const int target, vector<string> &ans,
             string cur_s, long long cur, int idx, int pv, char op)
    {
        if(idx == num.size() && cur == target)
        {
            ans.push_back(cur_s);
            return;
        }
        else
        {
            for(int k = idx+1; k <= num.size(); k++)
            {
                string n = num.substr(idx, k - idx);
                long long v = stol(n);
                if(to_string(v).size() != n.size())
                    continue;
                dfs(num, target, ans, cur_s+"+"+n, cur+v, k, v, '+');
                dfs(num, target, ans, cur_s+"-"+n, cur-v, k, v, '-');
                long long new_cur = cur;
                if(op == '+')  // cur: xxx+pv -> xxx+pv - pv + pv * v
                    new_cur = cur - pv + pv * v;
                else if(op == '-')  // cur: xxx-pv -> xxx-pv + pv - pv * v
                    new_cur = cur + pv - pv * v;
                else  // init case, match #
                    new_cur = pv * v;
                dfs(num, target, ans, cur_s+"*"+n, new_cur, k, pv * v, op);
            }
        }
    }
    vector<string> addOperators(string &num, int target) {
        vector<string> ans;
        for(int k = 1; k <= num.size(); k++)
        {
            string n = num.substr(0, k);
            long long v = stol(n);
            if(to_string(v).size() != n.size())
                break;
            dfs(num, target, ans, n, v, k, v, '#');
        }
        return ans;
    }
};
