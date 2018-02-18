class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int n = letters.size();
        if(target >= letters[n - 1])
            return letters[0];
        else
            target++;
        int l = 0, r = n;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(letters[m] == target)
                return target;
            else if(letters[m] > target)
                r = m;
            else
                l = m + 1;
        }
        return letters[l];
    }
};
