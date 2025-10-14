#pragma warning(disable:4996)

#include "stdafx.h"
#include "tchar.h"
#include "CSmartToolDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include<io.h>   //C����ͷ�ļ�
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

// CSmartToolDlg �Ի���



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


// CSmartToolDlg ��Ϣ�������
void CSmartToolDlg::SetDlgStatus()
{
	if (Reader.ActiveReader() == "")
	{//δ����
		//btnpcscConnect.SetWindowText(_T("Connect"));
		//btnpcscReset.EnableWindow(FALSE);//ΪFALSEʱ����Ч
		m_page1.EnableWindow(FALSE);
		m_page2.EnableWindow(FALSE);
		m_page3.EnableWindow(FALSE);
		m_page4.EnableWindow(FALSE);
	}
	else
	{//������
		//btnpcscConnect.SetWindowText(_T("Disconnect"));
		//btnpcscReset.EnableWindow(TRUE);//ΪTRUEʱ����Ч
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_tab.InsertItem(0, _T("APDU "));
	m_tab.InsertItem(1, _T("CardInfo "));
	//m_tab.InsertItem(2, _T("FileList "));
	m_tab.InsertItem(2, _T("��ѡ�������� "));
	m_tab.InsertItem(3, _T("COS���� "));
	m_tab.InsertItem(4, _T("Applet���� "));
	m_tab.InsertItem(5, _T("Card OTA  "));
	m_tab.InsertItem(6, _T("UKey OTA  "));


	//�����ӶԻ���
	m_page1.Create(MAKEINTRESOURCE(IDD_PAGE1_APDU), &m_tab);
	m_page2.Create(MAKEINTRESOURCE(IDD_PAGE2_CardInfo), &m_tab);
	//m_page3.Create(MAKEINTRESOURCE(IDD_PAGE_Native_PLUS), &m_tab);
	m_page3.Create(MAKEINTRESOURCE(IDD_PAGE5_SetFunc), &m_tab);
	m_page4.Create(MAKEINTRESOURCE(IDD_PAGE3_Download), &m_tab);
	m_page5.Create(MAKEINTRESOURCE(IDD_PAGE4_CapLoadandInstall), &m_tab);
	m_page6.Create(MAKEINTRESOURCE(IDD_PAGE_CardOTA), &m_tab);
	m_page7.Create(MAKEINTRESOURCE(IDD_PAGE_UKeyOTA), &m_tab);
	//����Ի������ʵλ�úʹ�С
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 45;
	//rc.left += 2;
	//rc.right -= 2;
	rc.bottom -= 2;

	//�ƶ��Ի���
	m_page1.MoveWindow(rc);
	m_page2.MoveWindow(rc);
	m_page3.MoveWindow(rc);
	m_page4.MoveWindow(rc);
	m_page5.MoveWindow(rc);
	m_page6.MoveWindow(rc);
	m_page7.MoveWindow(rc);

	//Ĭ����ʾ��һҳ
	m_page1.ShowWindow(SW_SHOW);
	m_page2.ShowWindow(SW_HIDE);
	m_page3.ShowWindow(SW_HIDE);
	m_page4.ShowWindow(SW_HIDE);
	m_page5.ShowWindow(SW_HIDE);
	m_page6.ShowWindow(SW_HIDE);
	m_page7.ShowWindow(SW_HIDE);
	if (!flag_page1)
	{
		m_page1.initAPDUPage();
		flag_page1 = true;
	}

	LoadReadersList();
	SetDlgStatus();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}




// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSmartToolDlg::OnPaint()
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
		m_page6.ShowWindow(SW_HIDE);
		m_page7.ShowWindow(SW_HIDE);
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
		m_page6.ShowWindow(SW_HIDE);
		m_page7.ShowWindow(SW_HIDE);
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
		m_page6.ShowWindow(SW_HIDE);
		m_page7.ShowWindow(SW_HIDE);
		if (!flag_page3)
		{
			m_page3.initSetFuncPage();
			flag_page3 = true;
		}
		break;
	case 3:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_SHOW);
		m_page5.ShowWindow(SW_HIDE);
		m_page6.ShowWindow(SW_HIDE);
		m_page7.ShowWindow(SW_HIDE);
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
		m_page6.ShowWindow(SW_HIDE);
		m_page7.ShowWindow(SW_HIDE);
		if (!flag_page4)
		{
			m_page5.initAppletLOADPage();
			flag_page4 = true;
		}
		break;
	case 5:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		m_page5.ShowWindow(SW_HIDE);
		m_page6.ShowWindow(SW_SHOW);
		m_page7.ShowWindow(SW_HIDE);
		break;
	case 6:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		m_page4.ShowWindow(SW_HIDE);
		m_page5.ShowWindow(SW_HIDE);
		m_page6.ShowWindow(SW_HIDE);
		m_page7.ShowWindow(SW_SHOW);
	default:
		break;
	}

	*pResult = 0;
}
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = comboReaderList.GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	//comboReaderList.GetLBText(nSel, strWeb);
	//MessageBox(strWeb);
	// ����Ͽ���ѡ�е��ַ�����ʾ��IDC_SEL_WEB_EDIT�༭����
	//SetDlgItemText(IDC_SEL_WEB_EDIT, strWeb);
	reConnect();
}


void CSmartToolDlg::OnDropdownComboreaderlist()
{
	LoadReadersList();//ֱ��ˢ���б�
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	if (0 == lstrcmp(ATR.Mid(26, 14), _T("626F79615F5632")))
		gAtrCosType = _T("boya_V2");
	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("626F796153494D")))
		gAtrCosType = _T("boyaSIM");
	else if (0 == lstrcmp(ATR.Mid(26, 14), _T("626F79614C4F44")))
		gAtrCosType = _T("boyaLOD");
	else if (0 == lstrcmp(ATR.Mid(28, 4), _T("C300")))//3B1D968117081212003D17040000C300
		gAtrCosType = _T("M25_Boot");

	else
		gAtrCosType = _T("δ֪��Ƭ");
	
	return true;
}

void CSmartToolDlg::reConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString SelReader;

	int selIndex = comboReaderList.GetCurSel();
	if (selIndex < 0)return;
	comboReaderList.GetLBText(selIndex, SelReader);

		Reader.DisConnectReader();

		//���β���������
		if (!Reader.ConnectReader(SelReader))
		{
			m_page1.AddLog(_T("����ʧ��:") + SelReader);
			m_page1.AddLog(Reader.GetError());
			return;
		}
		//lbpcscActiveReader.SetWindowText(SelReader);//�ŵ������״̬����ʾ
		m_page1.AddLog(SelReader + _T("���ӳɹ���"));

		CString ATR;
		if (!GetgAtrCosType(ATR))
			return;		

		//MessageBox(_T("��ǰ��Ƭ�ǣ�") + gAtrCosType);
		m_page1.AddLog(_T("ATR=") + ATR + _T(" ��ǰ��Ƭ�ǣ�") + gAtrCosType);
		
		lbpcscActiveReader.SetWindowText(SelReader + _T("���ӳɹ���") + _T(" ��ǰ��Ƭ�ǣ�") + gAtrCosType);

		m_page1.initAPDUPage();
		m_page2.initCardInfoPage();
		//m_page3.initNativePlusage();
		m_page4.initDownloadPage();
		m_page5.initAppletLOADPage();

	//ˢ�°�ť��״̬
	SetDlgStatus();
}

void CSmartToolDlg::reConnectForContinue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString SelReader;

	int selIndex = comboReaderList.GetCurSel();
	if (selIndex < 0)return;

	comboReaderList.GetLBText(selIndex, SelReader);
		
	if (!Reader.DisConnectReader())
	{
		m_page1.AddLog(_T("��������ʧ��:") + SelReader);
		m_page1.AddLog(Reader.GetError());
		return;
	}
		

	//���β���������
	if (!Reader.ConnectReader(SelReader))
	{
		m_page1.AddLog(_T("����ʧ��:") + SelReader);
		m_page1.AddLog(Reader.GetError());
		return;
	}
	//lbpcscActiveReader.SetWindowText(SelReader);//�ŵ������״̬����ʾ
	m_page1.AddLog(SelReader + _T("���ӳɹ���"));

	CString ATR;
	if (!GetgAtrCosType(ATR))
		return;

	gCardIsConnected = true;

	m_page1.AddLog(_T("ATR=") + ATR + _T(" ��ǰ��Ƭ�ǣ�") + gAtrCosType);
	lbpcscActiveReader.SetWindowText(SelReader + _T("��Ƭ��λ���ӳɹ���") + _T(" ��ǰ��Ƭ�ǣ�") + gAtrCosType);
}

void CSmartToolDlg::OnBnClickedbtnreset()//Button����λ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString SelReader;

	int selIndex = comboReaderList.GetCurSel();
	if (selIndex < 0)return;
	comboReaderList.GetLBText(selIndex, SelReader);

	//�ȶϿ�
	if (!Reader.DisConnectReader())
	{
		m_page1.AddLog(_T("�Ͽ�����ʧ��:") + SelReader);
		m_page1.AddLog(Reader.GetError());
		return;
	}

	if (!Reader.ConnectReader(SelReader))
	{
		m_page1.AddLog(_T("����ʧ��:") + SelReader);
		m_page1.AddLog(Reader.GetError());
		return;
	}
	//lbpcscActiveReader.SetWindowText(SelReader);//�ŵ������״̬����ʾ

	CString ATR;
	if (!GetgAtrCosType(ATR))
		return;

	//MessageBox(_T("��ǰ��Ƭ�ǣ�") + gAtrCosType);
	m_page1.AddLog(_T("ATR=") + ATR + _T(" ��ǰ��Ƭ�ǣ�") + gAtrCosType);
	lbpcscActiveReader.SetWindowText(SelReader + _T("���ӳɹ���") + +_T(" ��ǰ��Ƭ�ǣ�") + gAtrCosType);
}

void CSmartToolDlg::OnBnClickedbtnconnect()
{
	reConnect();
}

