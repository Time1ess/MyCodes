class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> deadends_set;
        unordered_set<string> tried;
        for(auto x: deadends)
            deadends_set.insert(x);
        unordered_map<string, string> relations;
        relations["0000"] = "0000";
        queue<string> codes;
        codes.push("0000");
        string s;
        bool found = false;
        while(!codes.empty())
        {
            s = codes.front();
            codes.pop();
            // Found
            if(s == target)
            {
                found = true;
                break;
            }
            // Deadends or tried already
            if(tried.find(s) != tried.end() || deadends_set.find(s) != deadends_set.end())
                continue;
            tried.insert(s);
            string origin_s = s;
            // Generates other ways
            for(int i = 0; i < 4; i++)
            {
                s[i] = '0' + (s[i] - '0' + 1) % 10;
                codes.push(s);
                if(relations.find(s) == relations.end())
                    relations[s] = origin_s;
                s[i] = '0' + (s[i] - '0' + 9) % 10;
                s[i] = '0' + (s[i] - '0' + 9) % 10;
                codes.push(s);
                if(relations.find(s) == relations.end())
                    relations[s] = origin_s;
                s[i] = '0' + (s[i] - '0' + 1) % 10;
            }
        }
        if(!found)
            return -1;
        int length = 0;
        while(relations[s] != s)
        {
            length++;
            s = relations[s];
        }
        return length;
    }
};
