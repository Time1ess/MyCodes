/*
本题研究3个野人和3个牧师过河的问题
规则如下：
小船每次最多坐两个人，没有人则无法开动
任意时刻如果河岸任意一边野人数量大于牧师数量，则游戏失败

程序内容：
采用DFS(深度优先搜索）算法，按照野人优先过河的原则
按顺序分别采用2野人、1野人1牧师、1野人、1牧师、2牧师的过河优先级
首先判断当前结点是否顺序满足其中一种情况，判断过河以后河左右两岸的人数合法性
若不合法，则进行下一种情况的尝试
若合法，则将该结点添加至结果序列中
然后采用递归，对新扩展的结点进行以上操作
直至得到3个野人和3个牧师都成功过河的结点序列，将事先设置的判断变量置为TRUE(1)，退出所有循环
输出整个过河的方法
程序结束
*/
#include <iostream>
using namespace std;

#define N 3

struct riverside
{
	int wildman;
	int priest;
};

struct Boat
{
	int side;//0代表当前船在左岸，1为右岸
	int wildman;
	int priest;
};

struct status
{
	riverside rightside;
	riverside leftside;
	Boat boat;              //船的位置代表当前位置，下一次移动将移动到对岸，人数代表下一次移动时将要移动的牧师和野人数量
	status *prev;           //指向当前结点的前一结点
	status *next;           //指向当前结点的后一结点			
};

Boat boatman[5], lastboat;
bool process(status *);
bool thesame(status *);
bool nextmove(status *);
void setstatus();

int flag = 0;          //判断变量，判断是否完成过河操作
status *head = new status;



int main()
{
	setstatus();
	head->rightside.wildman = 0;
	head->rightside.priest = 0;
	head->leftside.priest = N;
	head->leftside.wildman = N;
	head->prev = nullptr;
	head->next = nullptr;
	head->boat.side = 0;
	head->boat.priest = 0;
	head->boat.wildman = 0;
	process(head);
	status *p;
	p = head;
	cout << "结点序列如下:" << endl;
	do
	{
		cout << " 左岸野人:" << p->leftside.wildman << " 左岸牧师:" << p->leftside.priest
			<< " 右岸野人:" << p->rightside.wildman << " 右岸牧师:" << p->rightside.priest << "   下一步操作：";
		if (p->boat.side == 0)cout << "左岸->右岸";
		else cout << "左岸<-右岸";
		cout << endl;
		p = p->next;
	} while (p != nullptr);
	cout << "输出完毕！";
	cin.get();
	return 0;
}

void setstatus()       //对全局变量（小船移动人员的5种情况）进行初始化
{
	boatman[0].wildman = 2;
	boatman[0].priest = 0;
	boatman[1].wildman = 1;
	boatman[1].priest = 1;
	boatman[2].wildman = 1;
	boatman[2].priest = 0;
	boatman[3].wildman = 0;
	boatman[3].priest = 1;
	boatman[4].wildman = 0;
	boatman[4].priest = 2;
	for (int i = 0; i < 5; i++)
		boatman[i].side = 0;
	lastboat.side = 0;
}


bool process(status *node)
{
	int i;
	if (node->rightside.wildman == N && node->rightside.priest == N)flag = 1;
	for (i = 0; i < 5; i++)
	{
		node->boat.wildman = boatman[i].wildman;
		node->boat.priest = boatman[i].priest;
		if (nextmove(node))
			process(node->next);
		if (flag == 1)return true;
	}
	return false;
}

bool thesame(status *p, status *node)
{
	for (p; p != node; p = p->next)
	if ((p->leftside.priest == node->leftside.priest) && (p->leftside.wildman == node->leftside.wildman) && (p->rightside.priest == node->rightside.priest) &&
		(p->rightside.wildman == node->rightside.wildman) && (p->boat.priest == node->boat.side) &&
		(p->boat.wildman == node->boat.wildman) && (p->boat.side == node->boat.side))return false;
	return true;
}

bool nextmove(status *node)
{
	//判断当前结点是否可以进行移动到下一个合法结点
	status *p;
	p = head;
	if (thesame(p, node) == false)return false;      //保证当前结点在结点序列中未曾出现
	if (lastboat.priest == node->boat.priest&&lastboat.wildman == node->boat.wildman)return false;  //保证接下来的动作与刚刚发生的动作不相同
	if (node->boat.side == 1)
	{
		if ((node->rightside.priest - node->boat.priest) < 0)return false;  //保证执行动作后当前岸人数大于等于0
		if ((node->rightside.wildman - node->boat.wildman) < 0)return false; //保证执行动作后当前岸人数大于等于0
		if (((node->rightside.priest - node->boat.priest)<(node->rightside.wildman - node->boat.wildman)) &&
			(node->rightside.priest - node->boat.priest)>0)return false;  //保证当前岸执行动作后在牧师人数不为0时牧师数量大于等于野人数量 
		if ((((node->leftside.priest + node->boat.priest)<(node->leftside.wildman + node->boat.wildman))) &&
			(node->leftside.priest + node->boat.priest)>0)return false;   //保证对岸执行动作后在牧师人数不为0时牧师数量大于等于野人数量
	}
	else
	{
		if ((node->leftside.priest - node->boat.priest) < 0)return false;          //同上
		if ((node->leftside.wildman - node->boat.wildman) < 0)return false;	          //同上
		if ((((node->leftside.priest - node->boat.priest)<(node->leftside.wildman - node->boat.wildman))) &&
			(node->leftside.priest - node->boat.priest)>0)return false;          //同上
		if (((node->rightside.priest + node->boat.priest)<(node->rightside.wildman + node->boat.wildman)) &&
			(node->rightside.priest + node->boat.priest)>0)return false;          //同上
	}
	//如果满足以上条件，则扩展当前结点，进行移动
	status *nodenext = new status;
	node->next = nodenext;
	if (node->boat.side == 0)
	{
		nodenext->rightside.priest = node->rightside.priest + node->boat.priest;
		nodenext->rightside.wildman = node->rightside.wildman + node->boat.wildman;
		nodenext->leftside.priest = node->leftside.priest - node->boat.priest;
		nodenext->leftside.wildman = node->leftside.wildman - node->boat.wildman;
		nodenext->prev = node;
		nodenext->next = nullptr;
		nodenext->boat.side = 1;
		nodenext->boat.priest = nodenext->boat.wildman = 0;
		lastboat.priest = node->boat.priest;
		lastboat.wildman = node->boat.wildman;
	}
	else
	{
		nodenext->rightside.priest = node->rightside.priest - node->boat.priest;
		nodenext->rightside.wildman = node->rightside.wildman - node->boat.wildman;
		nodenext->leftside.priest = node->leftside.priest + node->boat.priest;
		nodenext->leftside.wildman = node->leftside.wildman + node->boat.wildman;
		nodenext->prev = node;
		nodenext->next = nullptr;
		nodenext->boat.side = 0;
		nodenext->boat.priest = nodenext->boat.wildman = 0;
		lastboat.priest = node->boat.priest;
		lastboat.wildman = node->boat.wildman;
	}
	return true;
}