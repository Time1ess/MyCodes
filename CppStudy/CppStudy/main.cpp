#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

class Base
{
private:
	int x;
public:
	Base() :x(11) {}
	void func1() { cout << x << endl; }
	virtual void func2(int a) { cout << x + a << endl; }
	void disp() { cout << x << endl; }
};

class Derived :public Base
{
private:
	int y;
public:
	Derived() :Base() { y = 22; }
	void func1() { cout << y << endl; }
	void func2(int a) { cout << y + a << endl; }
	void disp() { cout << y << endl; }
};

int main()
{
	Derived a;
	Base *p1 = &a;
	Base &p2 = a;
	Base p3 = a;
	p1->func1(); p1->func2(1);
	p2.func1(); p2.func2(2);
	p3.func1(); p3.func2(3);
	a.disp();
	p1->disp();
	cin.get();
	return 0;
}