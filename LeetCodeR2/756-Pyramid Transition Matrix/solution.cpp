class Solution {
public:
    bool pyramidTransition(string bottom, string current, map<pair<char, char>, vector<char>> &trans, int idx)
    {
        if(bottom.length() == 1)
            return true;
        if(idx == bottom.length() - 1)
            return pyramidTransition(current, "", trans, 0);
        if(trans.find({bottom[idx], bottom[idx+1]}) == trans.end())
            return false;
        bool can_trans = false;
        for(auto c: trans[{bottom[idx], bottom[idx+1]}])
            can_trans = can_trans || pyramidTransition(bottom, current+c, trans, idx+1);
        return can_trans;
    }
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        map<pair<char, char>, vector<char>> trans;
        for(auto s: allowed)
            trans[{s[0], s[1]}].push_back(s[2]);
        return pyramidTransition(bottom, "", trans, 0);
    }
};
