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


int CSmartToolDlg::InitSha1List()
{
	const char* filepath = sha1filepath;// "SHA1_List.csv";

	struct _stat info;
	_stat(filepath, &info);
	int fileSize = info.st_size;

	// д�ļ�
	ofstream outFile;// ("SHA1_List.csv", ios::app);//ios::app��ʾ��ԭ�ļ�ĩβ׷��
	outFile.open(filepath, ios::app); // ����Ĵ�ģʽ����ʡ�ԣ�app��ʾ���ļ�ĩβ���
	if (!outFile) {
		cout << "Open the file failure...";
		exit(0);
	}
	if (fileSize == 0)
	{
		outFile << "SHA1" << ',' << "Information" << ',' << endl;
		outFile << "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" << ',' << "�հ�" << ',' << endl;
		outFile << "7CAD24AAC1B78EBD8BE7F08225AD56F91BB2B839" << ',' << "��ȫ��(ͬ�ܵ�)" << ',' << endl;
		outFile << "C3F75A483FDCECE714A953BAE48B0F82E61439B7" << ',' << "��Ϊ1" << ',' << endl;
		outFile << "6ED3668F09206CB45417C1C655E1B5EF9573B32D" << ',' << "��Ϊ2" << ',' << endl;
		outFile << "3C4198063E8C26AFC2BEFA7CE0ED5FA581BC82DB" << ',' << "����OA" << ',' << endl;
		outFile << "3B4A8033FAD95803EB21EA3F0FD95DB9CD030C4F" << ',' << "�п�" << ',' << endl;
		outFile << "C14646CF5AEBBE40ADC659A55B0B0F45F854F80F" << ',' << "�����ƶ�" << ',' << endl;
		outFile << "8C543471D44F0821AC1109879DA08C32AF3EBB92" << ',' << "���մ�������Ŀ���밲�����ֻ���" << ',' << endl;
		outFile << "1952B350971AFEBD7D41945F530B31AEC7F850C3" << ',' << "�����" << ',' << endl;
		outFile << "10B6FE759A81D52DBDC03417CB4F9C6FA32842B5" << ',' << "��ȫ�ݺ���" << ',' << endl;
		outFile << "DC3B7345CB8327BCA9B09A17378BF573AF4D3E20" << ',' << "����" << ',' << endl;
		outFile << "6987335CE18D8BC9263AF2969BACEE175CFB4E86" << ',' << "������" << ',' << endl;
		outFile << "65D0D48C301E5B54F40D880D39AB9C7104C671AC" << ',' << "����" << ',' << endl;
		outFile << "E8259ACBBC13105321ACCACF891AD00B802F858E" << ',' << "����˼������" << ',' << endl;
		outFile << "E7CE74187B23472C8D25BCDA651796BB585E5305" << ',' << "�Rҫ����" << ',' << endl;
		outFile << "8722399D037A4D0B4C17583A2DFBEFD3F848B09E" << ',' << "�����" << ',' << endl;
		outFile << "B61D0C972ED638946621BA7F74BB6611DA24D8D1" << ',' << "�����侯��Ŀ���Խ�һ����" << ',' << endl;
		outFile << "2509952797814FBDCF3D1AEFEB8F059FFCFEBA6C" << ',' << "��������ί��shaֵ" << ',' << endl;
		outFile << "34F8756D8C408AE9F62AD3F234DAD3D880A30FFD" << ',' << "����" << ',' << endl;
	}
	outFile.close();

	return 0;
}

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

	m_tab.InsertItem(0, _T("APDU"));
	m_tab.InsertItem(1, _T("����Ϣ���ɣ�"));
	m_tab.InsertItem(3, _T("Native+ FileList"));
	m_tab.InsertItem(4, _T("COS���أ��ɣ�"));
	m_tab.InsertItem(5, _T("Applet"));


	//�����ӶԻ���
	m_page1.Create(MAKEINTRESOURCE(IDD_PAGE1_APDU), &m_tab);
	m_page2.Create(MAKEINTRESOURCE(IDD_PAGE2_CardInfo), &m_tab);
	m_page3.Create(MAKEINTRESOURCE(IDD_PAGE_Native_PLUS), &m_tab);
	m_page4.Create(MAKEINTRESOURCE(IDD_PAGE3_Download), &m_tab);
	m_page5.Create(MAKEINTRESOURCE(IDD_PAGE4_CapLoadandInstall), &m_tab);
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

	//Ĭ����ʾ��һҳ
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

	//��ʼ��ʾֵ
	//m_page1.GetDlgItem(IDC_EDT_DATA)->SetWindowText(_T("7E25000021"));

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//LoadReaders();
	LoadReadersList();
	SetDlgStatus();

	InitSha1List();

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
		gAtrCosType = _T("�п�COS");
	else if (0 == lstrcmp(ATR.Mid(6, 2) + ATR.Mid(22, 2), _T("E086")))
		gAtrCosType = _T("MT1_Boot");

	else if (0 == lstrcmp(ATR.Mid(8, 8), _T("57694C4C")))
		gAtrCosType = _T("THD88_JCOS");
	else if (0 == lstrcmp(ATR, _T("3B9796803F47A08031E073FE211BBF")))
		gAtrCosType = _T("�ڿ�_JCOS");
	else if (0 == lstrcmp(ATR, _T("3B9F96803FC7A08031E073FE211B634E10518300900048")))
		gAtrCosType = _T("�㱦_JCOS");
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
		m_page3.initNativePlusage();
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

