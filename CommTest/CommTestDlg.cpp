
// CommTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CommTest.h"
#include "CommTestDlg.h"
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


// CCommTestDlg 对话框




CCommTestDlg::CCommTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommTestDlg::IDD, pParent)
	, dataSend(_T("SA0100#"))
	, dataRecv(_T(""))
	, lpszPortNum(_T("COM3"))
	, dwBaudRate(19200)
	, byParity(0)
	, byStopBits(0)
	, byByteSize(8)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCommTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, dataSend);
	DDX_Text(pDX, IDC_EDIT_RECV, dataRecv);
	DDX_Text(pDX, IDC_EDIT_PORT, lpszPortNum);
	DDX_Text(pDX, IDC_EDIT_RATE, dwBaudRate);
	DDX_Text(pDX, IDC_EDIT_PARI, byParity);
	DDX_Text(pDX, IDC_EDIT_STOP, byStopBits);
	DDX_Text(pDX, IDC_EDIT_BYTE, byByteSize);
}

BEGIN_MESSAGE_MAP(CCommTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CCommTestDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CCommTestDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CCommTestDlg 消息处理程序

BOOL CCommTestDlg::OnInitDialog()
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
	UpdateData(FALSE);
	if ( ! (com = new ComAccess()) )
	{
		MessageBox(L"Error: Not enough memory to create ComAccess object!\n");
		return FALSE;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCommTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCommTestDlg::OnPaint()
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
HCURSOR CCommTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCommTestDlg::OnBnClickedButtonSend()
{
	//发送数据
	UpdateData(TRUE);
	USES_CONVERSION; 
	char* str = W2A(dataSend);
	int write_result = com->WriteData(str, strlen(str));

	// -1 ? then we got an error and print it
	if ( write_result < 0 )
		MessageBox(A2W(com->GetErrorMessage()));

	char buf[255];
	int read_result = com->ReadData(buf, DATA_LEN);

	// -1 ? then we got an error and print it
	if ( (read_result < 0)  )
		MessageBox(A2W(com->GetErrorMessage()));

	// set end of received data
	buf[DATA_LEN] = '\0';

	dataRecv =  A2W(buf);

	UpdateData(FALSE);
}


void CCommTestDlg::OnBnClickedButtonOpen()
{
	UpdateData(true);
	if ( ! com->Open(lpszPortNum, dwBaudRate, byParity, byStopBits, byByteSize) )
	{
		USES_CONVERSION; 
		CString str;
		str.Format(L"Error: Can't open communication device!\n%s", A2W(com->GetErrorMessage()));
		MessageBox(str);
		delete com;
		return;
	}
}
