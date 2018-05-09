class Solution {
public:
    /**
     * @param numbers: An array of Integer
     * @param target: target = numbers[index1] + numbers[index2]
     * @return: [index1 + 1, index2 + 1] (index1 < index2)
     */
    vector<int> twoSum(vector<int> &numbers, int target) {
        // write your code here
        unordered_map<int, int> val_pos;
        int n = numbers.size();
        for(int i = 0; i < n; i++)
        {
            if(val_pos.find(target-numbers[i]) != val_pos.end())
                return {val_pos[target-numbers[i]], i};
            val_pos[numbers[i]] = i;
        }
        return {-1, -1};
    }
};
