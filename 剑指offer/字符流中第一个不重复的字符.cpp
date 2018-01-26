class Solution
{
private:
    int occurence[256];
    int index;
    bool initialized = false;
public:
    void init()
    {
        index = 0;
        for(int i = 0; i < 256; i++)
            occurence[i] = -1;
        initialized = true;
    }
  //Insert one char from stringstream
    void Insert(char ch)
    {
        if(!initialized)
            init();
        if(occurence[ch] == -2)
            return;
        else if(occurence[ch] == -1)
            occurence[ch] = index++;
        else
            occurence[ch] = -2;
    }
  //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        if(!initialized)
            init();
    	char ch = '#';
        int min_index = 256;
        for(int i = 0; i < 256; i++)
            if(occurence[i] < 0)
                continue;
        	else if(occurence[i] < min_index)
            {
                min_index = occurence[i];
                ch = i;
            }
        return ch;
    }

};
