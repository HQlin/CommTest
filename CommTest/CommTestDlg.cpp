
// CommTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "CommTestDlg.h"
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


// CCommTestDlg �Ի���




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


// CCommTestDlg ��Ϣ�������

BOOL CCommTestDlg::OnInitDialog()
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
	UpdateData(FALSE);
	if ( ! (com = new ComAccess()) )
	{
		MessageBox(L"Error: Not enough memory to create ComAccess object!\n");
		return FALSE;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCommTestDlg::OnPaint()
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
HCURSOR CCommTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCommTestDlg::OnBnClickedButtonSend()
{
	//��������
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
