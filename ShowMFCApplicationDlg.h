
// ShowMFCApplicationDlg.h : ͷ�ļ�
//

#pragma once
#include "GetData.h"

// CShowMFCApplicationDlg �Ի���
class CShowMFCApplicationDlg : public CDialogEx
{
// ����
public:
	CShowMFCApplicationDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOWMFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CWnd * pWnd;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	PeopleData Pdata1;//ʹ�õ�������
	PeopleData Pdata2;//ȫ���
	vector<int> YNum1;
	vector<int> YNum2;				//ÿ�����yֵ��X������ľ���
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnStnClickedMystatic();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnStnClickedStrstatic();
};
