struct Item
{
    vector<int>::iterator cur, end;
    Item(vector<int>::iterator cur, vector<int>::iterator end)
    {
        this->cur = cur;
        this->end = end;
    }
    bool operator<(const Item &other) const
    {
        return *cur > *(other.cur);
    }
};

class Solution {
public:
    /**
     * @param arrays: k sorted integer arrays
     * @return: a sorted array
     */
    vector<int> mergekSortedArrays(vector<vector<int>> &arrays) {
        // write your code here
        vector<int> ans;
        priority_queue<Item> pq;
        int n = arrays.size();
        for(int i = 0; i < n; i++)
        {
            if(arrays[i].begin() != arrays[i].end())
            {
                Item item(arrays[i].begin(), arrays[i].end());
                pq.push(item);
            }
        }
        while(!pq.empty())
        {
            Item item = pq.top();
            pq.pop();
            ans.push_back(*(item.cur));
            ++(item.cur);
            if(item.cur != item.end)
                pq.push(item);
        }
        return ans;
    }
};
