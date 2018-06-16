class Solution {
public:
    /**
     * @param s: a string
     * @return: return a string
     */
    string removeDuplicateLetters(string &s) {
        // write your code here
        int cnts[256];
        for(auto c: s)
            cnts[c]++;
        stack<char> st;
        bool inStack[256] = {false};
        for(auto c: s) {
            if(!inStack[c]) {
                while(!st.empty() && st.top() > c && cnts[st.top()] > 0) {
                    inStack[st.top()] = false;
                    st.pop();
                }
                inStack[c] = true;
                st.push(c);
            }
            cnts[c]--;
        }
        string ans = "";
        while(!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
