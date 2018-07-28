class Solution {
public:
    /*
     * @param strs: a list of strings
     * @return: encodes a list of strings to a single string.
     */
    string encode(vector<string> &strs) {
        // write your code here
        string ans = "";
        for(auto s: strs) {
            ans.append(to_string(s.length()) + "," + s);
        }
        return ans;
    }
    
    int read_length(const string& str, int& s, int e) {
        int ans = 0;
        while(s < e && str[s] != ',') {
            ans = ans * 10 + str[s] - '0';
            s++;
        }
        return ans;
    }

    /*
     * @param str: A string
     * @return: dcodes a single string to a list of strings
     */
    vector<string> decode(string &str) {
        // write your code here
        vector<string> ans;
        int s = 0;
        int e = str.length();
        while(s < e) {
            int len = read_length(str, s, e);
            s++;
            ans.push_back(str.substr(s, len));
            s += len;
        }
        return ans;
    }
};
