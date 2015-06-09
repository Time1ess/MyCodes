
// TCP通信-空调终端-MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TCP通信-空调终端-MFC.h"
#include "TCP通信-空调终端-MFCDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <winsock.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdlib.h>
#include <cctype>
#pragma comment(lib,"Ws2_32")
#pragma warning(disable:4996)
#define MAXDATASIZE 100 
#define MYPORT 6667  /*定义用户连接端口*/ 
#define BACKLOG 10  /*多少等待连接控制*/
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char ins[20];//存放指令
int SPACEPOS = -1;
static STATUS status;

UINT CTCP通信空调终端MFCDlg::ThreadProc(LPVOID pParam)
{
	int sockfd, new_fd;                                  /*定义套接字*/
	struct sockaddr_in my_addr;          /*本地地址信息 */
	struct sockaddr_in their_addr;        /*连接者地址信息*/
	int sin_size, numbytes;   char msg[10], buf[MAXDATASIZE];
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);           //初始化Windows Socket Dll
	//建立socket
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		//如果建立socket失败，退出程序
		//printf("socket error\n");
		exit(1);
	}
	bool optval = true;
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(bool));
	//bind本机的MYPORT端口
	my_addr.sin_family = AF_INET;                     /* 协议类型是INET  */
	my_addr.sin_port = htons(MYPORT);            /* 绑定MYPORT端口*/
	my_addr.sin_addr.s_addr = INADDR_ANY;    /* 本机IP*/
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{
		//bind失败，退出程序
		//printf("bind error\n");
		closesocket(sockfd);
		exit(1);
	}


	//listen，监听端口
	//printf("listen...\n");
	int ret;
	int size = sizeof(struct sockaddr);
	while (1)
	{
		//	if ((numbytes = recv(new_fd, buf, MAXDATASIZE, 0)) == -1)  continue;
		ret = recvfrom(sockfd, buf, MAXDATASIZE, 0, (SOCKADDR*)&my_addr, &size);
		//Instructions(pParam,buf, sizeof(buf));
		SPACEPOS = -1;
		while (!(buf[++SPACEPOS] == ' '||buf[SPACEPOS] == '\0'));
		strcpy(ins, buf);
		ins[SPACEPOS] = '\0';
		status.checkInstrucion(ins, atoi(buf + SPACEPOS + 1));
		//printf("\n");
	}
	return 0;
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


// CTCP通信空调终端MFCDlg 对话框



CTCP通信空调终端MFCDlg::CTCP通信空调终端MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCP通信空调终端MFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCP通信空调终端MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTCP通信空调终端MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INIT, &CTCP通信空调终端MFCDlg::OnBnClickedInit)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_ON, &CTCP通信空调终端MFCDlg::OnBnClickedBtnOn)
	ON_BN_CLICKED(IDC_BTN_RATE, &CTCP通信空调终端MFCDlg::OnBnClickedBtnRate)
	ON_BN_CLICKED(IDC_BTN_TIME, &CTCP通信空调终端MFCDlg::OnBnClickedBtnTime)
	ON_BN_CLICKED(IDC_BTN_SLEEP2, &CTCP通信空调终端MFCDlg::OnBnClickedBtnSleep2)
	ON_BN_CLICKED(IDC_BTN_UP, &CTCP通信空调终端MFCDlg::OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, &CTCP通信空调终端MFCDlg::OnBnClickedBtnDown)
	ON_BN_CLICKED(IDC_BTN_MODE, &CTCP通信空调终端MFCDlg::OnBnClickedBtnMode)
	ON_BN_CLICKED(IDC_BTN_ON, &CTCP通信空调终端MFCDlg::OnClickedBtnOn)
	ON_BN_CLICKED(IDC_BTN_POWER, &CTCP通信空调终端MFCDlg::OnBnClickedBtnPower)
END_MESSAGE_MAP()


// CTCP通信空调终端MFCDlg 消息处理程序

BOOL CTCP通信空调终端MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	//OnBnClickedInit();


	status.setPointer((LPVOID)this);
	status.setAirconditioner();
	Thread1 = AfxBeginThread(ThreadProc, (LPVOID)this);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTCP通信空调终端MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTCP通信空调终端MFCDlg::OnPaint()
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
HCURSOR CTCP通信空调终端MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTCP通信空调终端MFCDlg::OnBnClickedInit()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_ONOFF, CString("离线中"));
	SetDlgItemText(IDC_TEMPRATURE, CString("26"));
	SetDlgItemText(IDC_TIME, CString("关"));
	SetDlgItemText(IDC_MODE, CString("制冷"));
	SetDlgItemText(IDC_SLEEP, CString("关"));
	SetDlgItemText(IDC_RATE, CString("自动"));
}


HBRUSH CTCP通信空调终端MFCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	CString onoff;
	GetDlgItemText(IDC_ONOFF, onoff);
	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_ONOFF || pWnd->GetDlgCtrlID() == IDC_TEMPRATURE || pWnd->GetDlgCtrlID() == IDC_TIME
		|| pWnd->GetDlgCtrlID() == IDC_MODE || pWnd->GetDlgCtrlID() == IDC_SLEEP || pWnd->GetDlgCtrlID() == IDC_RATE)
	{
		if (onoff == "离线中")
		{
			pDC->SetTextColor(RGB(255, 0, 0));       
		}
		else if (onoff == "运行中")
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CTCP通信空调终端MFCDlg::OnBnClickedBtnOn()
{
	// TODO:  在此添加控件通知处理程序代码
	
}


void CTCP通信空调终端MFCDlg::OnBnClickedBtnRate()
{
	// TODO:  在此添加控件通知处理程序代码
	static int rate = 0;
	status.checkInstrucion("RATE", (rate++)%4);
}


void CTCP通信空调终端MFCDlg::OnBnClickedBtnTime()
{
	// TODO:  在此添加控件通知处理程序代码
	status.checkInstrucion("TIME", 100);
}


void CTCP通信空调终端MFCDlg::OnBnClickedBtnSleep2()
{
	// TODO:  在此添加控件通知处理程序代码
	status.checkInstrucion("SLEEP", NULL);
}


void CTCP通信空调终端MFCDlg::OnBnClickedBtnUp()
{
	// TODO:  在此添加控件通知处理程序代码
	status.checkInstrucion("TEMPERATURE", 1);
}


void CTCP通信空调终端MFCDlg::OnBnClickedBtnDown()
{
	// TODO:  在此添加控件通知处理程序代码
	status.checkInstrucion("TEMPERATURE", -1);
}


void CTCP通信空调终端MFCDlg::OnBnClickedBtnMode()
{
	// TODO:  在此添加控件通知处理程序代码
	static int mode = 0;
	status.checkInstrucion("MODE", (mode++)%3);
}


void CTCP通信空调终端MFCDlg::OnClickedBtnOn()
{
	// TODO:  在此添加控件通知处理程序代码
	status.checkInstrucion("POWER", NULL);
}


void CTCP通信空调终端MFCDlg::OnBnClickedBtnPower()
{
	// TODO:  在此添加控件通知处理程序代码
	status.checkInstrucion("POWER", NULL);
}
