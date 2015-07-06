
// 编译原理课程设计-简易C中间代码生成器Dlg.h : 头文件
//

#pragma once


// C编译原理课程设计简易C中间代码生成器Dlg 对话框
class C编译原理课程设计简易C中间代码生成器Dlg : public CDialogEx
{
// 构造
public:
	C编译原理课程设计简易C中间代码生成器Dlg(CWnd* pParent = NULL);	// 标准构造函数
	CString midcodes, tmpcs;
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
	double C编译原理课程设计简易C中间代码生成器Dlg::calculation();
	void C编译原理课程设计简易C中间代码生成器Dlg::booleanstatement();
	void C编译原理课程设计简易C中间代码生成器Dlg::ifstatement();
	void C编译原理课程设计简易C中间代码生成器Dlg::statement();
	void C编译原理课程设计简易C中间代码生成器Dlg::whilestatement();
	void C编译原理课程设计简易C中间代码生成器Dlg::forstatement();
	void C编译原理课程设计简易C中间代码生成器Dlg::declare();
	void C编译原理课程设计简易C中间代码生成器Dlg::entrance();
	void C编译原理课程设计简易C中间代码生成器Dlg::compoundstatement();
	CFont font;
};
