class Solution {
public:
    /**
     * @param words: a string array
     * @return: the maximum product
     */
    int maxProduct(vector<string> &words) {
        // Write your code here
        vector<pair<int, int>> length_checksum_pairs;
        for(auto word: words) {
            int checksum = 0;
            for(auto c: word)
                checksum |= 1 << (c - 'a');
            length_checksum_pairs.push_back({word.length(), checksum});
        }
        int n = words.size();
        int ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                auto p1 = length_checksum_pairs[i];
                auto p2 = length_checksum_pairs[j];
                if((p1.second & p2.second) == 0)
                    ans = max(ans, p1.first * p2.first);
            }
        }
        return ans;
    }
};
