#include <list>

class RandomizedSet {
private:
    list<int> vals;
    unordered_map<int, list<int>::iterator> storage;
    
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(storage.find(val) != storage.end())
            return false;
        vals.push_back(val);
        storage[val] = --vals.end();
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(storage.find(val) == storage.end())
            return false;
        vals.erase(storage[val]);
        storage.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int val = vals.front();
        int k = 2;
        list<int>::iterator it = ++vals.begin();
        while(it != vals.end())
        {
            int idx = rand() % k;
            if(idx == 0)
                val = *it;
            k++;
            ++it;
        }
        return val;
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
