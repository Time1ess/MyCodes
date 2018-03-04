class LRUCache {
private:
    list<int> lru;
    unordered_map<int, pair<int, list<int>::iterator>> data;
    int capacity;
    
public:
    LRUCache(int capacity) {
        this->capacity = capacity;    
    }
    
    void touch(unordered_map<int, pair<int, list<int>::iterator>>::iterator it)
    {
        int key = it->first;
        lru.erase(it->second.second);
        lru.push_front(key);
        it->second.second = lru.begin();
    }
    
    int get(int key) {
        auto it = data.find(key);
        if(it == data.end())
            return -1;
        touch(it);
        return it->second.first;
    }
    
    void put(int key, int value) {
        auto it = data.find(key);
        if(it != data.end())
        {
            touch(it);
            it->second.first = value;
        }
        else
        {
            if(lru.size() == capacity)
            {
                data.erase(lru.back());
                lru.pop_back();
            }
            lru.push_front(key);
            data[key] = {value, lru.begin()};
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
