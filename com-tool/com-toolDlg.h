
// com-toolDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CcomtoolDlg 对话框
class CcomtoolDlg : public CDialogEx
{
// 构造
public:
	CcomtoolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMTOOL_DIALOG };

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
	afx_msg void OnBnClickedOk();
	CComboBox m_coms_combo;
	CMscomm1 m_comm_ctl;
private:
	int GetComm(void);
public:
	afx_msg void OnEnChangeInput();
	int InitView(void);
	afx_msg void OnBnClickedOpenclosecomm();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	afx_msg void OnBnClickedSend();
};
