#include <iostream>
using namespace std;

class CMyString
{
public:
	CMyString(char*pData = NULL);
	CMyString(const CMyString &str);
	CMyString & operator=(const CMyString &str);
	~CMyString(void);
private:
	char* m_pData;
};

//经典的解法，适用于初级程序员

/*
CMyString & CMyString::operator(const CMyString &str)
{
	if(this==&str)
		return *this;
	delete []m_pData;
	m_pData=NULL;
	m_pData=new char[strlen(str.m_pData)+1];
	strcpy(m_pData,str.m_pData);

	return *this;
*/



//考虑异常安全性的解法，高级程序员必备
CMyString & CMyString::operator=(const CMyString &str)
{
	if (this != &str)
	{
		CMyString tmpStr(str);

		char* mTemp = tmpStr.m_pData;
		tmpStr.m_pData = this->m_pData;
		this->m_pData = mTemp;
	}
	return *this;
}