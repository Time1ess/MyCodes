#include "afxdialogex.h"
#include "TCP通信-空调终端-MFC.h"
#include "TCP通信-空调终端-MFCDlg.h"
#include <stdlib.h>



class STATUS
{
private:

	bool on;		//开关状态
	int mode;		//模式
	bool cooling;		//制冷/制热
	bool sleep;			//睡眠
	int time;		//定时
	int temperature;		//温度
	int rate;			//风量
	CTCP通信空调终端MFCDlg * pointer;
public:
	STATUS();
	~STATUS();
	void setPointer(LPVOID pParam);
	void Reset();
	void checkInstrucion(char *ins,int val);
	void setOn();
	void setMode(int m);
	void setCooling();
	void setSleep();
	void setTime(int c);
	void setTemperature(int t);
	void setRate(int r);
	void setAirconditioner();
};