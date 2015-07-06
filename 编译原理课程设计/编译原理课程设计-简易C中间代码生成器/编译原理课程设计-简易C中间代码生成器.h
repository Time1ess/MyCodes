
// 编译原理课程设计-简易C中间代码生成器.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// C编译原理课程设计简易C中间代码生成器App: 
// 有关此类的实现，请参阅 编译原理课程设计-简易C中间代码生成器.cpp
//

class C编译原理课程设计简易C中间代码生成器App : public CWinApp
{
public:
	C编译原理课程设计简易C中间代码生成器App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C编译原理课程设计简易C中间代码生成器App theApp;