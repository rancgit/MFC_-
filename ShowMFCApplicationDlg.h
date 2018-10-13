
// ShowMFCApplicationDlg.h : 头文件
//

#pragma once
#include "GetData.h"

// CShowMFCApplicationDlg 对话框
class CShowMFCApplicationDlg : public CDialogEx
{
// 构造
public:
	CShowMFCApplicationDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOWMFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CWnd * pWnd;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	PeopleData Pdata1;//使用单独二孩
	PeopleData Pdata2;//全面二
	vector<int> YNum1;
	vector<int> YNum2;				//每个点的y值到X坐标轴的距离
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnStnClickedMystatic();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnStnClickedStrstatic();
};
