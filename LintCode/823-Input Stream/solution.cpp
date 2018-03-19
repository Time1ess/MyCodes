class Solution {
public:
    /**
     * @param inputA: Input stream A
     * @param inputB: Input stream B
     * @return: The answer
     */
    string inputStream(string &inputA, string &inputB) {
        // Write your code here
        stack<char> clean_a, clean_b;
        for(auto c: inputA)
            if(c != '<')
                clean_a.push(c);
            else if(!clean_a.empty())
                clean_a.pop();
        for(auto c: inputB)
            if(c != '<')
                clean_b.push(c);
            else if(!clean_b.empty())
                clean_b.pop();
        while(!clean_a.empty() && !clean_b.empty())
        {
            if(clean_a.top() != clean_b.top())
                return "NO";
            clean_a.pop();
            clean_b.pop();
        }
        return (clean_a.empty() && clean_b.empty()) ? "YES" : "NO";
    }
};
