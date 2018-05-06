#include <list>


class LFUCache {
private:
    unordered_map<int, list<int>> freqs;  // freq -> [key1, key2, ...]
    unordered_map<int, pair<int, int>> value_freq;  // key -> value, freq
    unordered_map<int, list<int>::iterator> pos;  // key -> pos
    int min_freq;
    int capacity;
public:
    /*
    * @param capacity: An integer
    */LFUCache(int capacity) {
        this->capacity = capacity;
        this->min_freq = 1;
        // do intialization if necessary
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        int old_value = get(key);
        if(this->capacity == 0)
            return;
        if(old_value != -1)
        {
            // Exists, Already updated frequency, just update value and return
            value_freq[key].first = value;
            return;
        }
        if(value_freq.size() == this->capacity)
        {
            // Full, Eject LFU item
            int delete_key = freqs[min_freq].back();
            freqs[min_freq].pop_back();
            value_freq.erase(delete_key);
            pos.erase(delete_key);
        }
        // Insert a new key-value pair
        min_freq = 1;
        value_freq[key] = {value, 1};
        freqs[min_freq].push_front(key);
        pos[key] = freqs[min_freq].begin();
    }

    /*
     * Get value with specified key, if exists, return value and update frequency,
     * If not exists, return -1.
     * 
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        auto it = value_freq.find(key);
        if(it == value_freq.end())
            return -1;
        int val = value_freq[key].first;
        int freq = value_freq[key].second;
        freqs[freq].erase(pos[key]);
        freqs[freq+1].push_front(key);
        pos[key] = freqs[freq+1].begin();
        value_freq[key].second = freq + 1;
        if(freqs[min_freq].size() == 0)
            min_freq++;
        return val;
    }
};
