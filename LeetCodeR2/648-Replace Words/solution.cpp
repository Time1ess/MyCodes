struct TrieNode
{
    bool end;
    TrieNode* nexts[26];
    TrieNode()
    {
        end = false;
        for(int i = 0; i < 26; i++)
            nexts[i] = NULL;
    }
};

class Solution {
public:
    TrieNode* build_Trie(vector<string>& dict)
    {
        TrieNode* root = new TrieNode();
        for(auto word: dict)
        {
            TrieNode* tmp = root;
            for(auto ch: word)
            {
                if(tmp->nexts[ch-'a'] == NULL)
                    tmp->nexts[ch-'a'] = new TrieNode();
                tmp = tmp->nexts[ch-'a'];
            }
            tmp->end = true;
        }
        return root;
    }
    string replace_word(string word, TrieNode* root)
    {
        TrieNode* tmp = root;
        string root_word = "";
        for(auto ch: word)
        {
            root_word.push_back(ch);
            if(tmp->nexts[ch-'a'] == NULL)
                return word;
            tmp = tmp->nexts[ch-'a'];
            if(tmp->end == true)
                return root_word;
        }
        return word;
    }
    string replaceWords(vector<string>& dict, string sentence) {
        TrieNode* root = build_Trie(dict);
        int length = sentence.length();
        string ans = "";
        int i = 0;
        while(i < length && sentence[i] == ' ')
            i++;
        ans.append(i, ' ');
        while(i < length)
        {
            int j = i + 1;
            while(j < length && sentence[j] != ' ')
                j++;
            ans.push_back(' ');
            ans.append(replace_word(sentence.substr(i, j - i), root));
            i = j + 1;
        }
        return ans.substr(1);
    }
};
