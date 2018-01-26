class Solution {
public:
    void ScanDigits(char **string)
    {
        while(**string != '\0' && **string >= '0' && **string <= '9')
            ++(*string);
    }
    bool CheckExponential(char **string)
    {
        if(**string != 'E' && **string != 'e')
            return false;
        ++(*string);
        if(**string == '+' || **string == '-')
            ++(*string);
        if(**string == '\0')
            return false;
        ScanDigits(string);
        return **string == '\0' ? true : false;
    }
    bool isNumeric(char* string)
    {
        if(!string || *string == '\0')
            return false;
        if(*string == '+' || *string == '-')
            string++;
        ScanDigits(&string);
        bool is_numeric = true;
        if(*string != '\0')
        {
            if(*string == '.')
            {
                ScanDigits(&(++string));
                if(*string == 'e' || *string == 'E')
                    is_numeric = CheckExponential(&string);
            }
            else if(*string == 'e' || *string == 'E')
                is_numeric = CheckExponential(&string);
            else
                is_numeric = false;
        }
        return is_numeric && *string == '\0';
    }

};
