bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.first > b.first || (a.first == b.first && a.second < b.second);
}

class Solution {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        vector<pair<int, int>> ans;
        if(people.empty())
            return ans;
        sort(people.begin(), people.end(), cmp);
        ans.push_back(people[0]);
        for(int i = 1; i < people.size(); i++)
        {
            int h = people[i].first;
            int k = people[i].second;
            int j = 0;
            for(; j < ans.size(); j++)
                if(j == k)
                    break;
            ans.insert(ans.begin() + j, people[i]);
        }
        return ans;
    }
};
