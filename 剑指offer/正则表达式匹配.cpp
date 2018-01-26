class Solution {
public:
    bool match(char* str, char* pattern)
    {
    	if((!str && !pattern) || (*str == '\0' && *pattern == '\0'))
            return true;
        if(!str || !pattern || (*str != '\0' && *pattern == '\0'))
            return false;
        if(*(pattern+1) == '*')
            if(*str == *pattern || (*str != '\0' && *pattern == '.'))
            	return match(str+1, pattern) || match(str+1, pattern+2) || match(str, pattern+2);
            else
                return match(str, pattern+2);
        else if((*str != '\0' && *pattern == '.') || *str == *pattern)
            return match(str+1, pattern+1);
        else
            return false;
    }
};
