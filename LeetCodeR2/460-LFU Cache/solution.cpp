#include <list>

class LFUCache {
    unordered_map<int, pair<int, int>> value_freq;  // {value, freq}
    unordered_map<int, list<int>::iterator> iters;
    unordered_map<int, list<int>> freq_list;
    int capacity;
    int min_freq = 1;
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if(value_freq.find(key) == value_freq.end())
            return -1;
        freq_list[value_freq[key].second].erase(iters[key]);
        int freq = ++value_freq[key].second;
        freq_list[freq].push_back(key);
        iters[key] = --freq_list[freq].end();
        
        if(freq_list[min_freq].size() == 0)
            min_freq++;
        return value_freq[key].first;
    }
    
    void put(int key, int value) {
        if(capacity <= 0)
            return;
        int v = get(key);
        if(v != -1)
        {
            value_freq[key].first = value;
            return;
        }
        
        if(value_freq.size() == capacity)
        {
            int deleted_key = freq_list[min_freq].front();
            freq_list[min_freq].pop_front();
            iters.erase(deleted_key);
            value_freq.erase(deleted_key);
        }
        
        value_freq[key] = {value, 1};
        min_freq = 1;
        freq_list[min_freq].push_back(key);
        iters[key] = --freq_list[min_freq].end();
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
