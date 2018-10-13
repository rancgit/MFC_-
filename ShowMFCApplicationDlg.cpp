
// ShowMFCApplicationDlg.cpp : ʵ���ļ�
//


#include "stdafx.h"
#include "ShowMFCApplication.h"
#include "ShowMFCApplicationDlg.h"
#include "afxdialogex.h"
#include "GetData.h"
//���������С����ֵ
#define YMIN 13
#define YMAX 18
//���ο�����Ͻ�����
#define XBORD 35
#define YBORD 44
//y���x����
#define YX 65
//x����ļ��
#define XGAP 18

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShowMFCApplicationDlg �Ի���



CShowMFCApplicationDlg::CShowMFCApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SHOWMFCAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShowMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShowMFCApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_MYSTATIC, &CShowMFCApplicationDlg::OnStnClickedMystatic)
	ON_WM_LBUTTONDOWN()
	ON_STN_CLICKED(IDC_STRSTATIC, &CShowMFCApplicationDlg::OnStnClickedStrstatic)
END_MESSAGE_MAP()


// CShowMFCApplicationDlg ��Ϣ�������

BOOL CShowMFCApplicationDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CShowMFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CShowMFCApplicationDlg::OnPaint()
{
	PeopleData peo(1);
	Pdata1 = peo;
	PeopleData peo2(2);
	Pdata2 = peo2;
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

	//ʵ�ֻ���������
	CRect rect;
	GetDlgItem(IDC_MYSTATIC)->GetClientRect(rect);
	//GetDlgItem(IDC_MYTSTATIC)->GetClientRect(rect);
	rect.Width();
	rect.Height();
	//��rect.Width()���nxLength��rect.Height()���nyLength
	int nxLength = 800;
	int nyLength = 300;

	int ylen = 270;//�����ymax�ĳ��ȣ���һ������y��ĳ���
	unsigned long ymax = 1800000000;//����yֵ�����������������ֵ��һ��������
	unsigned long ymin = 1300000000;//>>>>>>>>>>>>>>>>>>>>��>>>>>
								  //�������ݺ����������


	int nxDivisionNumber = 40;
	int nyDivisionNumber = 6;

	int nMeshLength;
	CString str;
	int i;
	CWnd *pWnd = GetDlgItem(IDC_MYSTATIC);
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();

	pDC->Rectangle(0, 0, nxLength, nyLength);


	CPen* pPenRed = new CPen;                                          //�������ʶ���
	pPenRed->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));  //��ɫ����

	CPen* pPenGreen = new CPen;                                //�������ʶ���
	pPenGreen->CreatePen(PS_SOLID, 1, RGB(0, 255, 0));//��ɫ����

	CPen* pPenBlue = new CPen;                                  //�������ʶ���
	pPenBlue->CreatePen(PS_DOT, 1, RGB(0, 0, 255));     //��ɫ����

	CPen* pPenBlack = new CPen;                                 //�������ʶ���
	pPenBlack->CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); //��ɫ����

													 //ѡ�к�ɫ���ʣ������浱ǰ����
	CGdiObject* pOldPen = pDC->SelectObject(pPenBlack);
	pDC->MoveTo(30, 10);                              //����������
	pDC->LineTo(30, nyLength - 30);                  //��ֱ��
	pDC->LineTo(nxLength - 10, nyLength - 30);   //ˮƽ��

												 //�������ͷ
	pDC->MoveTo(nxLength - 10 - 10, nyLength - 30 - 5);
	pDC->LineTo(nxLength - 10, nyLength - 30);
	pDC->MoveTo(nxLength - 10 - 10, nyLength - 30 + 5);
	pDC->LineTo(nxLength - 10, nyLength - 30);

	//�������ͷ
	pDC->MoveTo(25, 20);
	pDC->LineTo(30, 10);
	pDC->MoveTo(35, 20);
	pDC->LineTo(30, 10);
	//����������
	nMeshLength = (nxLength - 30) / (nxDivisionNumber + 1);
	CFont font;
	//������ݵ����Ϊ��б���
	VERIFY(font.CreateFont(
		12,                        // ��������߶�
		0,                         // ����������
		-600,                         // nEscapement,�������ֵ���ʾ�Ƕȣ�ע�ⵥλΪ0.1��
		90,                         //
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // �Ƿ���
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Arial"));                 // lpszFacename
								   // ����ʵ���������
								   //CClientDC dc(this);
	CFont* def_font = pDC->SelectObject(&font);
	for (i = 0; i < nxDivisionNumber + 1; i++) {
		str.Format("%d", i + 2010);
		pDC->TextOut(35 + i*nMeshLength, nyLength - 30, str);
	}
	pDC->SelectObject(def_font);
	// ��ת��ɣ��ͷſռ�
	font.DeleteObject();
	//�������ʶ
	str.Format("���");
	pDC->TextOut(nxLength - 32, nyLength - 26, str);

	//����������
	//y��ĵ�λ����
	//double Yper = (nyDivisionNumber + 1) / (int)(YMAX - YMIN);
	nMeshLength = (nyLength - 30) / (nyDivisionNumber );
	int Ycount;//��λ���
	if ((double)((YMAX - YMIN) / (nyDivisionNumber ))> 0.5)
	{
		Ycount = floor((double)((YMAX - YMIN) / (nyDivisionNumber )) + 0.5);
	}
	else  
		Ycount = ceil((double)((YMAX - YMIN) / (nyDivisionNumber )) + 0.5);
	for (i = 0; i < nyDivisionNumber ; i++) {
		int  YNum = i * Ycount + YMIN;
		str.Format("%d", YNum);
		pDC->TextOut(3, nyLength - 37 - i*nMeshLength, str);
	}
	//�������ʶ
	str.Format("����/��λ������");
	pDC->TextOut(1, 1, str);

	//����������
	pDC->SelectObject(pPenBlue);
	nMeshLength = (nxLength - 40) / (nxDivisionNumber + 1);
	//����������
	for (i = 1; i < nxDivisionNumber + 2; i++) {
		pDC->MoveTo(30 + i*nMeshLength, nyLength - 30);
		pDC->LineTo(30 + i*nMeshLength, 38);
	}
	//����������
	int nyMeshLength = (nyLength - 30) / (nyDivisionNumber );
	for (i = 1; i < nyDivisionNumber ; i++) {
		pDC->MoveTo(30, nyLength - 30 - i*nyMeshLength);
		pDC->LineTo(nxLength - 31, nyLength - 30 - i*nyMeshLength);
	}

	//�ָ���ǰ�Ļ���
	pDC->SelectObject(pPenGreen);

	//delete pPenRed;
	//	delete pPenGreen;
	delete pPenBlue;
	//delete pPenBlack;
	vector<unsigned long> PeopleSum;//�Ȼ��ÿ����˿���������vector�洢
	int x = 30;//y = nyLength - 30 - ny;
	for (int i = 0; i < NYEAR; i++) {
		unsigned long sum = Pdata1.GetSumOfYear(i);
	//	CString str;
	//	str.Format("%u", sum);
		//if(i==7) pDC->TextOut(10, 10, str);
		nMeshLength = (nxLength - 40) / (nxDivisionNumber + 1);
		PeopleSum.push_back(sum);
		//������Ҫ�������sumִ��һ�����ţ��ȼ���
		int ny = ((long double)(sum - ymin) / (ymax - ymin))*ylen;
		
		//��ž����������ٻ��ߣ����趨���
		if (i == 0)
		{
			//str.Format(_T("%u"),sum);
			//pDC->TextOut(10, 10, str);
			//֤���ǵ�һ���㣬���������
			//int x = 50, y = 50;//������꣬��������30, nyLength - 30
			int y = nyLength - 30 - ny;
			YNum1.push_back(y);
			pDC->MoveTo(x, y);
			pDC->Ellipse(x - 4, y - 4, x + 4, y + 4);
		}
		else
		{
			//int x = 100, y = 120;//������꣬������ת��
			x += nMeshLength;
			int y = nyLength - 30 - ny;
			YNum1.push_back(y);
			pDC->SelectObject(pPenRed);
			pDC->Ellipse(x - 4, y - 4, x + 4, y + 4);
			pDC->SelectObject(pPenGreen);
			pDC->LineTo(x, y);
		}
	}
	x = 30;
	for (int i = 0; i < NYEAR; i++) {
		unsigned long sum = Pdata2.GetSumOfYear(i);
		nMeshLength = (nxLength - 40) / (nxDivisionNumber + 1);
		PeopleSum.push_back(sum);
		//unsigned long sum = Pdata1.GetSumOfYear(i);
	//	CString str;
	//	str.Format("%u", sum);
		//if (i == 0) pDC->TextOut(20, 10, str);
		//������Ҫ�������sumִ��һ�����ţ��ȼ���
		int ny = ((long double)(sum - ymin) / (ymax - ymin))*ylen;
		
		//��ž����������ٻ��ߣ����趨���
		if (i == 0)
		{
			//str.Format(_T("%u"),sum);
			//pDC->TextOut(10, 10, str);
			//֤���ǵ�һ���㣬���������
			//int x = 50, y = 50;//������꣬��������30, nyLength - 30
			int y = nyLength - 30 - ny;
			YNum2.push_back(y);
			pDC->MoveTo(x, y);
			pDC->Ellipse(x - 4, y - 4, x + 4, y + 4);
		}
		else
		{
			//int x = 100, y = 120;//������꣬������ת��
			x += nMeshLength;
			int y = nyLength - 30 - ny;
			YNum2.push_back(y);
			pDC->SelectObject(pPenRed);
			pDC->Ellipse(x - 4, y - 4, x + 4, y + 4);
			pDC->SelectObject(pPenBlack);
			pDC->LineTo(x, y);
		}
	}
	delete pPenBlack;
	delete pPenGreen;
	delete pPenRed;


}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CShowMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CShowMFCApplicationDlg::OnStnClickedMystatic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pWnd = GetDlgItem(IDC_MYSTATIC);
}

//�����ֱ������λ�ã�����yֵ�����������صڼ���Ԫ�أ��������ĸ�Pdata�У�po=1��ʾ��Pdata1�У�2��ʾ��Pdata2��
bool GetIndex (POINT point,vector<int> ny1,vector<int>ny2,int &index,int &po)
{
	//�������Ҽ������ǵ�point�����ھ����У������ٻ���
	//int xgap = 30;
	int x = point.x-YX;
	int y = point.y-YBORD;
	//double tmpx = x / XGAP;
	for (int i = 0; i < NYEAR; i++)
	{
		if (y>=ny1[i]-4&&y<=ny1[i]+4)
		{
			if (x>=i*XGAP-4&&x<=i*XGAP+4)
			{
				index = i;
				po = 1;
				return true;
			}
		}
		if (y >= ny2[i] - 4 && y <= ny2[i] + 4)
		{
			if (x >= i * XGAP - 4 && x <= i * XGAP + 4)
			{
				index = i;
				po = 2;
				return true;
			}
		}
	}
	return false;
}

//void CShowMFCApplicationDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	
//	CDialogEx::OnLButtonDown(nFlags, point);
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	pWnd = GetDlgItem(IDC_STRSTATIC);
//	CDC *pDC=pWnd->GetDC();
//	//int x = point.x;
//	//int y = point.y;
//	//CString str1,str2;
//	//str1.Format("%u", x);
//	//str2.Format("%u", y);
//	//pDC->TextOut(1, 1, str1 + " "+str2);
//	int index = 0;
//	int po = 0;
//	//GetIndex(point, YNum1, YNum2, index, po);
//	//CString str3, str4;
//	//str3.Format("%d", index);
//	//str4.Format("%d", po);
//	//pDC->TextOut(10, 10, str3 + " " + str4);
//	if (GetIndex(point, YNum1, YNum2, index, po))
//	{
//		vector<unsigned long> Vecstr;
//		unsigned long WomanTotal;
//		if (po == 1)
//		{
//			Vecstr = Pdata1.GetStrOfYear(index);
//			WomanTotal = Pdata1.GetWomanSumOfYear(index);
//		}
//		else if (po == 2)
//		{
//			Vecstr = Pdata2.GetStrOfYear(index);
//			WomanTotal = Pdata1.GetWomanSumOfYear(index);
//		}
//		//�����ﻭ
//		COLORREF color;
//		double percentage;
//		CString m_itemName[3] = { "����","����", "����" };
//		vector<double> m_percentage;  //�ٷֱ�
//		unsigned long    YoungNum = Vecstr[0];
//		unsigned long    AdultNum = Vecstr[1];
//		unsigned long    OldNum = Vecstr[2];
//		//�������
//
//
//		//�˿�������
//		unsigned long   Total = (YoungNum + AdultNum + OldNum);
//		//	 = Pdata.GetWomanOfYear(index);
//		unsigned long ManTotal = Total - WomanTotal;
//		//���Ա��
//		double sexper = (double)ManTotal / WomanTotal * 100;
//		//����������Ҫ��str.Fotmat("%f66666)������λ��
//		//����Ҫָ��һ��λ��
//
//
//	//}
//	//bl();
//	//COLORREF color;
//	//double percentage;
//	//CString m_itemName[3] = { "����","����", "����" };
//		//vector<double> m_percentage = { 0.3,0.5,0.2 };  //�ٷֱ�
//		vector<COLORREF> m_color = { RGB(255,0, 0),RGB(0,  255,0), RGB(0, 0, 255), };  //��ű�ͼ�����ֵ���ɫ
//		POINT m_COpt = { 1000,100 };              //����ԭ��
//		int m_Radius = 150;			   //�뾶
//		int m_expW = 50, m_expH = 30;    //С���εĴ�С
//		int m_itemNums = 3;              //��ĸ���
//
//		double Xgap = 770 / 41;
//		int i = (point.x - 67) / Xgap;
//		if (0 <= i <= 40)
//		{
//			int y = YNum1[i];
//			if (abs(y - point.y) < 5)
//			{
//				//�洢���ꡢ���ꡢ��������
//				vector<unsigned long>  Vecstr = Pdata1.GetStrOfYear(i);
//
//				unsigned long    YoungNum = Vecstr[0];
//				unsigned long    AdultNum = Vecstr[1];
//				unsigned long    OldNum = Vecstr[2];
//				unsigned long   Total = (YoungNum + AdultNum + OldNum);
//				double    YoungPercent = YoungNum / Total;
//				double   AdultPercent = AdultNum / Total;
//				double    OldPercent = OldNum / Total;
//
//
//			}
//		}
//
//
//		CWnd *pWnd = GetDlgItem(IDC_STRSTATIC);
//		CDC* pDC = pWnd->GetDC();
//		CRect rect;
//		GetClientRect(&rect);
//		CBrush brush(RGB(255, 255, 255));
//		pDC->FillRect(&rect, &brush);
//		//��������ԭ��
//		SetViewportOrgEx((HDC)pDC, m_COpt.x, m_COpt.y, NULL);
//
//		//����Բ����Ӿ��δ�С
//		CRect pieRect(-m_Radius, -m_Radius, m_Radius, m_Radius);
//		pDC->Ellipse(&pieRect);
//		POINT pt_start;
//		POINT pt_end;
//
//		//����ͼ
//		double R = m_Radius;
//		const double PI = 3.1415926;
//		double sum = 0;
//		for (int i = 0; i < m_itemNums; i++)
//			sum += m_percentage[i];
//
//		//��֤ռ�ȼ������Ȳ�����1
//		if (sum == 1)
//		{
//			//��һ�����ε�����
//			int angle = m_percentage[0] * 360;  //����ռ�ĽǶ�
//			POINT pt_s_e;
//			pt_start = { (int)R,0 };
//			pt_s_e = pt_start;
//			pt_end = { int(R*cos(angle * PI / 180)),int(-R * sin(angle * PI / 180)) };
//			pDC->SelectObject(CreateSolidBrush(m_color[0])); //����ɫ
//			pDC->Pie(&pieRect, pt_start, pt_end);
//			for (int i = 1; i < m_itemNums; i++)
//			{
//				pt_start = pt_end;
//				angle += m_percentage[i] * 360;
//				pt_end = { int(R*cos(angle * PI / 180)),int(-R * sin(angle * PI / 180)) };
//				pDC->SelectObject(CreateSolidBrush(m_color[i])); //����ɫ
//				if (i == m_itemNums - 1)
//					pDC->Pie(&pieRect, pt_start, pt_s_e);
//				else
//					pDC->Pie(&pieRect, pt_start, pt_end);
//			}
//
//			//��С����
//			CRect expRect;
//			int l = 0, t = 0;
//			for (int i = 0; i < m_itemNums; i++)
//			{
//				l = m_Radius + 50;
//				t = -2 * m_Radius + m_expH * i + 30;
//				expRect = { l + 100,t + 50,l + m_expW,t + m_expH + 60 };
//				pDC->SelectObject(CreateSolidBrush(m_color[i])); //����ɫ
//				pDC->Rectangle(&expRect);
//				pDC->TextOut(l + m_expW + 10, t + m_expH + 30, m_itemName[i]);
//			}
//			//��ʾ�ٷֱ�
//			CString s;
//			int strLen = m_itemName[0].GetLength();
//			for (int i = 0; i < m_itemNums; i++)
//			{
//				l = -2 * m_Radius - strLen * 10;
//				t = -2 * m_Radius + m_expH * i;
//				s.Format(TEXT("%s -- %0.2f%s"), m_itemName[i], m_percentage[i] * 100, TEXT("%"));
//				pDC->TextOut(l + 20, t + 60 + m_expH / 3, s);
//			}
//		}
//
//	}
//
//}

void CShowMFCApplicationDlg::OnLButtonDown(UINT nFlags, CPoint point)
{

	CDialogEx::OnLButtonDown(nFlags, point);
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPaintDC dc(this);
	pWnd = GetDlgItem(IDC_STRSTATIC);
	int index = 0;
	int po = 0;
	if (GetIndex(point, YNum1, YNum2, index, po))
	{
		vector<unsigned long> Vecstr;
		unsigned long WomanTotal;
		if (po == 1)
		{
			Vecstr = Pdata1.GetStrOfYear(index);
			WomanTotal = Pdata1.GetWomanSumOfYear(index);
		}
		else if (po == 2)
		{
			Vecstr = Pdata2.GetStrOfYear(index);
			WomanTotal = Pdata1.GetWomanSumOfYear(index);
		}
		//�����ﻭ
		COLORREF color;
		double percentage;
		CString m_itemName[3] = { "����","����", "����" };
		unsigned long    YoungNum = Vecstr[0];
		unsigned long    AdultNum = Vecstr[1];
		unsigned long    OldNum = Vecstr[2];
		//�˿�������
		unsigned long   Total = (YoungNum + AdultNum + OldNum);
		//�������	
		double    YoungPercent = (double)YoungNum / Total;
		double   AdultPercent = (double)AdultNum / Total;
		double    OldPercent = 1-YoungPercent-AdultPercent;
		vector<double> m_percentage = { YoungPercent,AdultPercent,OldPercent };  //�ٷֱ�

		unsigned long ManTotal = Total - WomanTotal;
		//���Ա��
		double sexper = (double)ManTotal / WomanTotal * 100;
		//�����Ҫ����λ�� ָ��һ��λ��
		CString str;
		CDC *pDC=pWnd->GetDC();
	//	str.Format(_T("%.1lf"), sexper);
			//pWnd = GetDlgItem(IDC_MYSTATIC);
			//CDC *pDC=pWnd->GetDC();
			//int x = point.x;
			//int y = point.y;
			//CString str1,str2;
			//str1.Format("%u", x);
			//str2.Format("%u", y);
		//	pDC->TextOut(1, 1,  "nihao ");
	//	pDC->TextOut(150,150, str);
		vector<COLORREF> m_color = { RGB(100,100, 100),RGB(19,  255,79), RGB(180, 80, 155), };  //��ű�ͼ�����ֵ���ɫ
		POINT m_COpt = { 1000,100 };              //����ԭ��
		int m_Radius = 150;			   //�뾶
		int m_expW = 50, m_expH = 30;    //С���εĴ�С
		int m_itemNums = 3;              //��ĸ���

		CWnd *pWnd = GetDlgItem(IDC_STRSTATIC);
		//CDC* pDC = pWnd->GetDC();
		//CRect rect;
		//GetClientRect(&rect);
		CBrush brush(RGB(255, 255, 255));
		///pDC->FillRect(&rect, &brush);
		//��������ԭ��
		SetViewportOrgEx((HDC)pDC, m_COpt.x, m_COpt.y, NULL);
		//pDC->TextOut(50, 50, "str");
		//����Բ����Ӿ��δ�С
		CRect pieRect(-m_Radius, -m_Radius, m_Radius, m_Radius);
		pDC->Ellipse(&pieRect);
		POINT pt_start;
		POINT pt_end;

		//����ͼ
		double R = m_Radius;
		const double PI = 3.1415926;
		double sum = 0;
		//for (int i = 0; i < m_itemNums; i++)
		//	sum += m_percentage[i];

		//��֤ռ�ȼ������Ȳ�����1
		if (/*sum ==*/ 1)
		{
			//��һ�����ε�����
			int angle = m_percentage[0] * 360;  //����ռ�ĽǶ�
			POINT pt_s_e;
			pt_start = { (int)R,0 };
			pt_s_e = pt_start;
			pt_end = { int(R*cos(angle * PI / 180)),int(-R * sin(angle * PI / 180)) };
			pDC->SelectObject(CreateSolidBrush(m_color[0])); //����ɫ
			pDC->Pie(&pieRect, pt_start, pt_end);
			for (int i = 1; i < m_itemNums; i++)
			{
				pt_start = pt_end;
				angle += m_percentage[i] * 360;
				pt_end = { int(R*cos(angle * PI / 180)),int(-R * sin(angle * PI / 180)) };
				pDC->SelectObject(CreateSolidBrush(m_color[i])); //����ɫ
				if (i == m_itemNums - 1)
					pDC->Pie(&pieRect, pt_start, pt_s_e);
				else
					pDC->Pie(&pieRect, pt_start, pt_end);
			}

			//��С����
			CRect expRect;
			int l = 0, t = 0;
			for (int i = 0; i < m_itemNums; i++)
			{
				l = m_Radius + 50;
				t = -2 * m_Radius + m_expH * i + 30;
				expRect = { l + 100,t + 50,l + m_expW,t + m_expH + 60 };
				pDC->SelectObject(CreateSolidBrush(m_color[i])); //����ɫ
				pDC->Rectangle(&expRect);
				pDC->TextOut(l + m_expW + 10, t + m_expH + 30, m_itemName[i]);
			}
			//CRect YearRect(130, 150, 160, 170);
			//pDC->Rectangle(&YearRect);
			int year = index + 2010;
			str.Format("%d", year);
			CString poli;
			if (po==1)
			{
				poli = "��������������";
			}
			else
			{
				poli = "ȫ�����������";
			}

			pDC->TextOut(70, 170, poli + str + "����˿ڽṹ");
			str.Format("%u", Total);
			pDC->TextOut(70, 189, "�������� " + str);
			str.Format("%u", WomanTotal);
			pDC->TextOut(70, 210, "Ů���������� " + str);
			str.Format("%u", ManTotal);
			pDC->TextOut(70, 230, "�������������� " + str);
			//��ʾ�ٷֱ�
			CString s;
			int strLen = m_itemName[0].GetLength();
			for (int i = 0; i < m_itemNums; i++)
			{
				l = -2 * m_Radius - strLen * 10;
				t = -2 * m_Radius + m_expH * i;
				s.Format(TEXT("%s -- %0.2f%s"), m_itemName[i], m_percentage[i] * 100, TEXT("%"));
				//pDC->TextOut(l + 20, t + 60 + m_expH / 3, s);
				pDC->TextOut(l + 460, t + 78 + m_expH / 3, s);
			}
		}
	}
}




void CShowMFCApplicationDlg::OnStnClickedStrstatic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pWnd = GetDlgItem(IDC_STRSTATIC);
}
