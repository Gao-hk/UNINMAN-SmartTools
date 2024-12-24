#pragma warning(disable:4996)

#include "stdafx.h"
#include "tchar.h"
#include "CSmartToolDlg.h"
#include "afxdialogex.h"
#include "PAGE1_APDU.h"
#include "PAGE2_CardInfo.h"




#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include<io.h>   //C语言头文件
#include<iostream>   //for system();


using namespace std;

#define	_CRT_SECURE_NO_WARNINGS

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
		//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUT_DIALOG	};
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CSmartToolDlg 对话框



CSmartToolDlg::CSmartToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmartToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Reader =  PCSCReader();
}

void CSmartToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TAB1, m_tab);

	DDX_Control(pDX, btnReset, btnpcscReset);
	DDX_Control(pDX, lbActiveReader, lbpcscActiveReader);
	DDX_Control(pDX, IDC_comboReaderList, comboReaderList);
	DDX_Control(pDX, btnConnect, btnpcscConnect);
}

BEGIN_MESSAGE_MAP(CSmartToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_CBN_SELCHANGE(IDC_comboReaderList, &CSmartToolDlg::OnCbnSelchangecomboreaderlist)
	ON_BN_CLICKED(btnReset, &CSmartToolDlg::OnBnClickedbtnreset)
	ON_BN_CLICKED(btnConnect, &CSmartToolDlg::OnBnClickedbtnconnect)
	ON_BN_CLICKED(btnConnect, &CSmartToolDlg::OnBnClickedbtnconnect)
	ON_CBN_DROPDOWN(IDC_comboReaderList, &CSmartToolDlg::OnDropdownComboreaderlist)
END_MESSAGE_MAP()


// CSmartToolDlg 消息处理程序


int CSmartToolDlg::InitSha1List()
{
	const char* filepath = sha1filepath;// "SHA1_List.csv";

	struct _stat info;
	_stat(filepath, &info);
	int fileSize = info.st_size;

	// 写文件
	ofstream outFile;// ("SHA1_List.csv", ios::app);//ios::app表示在原文件末尾追加
	outFile.open(filepath, ios::app); // 这里的打开模式不可省略，app表示在文件末尾添加
	if (!outFile) {
		cout << "Open the file failure...";
		exit(0);
	}
	if (fileSize == 0)
	{
		outFile << "SHA1" << ',' << "Information" << ',' << endl;
		outFile << "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" << ',' << "空白" << ',' << endl;
		outFile << "7CAD24AAC1B78EBD8BE7F08225AD56F91BB2B839" << ',' << "安全屋(同密电)" << ',' << endl;
		outFile << "C3F75A483FDCECE714A953BAE48B0F82E61439B7" << ',' << "华为1" << ',' << endl;
		outFile << "6ED3668F09206CB45417C1C655E1B5EF9573B32D" << ',' << "华为2" << ',' << endl;
		outFile << "3C4198063E8C26AFC2BEFA7CE0ED5FA581BC82DB" << ',' << "湖南OA" << ',' << endl;
		outFile << "3B4A8033FAD95803EB21EA3F0FD95DB9CD030C4F" << ',' << "中卡" << ',' << endl;
		outFile << "C14646CF5AEBBE40ADC659A55B0B0F45F854F80F" << ',' << "宁夏移动" << ',' << endl;
		outFile << "8C543471D44F0821AC1109879DA08C32AF3EBB92" << ',' << "安徽大数据项目（齐安信云手机）" << ',' << endl;
		outFile << "1952B350971AFEBD7D41945F530B31AEC7F850C3" << ',' << "琥珀盾" << ',' << endl;
		outFile << "10B6FE759A81D52DBDC03417CB4F9C6FA32842B5" << ',' << "安全屋海外" << ',' << endl;
		outFile << "DC3B7345CB8327BCA9B09A17378BF573AF4D3E20" << ',' << "兵器" << ',' << endl;
		outFile << "6987335CE18D8BC9263AF2969BACEE175CFB4E86" << ',' << "网信所" << ',' << endl;
		outFile << "65D0D48C301E5B54F40D880D39AB9C7104C671AC" << ',' << "启迪" << ',' << endl;
		outFile << "E8259ACBBC13105321ACCACF891AD00B802F858E" << ',' << "国网思极网安" << ',' << endl;
		outFile << "E7CE74187B23472C8D25BCDA651796BB585E5305" << ',' << "齊耀电子" << ',' << endl;
		outFile << "8722399D037A4D0B4C17583A2DFBEFD3F848B09E" << ',' << "对外版" << ',' << endl;
		outFile << "B61D0C972ED638946621BA7F74BB6611DA24D8D1" << ',' << "甘肃武警项目（对接一所）" << ',' << endl;
		outFile << "2509952797814FBDCF3D1AEFEB8F059FFCFEBA6C" << ',' << "宁夏政法委新sha值" << ',' << endl;
		outFile << "34F8756D8C408AE9F62AD3F234DAD3D880A30FFD" << ',' << "南瑞" << ',' << endl;
	}
	outFile.close();

	return 0;
}

void CSmartToolDlg::SetDlgStatus()
{
	if (Reader.ActiveReader() == "")
	{//未连接
		//btnpcscConnect.SetWindowText(_T("Connect"));
		//btnpcscReset.EnableWindow(FALSE);//为FALSE时是无效
		m_page1.EnableWindow(FALSE);
		m_page2.EnableWindow(FALSE);
		m_page3.EnableWindow(FALSE);
		m_page4.EnableWindow(FALSE);
	}
	else
	{//已连接
		//btnpcscConnect.SetWindowText(_T("Disconnect"));
		//btnpcscReset.EnableWindow(TRUE);//为TRUE时是有效
		m_page1.EnableWindow(TRUE);
		m_page2.EnableWindow(TRUE);
		m_page3.EnableWindow(TRUE);
		m_page4.EnableWindow(TRUE);
	}
}

void CSmartToolDlg::LoadReaders()
{
	lstpcscReaders.ResetContent();

	if (Reader.EnmuReaders())
	{
		for (int i = 0; i < Reader.ReaderCount(); i++)
		{
			lstpcscReaders.AddString(Reader.GetReaderName(i));
		}
	}
}
void CSmartToolDlg::LoadReadersList()
{
	comboReaderList.ResetContent();

	if (Reader.EnmuReaders())
	{
		for (int i = 0; i < Reader.ReaderCount(); i++)
		{
			comboReaderList.InsertString(-1, Reader.GetReaderName(i));
		}
	}
}

BOOL CSmartToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		if (strAboutMenu.LoadString(IDS_ABOUTBOX))
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_tab.InsertItem(0, _T("APDU"));
	m_tab.InsertItem(1, _T("卡信息（旧）"));
	m_tab.InsertItem(3, _T("Native+ FileList"));
	m_tab.InsertItem(4, _T("COS下载（旧）"));
	m_tab.InsertItem(5, _T("Applet"));


	//创建子对话框
	m_page1.Create(MAKEINTRESOURCE(IDD_PAGE1_APDU), &m_tab);
	m_page2.Create(MAKEINTRESOURCE(IDD_PAGE2_CardInfo), &m_tab);
	m_page3.Create(MAKEINTRESOURCE(IDD_PAGE_Native_PLUS), &m_tab);
	m_page4.Create(MAKEINTRESOURCE(IDD_PAGE3_Download), &m_tab);
	m_page5.Create(MAKEINTRESOURCE(IDD_PAGE4_CapLoadandInstall), &m_tab);
	//计算对话框的现实位置和大小
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 45;
	//rc.left += 2;
	//rc.right -= 2;
	rc.bottom -= 2;

	//移动对话框
	m_page1.MoveWindow(rc);
	m_page2.MoveWindow(rc);
	m_page3.MoveWindow(rc);
	m_page4.MoveWindow(rc);
	m_page5.MoveWindow(rc);

	//默认显示第一页
	m_page1.ShowWindow(SW_SHOW);
	m_page2.ShowWindow(SW_HIDE);
	m_page3.ShowWindow(SW_HIDE);
	m_page4.ShowWindow(SW_HIDE);
	m_page5.ShowWindow(SW_HIDE);
	if (!flag_page1)
	{
		m_page1.initAPDUPage();
		flag_page1 = true;
	}

	//初始显示值
	//m_page1.GetDlgItem(IDC_EDT_DATA)->SetWindowText(_T("7E25000021"));

	// TODO:  在此添加额外的初始化代码
	//LoadReaders();
	LoadReadersList();
	SetDlgStatus();

	InitSha1List();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}




// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSmartToolDlg::OnPaint()
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

void CSmartToolDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	switch (m_tab.GetCurSel())
	{
	case 0:
		m_page1.ShowWindow(SW_SHOW);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		m_page5.ShowWindow(SW_HIDE);
		if (!flag_page1)
		{			
			m_page1.initAPDUPage();
			flag_page1 = true;
		}
		break;
	case 1:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_SHOW);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		m_page5.ShowWindow(SW_HIDE);
		if (!flag_page2)
		{
			m_page2.initCardInfoPage();
			flag_page2 = true;
		}		
		break;
	case 2:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_SHOW);
		m_page4.ShowWindow(SW_HIDE);
		m_page5.ShowWindow(SW_HIDE);
		if (!flag_page3)
		{
			m_page3.initNativePlusage();
			flag_page3 = true;
		}
		break;
	case 3:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_SHOW);
		m_page5.ShowWindow(SW_HIDE);
		if (!flag_page4)
		{
			m_page4.initDownloadPage();
			flag_page4 = true;
		}
		break;
	case 4:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		m_page5.ShowWindow(SW_SHOW);
		if (!flag_page4)
		{
			m_page5.initAppletLOADPage();
			flag_page4 = true;
		}
		break;
	default:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		m_page5.ShowWindow(SW_SHOW);
		break;
	}

	*pResult = 0;
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSmartToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}








boolean gCardIsConnected = false;
void CSmartToolDlg::OnCbnSelchangecomboreaderlist()
{
	// TODO: Add your control notification handler code here
	CString strWeb;
	int nSel;
	// 获取组合框控件的列表框中选中项的索引
	nSel = comboReaderList.GetCurSel();
	// 根据选中项索引获取该项字符串
	//comboReaderList.GetLBText(nSel, strWeb);
	//MessageBox(strWeb);
	// 将组合框中选中的字符串显示到IDC_SEL_WEB_EDIT编辑框中
	//SetDlgItemText(IDC_SEL_WEB_EDIT, strWeb);
	reConnect();
}


void CSmartToolDlg::OnDropdownComboreaderlist()
{
	LoadReadersList();//直接刷新列表
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}

void CSmartToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


boolean CSmartToolDlg::GetgAtrCosType(CString &ATR)
{
	ATR = Reader.ATRByResetCard();
	if (ATR == _T(""))
	{
		m_page1.AddLog(Reader.GetError());
		return false;
	}

	if (0 == lstrcmp(ATR.Mid(12, 12), _T("43532E4A4F53")))//3B9D96801FC743532E4A4F532056322E323094C7
		gAtrCosType = _T("CS.JCOS");

	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("4D54325F576C74")))
		gAtrCosType = _T("MT2_Wlt");
	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("4D54325F434F53")))
		gAtrCosType = _T("MT2_COS");
	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("4D5432224E6174")))
		gAtrCosType = _T("MT222_Nat+");
	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("4D5432114E6174")))
		gAtrCosType = _T("MT211_Nat+");
	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("4153494D4E6174")))
		gAtrCosType = _T("SIM_Nat+");

	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("4D543222534B46")))
		gAtrCosType = _T("MT222_SKF");
	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("4D543211534B46")))
		gAtrCosType = _T("MT211_SKF");
	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("4153494D534B46")))
		gAtrCosType = _T("SIM_SKF");

	else if (0 == lstrcmp(ATR.Mid(28, 4), _T("C300")))//3B1D968117081212003D17040000C300
		gAtrCosType = _T("MT2_Boot");

	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("4D54315F434F53")))
		gAtrCosType = _T("MT1_COS");
	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("4D54315F534B46")))
		gAtrCosType = _T("MT1_SKF");

	else if (0 == lstrcmp(ATR, _T("3B9F96801FC38031E073FA211B678500000200020055")))
		gAtrCosType = _T("中卡COS");
	else if (0 == lstrcmp(ATR.Mid(6, 2) + ATR.Mid(22, 2), _T("E086")))
		gAtrCosType = _T("MT1_Boot");

	else if (0 == lstrcmp(ATR.Mid(8, 8), _T("57694C4C")))
		gAtrCosType = _T("THD88_JCOS");
	else if (0 == lstrcmp(ATR, _T("3B9796803F47A08031E073FE211BBF")))
		gAtrCosType = _T("融卡_JCOS");
	else if (0 == lstrcmp(ATR, _T("3B9F96803FC7A08031E073FE211B634E10518300900048")))
		gAtrCosType = _T("恒宝_JCOS");
	else
		gAtrCosType = _T("未知卡片");
	
	return true;
}

void CSmartToolDlg::reConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	CString SelReader;

	int selIndex = comboReaderList.GetCurSel();
	if (selIndex < 0)return;
	comboReaderList.GetLBText(selIndex, SelReader);

		Reader.DisConnectReader();

		//本次操作：连接
		if (!Reader.ConnectReader(SelReader))
		{
			m_page1.AddLog(_T("连接失败:") + SelReader);
			m_page1.AddLog(Reader.GetError());
			return;
		}
		//lbpcscActiveReader.SetWindowText(SelReader);//放到后面的状态栏显示
		m_page1.AddLog(SelReader + _T("连接成功！"));

		CString ATR;
		if (!GetgAtrCosType(ATR))
			return;		

		//MessageBox(_T("当前卡片是：") + gAtrCosType);
		m_page1.AddLog(_T("ATR=") + ATR + _T(" 当前卡片是：") + gAtrCosType);
		
		lbpcscActiveReader.SetWindowText(SelReader + _T("连接成功！") + _T(" 当前卡片是：") + gAtrCosType);

		m_page1.initAPDUPage();
		m_page2.initCardInfoPage();
		m_page3.initNativePlusage();
		m_page4.initDownloadPage();
		m_page5.initAppletLOADPage();

	//刷新按钮等状态
	SetDlgStatus();
}

void CSmartToolDlg::reConnectForContinue()
{
	// TODO: 在此添加控件通知处理程序代码
	CString SelReader;

	int selIndex = comboReaderList.GetCurSel();
	if (selIndex < 0)return;

	comboReaderList.GetLBText(selIndex, SelReader);
		
	if (!Reader.DisConnectReader())
	{
		m_page1.AddLog(_T("重新连接失败:") + SelReader);
		m_page1.AddLog(Reader.GetError());
		return;
	}
		

	//本次操作：连接
	if (!Reader.ConnectReader(SelReader))
	{
		m_page1.AddLog(_T("连接失败:") + SelReader);
		m_page1.AddLog(Reader.GetError());
		return;
	}
	//lbpcscActiveReader.SetWindowText(SelReader);//放到后面的状态栏显示
	m_page1.AddLog(SelReader + _T("连接成功！"));

	CString ATR;
	if (!GetgAtrCosType(ATR))
		return;

	gCardIsConnected = true;

	m_page1.AddLog(_T("ATR=") + ATR + _T(" 当前卡片是：") + gAtrCosType);
	lbpcscActiveReader.SetWindowText(SelReader + _T("卡片复位连接成功！") + _T(" 当前卡片是：") + gAtrCosType);
}

void CSmartToolDlg::OnBnClickedbtnreset()//Button：复位
{
	// TODO:  在此添加控件通知处理程序代码
	CString SelReader;

	int selIndex = comboReaderList.GetCurSel();
	if (selIndex < 0)return;
	comboReaderList.GetLBText(selIndex, SelReader);

	//先断开
	if (!Reader.DisConnectReader())
	{
		m_page1.AddLog(_T("断开连接失败:") + SelReader);
		m_page1.AddLog(Reader.GetError());
		return;
	}

	if (!Reader.ConnectReader(SelReader))
	{
		m_page1.AddLog(_T("连接失败:") + SelReader);
		m_page1.AddLog(Reader.GetError());
		return;
	}
	//lbpcscActiveReader.SetWindowText(SelReader);//放到后面的状态栏显示

	CString ATR;
	if (!GetgAtrCosType(ATR))
		return;

	//MessageBox(_T("当前卡片是：") + gAtrCosType);
	m_page1.AddLog(_T("ATR=") + ATR + _T(" 当前卡片是：") + gAtrCosType);
	lbpcscActiveReader.SetWindowText(SelReader + _T("连接成功！") + +_T(" 当前卡片是：") + gAtrCosType);
}

void CSmartToolDlg::OnBnClickedbtnconnect()
{
	reConnect();
}

