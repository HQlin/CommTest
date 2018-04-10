
// CommTestDlg.h : 头文件
//

#pragma once
#include "comaccess.h"

// CCommTestDlg 对话框
class CCommTestDlg : public CDialogEx
{
// 构造
public:
	CCommTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMMTEST_DIALOG };

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
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonOpen();

public:
	ComAccess  *com;

	//初始化
	CString lpszPortNum;	//COM
	int dwBaudRate;			//波特率
	int byParity;			//校验位
	int byStopBits;			//停止位
	int byByteSize;			//数据位

	CString dataSend;		//发送数据
	CString dataRecv;		//接收数据
	
	// 16进制
	BOOL m_is16;
	};
#define DATA_LEN 255		//接收数据长度