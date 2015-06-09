#include "STATUS.h"
#include "stdafx.h"

STATUS::STATUS()
{
	on=false;		
	mode=0;		
	cooling = true;		//制冷/制热
	sleep = false;			//睡眠
	time = -1;		//定时
	temperature = 26;		//温度
	rate = 0;			//风量
	
}

STATUS::~STATUS()
{

}

void STATUS::setPointer(LPVOID pParam)
{
	pointer = (CTCP通信空调终端MFCDlg *)pParam;
}

void STATUS::checkInstrucion(char *ins,int val)
{
	pointer->SetDlgItemText(IDC_TEST, CString(ins));
	if (!strcmp(ins, "POWER"))
	{
		setOn();
		return;
	}
	if (!strcmp(ins, "MODE"))
	{
		setMode(val);
		return;
	}
	if (!strcmp(ins, "RATE"))
	{
		setRate(val);
		return;
	}
	if (!strcmp(ins, "SLEEP"))
	{
		setSleep();
		return;
	}
	if (!strcmp(ins, "TIME"))
	{
		setTime(val);
		return;
	}
	if (!strcmp(ins, "TEMPERATURE"))
	{
		setTemperature(val);
		return;
	}
}

void STATUS::Reset()
{
	mode = 0;
	cooling = true;		//制冷/制热
	sleep = false;			//睡眠
	time = -1;		//定时
	temperature = 26;		//温度
	rate = 0;			//风量
}

void STATUS::setOn()
{
	on=on == true ? false : true;
	if (on)Reset();
	setAirconditioner();
}
void STATUS::setMode(int m)
{
	if (!on)return;
	if (mode == m || m<0 || m>2)return;
	mode = m;
	setAirconditioner();
}
void STATUS::setCooling()
{
	if (!on)return;
	cooling=cooling == true ? false : true;
	setAirconditioner();
}
void STATUS::setSleep()
{
	if (!on)return;
	sleep=sleep == true ? false : true;
	setAirconditioner();
}
void STATUS::setTime(int c)
{
	if (!on)return;
	if (c < -1)return;
	time = c;
	setAirconditioner();
}
void STATUS::setTemperature(int t)
{
	if (!on)return;
	int tmp = temperature + t;
	if (tmp<10 || tmp>36)return;
	temperature = tmp;
	setAirconditioner();
}
void STATUS::setRate(int r)
{
	if (!on)return;
	if (rate == r || r<0 || r>3)return;
	rate = r;
	setAirconditioner();
}
void STATUS::setAirconditioner()
{
	static const char* MODES[3]{"自动", "制冷", "制热"};
	static const char* RATES[4]{"自动", "低风", "中风", "高风"};
	if (on)
	{
		CString temp,temptime;
		temp.Format(_T("%d"),temperature);
		temptime.Format(_T("%d"), time);
		pointer->SetDlgItemText(IDC_ONOFF, CString("运行中"));
		pointer->SetDlgItemText(IDC_TEMPRATURE, temp);
		pointer->SetDlgItemText(IDC_MODE, CString(MODES[mode]));
		pointer->SetDlgItemText(IDC_TIME, time == -1 ? CString("关闭") : temptime);
		pointer->SetDlgItemText(IDC_SLEEP, sleep==false?CString("关闭"):CString("开启"));
		pointer->SetDlgItemText(IDC_RATE, CString(RATES[rate]));
	}
	else
	{
		pointer->SetDlgItemText(IDC_ONOFF, CString("离线中"));
		pointer->SetDlgItemText(IDC_TEMPRATURE, CString("离线中"));
		pointer->SetDlgItemText(IDC_MODE, CString("离线中"));
		pointer->SetDlgItemText(IDC_TIME, CString("离线中"));
		pointer->SetDlgItemText(IDC_SLEEP, CString("离线中"));
		pointer->SetDlgItemText(IDC_RATE, CString("离线中"));
	}
}