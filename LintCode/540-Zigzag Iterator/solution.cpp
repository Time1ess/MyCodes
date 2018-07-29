class ZigzagIterator {
private:
    vector<int>::iterator iter1, iter2, iter1_end, iter2_end;
    bool return_iter1;
public:
    /*
    * @param v1: A 1d vector
    * @param v2: A 1d vector
    */ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        // do intialization if necessary
        return_iter1 = true;
        iter1 = v1.begin();
        iter1_end = v1.end();
        iter2 = v2.begin();
        iter2_end = v2.end();
    }

    /*
     * @return: An integer
     */
    int next() {
        // write your code here
        int x;
        if((return_iter1 && iter1 != iter1_end) || iter2 == iter2_end) {
            x = *iter1;
            ++iter1;
        } else {
            x = *iter2;
            ++iter2;
        }
        return_iter1 = !return_iter1;
        return x;
    }

    /*
     * @return: True if has next
     */
    bool hasNext() {
        // write your code here
        if(iter1 == iter1_end && iter2 == iter2_end) {
            return false;
        }
        return true;
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator solution(v1, v2);
 * while (solution.hasNext()) result.push_back(solution.next());
 * Ouptut result
 */
