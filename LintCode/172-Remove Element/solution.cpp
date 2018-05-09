class Solution {
public:
    /*
     * @param A: A list of integers
     * @param elem: An integer
     * @return: The new length after remove
     */
    int removeElement(vector<int> &A, int elem) {
        // write your code here
        int n = A.size();
        int read = 0, write = 0;
        while(read < n)
        {
            if(A[read] != elem)
                A[write++] = A[read];
            read++;
        }
        return write;
    }
};
