#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <exception>
#include <cctype>
#include <algorithm>
#include <stack>
#include <map>
#pragma warning(disable:4996)
//#define syntaxtree
#define middlecode
using namespace std;
char sym;
string word;
vector<int> errorlist;


#ifdef syntaxtree
int depth = 2;
#endif
#ifdef middlecode
struct status
{
	bool init;
	int num;
	double value;
	status(int n = 0, double val = 0, bool in = false)
	{
		init = in;
		num = n;
		value = val;
	}
};
int varnum = 1;
bool ifmatch = false;
bool hasif = false;
map<string, status> vars;
int label = 0;
#endif

void statement();
void entrance();
void declare();
void compoundstatement();
int ifstatement();
void booleanstatement();
string lower(string &s);
string getachar();
string getvalue();
double getdouble();
int getint();
string getword();
char getsym();
int whilestatement();
int forstatement();
double calculation();
bool isnum(string);
double strtodoub(string &s);



double strtodoub(string &s)
{
	double tmp = 0,ptmp=0;
	int i=0;
	bool negative = false;
	if (s[i] == '-')
	{
		negative = true;
		i++;
	}
	for (; i < s.length(); i++)
	{
		if (s[i] == '.')
			break;
		tmp = tmp * 10 + s[i] - '0';
	}
	i++;
	for (int k=s.length()-1; k>=i; k--)
	{
		ptmp = (ptmp + s[k] - '0')/10;
	}
	return (negative?-1:1)*(tmp + ptmp);
}

bool isnum(string str)
{
	for (int i = 0; i<str.size(); i++)
	{
		if ((str.at(i)>'9') || (str.at(i) < '0'))
		{
			return   false;
		}
	}
	return   true;
}

double calculation()// a=(b+6)/3+c*8.2-11*(11-d);
{
	string tmp;
	char tmps[20];
	double tmpd;
#ifdef syntaxtree
	depth++;
#endif
	stack<string> cal;
	stack<int> state;
	double ans=1;
	//start with state 0 in state-stack,and cal is empty
	//use LR-parser,the calculation ends up with ';'
	//if meets ';',and cal is not empty,throw exception
	state.push(0);
	tmp = "#";
	cal.push(tmp);
	char m=cin.peek();
	while (true)
	{
		switch (state.top())
		{
		case 0:
			if ((cal.top())[0] == 'E')
			{
				state.push(1);
				continue;
			}
			else if ((cal.top())[0] == 'T')
			{
				state.push(2);
				continue;
			}
			else if ((cal.top())[0] == 'F')
			{
				state.push(3);
				continue;
			}
			else if (m == '(')
			{
				state.push(4);
				tmp = m;
				cal.push(tmp);
				getsym();
			}
			else if (isalpha(m))
			{
				tmp="_"+getvalue();
				state.push(5);
				cal.push(tmp);
			}
			else if (isdigit(m))
			{
				tmpd=getdouble();
				sprintf(tmps, "i%g", tmpd);
				tmp = tmps;
				state.push(5);
				cal.push(tmp);
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 1:
			if (m == '+')
			{
				state.push(6);
				tmp = m;
				cal.push(tmp);
				getsym();
			}
			else if (m == '-')
			{
				tmp = m;
				state.push(7);
				cal.push(tmp);
				getsym();
			}
			else if (m == ';')
			{
#ifdef syntaxtree
				depth--;
#endif
#ifdef middlecode
				ans = strtodoub(cal.top().substr(2));
#endif
				return ans;
			}
			break;
		case 2:
			if (m == '+' || m == '-' || m == ')' || m == ';')
			{
				if ((cal.top())[0] == 'T')
				{
					tmp = "E" + cal.top().substr(1);
					cal.pop();
					cal.push(tmp);
					state.pop();
					continue;
				}
				else
				{
					errorlist.push_back(11);	//operator error,error 11
					throw exception();
				}
			}
			else if (m == '*')
			{
				tmp = m;
				cal.push(tmp);
				state.push(8);
				getsym();
			}
			else if (m == '/')
			{
				tmp = m;
				cal.push(tmp);
				state.push(9);
				getsym();
			}
			else
			{
				errorlist.push_back(11);	//operator error,error 11
				throw exception();
			}
			break;
		case 3:
			if (m == '+' || m == '-' || m == '*' || m == '/' || m == ')' || m == ';')
			{
				if ((cal.top())[0] == 'F')
				{
					tmp = "T" + cal.top().substr(1);
					cal.pop();
					cal.push(tmp);
					state.pop();
					continue;
				}
				else
				{
					errorlist.push_back(11);	//operator error,error 11
					throw exception();
				}
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 4:
			if ((cal.top())[0] == 'E')
			{
				state.push(10);
				continue;
			}
			else if ((cal.top())[0] == 'T')
			{
				state.push(2);
				continue;
			}
			else if ((cal.top())[0] == 'F')
			{
				state.push(3);
				continue;
			}
			else if (m == '(')
			{
				tmp = m;
				cal.push(tmp);
				state.push(4);
				getsym();
			}
			else if (isalpha(m))
			{
				tmp="_"+getvalue();
				state.push(5);
				cal.push(tmp);
			}
			else if (isdigit(m))
			{
				tmpd=getdouble();
				sprintf(tmps, "i%g", tmpd);
				tmp = tmps;
				state.push(5);
				cal.push(tmp);
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 5:
			if (m == '+' || m == '-' || m == '*' || m == '/' || m == ')' || m == ';')
			{
				if ((cal.top())[0] == 'i' || (cal.top())[0] == '_')
				{
					tmp = "F" + cal.top();
					cal.pop();
					cal.push(tmp);
					state.pop();
					continue;
				}
				else
				{
					errorlist.push_back(11);	//operator error,error 11
					throw exception();
				}
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 6:
			if ((cal.top())[0] == 'T')
			{
				state.push(11);
				continue;
			}
			else if ((cal.top())[0] == 'F')
			{
				state.push(3);
				continue;
			}
			else if (m == '(')
			{
				tmp = m;
				cal.push(tmp);
				state.push(4);
				getsym();
			}
			else if (isalpha(m))
			{
				tmp = "_"+getvalue();
				state.push(5);
				cal.push(tmp);
			}
			else if (isdigit(m))
			{
				tmpd = getdouble();
				sprintf(tmps, "i%g", tmpd);
				tmp = tmps;
				state.push(5);
				cal.push(tmp);
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}

			break;
		case 7:
			if ((cal.top())[0] == 'T')
			{
				state.push(12);
				continue;
			}
			else if ((cal.top())[0] == 'F')
			{
				state.push(3);
				continue;
			}
			else if (m == '(')
			{
				tmp = m;
				cal.push(tmp);
				state.push(4);
				getsym();
			}
			else if (isalpha(m))
			{
				tmp = "_"+getvalue();
				state.push(5);
				cal.push(tmp);

			}
			else if (isdigit(m))
			{
				tmpd = getdouble();
				sprintf(tmps, "i%g", tmpd);
				tmp = tmps;
				state.push(5);
				cal.push(tmp);
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 8:
			if ((cal.top())[0] == 'F')
			{
				state.push(13);
				continue;
			}
			else if (m == '(')
			{
				tmp = m;
				cal.push(tmp);
				state.push(4);
				getsym();
			}
			else if (isalpha(m))
			{
				tmp = "_"+getvalue();
				state.push(5);
				cal.push(tmp);

			}
			else if (isdigit(m))
			{
				tmpd = getdouble();
				sprintf(tmps, "i%g", tmpd);
				tmp = tmps;
				state.push(5);
				cal.push(tmp);
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 9:
			if ((cal.top())[0] == 'F')
			{
				state.push(14);
				continue;
			}
			else if (m == '(')
			{
				tmp = m;
				cal.push(tmp);
				state.push(4);
				getsym();
			}
			else if (isalpha(m))
			{
				tmp = "_"+getvalue();
				state.push(5);
				cal.push(tmp);

			}
			else if (isdigit(m))
			{
				tmpd = getdouble();
				sprintf(tmps, "i%g", tmpd);
				tmp = tmps;
				state.push(5);
				cal.push(tmp);
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 10:
			if (m == '+')
			{
				tmp = m;
				state.push(6);
				cal.push(tmp);
				getsym();
			}
			else if (m == '-')
			{
				tmp = m;
				state.push(7);
				cal.push(tmp);
				getsym();
			}
			else if (m == ')')
			{
				tmp = m;
				state.push(15);
				cal.push(tmp);
				getsym();
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 11:
			if (m == '*')
			{
				tmp = m;
				state.push(8);
				cal.push(tmp);
				getsym();
			}
			else if (m == '/')
			{
				tmp = m;
				state.push(9);
				cal.push(tmp);
				getsym();
			}
			else if (m == '+' || m == '-' || m == ')' || m == ';')
			{
				tmpd = 0;
				for (int i = 1; i <= 3; i++)
				{
#ifdef middlecode
					tmp = cal.top();
					if (i==1||i==3)
					{
						if (tmp[1] == '_')
						{
							cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpd += vars[tmp.substr(2)].value;
						}
						else
						{
							cout << "    Pushi  " << tmp.substr(2) << endl;
							tmpd += strtodoub(tmp.substr(2));
						}
					}
					if (i == 3)
					{
						cout << "    Add    " << endl;
						
					}
#endif
					state.pop();
					cal.pop();
#ifdef middlecode
					if (i == 3)
					{
						sprintf(tmps, "Ei%g", tmpd);
						tmp = tmps;
						cal.push(tmp);
					}
#endif
				}
				continue;
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 12:
			if (m == '*')
			{
				tmp = m;
				state.push(8);
				cal.push(tmp);
				getsym();
			}
			else if (m == '/')
			{
				tmp = m;
				state.push(9);
				cal.push(tmp);
				getsym();
			}
			else if (m == '+' || m == '-' || m == ')' || m == ';')
			{
				tmpd = 0;
				for (int i = 1; i <= 3; i++)
				{
#ifdef middlecode
					tmp = cal.top();
					if (i==1)
					{
						if (tmp[1] == '_')
						{
							cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpd -= vars[tmp.substr(2)].value;
						}
						else
						{
							cout << "    Pushi  " << tmp.substr(2) << endl;
							tmpd -= strtodoub(tmp.substr(2));
						}
					}
					else if (i == 3)
					{
						if (tmp[1] == '_')
						{
							cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpd += vars[tmp.substr(2)].value;
						}
						else
						{
							cout << "    Pushi  " << tmp.substr(2) << endl;
							tmpd += strtodoub(tmp.substr(2));
						}
						cout << "    Sub    " << endl;
					}
#endif
					state.pop();
					cal.pop();
#ifdef middlecode
					if (i == 3)
					{
						sprintf(tmps, "Ei%g", tmpd);
						tmp = tmps;
						cal.push(tmp);
					}
#endif
				}
				continue;
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 13:
			if (m == '+' || m == '-' || m == ')' || m == ';'||m=='*'||m=='/')
			{
				tmpd = 0;
				for (int i = 1; i <= 3; i++)
				{
#ifdef middlecode
					tmp = cal.top();
					if (i == 1)
					{
						if (tmp[1] == '_')
						{
							cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpd += vars[tmp.substr(2)].value;
						}
						else
						{
							cout << "    Pushi  " << tmp.substr(2) << endl;
							tmpd += strtodoub(tmp.substr(2));
						}
					}
					else if (i == 3)
					{
						if (tmp[1] == '_')
						{
							cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpd *= vars[tmp.substr(2)].value;
						}
						else
						{
							cout << "    Pushi  " << tmp.substr(2) << endl;
							tmpd *= strtodoub(tmp.substr(2));
						}
						cout << "    Mul    " << endl;
					}
#endif
					state.pop();
					cal.pop();
#ifdef middlecode
					if (i == 3)
					{
						sprintf(tmps, "Ti%g", tmpd);
						tmp = tmps;
						cal.push(tmp);
					}
#endif
				}
				continue;
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 14:
			if (m == '+' || m == '-' || m == ')' || m == ';' || m == '*' || m == '/')
			{
				tmpd = 0;
				for (int i = 1; i <= 3; i++)
				{
#ifdef middlecode
					tmp = cal.top();
					if (i == 1)
					{
						if (tmp[1] == '_')
						{
							cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpd += vars[tmp.substr(2)].value;
						}
						else
						{
							cout << "    Pushi  " << tmp.substr(2) << endl;
							tmpd += strtodoub(tmp.substr(2));
						}
					}
					else if (i == 3)
					{
						if (tmp[1] == '_')
						{
							cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpd = vars[tmp.substr(2)].value/tmpd;
						}
						else
						{
							cout << "    Pushi  " << tmp.substr(2) << endl;
							tmpd = strtodoub(tmp.substr(2))/tmpd;
						}
						cout << "    Div    " << endl;
					}
#endif
					state.pop();
					cal.pop();
#ifdef middlecode
					if (i == 3)
					{
						sprintf(tmps, "Ti%g", tmpd);
						tmp = tmps;
						cal.push(tmp);
					}
#endif
				}
				continue;
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		case 15:
			if (m == '+' || m == '-' || m == ')' || m == ';' || m == '*' || m == '/')
			{
				for (int i = 1; i <= 3; i++)
				{
#ifdef middlecode
					if (i == 2)
						tmp = cal.top();
#endif
					state.pop();
					cal.pop();

				}
				tmp = "F"+tmp.substr(1);
				cal.push(tmp);
				continue;
			}
			else
			{
				errorlist.push_back(11);
				throw exception();
			}
			break;
		}
		m = cin.peek();
	}
#ifdef syntaxtree
	depth--;
#endif
	return -1;
}

void nospace()
{
	while (cin.peek() == '\t' || cin.peek() == '\n'||cin.peek()==' ')
	{
		cin.get();
	}
}

char getsym()
{
	char c=cin.get();
	while (c == '\n' || c == '\t')
		c = cin.get();
	return c;
}

string getword()
{
	string tmp = "";
	char m = cin.peek();
	while (m == '\n' || m == '\t' || m == ' ')
	{
		cin.get();
		m = cin.peek();
	}
	while ((m >= 'A'&&m <= 'Z') || (m >= 'a'&&m <= 'z') || (m >= '0'&&m <= '9'))
	{
		tmp += m;
		cin.get();
		m = cin.peek();
	}
	return tmp;
}

int getint()
{
	int tmp;
	cin >> tmp;
	return tmp;
}

double getdouble()
{
	double tmp;
	cin >> tmp;
	return tmp;
}

string getvalue()
{
	string tmp = "";
	char m = cin.peek();
	while (m == '\n' || m == '\t' || m == ' ')
	{
		cin.get();
		m = cin.peek();
	}
	while ((m >= 'A'&&m <= 'Z') || (m >= 'a'&&m <= 'z') || (m >= '0'&&m <= '9')||m=='.')
	{
		tmp += m;
		cin.get();
		m = cin.peek();
	}
	return tmp;
}

string getachar()
{
	string tmp = "";
	char m = cin.peek();
	while (m == '\n' || m == '\t' || m == ' ')
	{
		cin.get();
		m = cin.peek();
	}
	while (m != ','&&m != ';')
	{
		tmp += m;
		cin.get();
		m = cin.peek();
	}
	if (tmp[0] == '\'')
	{
		if (tmp[2] == '\'')
			return tmp;
		errorlist.push_back(7);
		throw exception();
	}
	else if (tmp.length() == 1)
		return tmp;
	else
	{
		errorlist.push_back(7);
		throw exception();
	}



}

string lower(string &s)
{
	string t;
	transform(s.begin(), s.end(), t.begin(), ::tolower);
	return t;
}


//<booleanstatement> | <booleanstatement> && <booleanstatement>	| <booleanstatement> || <booleanstatement> | ID relop ID | ID
//there exists at least a ID,might be more as relop ID or && <booleanstatement> or ||
//boleanstatement should start with the first character of the first word of the boolean expression
void booleanstatement()
{
	string value;
	bool tlabel=false;
	char lastlabel;
	char m=cin.peek();
	if(m != ')')
	{
		value= getvalue();
		if (value == "")value = word;
		m = cin.peek();
		if (m == ')')
			return;
		if (m == '<' || m == '>' || m == '!' || m == '=')
		{
			getsym();
			lastlabel = m;
			sym = cin.peek();
#ifdef middlecode
			if (vars[value].num == 0)
			{
				cout << "Fatal Error:Variable " << value << "is not defined." << endl;
				errorlist.push_back(13);
				throw exception();
			}
			else
			{
				cout << "    Push   " << vars[value].num << endl;
			}
#endif
			if ((sym == '=') && (m == '<' || m == '>' || m == '!'||m=='='))
			{
				sym = getsym();
#ifdef middlecode
				tlabel = true;
#endif
			}
			value=getvalue();
#ifdef middlecode
			if (!isnum(value)&&vars[value].num == 0)
			{
				cout << "Fatal Error:Variable " << value << "is not defined." << endl;
				errorlist.push_back(13);
				throw exception();
			}
			else
			{
				if (isnum(value))
					cout << "    Pushi  " << value << endl;
				else
					cout << "    Push   " << vars[value].num << endl;
				switch (lastlabel)
				{
				case '<':
					if (tlabel)
					{
						cout << "    Leq    " << endl;
					}
					else
					{
						cout << "    Ls     " << endl;
					}
					break;
				case '>':
					if (tlabel)
					{
						cout << "    Geq    " << endl;
					}
					else
					{
						cout << "    Gt     " << endl;
					}
					break;
				case '!':
					if (tlabel)
					{
						cout << "    Noteq  " << endl;
					}
					else
					{
						errorlist.push_back(9);
						throw exception();
					}
					break;
				case '=':
					if (tlabel)
					{
						cout << "    Eq     " << endl;
					}
					else
					{
						errorlist.push_back(9);
						throw exception();
					}
					break;
				}
			}
#endif
		}
		else if (m != '&'&&m != '|')
		{
			errorlist.push_back(9);
			throw exception();
		}
	}

	m = cin.peek();
	if (m == ')' || m == ';')
		return;
	if (m != '&'&&m != '|')
	{
		errorlist.push_back(9);
		throw exception();
	}
	sym = getsym();
	m = cin.peek();
	if (sym!=m)
	{
		errorlist.push_back(9);
		throw exception();
	}
	sym = getsym();
	booleanstatement();
#ifdef middlecode
	if (m == '&')
	{
		cout << "    And    " << endl;
	}
	else
	{
		cout << "    Or     " << endl;
	}
#endif
}

//ifstatement goes here
//do if-statement,and if there exists a "else",do else,otherwise another statement
int ifstatement()
{
#ifdef syntaxtree
	for (int i = 1; i <= depth; i++)
		cout << "  ";
	cout << "if-statement" << endl;
	depth++;
#endif
	sym = getsym();
	if (sym != '(')
	{
		errorlist.push_back(1);//missing (,error 1
		throw exception();
	}
#ifdef syntaxtree
	for (int i = 1; i <= depth; i++)
		cout << "  ";
	cout << "boolean-statement" << endl;
	depth++;
#endif
#ifdef middlecode
	cout << "label " << label++ << ":" << endl;
#endif
	//boolean codes goes here
	booleanstatement();
#ifdef middlecode
	cout << "    jmpz   " <<label<< endl;
#endif
	sym = getsym();
	if (sym != ')')
	{
		errorlist.push_back(2);//missing ),error 2
		throw exception();
	}
	word = getword();
	statement();
#ifdef syntaxtree
	depth--;
#endif
#ifdef syntaxtree
	depth--;
#endif
}

//forstatement goes here
//do for-statement
int forstatement()
{
#ifdef syntaxtree
	for (int i = 1; i <= depth; i++)
		cout << "  ";
	cout << "for-statement" << endl;
	depth++;
#endif
	sym = getsym();
	if (sym != '(')
	{
		errorlist.push_back(1);//missing (,error 1
		throw exception();
	}
#ifdef syntaxtree
	for (int i = 1; i <= depth; i++)
		cout << "  ";
	cout << "declare" << endl;
#endif
	declare();
#ifdef syntaxtree
	for (int i = 1; i <= depth; i++)
		cout << "  ";
	cout << "boolean-statement" << endl;
#endif
	//boolean codes goes here
#ifdef middlecode
	cout << "label " << label++ << ":" << endl;
#endif
	booleanstatement();
#ifdef middlecode
	cout << "    jnz   " << label+1 << endl;
	cout << "    jmp   " << label+2 << endl;
#endif
	sym = getsym();
	if (sym != ';')
	{
		errorlist.push_back(8);//missing ;,error 8
		throw exception();
	}
#ifdef middlecode
	cout << "label " << label++ << ":" << endl;
#endif

	word = getword();
	statement();
#ifdef middlecode
	cout << "    jmp   " << label - 2 << endl;
#endif
#ifdef syntaxtree
	depth++;
#endif

#ifdef middlecode
	cout << "label " << label++ << ":" << endl;
#endif

	word = getword();
	compoundstatement();

#ifdef middlecode
	cout << "    jmp   " << label - 2 << endl;
	cout << "label " << label++ << ":" << endl;
#endif
#ifdef syntaxtree
	depth--;
#endif
#ifdef syntaxtree
	depth--;
#endif
}




//whilestatement goes here
//do while-statement
int whilestatement()
{
#ifdef syntaxtree
	for (int i = 1; i <= depth; i++)
		cout << "  ";
	cout << "while-statement" << endl;
	depth++;
#endif
	sym = getsym();
	if (sym != '(')
	{
		errorlist.push_back(1);//missing (,error 1
		throw exception();
	}
#ifdef syntaxtree
	for (int i = 1; i <= depth; i++)
		cout << "  ";
	cout << "boolean-statement" << endl;
	depth++;
#endif
	//boolean codes goes here
#ifdef middlecode
	cout << "label " << label++ << ":" << endl;
#endif
	booleanstatement();
#ifdef middlecode
	cout << "    jmpz   " << label << endl;
#endif
	sym = getsym();
	if (sym != ')')
	{
		errorlist.push_back(2);//missing ),error 2
		throw exception();
	}

	word = getword();
	statement();
#ifdef middlecode
	cout << "    jmp    " << label-1 << endl;
#endif
#ifdef middlecode
	cout << "label " << label++ << ":" << endl;
#endif
#ifdef syntaxtree
	depth--;
#endif
#ifdef syntaxtree
	depth--;
#endif
}



//compoundstatement goes here
//start with the first word of the firt statement (the first word is already in -word-
//or the -word- might be empty for such as {...} )

void compoundstatement()
{
#ifdef syntaxtree
#endif
	while (cin.peek() != '}'&&sym!='}')
	{
		word = getword();
		statement();
		nospace();
	}
#ifdef syntaxtree
#endif
}

//statement goes here
//start with the first word of the firt statement (the first word is already in -word-
//or the -word- might be empty for such as {...} )

void statement()
{
	char oldsym=0;
	if (word.length() == 0)
	{
		sym = getsym();
		if (sym != '{')
		{
			errorlist.push_back(5);//missing {,error 5
			throw exception();
		}

		compoundstatement();
		oldsym = sym;
		sym = getsym();
		if (sym != '}'&&oldsym!='}')
		{
			errorlist.push_back(6);//missing },error 6
			throw exception();
		}
	}
	else
	{
		if (hasif&&!ifmatch&&word!="else")
		{
#ifdef middlecode
			cout << "label " << label++ << ":" << endl;
#endif
		}
		hasif = ifmatch = false;
		if (word == "if")
		{
			ifstatement();
			//if exists "else" do else,otherwise do another statement
			hasif = true;
		}
		else if (word == "else")
		{
			ifmatch=true;
#ifdef syntaxtree
			for (int i = 1; i <= depth; i++)
				cout << "  ";
			cout << "else-statement" << endl;
			depth += 2;
#endif
#ifdef middlecode
			cout << "    jmp    " << label + 1 << endl;
			cout << "label " << label++ << ":" << endl;

#endif
			word = getword();
			statement();
#ifdef middlecode
			cout << "label " << label++ << ":" << endl;
#endif
#ifdef syntaxtree
			depth -= 2;
#endif
		}
		else if (word == "while")
		{
			whilestatement();
		}
		else if (word == "for")
		{
			forstatement();
		}

		else	//equation such as a=6;b=3;c=b;
		{
#ifdef syntaxtree
			for (int i = 1; i <= depth; i++)
				cout << "  ";
			cout << "statement" << endl;
#endif
			sym = getsym();
			if (sym == '+' || sym == '-')
			{
				char m = getsym();
				if (sym != m)
				{
					errorlist.push_back(10);
					throw exception();
				}
				//complete ++ or -- operation
				sym = getsym();
				if (sym != ';'&&sym != ')')
				{
					errorlist.push_back(8);//missing ;,error 8
					throw exception();
				}
#ifdef middlecode
				if (vars[word].init == false)
				{
					errorlist.push_back(14);
					throw exception();
				}
				cout << "    Push   "  <<vars[word].num<< endl;
				cout << "    Pushi  1" << endl;
				if (m == '+')
				{
					cout << "    Add   " << endl;
					vars[word].value += 1;
				}
				else
				{
					cout << "    Sub   " << endl;
					vars[word].value -= 1;
				}
				cout << "    Sto    " << vars[word].num << endl;
#endif
				return;
			}
			else if (sym == '=')
			{
				vars[word].value=calculation();
				vars[word].init = true;
			}
			else
			{
				errorlist.push_back(10);
				throw exception();
			}
			getvalue();
			sym = getsym();
			if (sym != ';'&&sym!=')')
			{
				errorlist.push_back(8);//missing ;,error 8
				throw exception();
			}
		}
	}
#ifdef syntaxtree
#endif
}

//declare statement ex:int h,c=3;double a=3.5;int b=c;
//start with the first character of the type
void declare()		
{
	string value;
	while (true)
	{
		word = getword();
		bool con = true;
		if (word == "int")
		{
			while (con)
			{
				word = getword();	//get a variable name
				sym = getsym();		//get a signal,ex ','(mean no init) or '='(mean init) or ';'(mean declare end)
				switch (sym)
				{
				case ',':
#ifdef middlecode
					if (vars[word].num == 0)
					{
						vars[word].num = varnum++;
					}
					else
					{
						errorlist.push_back(12);
						throw exception();
					}
#endif
					continue;
				case '=':
					//check type transform
					value=getvalue();
					sym = getsym();
#ifdef middlecode
					if (vars[word].num == 0)
					{
						cout << "    Pushi  " << value << endl;
						cout << "    Sto    " << varnum << endl;
						vars[word].value = strtodoub(value);
						vars[word].init = true;
						vars[word].num = varnum++;
					}
					else
					{
						errorlist.push_back(12);
						throw exception();
					}
#endif
					if (sym == ';')con = false;
					break;
				case ';':
					con = false;
					break;
				default:
					errorlist.push_back(4);
					throw exception();
					break;
				}
			}
		}
		else if (word == "double")
		{
			while (con)
			{
				word = getword();	//get a variable name
				sym = getsym();		//get a signal,ex ','(mean no init) or '='(mean init) or ';'(mean declare end)
				switch (sym)
				{
				case ',':
#ifdef middlecode
					if (vars[word].num == 0)
						vars[word].num = varnum++;
					else
					{
						errorlist.push_back(12);
						throw exception();
					}
#endif
					continue;
				case '=':
					//check type transform
					value=getvalue();
					sym = getsym();
#ifdef middlecode
					if (vars[word].num == 0)
					{
						cout << "    Pushi  " << value << endl;
						cout << "    Sto    " << varnum << endl;
						vars[word].value = strtodoub(value);
						vars[word].init = true;
						vars[word].num = varnum++;
					}
					else
					{
						errorlist.push_back(12);
						throw exception();
					}
#endif
					if (sym == ';')con = false;
					break;
				case ';':
					con = false;
					break;
				default:
					errorlist.push_back(4);
					throw exception();
					break;
				}
			}
		}
		else if (word == "char")
		{
			while (con)
			{
				word = getword();	//get a variable name
				sym = getsym();		//get a signal,ex ','(mean no init) or '='(mean init) or ';'(mean declare end)
				switch (sym)
				{
				case ',':
#ifdef middlecode
					if (vars[word].num == 0)
						vars[word].num = varnum++;
					else
					{
						errorlist.push_back(12);
						throw exception();
					}
#endif
					continue;
				case '=':
					//check type transform
					value=getachar();	//get the value
					sym = getsym();
#ifdef middlecode
					if (vars[word].num == 0)
					{
						if (value[0] == '\'')
						{
							cout << "    Pushi  " << value << endl;
							cout << "    Sto    " << varnum << endl;
							value = value[1];
							vars[word].value = strtodoub(value);
						}
						else
						{
							cout << "    Push  " << value << endl;
							cout << "    Sto    " << varnum << endl;
							vars[word].value = vars[value].value;
						}
						vars[word].init = true;
						vars[word].num = varnum++;
					}
					else
					{
						errorlist.push_back(12);
						throw exception();
					}
#endif
					if (sym == ';')con = false;
					break;
				case ';':
					con = false;
					break;
				default:
					errorlist.push_back(4);
					throw exception();
					break;
				}
			}
		}
		else
		{
			break;
		}

	}
}

void entrance()		//main entrance
{
#ifdef syntaxtree
	for (int i = 1; i < depth; i++)
		cout << "  ";
	cout << "main" << endl;
	depth++;
#endif
	if (word == "main")
	{
		sym = getsym();
		if (sym != '(')
		{
			errorlist.push_back(1);//missing (,error 1
			throw exception();
		}
		sym = getsym();
		if (sym != ')')
		{
			errorlist.push_back(2);//missing ),error 2
			throw exception();
		}
		sym = getsym();
		if (sym != '{')
		{
			errorlist.push_back(5);//missing {,error 5
			throw exception();
		}

#ifdef syntaxtree
		for (int i = 1; i <= depth; i++)
			cout << "  ";
		cout << "declare" << endl;
#endif
		//declare goes here
		declare();
		//codes goes here
		while (cin.peek() != '}')//while have not reach the end of the main function,continue statement
		{
			statement();
			word = getword();
		}


		sym = getsym();
		if (sym != '}')
		{
			errorlist.push_back(6);//missing },error 6
			throw exception();
		}
	}
	else
	{
		errorlist.push_back(0);//missing main,error 0
		throw exception();
	}
#ifdef syntaxtree
	depth--;
	for (int i = 1; i < depth; i++)
		cout << "  ";
	cout << "end" << endl;
#endif
}

int main()
{
	freopen("a.txt", "r", stdin);
	word = getword();
	cout << "##BEGIN##" << endl;
	try
	{
		entrance();
	}
	catch (exception &s)
	{
		//catch fatal error,print errorlist
		cout << "##Catch ERROR##" << endl;
		for (auto x : errorlist)
		{
			cout << x << endl;
		}
		return -1;
	}
	cout << "##SUCCESS##" << endl;
	return 0;
}


/*
int main()
{
	while (1)
	{
		double d;
		string s;
		cin >> s;
		d = strtodoub(s);
		cout << d << endl;
	}
	return 0;
}
*/

/*
int main()
{
	freopen("b.txt", "r", stdin);
	try
	{
		double m = calculation();
		cout << m << endl;
	}
	catch (exception &s)
	{
		//catch fatal error,print errorlist
		cout << "##Catch##" << endl;
		for (auto x : errorlist)
		{
			cout << x << endl;
		}
		return -1;
	}
	cout << "##SUCCESS##" << endl;
	return 0;
}
*/