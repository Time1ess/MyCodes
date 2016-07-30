
// TCP通信-空调终端-MFCDlg.h : 头文件
//

#pragma once


// CTCP通信空调终端MFCDlg 对话框
class CTCP通信空调终端MFCDlg : public CDialogEx
{
// 构造
public:
	CTCP通信空调终端MFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TCPMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	CWinThread *Thread1;
//	void Instructions(char *ins, int size);
	static UINT ThreadProc(LPVOID pParam);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnOn();
	afx_msg void OnBnClickedBtnRate();
	afx_msg void OnBnClickedBtnTime();
	afx_msg void OnBnClickedBtnSleep2();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedBtnMode();
	afx_msg void OnClickedBtnOn();
	afx_msg void OnBnClickedBtnPower();
};
