
// 编译原理课程设计-简易C中间代码生成器Dlg.h : 头文件
//

#pragma once
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
// C编译原理课程设计简易C中间代码生成器Dlg 对话框
class C编译原理课程设计简易C中间代码生成器Dlg : public CDialogEx
{
// 构造
public:
	C编译原理课程设计简易C中间代码生成器Dlg(CWnd* pParent = NULL);	// 标准构造函数
	CString midcodes, tmpcs, totalcodes;
// 对话框数据
	enum { IDD = IDD_C_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

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
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedExecute();
	afx_msg void OnBnClickedClear();
	afx_msg void OnStnClickedMiddlecodes();
	afx_msg void OnStnClickedCodes();
	void AppendText(int controlId, CString strAdd);
	void ShowCodes(int controlId, CString strAdd);
	double calculation();
	void booleanstatement();
	void ifstatement();
	void statement();
	void whilestatement();
	void forstatement();
	void declare();
	void entrance();
	void compoundstatement();
	int replacelabel(int,int);
	void findallsharps();
	CFont font;
	afx_msg void OnBnClickedReplace();
	

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedConpile();
	afx_msg void OnBnClickedConfirm();
	afx_msg void OnBnClickedTest();
};
