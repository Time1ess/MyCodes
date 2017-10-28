class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        unordered_map<int, set<int>> reqs, childs;
        for(auto x: prerequisites)
        {
            reqs[x.first].insert(x.second);
            childs[x.second].insert(x.first);
        }
        queue<int> availables;
        for(int i = 0; i < numCourses; i++)
            if(reqs[i].size() == 0)
                availables.push(i);
        vector<int> ans;
        while(!availables.empty())
        {
            int course = availables.front();
            availables.pop();
            ans.push_back(course);
            for(auto child: childs[course])
            {
                reqs[child].erase(course);
                if(reqs[child].size() == 0)
                    availables.push(child);
            }
        }
        if(ans.size() == numCourses)
            return ans;
        else
            return vector<int>();
    }
};
