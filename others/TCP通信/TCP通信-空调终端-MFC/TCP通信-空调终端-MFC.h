
// TCP通信-空调终端-MFC.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CTCP通信空调终端MFCApp: 
// 有关此类的实现，请参阅 TCP通信-空调终端-MFC.cpp
//

class CTCP通信空调终端MFCApp : public CWinApp
{
public:
	CTCP通信空调终端MFCApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CTCP通信空调终端MFCApp theApp;