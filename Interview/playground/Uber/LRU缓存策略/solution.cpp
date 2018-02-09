#include <list>

class LRUCache {
private:
    typedef list<int> LI;  // value
    typedef pair<int, LI::iterator> PLI;
    typedef unordered_map<int, PLI> UMILI;
    
    UMILI store;
    LI lru;
    int capacity;
public:
    /*
    * @param capacity: An integer
    */LRUCache(int capacity) {
        // do intialization if necessary
        this->capacity = capacity;
    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        auto it = store.find(key);
        if(it == store.end())
            return -1;
        update(it);
        return (it->second).first;
        // write your code here
    }
    
    void update(UMILI::iterator it)
    {
        int key = it->first;
        lru.erase(it->second.second);
        lru.push_front(key);
        it->second.second = lru.begin();
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        // write your code here
        auto it = store.find(key);
        if(it == store.end())
        {
            if(lru.size() == capacity)
            {
                store.erase(lru.back());
                lru.pop_back();
            }
            lru.push_front(key);
        }
        else
            update(it);
        store[key] = {value, lru.begin()};
    }
};
