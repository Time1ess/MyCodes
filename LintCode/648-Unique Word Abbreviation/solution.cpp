class ValidWordAbbr {
private:
    unordered_map<string, int> abbrs;
    unordered_set<string> words;
public:
    /*
    * @param dictionary: a list of words
    */ValidWordAbbr(vector<string> dictionary) {
        // do intialization if necessary
        unordered_set<string> unique_words(dictionary.begin(), dictionary.end());
        for(auto word: unique_words) {
            abbrs[make_abbr(word)]++;
            words.insert(word);
        }
    }
    
    string make_abbr(const string& s) {
        int n = s.length();
        if(n <= 2) {
            return s;
        }
        return s[0] + to_string(n-2) + s[n-1];
    }

    /*
     * @param word: a string
     * @return: true if its abbreviation is unique or false
     */
    bool isUnique(string &word) {
        // write your code here
        string abbr = make_abbr(word);
        if(words.find(word) != words.end() && abbrs[abbr] == 1) {
            return true;
        }
        return abbrs[abbr] == 0;
    }
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr obj = new ValidWordAbbr(dictionary);
 * bool param = obj.isUnique(word);
 */
