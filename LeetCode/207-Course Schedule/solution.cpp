// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-20 10:40
// Last modified: 2017-09-20 10:40
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool can_finish(int &numCourses, int course, unordered_map<int, vector<int>>& edges, vector<int>& visited)
    {
        if(course == numCourses)
            return true;
        visited[course] = 1;
        for(int i = 0; i < edges[course].size(); i++)
        {
            if(visited[edges[course][i]] == 2)
                continue;
            else if(visited[edges[course][i]] == 1)
                return false;
            else if(can_finish(numCourses, edges[course][i], edges, visited) == false)
                return false;
        }
        visited[course] = 2;
        return true;
    }
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        unordered_map<int, vector<int>> edges;
        vector<int> visited(numCourses, 0);
        for(auto x: prerequisites)
            edges[x.first].push_back(x.second);
        for(int i = 0; i < numCourses; i++)
            if(!can_finish(numCourses, i, edges, visited))
                return false;
        return true;
    }
};
