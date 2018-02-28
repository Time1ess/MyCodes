class Solution {
public:
    char *m_pData;
    Solution() {
        this->m_pData = NULL;
    }
    Solution(char *pData) {
        this->m_pData = pData;
    }

    // Implement an assignment operator
    Solution operator=(const Solution &object) {
        // write your code here
        if(this == &object)
            return object;
        delete this->m_pData;
        this->m_pData = NULL;
        if(object.m_pData != NULL)
        {
            int len = strlen(object.m_pData);
            this->m_pData = new char[len+1];
            strcpy(this->m_pData, object.m_pData);
        }
        return *this;
    }
};
