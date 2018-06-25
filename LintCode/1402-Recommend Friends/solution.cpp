class Solution {
public:
    /**
     * @param friends: people's friends
     * @param user: the user's id
     * @return: the person who most likely to know
     */
    int commonFriends(unordered_set<int>& userFriends, const vector<int>& xFriends) {
        int cnt = 0;
        for(auto x: xFriends)
            if(userFriends.find(x) != userFriends.end())
                cnt++;
        return cnt;
    }

    int recommendFriends(vector<vector<int>> &friends, int user) {
        // Write your code here 
        int n = friends.size();
        unordered_set<int> userFriends;
        for(auto x: friends[user])
            userFriends.insert(x);
        int bestCnt = 0;
        int bestFriend = -1;
        for(int x = 0; x < n; x++) {
            if(x == user || userFriends.find(x) != userFriends.end())
                continue;
            int cnt = commonFriends(userFriends, friends[x]);
            if(cnt > bestCnt) {
                bestCnt = cnt;
                bestFriend = x;
            }
        }
        return bestFriend;
    }
};
