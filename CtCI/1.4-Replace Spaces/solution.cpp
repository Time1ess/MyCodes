class Replacement {
public:
    string replaceSpace(string iniString, int length) {
        int spacesCnt = 0;
        for(int i = 0; i < length; i++)
            if(iniString[i] == ' ')
                spacesCnt++;
        int newLength = length + spacesCnt * 2;
        int j = newLength - 1;
        iniString.resize(newLength);
        for(int i = length - 1; i >= 0; i--) {
            if(iniString[i] == ' ') {
                iniString[j] = '0';
                iniString[j-1] = '2';
                iniString[j-2] = '%';
                j -= 3;
            } else
                iniString[j--] = iniString[i];
        }
        return iniString;
    }
};
