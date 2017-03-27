// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-27 10:50
// Last modified: 2017-03-27 10:50
// Filename: solution.cpp
// Description:
class RandomizedSet {
private:
    unordered_map<int, int> showup;
    vector<int> nums;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(showup.find(val) != showup.end())
            return false;
        showup[val] = nums.size();
        nums.push_back(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(showup.find(val) == showup.end())
            return false;
        nums[showup[val]] = nums.back();
        showup[nums.back()] = showup[val];
        nums.pop_back();
        showup.erase(val);
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
