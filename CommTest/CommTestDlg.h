
// CommTestDlg.h : ͷ�ļ�
//

#pragma once
#include "comaccess.h"

// CCommTestDlg �Ի���
class CCommTestDlg : public CDialogEx
{
// ����
public:
	CCommTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COMMTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

	//��ʼ��
	CString lpszPortNum;	//COM
	int dwBaudRate;			//������
	int byParity;			//У��λ
	int byStopBits;			//ֹͣλ
	int byByteSize;			//����λ

	CString dataSend;		//��������
	CString dataRecv;		//��������
	
	// 16����
	BOOL m_is16;
	};
#define DATA_LEN 255		//�������ݳ���