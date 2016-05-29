
// com-toolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "com-tool.h"
#include "com-toolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CcomtoolDlg 对话框




CcomtoolDlg::CcomtoolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcomtoolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcomtoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, m_coms_combo);
	DDX_Control(pDX, IDC_MSCOMM1, m_comm_ctl);
}

BEGIN_MESSAGE_MAP(CcomtoolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CcomtoolDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_INPUT, &CcomtoolDlg::OnEnChangeInput)
	ON_BN_CLICKED(IDC_OPENCLOSECOMM, &CcomtoolDlg::OnBnClickedOpenclosecomm)
	ON_BN_CLICKED(IDC_SEND, &CcomtoolDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CcomtoolDlg 消息处理程序

BOOL CcomtoolDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	GetComm();
	InitView();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcomtoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcomtoolDlg::OnPaint()
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
HCURSOR CcomtoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcomtoolDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnOK();
}




int CcomtoolDlg::GetComm(void)
{
	 //程序启动时获取全部可用串口
     HANDLE  hCom;
     int i,num,k;
     CString str;
     BOOL flag;
     
     ((CComboBox *)GetDlgItem(IDC_COMBO))->ResetContent();
     flag = FALSE;
     num = 0;
     for (i = 1;i <= 16;i++)
     {//此程序支持16个串口
		 str.Format(_T("\\\\.\\COM%d"),i);
         hCom = CreateFile(str, 0, 0, 0,
             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
         if(INVALID_HANDLE_VALUE != hCom )
         {//能打开该串口，则添加该串口
             CloseHandle(hCom);
             str = str.Mid(4);
             ((CComboBox *)GetDlgItem(IDC_COMBO))->AddString(str);
             if (flag == FALSE)
             {
                 flag = TRUE;
                 num = i;
             }
         }
     }
     i = ((CComboBox *)GetDlgItem(IDC_COMBO))->GetCount();
     if (i == 0)
     {//若找不到可用串口则禁用“打开串口”功能
         ((CComboBox *)GetDlgItem(IDC_COMBO))->EnableWindow(FALSE);
    }
    else
     {
         k = ((CComboBox *)GetDlgItem((IDC_COMBO)))->GetCount();
         ((CComboBox *)GetDlgItem(IDC_COMBO))->SetCurSel(k - 1);
    }
	return 0;
}


void CcomtoolDlg::OnEnChangeInput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


int CcomtoolDlg::InitView(void)
{
	((CEdit *)GetDlgItem(IDC_BAUD))->SetWindowTextW(_T("9600"));
	((CEdit *)GetDlgItem(IDC_DATA))->SetWindowTextW(_T("8"));
	((CEdit *)GetDlgItem(IDC_CHK))->SetWindowTextW(_T("N"));
	((CEdit *)GetDlgItem(IDC_STOP))->SetWindowTextW(_T("1"));
	((CEdit *)GetDlgItem(IDC_CTL))->SetWindowTextW(_T("N"));
	return 0;
}


void CcomtoolDlg::OnBnClickedOpenclosecomm()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	((CComboBox *)GetDlgItem(IDC_COMBO))->GetWindowTextW(str);

	if (str.GetLength() <= 0)
	{
		AfxMessageBox(_T("please select COMMs first"));
		return;
	} else {
		int com_index = _ttoi(str.Mid(3));

		CString settings,baud,data,chk,stop;

		((CEdit *)GetDlgItem(IDC_BAUD))->GetWindowTextW(baud);
		((CEdit *)GetDlgItem(IDC_DATA))->GetWindowTextW(data);
		((CEdit *)GetDlgItem(IDC_CHK))->GetWindowTextW(chk);
		((CEdit *)GetDlgItem(IDC_STOP))->GetWindowTextW(stop);

		settings.Format(_T("%s,%s,%s,%s"),
			baud,chk,data,stop);

		if (settings.GetLength()<10)
		{
			settings = "9600,N,8,1";
		}


		if (this->m_comm_ctl.get_PortOpen())
		{
			this->m_comm_ctl.put_PortOpen(false);
		}

		this->m_comm_ctl.put_CommPort(com_index);     // 选择COM1  
		this->m_comm_ctl.put_InBufferSize(1024);   // 指定接收缓冲区大小  
		this->m_comm_ctl.put_OutBufferSize(1024);// 指定发送缓冲区大小  
		this->m_comm_ctl.put_InputLen(0);     // 设置当前接收区数据长度为0,表示全部读取  
		this->m_comm_ctl.put_InputMode(1);    // 以二进制方式读写数据   
		this->m_comm_ctl.put_Settings(settings); // 波特率9600无检验位，8个数据位，1个停止位  
		this->m_comm_ctl.put_RThreshold(1);    // 接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm事件  
		try   
		{   
		   this->m_comm_ctl.put_PortOpen(TRUE);  
		}   
		catch (...)   
		{   
		   AfxMessageBox(L"串口打开失败");  
		   return;  
		}   
		AfxMessageBox(_T("串口打开成功"));
	}

}
BEGIN_EVENTSINK_MAP(CcomtoolDlg, CDialogEx)
	ON_EVENT(CcomtoolDlg, IDC_MSCOMM1, 1, CcomtoolDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CcomtoolDlg::OnCommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	// ==============串口数据接收过程===================   
	if(this->m_comm_ctl.get_CommEvent() == 2)   
	{   
		COleSafeArray SafeArray = this->m_comm_ctl.get_Input(); 
		int iLen = SafeArray.GetOneDimSize();   
		if (iLen >= 1024){
			AfxMessageBox(_T("data overflowed, only show first part."));
		}
		BYTE revBuf[1024];   
		revBuf[iLen] = '\0';
		for(long i = 0;i < iLen; i++)   
		{  
			SafeArray.GetElement(&i, revBuf + i);  
		}  
  
		//对revBuf进行处理  
		((CEdit *)GetDlgItem(IDC_OUTPUT))->SetWindowTextW(CString(revBuf));
	} 
}


void CcomtoolDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString in;
	((CEdit *)GetDlgItem(IDC_INPUT))->GetWindowTextW(in);

	
	this->m_comm_ctl.put_Output(COleVariant(in));
}
