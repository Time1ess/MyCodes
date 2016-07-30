#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#pragma warning(disable:4996)
using namespace std;

string  key[33] = { "main",
"auto", "short", "int", "long", "float", "double", "char", "struct"
, "union", "enum", "typedef", "const", "unsigned", "signed", "extern", "register"
, "static", "volatile", "void", "if", "else", "switch", "case", "for"
, "do", "while", "goto", "continue", "break", "default", "sizeof", "return" };


string  symbol[26] = {
	"=", "+", "-", "*", "/", "++", "--", "+=", "-=",
	"*=", "/=", "==", "!=", ">", "<", ">=", "<=", "(",
	")", "[", "]", "{", "}", ",", ":", ";" };

string constvalue[3] = { "整型常量", "实型常量", "字符常量" };

char ch;
string nowword="";

int main()
{
	int flag = 0;
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	cin.get(ch);
	while (cin)
	{
		nowword = "";
		flag = 0;
		while (ch == ' ' || ch == '\n')
			cin.get(ch);
		while (ch != ' ')
		{
			if (!cin)break;
			nowword += ch;
			cin.get(ch);
			if (isalpha(nowword[0]))
			{
				if (!isalpha(ch) && !isdigit(ch))break;
			}
			else if(isdigit(nowword[0]))
			{
				if (!isdigit(ch)&&ch!='.')break;
			}
			else if (nowword[0] == '(' || nowword[0] == '[' || nowword[0] == '{'
					 || ch == ' ' || ch == '\n')break;
			else if (nowword[0] == '\'')
			{
				nowword += ch;
				cin.get(ch);
				nowword += ch;
				cin.get(ch);
				break;
			}
			else if ((isdigit(ch) || isalpha(ch))||ch=='\'')break;
		}
		if (isdigit(nowword[0]))
		{
			int i = 0;
			while (i < nowword.length())
			{
				if (nowword[i] == '.')
				{
					cout.width(10);
					cout << nowword;
					cout << " :   " << constvalue[1] << endl;
					flag = 1;
					break;
				}
				i++;
			}
			if (flag == 1)continue;
			cout.width(10);
			cout << nowword;
			cout << " :   " << constvalue[0] << endl;
		}
		else if (isalpha(nowword[0]))
		{
			int i = 0;
			for (i = 0; i < 33;i++)
			if (key[i] == nowword)
			{
				cout.width(10);
				cout << nowword;
				cout << " :   关键字"  << endl;
				flag = 1;
				break;
			}
			if (flag == 1)continue;
			cout.width(10);
			cout << nowword;
			cout << " :   普通标识符" << endl;
		}
		else 
		{
			int i;
			int j;
			for (i = 0; i < 26;i++)
			if (symbol[i] == nowword)
			{
				cout.width(10);
				cout << nowword;
				cout << " :   ";
				if (i >= 17)cout << "界符" << endl;
				else cout << "运算符" << endl;
				break;
			}
			if (nowword[0] == '\'')
			{
				cout.width(10);
				cout << nowword;
				cout << " :   字符常量" << endl;
			}
		}

	}
	return 0;
}
