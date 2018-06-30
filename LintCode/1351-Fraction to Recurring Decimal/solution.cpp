class Solution {
public:
    /**
     * @param numerator: a integer
     * @param denominator: a integer
     * @return: return a string
     */
    string fractionToDecimal(int numerator, int denominator) {
        // write your code here
        if(numerator % denominator == 0)
            return to_string(numerator / denominator);
        unordered_map<int, int> divs;
        unordered_map<int, int> occurance;
        string first;
        if (numerator > denominator) {
            first = to_string(numerator / denominator);
            numerator %= denominator;
        } else {
            first = "0";
        }
        // numerator < denominator
        int x = numerator;
        int idx = 0;
        while(x != 0 && occurance.find(x) == occurance.end()) {
            occurance[x] = idx++;
            x *= 10;
            divs[x] = x / denominator;
            x %= denominator;
        }
        string second = "";
        if(x != 0) {
            // Repeated pattern found. 
            // Pattern from [occurance[x], idx) is repeated
            int start = occurance[x];
            int end = idx;
            x = numerator;
            for(int i = 0; i < end; i++) {
                x *= 10;
                if(i == start)
                    second.push_back('(');
                second.push_back('0' + x / denominator);
                x %= denominator;
            }
            second.push_back(')');
        } else {
            // Full devided.
            x = numerator;
            while(x != 0) {
                x *= 10;
                second.push_back('0' + x / denominator);
                x %= denominator;
            }
        }
        return first + "." + second;
    }
};
