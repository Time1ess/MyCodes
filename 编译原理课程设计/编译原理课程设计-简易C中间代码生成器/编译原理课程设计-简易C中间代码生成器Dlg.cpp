
// 编译原理课程设计-简易C中间代码生成器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "编译原理课程设计-简易C中间代码生成器.h"
#include "编译原理课程设计-简易C中间代码生成器Dlg.h"
#include "afxdialogex.h"
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
#include <queue>
#include <stack>
#include <map>
#pragma warning(disable:4996)
#define syntaxtree
#define middlecode
#define synlabel
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
char sym;
string word;
vector<int> errorlist;
vector<int> allsharps;
vector<int> alldollars;
bool inputconfirm = false;
#ifdef syntaxtree
int depth = 2;
#endif

#ifdef middlecode
int CodeMaxLength = 0;
int varnum = 1;
bool ifmatch = false;
bool hasif = false;
map<string, status> vars;
map<int, string>errors;
int label = 0;
string syns;
#endif

void statement();
void entrance();
void declare();
void compoundstatement();
void ifstatement();
void booleanstatement();
string lower(string &s);
string getachar();
string getvalue();
double getdouble();
int getint();
string getword();
char getsym();
void whilestatement();
void forstatement();
double calculation();
bool isnum(string);
double strtodoub(string &s);


void seterrors()
{
#ifdef middlecode
	errors[0] = "main函数缺失";
	errors[1] = "’(‘缺失";
	errors[2] = "’)‘缺失";
	errors[3] = "类型错误";
	errors[4] = "声明错误";
	errors[5] = "’{ ‘缺失";
	errors[6] = "’ }’缺失";
	errors[7] = "赋值错误";
	errors[8] = "’; ’缺失";
	errors[9] = "布尔表达式错误";
	errors[10] = "未定义运算";
	errors[11] = "运算符错误";
	errors[12] = "变量名重复";
	errors[13] = "变量未定义";
	errors[14] = "变量未初始化";
	errors[15] = "除0运算";
#endif

}



/*
void C编译原理课程设计简易C中间代码生成器Dlg::ShowCodes(int controlId, CString strAdd)
{
	((CEdit*)GetDlgItem(controlId))->SetSel(GetDlgItem(controlId)->GetWindowTextLength(), GetDlgItem(controlId)->GetWindowTextLength());
	((CEdit*)GetDlgItem(controlId))->ReplaceSel(totalcodes);
}*/


void C编译原理课程设计简易C中间代码生成器Dlg::findallsharps()
{
	int k = 0;
	int i;
	do
	{
		if (k >= totalcodes.GetLength())break;
		i = totalcodes.Find('#', k);
		if (i != -1)
			allsharps.push_back(i);
		k = i+1;
	} while (i != -1);

	k = 0;
	do
	{
		if (k >= totalcodes.GetLength())break;
		i = totalcodes.Find('$', k);
		if (i != -1)
			alldollars.push_back(i);
		k = i + 1;
	} while (i != -1);
	/*
	i = 0;
	for (auto x : allsharps)
	{
		totalcodes.Insert(x,'1');
		totalcodes.Remove('#');
	}
	*/
}

//replace # in totalcodes to make right label
//synindex defines the current index in syntax string
//strindex defines the current index in totalcodes CString
//tot defines how many # in totalcodes should be replaced for the current replace action
//compare the depth level ,if first level is bigger than second level,indicates break current control block
int C编译原理课程设计简易C中间代码生成器Dlg::replacelabel(int depth,int index)
{
	//for (int i = 0; i < allsharps.size(); i++)
	//{
	//	char s[10];
	//	sprintf(s, "%d", i);
	//	totalcodes.Insert(allsharps[i], s[0]);
	//	if(i>9)
	//		totalcodes.Insert(allsharps[i]+1, s[1]);
	//	totalcodes.Remove('#');
	//}
	char s[10];
	static queue<int> indexs;
	static int loc = 0;
	int tot = 0;
	if (index >= syns.length())
		return tot;
	int currentdep = syns[index]-'0';

	char order = syns[index + 1];

	if (currentdep >= depth)
	{
		switch (order)
		{
		case 'i':
			tot=replacelabel(currentdep, index + 2);

			sprintf(s, "%d", loc);
			totalcodes.Insert(allsharps[loc], s[0]);
			if (loc > 9)
				totalcodes.Insert(allsharps[loc] + 1, s[loc]);
			totalcodes.Remove('#');
			loc++;
			break;
		case 'w':
			sprintf(s, "%d", loc);
			totalcodes.Insert(allsharps[loc], s[0]);
			if (loc > 9)
				totalcodes.Insert(allsharps[loc] + 1, s[loc]);
			totalcodes.Remove('#');
			loc++;

			tot=replacelabel(currentdep, index + 2);

			sprintf(s, "%d", loc);
			totalcodes.Insert(allsharps[loc], s[0]);
			if (loc > 9)
				totalcodes.Insert(allsharps[loc] + 1, s[loc]);
			totalcodes.Remove('#');
			loc++;
			break;
		case 'f':
			sprintf(s, "%d", loc);
			totalcodes.Insert(allsharps[loc], s[0]);
			if (loc > 9)
				totalcodes.Insert(allsharps[loc] + 1, s[loc]);
			totalcodes.Remove('#');
			loc++;

			sprintf(s, "%d", loc);
			totalcodes.Insert(allsharps[loc], s[0]);
			if (loc > 9)
				totalcodes.Insert(allsharps[loc] + 1, s[loc]);
			totalcodes.Remove('#');
			loc++;

			sprintf(s, "%d", loc);
			totalcodes.Insert(allsharps[loc], s[0]);
			if (loc > 9)
				totalcodes.Insert(allsharps[loc] + 1, s[loc]);
			totalcodes.Remove('#');
			loc++;

			tot=replacelabel(currentdep, index + 2);

			sprintf(s, "%d", loc);
			totalcodes.Insert(allsharps[loc], s[0]);
			if (loc > 9)
				totalcodes.Insert(allsharps[loc] + 1, s[loc]);
			totalcodes.Remove('#');
			loc++;
			break;
		case 's':
			replacelabel(currentdep, index + 2);
			break;
		case 'd':
			replacelabel(currentdep, index + 2);
			break;
		case 'b':
			replacelabel(currentdep, index + 2);
			break;
		case 'e':
			sprintf(s, "%d", loc);
			totalcodes.Insert(allsharps[loc], s[0]);
			if (loc > 9)
				totalcodes.Insert(allsharps[loc] + 1, s[loc]);
			totalcodes.Remove('#');
			loc++;

			tot = replacelabel(currentdep, index + 2);

			break;
		case 'm':
			replacelabel(currentdep, index + 2);
			break;
		case 'x':
			break;
		}

		while (!indexs.empty())
		{
			int tdep = syns[indexs.front()] - '0';
			if (tdep==depth)
			{
				char torder = syns[indexs.front() + 1];
				indexs.pop();
				replacelabel(tdep, index);
			}
		}
	}
	else
	{
		indexs.push(index);
	}





	//replace $ in jmpjmpz jnzorders.
	//for (int i = 0; i < alldollars.size(); i++)
	//{
	//	char s[10];
	//	sprintf(s, "%d", i);
	//	totalcodes.Insert(alldollars[i], s[0]);
	//	if (i>9)
	//		totalcodes.Insert(alldollars[i] + 1, s[1]);
	//	totalcodes.Remove('$');
	//}
}

void C编译原理课程设计简易C中间代码生成器Dlg::ShowCodes(int controlId, CString strAdd)
{
	((CEdit*)GetDlgItem(controlId))->SetSel(GetDlgItem(controlId)->GetWindowTextLength(), GetDlgItem(controlId)->GetWindowTextLength());
	((CEdit*)GetDlgItem(controlId))->ReplaceSel(totalcodes);
}

void C编译原理课程设计简易C中间代码生成器Dlg::AppendText(int controlId, CString strAdd)
{
	totalcodes+=strAdd + L"\r\n";
}

double strtodoub(string &s)
{
	double tmp = 0, ptmp = 0;
	int i = 0;
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
	for (int k = s.length() - 1; k >= i; k--)
	{
		ptmp = (ptmp + s[k] - '0') / 10;
	}
	return (negative ? -1 : 1)*(tmp + ptmp);
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

double C编译原理课程设计简易C中间代码生成器Dlg::calculation()// a=(b+6)/3+c*8.2-11*(11-d);
{
	string tmp;
	char tmps[20];
	double tmpd;
#ifdef syntaxtree
	depth++;
#endif
	stack<string> cal;
	stack<int> state;
	double ans = 1;
	//start with state 0 in state-stack,and cal is empty
	//use LR-parser,the calculation ends up with ';'
	//if meets ';',and cal is not empty,throw exception
	state.push(0);
	tmp = "#";
	cal.push(tmp);
	char m = cin.peek();
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
				tmp = "_" + getvalue();
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
				if (isalpha((cal.top())[2]))
				{
					if (vars[cal.top().substr(2)].init == false)
					{
						errorlist.push_back(14);
						throw exception();
					}
					ans = vars[cal.top().substr(2)].value;
				}
				else
				{
					ans = strtodoub(cal.top().substr(2));

				}
				midcodes = _T("    Pushi  ");
				tmpcs.Format(_T("%g"), ans);
				midcodes += tmpcs;
				AppendText(IDC_MIDDLECODES, midcodes);
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
				tmp = "_" + getvalue();
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
				tmp = "_" + getvalue();
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
				tmp = "_" + getvalue();
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
				tmp = "_" + getvalue();
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
				tmp = "_" + getvalue();
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
					if (i == 1)		//E->E+T, there is T
					{
						if (tmp[1] == '_')
						{
							//cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpcs.Format(_T("%d"), vars[tmp.substr(2)].num);
							midcodes = _T("    Push   ")+tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd += vars[tmp.substr(2)].value;
						}
						else
						{
							//cout << "    Pushi  " << tmp.substr(2) << endl;
							midcodes = _T("    Pushi  ");
							tmpcs=tmp.substr(2).c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd += strtodoub(tmp.substr(2));
						}
					}
					else if (i == 3)	//E->E+T, there is E
					{
						if (tmp[1] == '_')
						{
							//cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpcs.Format(_T("%d"), vars[tmp.substr(2)].num);
							midcodes = _T("    Push   ") + tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd += vars[tmp.substr(2)].value;
						}
						else
						{
							//cout << "    Pushi  " << tmp.substr(2) << endl;
							midcodes = _T("    Pushi  ");
							tmpcs = tmp.substr(2).c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd += strtodoub(tmp.substr(2));
						}

						//cout << "    Add    " << endl;
						midcodes = _T("    Add    ");
						AppendText(IDC_MIDDLECODES, midcodes);
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
					if (i == 1)	//E->E-T,there is T
					{
						if (tmp[1] == '_')
						{
							//cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpcs.Format(_T("%d"), vars[tmp.substr(2)].num);
							midcodes = _T("    Push   ") + tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd -= vars[tmp.substr(2)].value;
						}
						else
						{
							//cout << "    Pushi  " << tmp.substr(2) << endl;
							midcodes = _T("    Pushi  ");
							tmpcs=tmp.substr(2).c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd -= strtodoub(tmp.substr(2));
						}
					}
					else if (i == 3)//E->E-T,there is E
					{
						if (tmp[1] == '_')
						{
							//cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpcs.Format(_T("%d"), vars[tmp.substr(2)].num);
							midcodes = _T("    Push   ") + tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd += vars[tmp.substr(2)].value;
						}
						else
						{
							//cout << "    Pushi  " << tmp.substr(2) << endl;
							midcodes = _T("    Pushi  ");
							tmpcs=tmp.substr(2).c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd += strtodoub(tmp.substr(2));
						}
						//cout << "    Sub    " << endl;
						midcodes = _T("    Sub    ");
						AppendText(IDC_MIDDLECODES, midcodes);
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
			if (m == '+' || m == '-' || m == ')' || m == ';' || m == '*' || m == '/')
			{
				tmpd = 0;
				for (int i = 1; i <= 3; i++)
				{
#ifdef middlecode
					tmp = cal.top();
					if (i == 1)		//T->T*F,there is F
					{
						if (tmp[1] == '_')
						{
							//cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpcs.Format(_T("%d"), vars[tmp.substr(2)].num);
							midcodes = _T("    Push   ") + tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd += vars[tmp.substr(2)].value;
						}
						else
						{
							//cout << "    Pushi  " << tmp.substr(2) << endl;
							midcodes = _T("    Pushi  ");
							tmpcs=tmp.substr(2).c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd += strtodoub(tmp.substr(2));
						}
					}
					else if (i == 3)		//T->T*F,there is T
					{
						if (tmp[1] == '_')
						{
							//cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpcs.Format(_T("%d"), vars[tmp.substr(2)].num);
							midcodes = _T("    Push   ") + tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd *= vars[tmp.substr(2)].value;
						}
						else
						{
							//cout << "    Pushi  " << tmp.substr(2) << endl;
							midcodes = _T("    Pushi  ");
							tmpcs=tmp.substr(2).c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd *= strtodoub(tmp.substr(2));
						}
						//cout << "    Mul    " << endl;
						midcodes = _T("    Mul    ");
						AppendText(IDC_MIDDLECODES, midcodes);
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
					if (i == 1)		//T->T/F,there is F
					{
						if (tmp[1] == '_')
						{
							//cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpcs.Format(_T("%d"), vars[tmp.substr(2)].num);
							midcodes = _T("    Push   ") + tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd += vars[tmp.substr(2)].value;
						}
						else
						{
							//cout << "    Pushi  " << tmp.substr(2) << endl;
							midcodes = _T("    Pushi  ");
							tmpcs=tmp.substr(2).c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd += strtodoub(tmp.substr(2));
						}
						if (tmpd == 0)
						{
							errorlist.push_back(15);
							throw exception();
						}
					}
					else if (i == 3)		//T->T/F,there is T
					{
						if (tmp[1] == '_')
						{
							//cout << "    Push   " << vars[tmp.substr(2)].num << endl;
							tmpcs.Format(_T("%d"), vars[tmp.substr(2)].num);
							midcodes = _T("    Push   ") + tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd = vars[tmp.substr(2)].value / tmpd;
						}
						else
						{
							//cout << "    Pushi  " << tmp.substr(2) << endl;
							midcodes = _T("    Pushi  ");
							tmpcs=tmp.substr(2).c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
							tmpd = strtodoub(tmp.substr(2)) / tmpd;
						}
						//cout << "    Div    " << endl;
						midcodes = _T("    Div    ");
						AppendText(IDC_MIDDLECODES, midcodes);
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
				tmp = "F" + tmp.substr(1);
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
	while (cin.peek() == '\t' || cin.peek() == '\n' || cin.peek() == ' ')
	{
		cin.get();
	}
}

char getsym()
{
	char c = cin.get();
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
	while ((m >= 'A'&&m <= 'Z') || (m >= 'a'&&m <= 'z') || (m >= '0'&&m <= '9') || m == '.')
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
void C编译原理课程设计简易C中间代码生成器Dlg::booleanstatement()
{
	string value;
	bool tlabel = false;
	char lastlabel;
	char m = cin.peek();
	if (m != ')')
	{
		value = getvalue();
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
				//cout << "    Push   " << vars[value].num << endl;
				tmpcs.Format(_T("%d"), vars[value].num);
				midcodes = _T("    Push   ") + tmpcs;
				AppendText(IDC_MIDDLECODES, midcodes);
			}
#endif
			if ((sym == '=') && (m == '<' || m == '>' || m == '!' || m == '='))
			{
				sym = getsym();
#ifdef middlecode
				tlabel = true;
#endif
			}
			value = getvalue();
#ifdef middlecode
			if (!isnum(value) && vars[value].num == 0)
			{
				cout << "Fatal Error:Variable " << value << "is not defined." << endl;
				errorlist.push_back(13);
				throw exception();
			}
			else
			{
				if (isnum(value))
				{
					//cout << "    Pushi  " << value << endl;
					midcodes = _T("    Pushi  ");
					tmpcs=value.c_str();
					midcodes += tmpcs;
					AppendText(IDC_MIDDLECODES, midcodes);
				}
				else
				{
					//cout << "    Push   " << vars[value].num << endl;
					tmpcs.Format(_T("%d"), vars[value].num);
					midcodes = _T("    Push   ") + tmpcs;
					AppendText(IDC_MIDDLECODES, midcodes);
				}
				switch (lastlabel)
				{
				case '<':
					if (tlabel)
					{
						//cout << "    Leq    " << endl;
						midcodes = _T("    Leq    ");
						AppendText(IDC_MIDDLECODES, midcodes);
					}
					else
					{
						//cout << "    Ls     " << endl;
						midcodes = _T("    Ls     ");
						AppendText(IDC_MIDDLECODES, midcodes);
					}
					break;
				case '>':
					if (tlabel)
					{
						//cout << "    Geq    " << endl;
						midcodes = _T("    Geq    ");
						AppendText(IDC_MIDDLECODES, midcodes);
					}
					else
					{
						//cout << "    Gt     " << endl;
						midcodes = _T("    Gt     ");
						AppendText(IDC_MIDDLECODES, midcodes);
					}
					break;
				case '!':
					if (tlabel)
					{
						//cout << "    Noteq  " << endl;
						midcodes = _T("    Noteq  ");
						AppendText(IDC_MIDDLECODES, midcodes);
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
						//cout << "    Eq     " << endl;
						midcodes = _T("    Eq     ");
						AppendText(IDC_MIDDLECODES, midcodes);
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
	if (sym != m)
	{
		errorlist.push_back(9);
		throw exception();
	}
	sym = getsym();
	booleanstatement();
#ifdef middlecode
	if (m == '&')
	{
		//cout << "    And    " << endl;
		midcodes = _T("    And    ");
		AppendText(IDC_MIDDLECODES, midcodes);
	}
	else
	{
		//cout << "    Or     " << endl;
		midcodes = _T("    Or     ");
		AppendText(IDC_MIDDLECODES, midcodes);
	}
#endif
}

//ifstatement goes here
//do if-statement,and if there exists a "else",do else,otherwise another statement
void C编译原理课程设计简易C中间代码生成器Dlg::ifstatement()
{
#ifdef syntaxtree
	for (int i = 1; i <= depth; i++)
		cout << "  ";
	cout << depth<<"if-statement" << endl;
#ifdef synlabel
	//cout << depth << "i";
#endif
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
	cout << depth<<"boolean-statement" << endl;
#ifdef synlabel
	//cout << depth << "b";
#endif
	depth++;
#endif
#ifdef middlecode
	//cout << "label " << label++ << ":" << endl;
	label++;
	midcodes = _T("label   ");
	tmpcs.Format(_T("%d:"), label - 1);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
#endif
	//boolean codes goes here
	booleanstatement();
#ifdef middlecode
	//cout << "    jmpz  " << label << endl;
	midcodes = _T("    jmpz   ");
	tmpcs.Format(_T("%d"), label);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
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
void C编译原理课程设计简易C中间代码生成器Dlg::forstatement()
{
#ifdef syntaxtree
	for (int i = 1; i <= depth; i++)
		cout << "  ";
	cout << depth<<"for-statement" << endl;
#ifdef synlabel
	//cout << depth << "f";
#endif
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
	cout <<depth<< "declare" << endl;
#ifdef synlabel
	//cout << depth << "d";
#endif
#endif
	declare();
#ifdef syntaxtree
	for (int i = 1; i <= depth; i++)
		cout << "  ";
	cout <<depth<< "boolean-statement" << endl;
#ifdef synlabel
	//cout << depth << "b";
#endif
#endif
	//boolean codes goes here
#ifdef middlecode
	//cout << "label " << label++ << ":" << endl;
	label++;
	midcodes = _T("label   ");
	tmpcs.Format(_T("%d:"), label - 1);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
#endif
	booleanstatement();
#ifdef middlecode
	//cout << "    jnz  " << label + 1 << endl;
	midcodes = _T("    jnz    ");
	tmpcs.Format(_T("%d"), label + 1);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);

	//cout << "    jmp   " << label + 2 << endl;
	midcodes = _T("    jmp    ");
	tmpcs.Format(_T("%d"), label + 2);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
#endif
	sym = getsym();
	if (sym != ';')
	{
		errorlist.push_back(8);//missing ;,error 8
		throw exception();
	}
#ifdef middlecode
	//cout << "label " << label++ << ":" << endl;
	label++;
	midcodes = _T("label   ");
	tmpcs.Format(_T("%d:"), label - 1);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
#endif

	word = getword();
	statement();
#ifdef middlecode 
	//cout << "    jmp   " << label - 2 << endl;
	midcodes = _T("    jmp    ");
	tmpcs.Format(_T("%d"), label - 2);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
#endif
#ifdef syntaxtree
	depth++;
#endif

#ifdef middlecode
	//cout << "label " << label++ << ":" << endl;
	label++;
	midcodes = _T("label   ");
	tmpcs.Format(_T("%d:"), label - 1);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
#endif

	word = getword();
	compoundstatement();

#ifdef middlecode
	//cout << "    jmp   " << label - 2 << endl;
	midcodes = _T("    jmp    ");
	tmpcs.Format(_T("%d"), label - 2);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);

	//cout << "label " << label++ << ":" << endl;
	label++;
	midcodes = _T("label   ");
	tmpcs.Format(_T("%d:"), label - 1);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
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
void C编译原理课程设计简易C中间代码生成器Dlg::whilestatement()
{
#ifdef syntaxtree
	for (int i = 1; i <= depth; i++)
		cout << "  ";
	cout << depth<<"while-statement" << endl;
#ifdef synlabel
	//cout << depth << "w";
#endif
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
	cout << depth<<"boolean-statement" << endl;
#ifdef synlabel
	//cout << depth << "b";
#endif
	depth++;
#endif
	//boolean codes goes here
#ifdef middlecode
	//cout << "label " << label++ << ":" << endl;
	label++;
	midcodes = _T("label   ");
	tmpcs.Format(_T("%d:"), label - 1);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
#endif
	booleanstatement();
#ifdef middlecode
	//cout << "    jmpz  " << label << endl;
	midcodes = _T("    jmpz   ");
	tmpcs.Format(_T("%d"), label);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
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
	//cout << "    jmp    " << label - 1 << endl;
	midcodes = _T("    jmp    ");
	tmpcs.Format(_T("%d"), label - 1);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
#endif
#ifdef middlecode
	//cout << "label " << label++ << ":" << endl;
	label++;
	midcodes = _T("label   ");
	tmpcs.Format(_T("%d:"), label - 1);
	midcodes += tmpcs;
	AppendText(IDC_MIDDLECODES, midcodes);
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

void C编译原理课程设计简易C中间代码生成器Dlg::compoundstatement()
{
#ifdef syntaxtree
#endif
	while (cin.peek() != '}'&&sym != '}')
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

void C编译原理课程设计简易C中间代码生成器Dlg::statement()
{
	char oldsym;
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
		if (hasif&&!ifmatch&&word != "else")
		{
#ifdef middlecode
			//cout << "label " << label++ << ":" << endl;
			label++;
			midcodes = _T("label   ");
			tmpcs.Format(_T("%d:"), label - 1);
			midcodes += tmpcs;
			AppendText(IDC_MIDDLECODES, midcodes);
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
			ifmatch = true;
#ifdef syntaxtree
			for (int i = 1; i <= depth; i++)
				cout << "  ";
			cout << depth<<"else-statement" << endl;
#ifdef synlabel
			//cout << depth << "e";
#endif
			depth += 2;
#endif
#ifdef middlecode
			//cout << "    jmp    " << label + 1 << endl;
			midcodes = _T("    jmp    ");
			tmpcs.Format(_T("%d"), label + 1);
			midcodes += tmpcs;
			AppendText(IDC_MIDDLECODES, midcodes);

			//cout << "label " << label++ << ":" << endl;
			label++;
			midcodes = _T("label   ");
			tmpcs.Format(_T("%d:"), label - 1);
			midcodes += tmpcs;
			AppendText(IDC_MIDDLECODES, midcodes);

#endif
			word = getword();
			statement();
#ifdef middlecode
			//cout << "label " << label++ << ":" << endl;
			label++;
			midcodes = _T("label   ");
			tmpcs.Format(_T("%d:"), label - 1);
			midcodes += tmpcs;
			AppendText(IDC_MIDDLECODES, midcodes);
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
		else if (word == "read")
		{
			word = getword();
			sym = getsym();
			if (sym != ';'&&sym != ')')
			{
				errorlist.push_back(8);//missing ;,error 8
				throw exception();
			}
			if (vars[word].num == 0)
			{
				errorlist.push_back(13);
				throw exception();
			}
#ifdef syntaxtree
			for (int i = 1; i <= depth; i++)
				cout << "  ";
			cout << depth << "statement" << endl;
#endif

#ifdef middlecode
			midcodes = _T("    Read   ");
			tmpcs.Format(_T("%d"), vars[word].num);
			midcodes += tmpcs;
			AppendText(IDC_MIDDLECODES, midcodes);

#endif
			return;
		}
		else	//equation such as a=6;b=3;c=b;
		{
#ifdef syntaxtree
			for (int i = 1; i <= depth; i++)
				cout << "  ";
			cout << depth<<"statement" << endl;
#ifdef synlabel
			//cout << depth << "s";
#endif
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
				//cout << "    Push   " << vars[word].num << endl;
				midcodes = _T("    Push   ");
				tmpcs.Format(_T("%d"), vars[word].num);
				midcodes += tmpcs;
				AppendText(IDC_MIDDLECODES, midcodes);

				//cout << "    Pushi  1" << endl;
				midcodes = _T("    Pushi  1");
				AppendText(IDC_MIDDLECODES, midcodes);
				if (m == '+')
				{
					//cout << "    Add   " << endl;
					midcodes = _T("    Add   ");
					AppendText(IDC_MIDDLECODES, midcodes);
					vars[word].value += 1;
				}
				else
				{
					//cout << "    Sub   " << endl;
					midcodes = _T("    Sub   ");
					AppendText(IDC_MIDDLECODES, midcodes);
					vars[word].value -= 1;
				}
				//cout << "    Sto    " << vars[word].num << endl;
				midcodes = _T("    Sto    ");
				tmpcs.Format(_T("%d"), vars[word].num);
				midcodes += tmpcs;
				AppendText(IDC_MIDDLECODES, midcodes);
				//cout << word << "\t" << vars[word].value << endl;
#endif
				return;
			}
			else if (sym == '=')
			{
				vars[word].value = calculation();
				vars[word].init = true;
#ifdef middlecode
				midcodes = _T("    Sti    ");
				tmpcs.Format(_T("%d"), vars[word].num);
				midcodes += tmpcs;
				AppendText(IDC_MIDDLECODES, midcodes);
#endif
				//cout << word << "\t" << vars[word].value << endl;
			}
			else
			{
				errorlist.push_back(10);
				throw exception();
			}
			getvalue();
			sym = getsym();
			if (sym != ';'&&sym != ')')
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
void C编译原理课程设计简易C中间代码生成器Dlg::declare()
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
					value = getvalue();
					sym = getsym();
#ifdef middlecode
					if (vars[word].num == 0)
					{
						//if value is char--,then should use Push instead of Pushi
						if (isalpha(value[0]))
						{
							//cout << "    Push  " << vars[value].num << endl;
							midcodes = _T("    Push   ");
							if (vars[value].init == false)
							{
								errorlist.push_back(14);
								throw exception();
							}
							tmpcs.Format(_T("%d"), vars[value].num);
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);

							//cout << "    Sto    " << varnum << endl;
							midcodes = _T("    Sto    ");
							tmpcs.Format(_T("%d"), varnum);
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);

							vars[word].value = vars[value].value;
							vars[word].init = true;
							vars[word].num = varnum++;
						}
						else
						{
							//cout << "    Pushi " << value << endl;
							midcodes = _T("    Pushi  ");

							tmpcs = value.c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);

							//cout << "    Sto    " << varnum << endl;
							midcodes = _T("    Sto    ");
							tmpcs.Format(_T("%d"), varnum);
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);

							vars[word].value = strtodoub(value);
							vars[word].init = true;
							vars[word].num = varnum++;
						}

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
					if (word.length() != 0)
					{
						if (vars[word].num == 0)
						{
							vars[word].num = varnum++;
						}
						else
						{
							errorlist.push_back(12);
							throw exception();
						}
					}
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
					value = getvalue();
					sym = getsym();
#ifdef middlecode
					if (vars[word].num == 0)
					{
						if (isalpha(value[0]))
						{
							//cout << "    Push  " << vars[value].num << endl;
							midcodes = _T("    Push   ");
							if (vars[value].init == false)
							{
								errorlist.push_back(14);
								throw exception();
							}
							tmpcs.Format(_T("%d"), vars[value].num);
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
						}
						else
						{
							//cout << "    Pushi " << value << endl;
							midcodes = _T("    Pushi  ");

							tmpcs = value.c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);
						}
						//cout << "    Sto    " << varnum << endl;
						midcodes = _T("    Sto    ");
						tmpcs.Format(_T("%d"), varnum);
						midcodes += tmpcs;
						AppendText(IDC_MIDDLECODES, midcodes);



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
					value = getachar();	//get the value
					sym = getsym();
#ifdef middlecode
					if (vars[word].num == 0)
					{
						if (value[0] == '\'')
						{
							//cout << "    Pushi " << value << endl;
							midcodes = _T("    Pushi  ");
							tmpcs = value.c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);

							value = value[1];
							vars[word].value = strtodoub(value);

							//cout << "    Sto    " << varnum << endl;
							midcodes = _T("    Sto    ");
							tmpcs.Format(_T("%d"), varnum);
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);

						}
						else if (isdigit(value[0]))
						{
							//cout << "    Pushi " << value << endl;
							midcodes = _T("    Pushi  ");
							tmpcs = value.c_str();
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);

							//cout << "    Sto    " << varnum << endl;
							midcodes = _T("    Sto    ");
							tmpcs.Format(_T("%d"), varnum);
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);


							vars[word].value = strtodoub(value);
						}
						else
						{
							//cout << "    Push  " << vars[value].num << endl;
							midcodes = _T("    Push  ");
							tmpcs.Format(_T("%d"), vars[value].num);
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);

							//cout << "    Sto    " << varnum << endl;
							midcodes = _T("    Sto    ");
							tmpcs.Format(_T("%d"), varnum);
							midcodes += tmpcs;
							AppendText(IDC_MIDDLECODES, midcodes);

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

void C编译原理课程设计简易C中间代码生成器Dlg::entrance()		//main entrance
{
#ifdef syntaxtree
	for (int i = 1; i < depth; i++)
		cout << "  ";
	cout << depth<<"main" << endl;
#ifdef synlabel
	//cout << depth << "m";
#endif
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
		cout << depth<<"declare" << endl;
#ifdef synlabel
		//cout << depth << "d";
#endif
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
	cout <<depth<< "end" << endl;
#ifdef synlabel
	//cout << depth << "x";
#endif
#endif
}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C编译原理课程设计简易C中间代码生成器Dlg 对话框



C编译原理课程设计简易C中间代码生成器Dlg::C编译原理课程设计简易C中间代码生成器Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C编译原理课程设计简易C中间代码生成器Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C编译原理课程设计简易C中间代码生成器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C编译原理课程设计简易C中间代码生成器Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Load, &C编译原理课程设计简易C中间代码生成器Dlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_EXECUTE, &C编译原理课程设计简易C中间代码生成器Dlg::OnBnClickedExecute)
	ON_BN_CLICKED(IDC_CLEAR, &C编译原理课程设计简易C中间代码生成器Dlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_CONPILE, &C编译原理课程设计简易C中间代码生成器Dlg::OnBnClickedConpile)
	ON_BN_CLICKED(IDC_CONFIRM, &C编译原理课程设计简易C中间代码生成器Dlg::OnBnClickedConfirm)
END_MESSAGE_MAP()


// C编译原理课程设计简易C中间代码生成器Dlg 消息处理程序

BOOL C编译原理课程设计简易C中间代码生成器Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	font.CreatePointFont(120, _T("consolas"));
	GetDlgItem(IDC_MIDDLECODES)->SetFont(&font);
	GetDlgItem(IDC_CODES)->SetFont(&font);
	GetDlgItem(IDC_SYNTAX)->SetFont(&font);
	GetDlgItem(IDC_INPUT)->SetFont(&font);
	GetDlgItem(IDC_OUTPUT)->SetFont(&font);
	seterrors();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	GetDlgItem(IDC_CODES)->ShowScrollBar(SB_VERT, TRUE);
	GetDlgItem(IDC_MIDDLECODES)->ShowScrollBar(SB_VERT, TRUE);
	GetDlgItem(IDC_SYNTAX)->ShowScrollBar(SB_VERT, TRUE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C编译原理课程设计简易C中间代码生成器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C编译原理课程设计简易C中间代码生成器Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C编译原理课程设计简易C中间代码生成器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C编译原理课程设计简易C中间代码生成器Dlg::OnBnClickedLoad()
{
	// TODO:  在此添加控件通知处理程序代码
	//GetDlgItem(IDC_MIDDLECODES)->SetWindowTextW(CString("hello world"));
	//freopen("d.txt", "r", stdin);
	//freopen("syn.txt", "w", stdout);
	OnBnClickedClear();
	CString FilePathName;
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("TEXT Files (*.txt)|*.txt|All Files (*.*)|*.*||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName(); //文件名保存在了FilePathName里
		fclose(stdin);
		string filename;
		string content="";
		string tmpss="";
		cin.clear();
		USES_CONVERSION;
		filename = W2A(FilePathName);
		freopen(filename.c_str(), "r", stdin);
		while (cin)
		{
			getline(cin, tmpss);
			content += tmpss+"\r\n";
		}
		cin.clear();
		fclose(stdin);
		CString t;
		t = content.c_str();
		GetDlgItem(IDC_CODES)->SetWindowTextW(t);
		freopen(filename.c_str(), "r", stdin);
		freopen("ans.txt", "w", stdout);
	}
	else
	{
		return;
	}

}


void C编译原理课程设计简易C中间代码生成器Dlg::OnBnClickedExecute()
{
	// TODO:  在此添加控件通知处理程序代码
	//AppendText(IDC_MIDDLECODES, _T("12345"));
	/*
	stack<double> numstack;//定义操作数栈

	int i = 0;
	int StackTopValue;
	double content;
	int operator1;
	int operator2;
	int Code[1000];//0存操作码，1存操作数，CodeMaxLength参数需要确定
	string Num[1000];
	while (i < CodeMaxLength)
	{
		switch (Code[i])
		{
		case 0://Push d
			content = vars[Num[i]].value;
			numstack.push(content);
			i++;
			break;
		case 1://Pushi N
			content = strtodoub(Num[i]);
			numstack.push(content);
			i++;
			break;
		case 2://Sto d
			content = numstack.top();
			vars[Num[i]].value = content;
			i++;
			break;
		case 3://Sti d
			content = numstack.top();
			vars[Num[i]].value = content;
			numstack.pop();
			i++;
			break;
		case 4://Add
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			numstack.push(operator1 + operator2);
			i++;
			break;
		case 5://Sub
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			numstack.push(operator1 - operator2);
			i++;
		case 6://Mul
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			numstack.push(operator1 * operator2);
			i++;
		case 7://Div
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			numstack.push(operator1 / operator2);
			i++;
		case 8://jmp
			i++;
			break;
		case 9://jnz
			i++;
			break;
		case 10://jmpz
			i++;
			break;
		case 11://Eq
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			if (operator1 == operator2)
				numstack.push(1);
			else numstack.push(0);
			i++;
			break;
		case 12://Noteq
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			if (operator1 == operator2)
				numstack.push(0);
			else numstack.push(1);
			i++;
			break;
		case 13://Gt
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			if (operator1 < operator2)
				numstack.push(1);
			else numstack.push(0);
			i++;
			break;
		case 14://Ls
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			if (operator1 > operator2)
				numstack.push(1);
			else numstack.push(0);
			i++;
			break;
		case 15://Geq
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			if (operator1 <= operator2)
				numstack.push(1);
			else numstack.push(0);
			i++;
			break;
		case 16://Leq
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			if (operator1 >= operator2)
				numstack.push(1);
			else numstack.push(0);
			i++;
			break;
		case 17://And
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			numstack.push(operator1&&operator2);
			i++;
			break;
		case 18://Or
			operator1 = numstack.top();
			numstack.pop();
			operator2 = numstack.top();
			numstack.pop();
			numstack.push(operator1 || operator2);
			i++;
			break;
		case 19://Not
			operator1 = numstack.top();
			numstack.pop();
			numstack.push(!operator1);
			i++;
			break;
		case 20://Stop
			i = CodeMaxLength;
			break;
		case 21:	//Read
		{
			CString s;
			GetDlgItem(IDC_INPUT)->GetWindowTextW(s);
			GetDlgItem(IDC_OUTPUT)->SetWindowTextW(s);
		}
			break;
		default:
			i++;
			break;
		}
	}
	*/
}


void C编译原理课程设计简易C中间代码生成器Dlg::OnBnClickedClear()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_MIDDLECODES)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_CODES)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_SYNTAX)->SetWindowTextW(_T(""));
	depth = 2;
	errorlist.clear();
	varnum = 1;
	ifmatch = false;
	hasif = false;
	CodeMaxLength = 0;
	vars.clear();
	label = 0;
	syns="";
	totalcodes = "";
	fclose(stdin);
	fclose(stdout);
//	findallsharps();
//	OnBnClickedReplace();
//	replacelabel(0,0);

}


void C编译原理课程设计简易C中间代码生成器Dlg::OnBnClickedConpile()
{
	// TODO:  在此添加控件通知处理程序代码
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
		cout << errorlist[0] << endl;
		midcodes = _T("##Catch ERROR##");
		AppendText(IDC_MIDDLECODES, midcodes);
		midcodes.Format(_T("%d"), errorlist[0]);
		AppendText(IDC_MIDDLECODES, midcodes);
		midcodes=errors[errorlist[0]].c_str();
		AppendText(IDC_MIDDLECODES, midcodes);
		ShowCodes(IDC_MIDDLECODES, totalcodes);
		return;
	}
	cout << "\n##SUCCESS##" << endl;
	ShowCodes(IDC_MIDDLECODES, totalcodes);
	fclose(stdin);
	string tmpss = "";
	string content = "";
	freopen("ans.txt", "r", stdin);
	cin.clear();
	while (cin)
	{
		getline(cin, tmpss);
		if (tmpss.length() != 0)
			content += tmpss + "\r\n";
	}
	cin.clear();
	fclose(stdin);
	CString t;
	t = content.c_str();
	GetDlgItem(IDC_SYNTAX)->SetWindowTextW(t);
	return;
}


void C编译原理课程设计简易C中间代码生成器Dlg::OnBnClickedConfirm()
{

	// TODO:  在此添加控件通知处理程序代码
	inputconfirm = true;
	
}