
// ShowMFCApplication.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CShowMFCApplicationApp: 
// �йش����ʵ�֣������ ShowMFCApplication.cpp
//

class CShowMFCApplicationApp : public CWinApp
{
public:
	CShowMFCApplicationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CShowMFCApplicationApp theApp;