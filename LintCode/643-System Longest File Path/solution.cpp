#include <iostream>
#include <string>
#include <vector>

using namespace std;



class Solution {
public:
    /*
     * @param input: an abstract file system
     * @return: return the length of the longest absolute path to file
     */
    void read_next_path(string &input, int &i, int &level, int &length, bool &is_file)
    {
        // (\t)*.+
        int size = input.size();
        if(i >= size)
            return;
        int j = i;
        while(j < size && input[j] != '\n')
        {
            if(input[j] == '\t')
                level++;
            else if(input[j] == '.')
                is_file = true;
            j++;
        }
        length = j - i - level;
        i = j + 1;
    }
    int lengthLongestPath(string &input) {
        // write your code here
        int ans = 0;
        if(input == "")
            return 0;
        int i = 0;
        int size = input.size();
        while(i < size && input[i] != '\n')
            i++;
        vector<pair<int, int>> s;
        s.push_back({0, i++});
        while(i < size)
        {
            int level = 0, length = 0;
            bool is_file = false;
            read_next_path(input, i, level, length, is_file);
            pair<int, int> top = s.back();
            if(is_file)
            {
                while(!s.empty() && s.back().first >= level)
                    s.pop_back();
                int tmp = 0;
                for(auto x: s)
                    tmp += x.second;
                tmp += length + level;
                ans = max(ans, tmp);
            }
            else if(level > top.first)
            {
                s.push_back({level, length});
            }
            else if(level == top.first)
            {
                s.back().second = length;
            }
            else if(level < top.first)
            {
                while(!s.empty() && s.back().first >= level)
                    s.pop_back();
                s.push_back({level, length});
            }
        }
        return ans;
    }
};


int main()
{
    string s = "skd\n\talskjv\n\t\tlskjf\n\t\t\tklsj.slkj\n\t\tsdlfkj.sdlkjf\n\t\tslkdjf.sdfkj\n\tsldkjf\n\t\tlskdjf\n\t\t\tslkdjf.sldkjf\n\t\t\tslkjf\n\t\t\tsfdklj\n\t\t\tlskjdflk.sdkflj\n\t\t\tsdlkjfl\n\t\t\t\tlskdjf\n\t\t\t\t\tlskdjf.sdlkfj\n\t\t\t\t\tlsdkjf\n\t\t\t\t\t\tsldkfjl.sdlfkj\n\t\t\t\tsldfjlkjd\n\t\t\tsdlfjlk\n\t\t\tlsdkjf\n\t\tlsdkjfl\n\tskdjfl\n\t\tsladkfjlj\n\t\tlskjdflkjsdlfjsldjfljslkjlkjslkjslfjlskjgldfjlkfdjbljdbkjdlkjkasljfklasjdfkljaklwejrkljewkljfslkjflksjfvsafjlgjfljgklsdf.a";
    Solution sol;
    cout<<sol.lengthLongestPath(s)<<endl;
    return 0;
}
