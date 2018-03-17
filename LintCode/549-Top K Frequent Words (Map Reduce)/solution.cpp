/**
 * Definition of Input:
 * template<class T>
 * class Input {
 * public:
 *     bool done(); 
 *         // Returns true if the iteration has elements or false.
 *     void next();
 *         // Move to the next element in the iteration
 *         // Runtime error if the iteration has no more elements
 *     T value();
 *        // Get the current element, Runtime error if
 *        // the iteration has no more elements
 * }
 * Definition of Document:
 * class Document {
 * public:
 *     int id; // document id
 *     string content; // document content
 * }
 */

vector<string> split(const string &str, char sep)
{
    vector<string> ans;
    int s = 0, e = str.find(sep);
    while(e < str.length())
    {
        ans.push_back(str.substr(s, e-s));
        s = e + 1;
        e = str.find(sep, s);
    }
    if(s != str.length())
        ans.push_back(str.substr(s));
    return ans;
}

class TopKFrequentWordsMapper: public Mapper {
public:
    void Map(Input<Document>* input) {
        // Write your code here
        // Please directly use func 'output' to output 
        // the results into output buffer.
        // void output(string &key, int value);
        map<string, int> cnts;
        while(!(input->done()))
        {
            Document doc = input->value();
            input->next();
            vector<string> words = split(doc.content, ' ');
            for(auto word: words)
                if(word != "")
                    cnts[word]++;
        }
        for(auto p: cnts)
        {
            string x = p.first;
            output(x, p.second);
        }
    }
};

bool cmp(const pair<string, int> &a, const pair<string, int> &b)
{
    return a.second > b.second || (a.second == b.second && a.first < b.first);
}

struct Compare
{
    bool operator()(const pair<string, int> &a, const pair<string, int> &b)
    {
        return cmp(a, b);
    }
};


class TopKFrequentWordsReducer: public Reducer {
private:
    int k;
    typedef pair<string, int> PSI;
    map<string, int> cnts;
public:
    void setUp(int k) {
        // initialize your data structure here
        this->k = k;
    }

    void Reduce(string &key, Input<int>* input) {
        // Write your code here     
        while(!(input->done()))
        {
            cnts[key] += input->value();
            input->next();
        }
    }

    void cleanUp() {
        priority_queue<PSI, vector<PSI>, Compare> pq;
        for(auto p: cnts)
        {
            PSI x{p.first, p.second};
            if(pq.size() < k)
                pq.push(x);
            else if(pq.size() == k && cmp(x, pq.top()))
            {
                pq.pop();
                pq.push(x);
            }
        }
        vector<PSI> ans;
        while(!pq.empty())
        {
            ans.push_back(pq.top());
            pq.pop();
        }
        reverse(ans.begin(), ans.end());
        for(auto x: ans)
        {
            string s = x.first;
            output(s, x.second);
        }
        // Please directly use func 'output' to output 
        // the top k pairs <word, times> into output buffer.
        // void output(string &key, int &value);
    }
};
