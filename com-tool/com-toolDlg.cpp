
// com-toolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "com-tool.h"
#include "com-toolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CcomtoolDlg �Ի���




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


// CcomtoolDlg ��Ϣ�������

BOOL CcomtoolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	GetComm();
	InitView();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CcomtoolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CcomtoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcomtoolDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CDialogEx::OnOK();
}




int CcomtoolDlg::GetComm(void)
{
	 //��������ʱ��ȡȫ�����ô���
     HANDLE  hCom;
     int i,num,k;
     CString str;
     BOOL flag;
     
     ((CComboBox *)GetDlgItem(IDC_COMBO))->ResetContent();
     flag = FALSE;
     num = 0;
     for (i = 1;i <= 16;i++)
     {//�˳���֧��16������
		 str.Format(_T("\\\\.\\COM%d"),i);
         hCom = CreateFile(str, 0, 0, 0,
             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
         if(INVALID_HANDLE_VALUE != hCom )
         {//�ܴ򿪸ô��ڣ�����Ӹô���
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
     {//���Ҳ������ô�������á��򿪴��ڡ�����
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

		this->m_comm_ctl.put_CommPort(com_index);     // ѡ��COM1  
		this->m_comm_ctl.put_InBufferSize(1024);   // ָ�����ջ�������С  
		this->m_comm_ctl.put_OutBufferSize(1024);// ָ�����ͻ�������С  
		this->m_comm_ctl.put_InputLen(0);     // ���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ  
		this->m_comm_ctl.put_InputMode(1);    // �Զ����Ʒ�ʽ��д����   
		this->m_comm_ctl.put_Settings(settings); // ������9600�޼���λ��8������λ��1��ֹͣλ  
		this->m_comm_ctl.put_RThreshold(1);    // ���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm�¼�  
		try   
		{   
		   this->m_comm_ctl.put_PortOpen(TRUE);  
		}   
		catch (...)   
		{   
		   AfxMessageBox(L"���ڴ�ʧ��");  
		   return;  
		}   
		AfxMessageBox(_T("���ڴ򿪳ɹ�"));
	}

}
BEGIN_EVENTSINK_MAP(CcomtoolDlg, CDialogEx)
	ON_EVENT(CcomtoolDlg, IDC_MSCOMM1, 1, CcomtoolDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CcomtoolDlg::OnCommMscomm1()
{
	// TODO: �ڴ˴������Ϣ����������
	// ==============�������ݽ��չ���===================   
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
  
		//��revBuf���д���  
		((CEdit *)GetDlgItem(IDC_OUTPUT))->SetWindowTextW(CString(revBuf));
	} 
}


void CcomtoolDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString in;
	((CEdit *)GetDlgItem(IDC_INPUT))->GetWindowTextW(in);

	
	this->m_comm_ctl.put_Output(COleVariant(in));
}
