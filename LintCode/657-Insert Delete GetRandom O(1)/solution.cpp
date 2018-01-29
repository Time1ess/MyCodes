class RandomizedSet {
private:
    unordered_map<int, int> positions;
    vector<int> items;
public:
    RandomizedSet() {
        // do intialization if necessary
    }

    /*
     * @param val: a value to the set
     * @return: true if the set did not already contain the specified element or false
     */
    bool insert(int val) {
        // write your code here
        if(positions.find(val) != positions.end())
            return false;
        positions[val] = items.size();
        items.push_back(val);
        return true;
    }

    /*
     * @param val: a value from the set
     * @return: true if the set contained the specified element or false
     */
    bool remove(int val) {
        // write your code here
        if(positions.find(val) == positions.end())
            return false;
        items[positions[val]] = items.back();
        positions[items.back()] = positions[val];
        items.pop_back();
        return true;
    }

    /*
     * @return: Get a random element from the set
     */
    int getRandom() {
        // write your code here
        return items[rand() % items.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param = obj.insert(val);
 * bool param = obj.remove(val);
 * int param = obj.getRandom();
 */
