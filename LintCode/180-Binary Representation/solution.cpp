class Solution {
public:
    /**
     * @param n: Given a decimal number that is passed in as a string
     * @return: A string
     */
    string int_to_bin(string s)
    {
        string ans = "";
        while(s.length() != 0)
        {
            int n = s.length();
            if((s[n-1] - '0') % 2 == 1)
                ans.push_back('1');
            else
                ans.push_back('0');
            string new_s = "";
            bool pre = false;
            for(int i = 0; i < n; i++)
            {
                int t = s[i] - '0' + (pre ? 10 : 0);
                new_s.push_back(t / 2 + '0');
                if(t % 2 == 1)
                    pre = true;
                else
                    pre = false;
            }
            int k = 0;
            while(k < new_s.length() && new_s[k] == '0')
                k++;
            s = new_s.substr(k);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
    string frac_to_bin(string s)
    {
        string ans = "";
        int cnt = 0;
        while(s.length() != 0 && cnt < 32)
        {
            cnt++;
            string new_s = "";
            int n = s.length();
            bool adding = false;
            for(int i = n - 1; i >= 0; i--)
            {
                int t = (s[i] - '0') * 2 + (adding ? 1 : 0);
                new_s.push_back(t % 10 + '0');
                if(t >= 10)
                    adding = true;
                else
                    adding = false;
            }
            reverse(new_s.begin(), new_s.end());
            if(adding)
                ans.push_back('1');
            else
                ans.push_back('0');
            s = new_s;
            bool all_zero = true;
            for(int i = 0; i < s.length(); i++)
                if(s[i] != '0')
                {
                    all_zero = false;
                    break;
                }
            if(all_zero)
                break;
        }
        if(cnt == 32 && s.length() != 0)
            return "ERROR";
        return ans;
    }
    string binaryRepresentation(string &s) {
        // write your code here
        auto dot_loc = s.find('.');
        if(dot_loc == string::npos)
            return int_to_bin(s);
        else
        {
            string int_part = s.substr(0, dot_loc);
            string frac_part = s.substr(dot_loc + 1);
            string int_bin = int_to_bin(int_part);
            string frac_bin = frac_to_bin(frac_part);
            if(frac_bin == "ERROR")
                return "ERROR";
            else if(frac_bin == "0")
                return int_bin;
            else
                return int_bin + "." + frac_bin;
        }
    }
};
