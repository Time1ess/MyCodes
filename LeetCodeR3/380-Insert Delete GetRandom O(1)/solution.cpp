class RandomizedSet {
private:
    unordered_map<int, int> pos;
    vector<int> nums;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (pos.find(val) != pos.end()) {
            return false;
        }
        pos[val] = nums.size();
        nums.push_back(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (pos.find(val) == pos.end()) {
            return false;
        }
        int n = nums.size();
        int pos_ = pos[val];
        swap(nums[n-1], nums[pos_]);
        nums.pop_back();
        pos[nums[pos_]] = pos_;
        pos.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
