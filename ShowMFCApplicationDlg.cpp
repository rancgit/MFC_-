
// ShowMFCApplicationDlg.cpp : 实现文件
//


#include "stdafx.h"
#include "ShowMFCApplication.h"
#include "ShowMFCApplicationDlg.h"
#include "afxdialogex.h"
#include "GetData.h"
//定义最大最小坐标值
#define YMIN 13
#define YMAX 18
//矩形框的左上角坐标
#define XBORD 35
#define YBORD 44
//y轴的x坐标
#define YX 65
//x坐标的间距
#define XGAP 18

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CShowMFCApplicationDlg 对话框



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


// CShowMFCApplicationDlg 消息处理程序

BOOL CShowMFCApplicationDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CShowMFCApplicationDlg::OnPaint()
{
	PeopleData peo(1);
	Pdata1 = peo;
	PeopleData peo2(2);
	Pdata2 = peo2;
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

	//实现绘制坐标轴
	CRect rect;
	GetDlgItem(IDC_MYSTATIC)->GetClientRect(rect);
	//GetDlgItem(IDC_MYTSTATIC)->GetClientRect(rect);
	rect.Width();
	rect.Height();
	//用rect.Width()替代nxLength，rect.Height()替代nyLength
	int nxLength = 800;
	int nyLength = 300;

	int ylen = 270;//这个是ymax的长度，不一定就是y轴的长度
	unsigned long ymax = 1800000000;//最大的y值，等于总人数的最大值加一个常数，
	unsigned long ymin = 1300000000;//>>>>>>>>>>>>>>>>>>>>减>>>>>
								  //以上数据后面具体再算


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


	CPen* pPenRed = new CPen;                                          //创建画笔对象
	pPenRed->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));  //红色画笔

	CPen* pPenGreen = new CPen;                                //创建画笔对象
	pPenGreen->CreatePen(PS_SOLID, 1, RGB(0, 255, 0));//绿色画笔

	CPen* pPenBlue = new CPen;                                  //创建画笔对象
	pPenBlue->CreatePen(PS_DOT, 1, RGB(0, 0, 255));     //蓝色画笔

	CPen* pPenBlack = new CPen;                                 //创建画笔对象
	pPenBlack->CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); //黑色画笔

													 //选中黑色画笔，并保存当前画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenBlack);
	pDC->MoveTo(30, 10);                              //绘制坐标轴
	pDC->LineTo(30, nyLength - 30);                  //垂直轴
	pDC->LineTo(nxLength - 10, nyLength - 30);   //水平轴

												 //横坐标箭头
	pDC->MoveTo(nxLength - 10 - 10, nyLength - 30 - 5);
	pDC->LineTo(nxLength - 10, nyLength - 30);
	pDC->MoveTo(nxLength - 10 - 10, nyLength - 30 + 5);
	pDC->LineTo(nxLength - 10, nyLength - 30);

	//纵坐标箭头
	pDC->MoveTo(25, 20);
	pDC->LineTo(30, 10);
	pDC->MoveTo(35, 20);
	pDC->LineTo(30, 10);
	//横坐标数字
	nMeshLength = (nxLength - 30) / (nxDivisionNumber + 1);
	CFont font;
	//控制年份的输出为倾斜输出
	VERIFY(font.CreateFont(
		12,                        // 设置字体高度
		0,                         // 设置字体宽度
		-600,                         // nEscapement,设置文字的显示角度，注意单位为0.1度
		90,                         //
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // 是否划线
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Arial"));                 // lpszFacename
								   // 调用实现纵向输出
								   //CClientDC dc(this);
	CFont* def_font = pDC->SelectObject(&font);
	for (i = 0; i < nxDivisionNumber + 1; i++) {
		str.Format("%d", i + 2010);
		pDC->TextOut(35 + i*nMeshLength, nyLength - 30, str);
	}
	pDC->SelectObject(def_font);
	// 旋转完成，释放空间
	font.DeleteObject();
	//横坐标标识
	str.Format("年份");
	pDC->TextOut(nxLength - 32, nyLength - 26, str);

	//纵坐标数字
	//y轴的单位长度
	//double Yper = (nyDivisionNumber + 1) / (int)(YMAX - YMIN);
	nMeshLength = (nyLength - 30) / (nyDivisionNumber );
	int Ycount;//单位间隔
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
	//纵坐标标识
	str.Format("人数/单位：亿人");
	pDC->TextOut(1, 1, str);

	//绘制网格线
	pDC->SelectObject(pPenBlue);
	nMeshLength = (nxLength - 40) / (nxDivisionNumber + 1);
	//纵向网格线
	for (i = 1; i < nxDivisionNumber + 2; i++) {
		pDC->MoveTo(30 + i*nMeshLength, nyLength - 30);
		pDC->LineTo(30 + i*nMeshLength, 38);
	}
	//横向网格线
	int nyMeshLength = (nyLength - 30) / (nyDivisionNumber );
	for (i = 1; i < nyDivisionNumber ; i++) {
		pDC->MoveTo(30, nyLength - 30 - i*nyMeshLength);
		pDC->LineTo(nxLength - 31, nyLength - 30 - i*nyMeshLength);
	}

	//恢复以前的画笔
	pDC->SelectObject(pPenGreen);

	//delete pPenRed;
	//	delete pPenGreen;
	delete pPenBlue;
	//delete pPenBlack;
	vector<unsigned long> PeopleSum;//先获得每年的人口总数，用vector存储
	int x = 30;//y = nyLength - 30 - ny;
	for (int i = 0; i < NYEAR; i++) {
		unsigned long sum = Pdata1.GetSumOfYear(i);
	//	CString str;
	//	str.Format("%u", sum);
		//if(i==7) pDC->TextOut(10, 10, str);
		nMeshLength = (nxLength - 40) / (nxDivisionNumber + 1);
		PeopleSum.push_back(sum);
		//可能需要在这里对sum执行一个缩放，先记着
		int ny = ((long double)(sum - ymin) / (ymax - ymin))*ylen;
		
		//大概就是这样，再画线，先设定起点
		if (i == 0)
		{
			//str.Format(_T("%u"),sum);
			//pDC->TextOut(10, 10, str);
			//证明是第一个点，就设置起点
			//int x = 50, y = 50;//起点坐标，后面再算30, nyLength - 30
			int y = nyLength - 30 - ny;
			YNum1.push_back(y);
			pDC->MoveTo(x, y);
			pDC->Ellipse(x - 4, y - 4, x + 4, y + 4);
		}
		else
		{
			//int x = 100, y = 120;//点的坐标，后面再转换
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
		//可能需要在这里对sum执行一个缩放，先记着
		int ny = ((long double)(sum - ymin) / (ymax - ymin))*ylen;
		
		//大概就是这样，再画线，先设定起点
		if (i == 0)
		{
			//str.Format(_T("%u"),sum);
			//pDC->TextOut(10, 10, str);
			//证明是第一个点，就设置起点
			//int x = 50, y = 50;//起点坐标，后面再算30, nyLength - 30
			int y = nyLength - 30 - ny;
			YNum2.push_back(y);
			pDC->MoveTo(x, y);
			pDC->Ellipse(x - 4, y - 4, x + 4, y + 4);
		}
		else
		{
			//int x = 100, y = 120;//点的坐标，后面再转换
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CShowMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CShowMFCApplicationDlg::OnStnClickedMystatic()
{
	// TODO: 在此添加控件通知处理程序代码
	pWnd = GetDlgItem(IDC_MYSTATIC);
}

//参数分别是鼠标位置，两个y值的向量，返回第几个元素，返回在哪个Pdata中，po=1表示在Pdata1中，2表示在Pdata2中
bool GetIndex (POINT point,vector<int> ny1,vector<int>ny2,int &index,int &po)
{
	//这里暂且假设我们的point就是在矩形中，后面再换算
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
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
//		//在这里画
//		COLORREF color;
//		double percentage;
//		CString m_itemName[3] = { "少年","中年", "老年" };
//		vector<double> m_percentage;  //百分比
//		unsigned long    YoungNum = Vecstr[0];
//		unsigned long    AdultNum = Vecstr[1];
//		unsigned long    OldNum = Vecstr[2];
//		//计算比例
//
//
//		//人口总数和
//		unsigned long   Total = (YoungNum + AdultNum + OldNum);
//		//	 = Pdata.GetWomanOfYear(index);
//		unsigned long ManTotal = Total - WomanTotal;
//		//算性别比
//		double sexper = (double)ManTotal / WomanTotal * 100;
//		//你待会输出需要用str.Fotmat("%f66666)来控制位数
//		//你需要指定一下位置
//
//
//	//}
//	//bl();
//	//COLORREF color;
//	//double percentage;
//	//CString m_itemName[3] = { "少年","中年", "老年" };
//		//vector<double> m_percentage = { 0.3,0.5,0.2 };  //百分比
//		vector<COLORREF> m_color = { RGB(255,0, 0),RGB(0,  255,0), RGB(0, 0, 255), };  //存放饼图各部分的颜色
//		POINT m_COpt = { 1000,100 };              //坐标原点
//		int m_Radius = 150;			   //半径
//		int m_expW = 50, m_expH = 30;    //小矩形的大小
//		int m_itemNums = 3;              //项的个数
//
//		double Xgap = 770 / 41;
//		int i = (point.x - 67) / Xgap;
//		if (0 <= i <= 40)
//		{
//			int y = YNum1[i];
//			if (abs(y - point.y) < 5)
//			{
//				//存储青年、中年、老年人数
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
//		//设置坐标原点
//		SetViewportOrgEx((HDC)pDC, m_COpt.x, m_COpt.y, NULL);
//
//		//设置圆的外接矩形大小
//		CRect pieRect(-m_Radius, -m_Radius, m_Radius, m_Radius);
//		pDC->Ellipse(&pieRect);
//		POINT pt_start;
//		POINT pt_end;
//
//		//画饼图
//		double R = m_Radius;
//		const double PI = 3.1415926;
//		double sum = 0;
//		for (int i = 0; i < m_itemNums; i++)
//			sum += m_percentage[i];
//
//		//验证占比加起来等不等于1
//		if (sum == 1)
//		{
//			//第一个扇形的坐标
//			int angle = m_percentage[0] * 360;  //计算占的角度
//			POINT pt_s_e;
//			pt_start = { (int)R,0 };
//			pt_s_e = pt_start;
//			pt_end = { int(R*cos(angle * PI / 180)),int(-R * sin(angle * PI / 180)) };
//			pDC->SelectObject(CreateSolidBrush(m_color[0])); //上颜色
//			pDC->Pie(&pieRect, pt_start, pt_end);
//			for (int i = 1; i < m_itemNums; i++)
//			{
//				pt_start = pt_end;
//				angle += m_percentage[i] * 360;
//				pt_end = { int(R*cos(angle * PI / 180)),int(-R * sin(angle * PI / 180)) };
//				pDC->SelectObject(CreateSolidBrush(m_color[i])); //上颜色
//				if (i == m_itemNums - 1)
//					pDC->Pie(&pieRect, pt_start, pt_s_e);
//				else
//					pDC->Pie(&pieRect, pt_start, pt_end);
//			}
//
//			//画小矩形
//			CRect expRect;
//			int l = 0, t = 0;
//			for (int i = 0; i < m_itemNums; i++)
//			{
//				l = m_Radius + 50;
//				t = -2 * m_Radius + m_expH * i + 30;
//				expRect = { l + 100,t + 50,l + m_expW,t + m_expH + 60 };
//				pDC->SelectObject(CreateSolidBrush(m_color[i])); //上颜色
//				pDC->Rectangle(&expRect);
//				pDC->TextOut(l + m_expW + 10, t + m_expH + 30, m_itemName[i]);
//			}
//			//显示百分比
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
		//在这里画
		COLORREF color;
		double percentage;
		CString m_itemName[3] = { "少年","中年", "老年" };
		unsigned long    YoungNum = Vecstr[0];
		unsigned long    AdultNum = Vecstr[1];
		unsigned long    OldNum = Vecstr[2];
		//人口总数和
		unsigned long   Total = (YoungNum + AdultNum + OldNum);
		//计算比例	
		double    YoungPercent = (double)YoungNum / Total;
		double   AdultPercent = (double)AdultNum / Total;
		double    OldPercent = 1-YoungPercent-AdultPercent;
		vector<double> m_percentage = { YoungPercent,AdultPercent,OldPercent };  //百分比

		unsigned long ManTotal = Total - WomanTotal;
		//算性别比
		double sexper = (double)ManTotal / WomanTotal * 100;
		//输出需要控制位数 指定一下位置
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
		vector<COLORREF> m_color = { RGB(100,100, 100),RGB(19,  255,79), RGB(180, 80, 155), };  //存放饼图各部分的颜色
		POINT m_COpt = { 1000,100 };              //坐标原点
		int m_Radius = 150;			   //半径
		int m_expW = 50, m_expH = 30;    //小矩形的大小
		int m_itemNums = 3;              //项的个数

		CWnd *pWnd = GetDlgItem(IDC_STRSTATIC);
		//CDC* pDC = pWnd->GetDC();
		//CRect rect;
		//GetClientRect(&rect);
		CBrush brush(RGB(255, 255, 255));
		///pDC->FillRect(&rect, &brush);
		//设置坐标原点
		SetViewportOrgEx((HDC)pDC, m_COpt.x, m_COpt.y, NULL);
		//pDC->TextOut(50, 50, "str");
		//设置圆的外接矩形大小
		CRect pieRect(-m_Radius, -m_Radius, m_Radius, m_Radius);
		pDC->Ellipse(&pieRect);
		POINT pt_start;
		POINT pt_end;

		//画饼图
		double R = m_Radius;
		const double PI = 3.1415926;
		double sum = 0;
		//for (int i = 0; i < m_itemNums; i++)
		//	sum += m_percentage[i];

		//验证占比加起来等不等于1
		if (/*sum ==*/ 1)
		{
			//第一个扇形的坐标
			int angle = m_percentage[0] * 360;  //计算占的角度
			POINT pt_s_e;
			pt_start = { (int)R,0 };
			pt_s_e = pt_start;
			pt_end = { int(R*cos(angle * PI / 180)),int(-R * sin(angle * PI / 180)) };
			pDC->SelectObject(CreateSolidBrush(m_color[0])); //上颜色
			pDC->Pie(&pieRect, pt_start, pt_end);
			for (int i = 1; i < m_itemNums; i++)
			{
				pt_start = pt_end;
				angle += m_percentage[i] * 360;
				pt_end = { int(R*cos(angle * PI / 180)),int(-R * sin(angle * PI / 180)) };
				pDC->SelectObject(CreateSolidBrush(m_color[i])); //上颜色
				if (i == m_itemNums - 1)
					pDC->Pie(&pieRect, pt_start, pt_s_e);
				else
					pDC->Pie(&pieRect, pt_start, pt_end);
			}

			//画小矩形
			CRect expRect;
			int l = 0, t = 0;
			for (int i = 0; i < m_itemNums; i++)
			{
				l = m_Radius + 50;
				t = -2 * m_Radius + m_expH * i + 30;
				expRect = { l + 100,t + 50,l + m_expW,t + m_expH + 60 };
				pDC->SelectObject(CreateSolidBrush(m_color[i])); //上颜色
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
				poli = "单独二孩政策下";
			}
			else
			{
				poli = "全面二孩政策下";
			}

			pDC->TextOut(70, 170, poli + str + "年的人口结构");
			str.Format("%u", Total);
			pDC->TextOut(70, 189, "总人数是 " + str);
			str.Format("%u", WomanTotal);
			pDC->TextOut(70, 210, "女性总人数是 " + str);
			str.Format("%u", ManTotal);
			pDC->TextOut(70, 230, "男性性总人数是 " + str);
			//显示百分比
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
	// TODO: 在此添加控件通知处理程序代码
	pWnd = GetDlgItem(IDC_STRSTATIC);
}
