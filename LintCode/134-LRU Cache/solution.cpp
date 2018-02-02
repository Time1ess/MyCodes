#include <list>

using namespace std;

class LRUCache {
private:
    typedef list<int> LI;
    typedef pair<int, LI::iterator> PII;
    typedef unordered_map<int, PII> UMPII;
    LI lru; // key
    UMPII keys;  //key : {val, pos}
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
        // write your code here
        auto it = keys.find(key);
        if(it == keys.end())
            return -1;
        update(it);
        return it->second.first;
    }
    
    void update(UMPII::iterator it)
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
        auto it = keys.find(key);
        if(it != keys.end())
            update(it);
        else
        {
            if(lru.size() == capacity)
            {
                keys.erase(lru.back());
                lru.pop_back();
            }
            lru.push_front(key);
        }
        keys[key] = {value, lru.begin()};
    }
};
