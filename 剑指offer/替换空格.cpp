class Solution {
public:
	void replaceSpace(char *str,int length) {
		if(!str || length <= 0)
            return;
        int char_cnt = 0, blank_cnt = 0, i = 0;
        while(str[i] != '\0')
        {
            char_cnt++;
            if(str[i++] == ' ')
                blank_cnt++;
        }
        int new_len = char_cnt + blank_cnt * 2;
        if(new_len > length)
            return;
        int new_index = new_len, original_index = char_cnt;
        while(original_index >= 0 && new_index > original_index)
        {
            if(str[original_index] == ' ')
            {
                str[new_index--] = '0';
                str[new_index--] = '2';
                str[new_index--] = '%';
            }
            else
                str[new_index--] = str[original_index];
            original_index--;
        }
	}
};
