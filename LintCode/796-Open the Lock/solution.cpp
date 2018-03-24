class Solution {
public:
    /**
     * @param deadends: the list of deadends
     * @param target: the value of the wheels that will unlock the lock
     * @return: the minimum total number of turns 
     */
    string rotate(string current, int idx, bool larger)
    {
        int new_wheel = current[idx] - '0' + (larger ? 1 : -1);
        if(new_wheel < 0)
            new_wheel += 10;
        new_wheel %= 10;
        current[idx] = new_wheel + '0';
        return current;
    }
    void push_next(unordered_set<string> &visited,
                   unordered_set<string> &deads,
                   queue<pair<string, int>> &combs,
                   string next, int costs)
    {
        if(visited.find(next) != visited.end() || deads.find(next) != deads.end())
            return;
        visited.insert(next);
        combs.push({next, costs});
    }
    int openLock(vector<string> &deadends, string &target) {
        // Write your code here
        unordered_set<string> visited, deads;
        for(auto deadend: deadends)
            deads.insert(deadend);
        if(deads.find("0000") != deads.end())
            return -1;
        queue<pair<string, int>> combs;
        combs.push({"0000", 0});
        visited.insert("0000");
        string next;
        pair<string, int> current;
        while(!combs.empty())
        {
            current = combs.front();
            combs.pop();
            if(current.first == target)
                break;
            for(int i = 0; i < 4; i++)
            {
                next = rotate(current.first, i, true);
                push_next(visited, deads, combs, next, current.second + 1);
                next = rotate(current.first, i, false);
                push_next(visited, deads, combs, next, current.second + 1);
            }
        }
        if(current.first == target)
            return current.second;
        return -1;
    }
};
