class Solution {
public:
    /**
     * @param n: An integer
     * @return: A list of strings.
     */
    vector<string> fizzBuzz(int n) {
        // write your code here
        vector<string> ans;
        for(int i = 1; i <= n; i++)
            ans.push_back(
                i % 15 == 0 ?
                    "fizz buzz" :
                    i % 5 == 0 ?
                        "buzz" :
                        i % 3 == 0 ?
                            "fizz" :
                            to_string(i)
                );
        return ans;
    }
};
