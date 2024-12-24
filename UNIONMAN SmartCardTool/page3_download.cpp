#include "stdafx.h"
#include "page3_download.h"
#include "CSmartToolDlg.h"
#include "afxdialogex.h"

#include "afxwin.h"
#include "afxcmn.h"


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include<io.h>   //C����ͷ�ļ�
#include<iostream>   //for system();


#include "tchar.h"
#include   "ATLCONV.H"
//#include "Thread.h"
#include   "..\SM4\sm4.h"

#include "progress.h"
#include "Init_MF.h"
#include "Init_SecurityHouse.h"
#include "Init_WeLink.h"

using namespace std;



// PAGE2_download �Ի���

page3downloadDlg::page3downloadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(page3downloadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void page3downloadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	

	DDX_Control(pDX, page3edtSHA1_1, page3edtpcscSHA1_1);
	DDX_Control(pDX, page3edtSHA1_2, page3edtpcscSHA1_2);
	DDX_Control(pDX, page3edtSHA1_3, page3edtpcscSHA1_3);
	DDX_Control(pDX, page3edtSHA1_4, page3edtpcscSHA1_4);
	DDX_Control(pDX, page3edtSHA1_5, page3edtpcscSHA1_5);

	DDX_Control(pDX, page3comboSha1List1, page3combopcscSha1List1);
	DDX_Control(pDX, page3comboSha1List2, page3combopcscSha1List2);
	DDX_Control(pDX, page3comboSha1List3, page3combopcscSha1List3);
	DDX_Control(pDX, page3comboSha1List4, page3combopcscSha1List4);
	DDX_Control(pDX, page3comboSha1List5, page3combopcscSha1List5);

	DDX_Control(pDX, page3edtBLE, page3edtpcscBLE);
	DDX_Control(pDX, page3edtSn, page3edtpcscSn);
	DDX_Control(pDX, page3edtStatus, page3edtpcscStatus);
	DDX_Control(pDX, page3edtCosFile, page3edtpcscCosFile);

	DDX_Control(pDX, page3btnOpenFile, page3btnpcscOpenFile);
	DDX_Control(pDX, page3btnBoot,page3btnpcscBoot);
	DDX_Control(pDX, page3process1,page3pcscprocess1);
}


#define WM_UPDATEDATA WM_USER + 1999 //�����¼�

BEGIN_MESSAGE_MAP(page3downloadDlg, CDialogEx)
	ON_MESSAGE(WM_UPDATEDATA, &page3downloadDlg::OnMsg)   //���¼���������
	//ON_BN_CLICKED(btnGet, &page3downloadDlg::OnBnClickedbtnGet)
	//ON_BN_CLICKED(btnSet, &page3downloadDlg::OnBnClickedbtnSet)
	ON_CBN_SELCHANGE(page3comboSha1List1, &page3downloadDlg::OnCbnSelchangepage3combosha1list1)
	ON_CBN_SELCHANGE(page3comboSha1List2, &page3downloadDlg::OnCbnSelchangepage3combosha1list2)
	ON_CBN_SELCHANGE(page3comboSha1List3, &page3downloadDlg::OnCbnSelchangepage3combosha1list3)
	ON_CBN_SELCHANGE(page3comboSha1List4, &page3downloadDlg::OnCbnSelchangepage3combosha1list4)
	ON_CBN_SELCHANGE(page3comboSha1List5, &page3downloadDlg::OnCbnSelchangepage3combosha1list5)

	ON_BN_CLICKED(page3btnOpenFile, &page3downloadDlg::OnBnClickedpage3btnopenfile)
	ON_BN_CLICKED(page3btnBoot, &page3downloadDlg::OnBnClickedpage3btnboot)

	ON_BN_CLICKED(page3radioMT222A, &page3downloadDlg::OnBnClickedpage3radiomt222a)
	ON_BN_CLICKED(page3radioMT222C, &page3downloadDlg::OnBnClickedpage3radiomt222c)
	ON_BN_CLICKED(page3radioMT211, &page3downloadDlg::OnBnClickedpage3radiomt211)
	ON_EN_CHANGE(page3edtBLE, &page3downloadDlg::OnChangePage3edtble)
	ON_EN_CHANGE(page3edtSn, &page3downloadDlg::OnChangePage3edtsn)
	ON_EN_CHANGE(page3edtSHA1_1, &page3downloadDlg::OnChangePage3edtsha11)
	ON_EN_CHANGE(page3edtSHA1_2, &page3downloadDlg::OnChangePage3edtsha12)
	ON_EN_CHANGE(page3edtSHA1_3, &page3downloadDlg::OnChangePage3edtsha13)
	ON_EN_CHANGE(page3edtSHA1_4, &page3downloadDlg::OnChangePage3edtsha14)
	ON_EN_CHANGE(page3edtSHA1_5, &page3downloadDlg::OnChangePage3edtsha15)
END_MESSAGE_MAP()




// PAGE2_CardInfo ��Ϣ�������
int page3downloadDlg::readpage3Sha1List()
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	const char* filepath2 = pDlg->sha1filepath;// "SHA1_List.csv";

	page3combopcscSha1List1.ResetContent();
	page3combopcscSha1List2.ResetContent();
	page3combopcscSha1List3.ResetContent();
	page3combopcscSha1List4.ResetContent();
	page3combopcscSha1List5.ResetContent();

	struct _stat info;
	_stat(filepath2, &info);
	int fileSize = info.st_size;
	char insertFlag=0;

	// ���ļ�
	CStdioFile file;
	file.Open(_T("./SHA1_List.csv"), CFile::modeRead);
	CString str;
	while (file.ReadString(str))
	{
		str = str.Trim(_T(" "));
		CString substr[6];
		int count = 0;
		int index = str.Find(_T(","));
		while (index != -1 && count < 6)
		{
			substr[count++] = str.Left(index);
			str = str.Right(str.GetLength() - index - 1);
			index = str.Find(_T(","));
		}
		substr[count++] = str;

		if(insertFlag==0)
		{
			insertFlag = 1;
		}
		else
		{
			page3combopcscSha1List1.InsertString(-1, substr[1]);
			page3combopcscSha1List2.InsertString(-1, substr[1]);
			page3combopcscSha1List3.InsertString(-1, substr[1]);
			page3combopcscSha1List4.InsertString(-1, substr[1]);
			page3combopcscSha1List5.InsertString(-1, substr[1]);
		}
	}
	file.Close();

	return 0;
}


void page3downloadDlg::setSHA1Disp(boolean dispFlag, boolean clearCheckSha1Flag)
{
	page3edtpcscSHA1_1.ShowWindow(dispFlag);
	page3edtpcscSHA1_2.ShowWindow(dispFlag);
	page3edtpcscSHA1_3.ShowWindow(dispFlag);
	page3edtpcscSHA1_4.ShowWindow(dispFlag);
	page3edtpcscSHA1_5.ShowWindow(dispFlag);


	page3combopcscSha1List1.ShowWindow(dispFlag);
	page3combopcscSha1List2.ShowWindow(dispFlag);
	page3combopcscSha1List3.ShowWindow(dispFlag);
	page3combopcscSha1List4.ShowWindow(dispFlag);
	page3combopcscSha1List5.ShowWindow(dispFlag);

	((CStatic*)GetDlgItem(IDC_STATIC_SHA1List))->ShowWindow(dispFlag);

	(CButton*)GetDlgItem(checkSha1)->ShowWindow(dispFlag);

}
void page3downloadDlg::setTypeDisp(boolean dispFlag, boolean clearCheckTypeFlag)
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();
	
	if (pDlg->gAtrCosType == _T("MT1_Boot"))
	{
		((CButton*)GetDlgItem(page3radioMT1))->SetCheck(true);
		((CButton*)GetDlgItem(page3radioMT1))->ShowWindow(true);
		((CButton*)GetDlgItem(page3radioMT222A))->ShowWindow(false);
		((CButton*)GetDlgItem(page3radioMT222C))->ShowWindow(false);
		((CButton*)GetDlgItem(page3radioMT211))->ShowWindow(false);

		((CStatic*)GetDlgItem(IDC_STATIC_CardType))->ShowWindow(true);
		(CButton*)GetDlgItem(checkCardType)->ShowWindow(true);
		(CButton*)GetDlgItem(checkCardType)->EnableWindow(false);
		setMacDisp(false);
	}
	else if ((pDlg->gAtrCosType == _T("MT2_Boot")) && dispFlag)
	{
		((CButton*)GetDlgItem(page3radioMT1))->ShowWindow(false);
		((CButton*)GetDlgItem(page3radioMT222A))->ShowWindow(true);
		((CButton*)GetDlgItem(page3radioMT222C))->ShowWindow(true);
		((CButton*)GetDlgItem(page3radioMT211))->ShowWindow(true);

		((CStatic*)GetDlgItem(IDC_STATIC_CardType))->ShowWindow(true);
		(CButton*)GetDlgItem(checkCardType)->ShowWindow(true);
		(CButton*)GetDlgItem(checkCardType)->EnableWindow(true);
		setMacDisp(true);
	}
	else
	{
		((CButton*)GetDlgItem(page3radioMT1))->ShowWindow(dispFlag);
		((CButton*)GetDlgItem(page3radioMT222A))->ShowWindow(dispFlag);
		((CButton*)GetDlgItem(page3radioMT222C))->ShowWindow(dispFlag);
		((CButton*)GetDlgItem(page3radioMT211))->ShowWindow(dispFlag);

		((CStatic*)GetDlgItem(IDC_STATIC_CardType))->ShowWindow(dispFlag);
		(CButton*)GetDlgItem(checkCardType)->ShowWindow(dispFlag);
		setMacDisp(dispFlag);
	}
}
void page3downloadDlg::setMacDisp(boolean dispFlag)
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();	

	if (pDlg->gAtrCosType != _T("MT2_Boot"))
	{
		page3edtpcscBLE.ShowWindow(false);
		((CStatic*)GetDlgItem(IDC_STATIC_BLE_P3))->ShowWindow(false);
		((CStatic*)GetDlgItem(IDC_STATIC_MAC))->ShowWindow(false);
		(CButton*)GetDlgItem(checkMAC)->ShowWindow(false);
		return;
	}

	if((radioFlag != _T("MT222A"))
		&& (radioFlag != _T("MT222C"))
		)
	{
		page3edtpcscBLE.ShowWindow(false);
		((CStatic*)GetDlgItem(IDC_STATIC_BLE_P3))->ShowWindow(false);
		((CStatic*)GetDlgItem(IDC_STATIC_MAC))->ShowWindow(false);
		(CButton*)GetDlgItem(checkMAC)->ShowWindow(false);
		return;
	}

	page3edtpcscBLE.ShowWindow(dispFlag);
	((CStatic*)GetDlgItem(IDC_STATIC_BLE_P3))->ShowWindow(dispFlag);
	((CStatic*)GetDlgItem(IDC_STATIC_MAC))->ShowWindow(dispFlag);
	(CButton*)GetDlgItem(checkMAC)->ShowWindow(dispFlag);
}
void page3downloadDlg::setSnDisp(boolean dispFlag, boolean clearCheckSnFlag)
{
	page3edtpcscSn.ShowWindow(dispFlag);
	((CStatic*)GetDlgItem(IDC_STATIC_SN))->ShowWindow(dispFlag);
	(CButton*)GetDlgItem(checkSN)->ShowWindow(dispFlag);
}

void page3downloadDlg::setAppDisp()
{
	CString filePath; 
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();


	page3edtpcscCosFile.GetWindowText(filePath);


	if (((pDlg->gAtrCosType == _T("MT1_Boot")) || (pDlg->gAtrCosType == _T("MT2_Boot"))))
	{
		if (std::string::npos != filePath.Find(_T("SmartCOS")))
		{
			(CButton*)GetDlgItem(checkSHouse)->ShowWindow(true);
			(CButton*)GetDlgItem(checkWeLink)->ShowWindow(true);
			setSHA1Disp(true, true);
		}
		else
		{
			if ((filePath.Find(_T("JOS")) != std::string::npos)
				|| (filePath.Find(_T("jos")) != std::string::npos)
				|| (filePath.Find(_T("JCOS")) != std::string::npos)
				|| (filePath.Find(_T("jcos")) != std::string::npos)
				)//Java Card��COS�ű�
			{
				setSHA1Disp(false, true);
			}
			else
			{
				setSHA1Disp(true, true);
			}
			(CButton*)GetDlgItem(checkSHouse)->ShowWindow(false);
			(CButton*)GetDlgItem(checkWeLink)->ShowWindow(false);
		}
	}
	else
	{

		(CButton*)GetDlgItem(checkSHouse)->ShowWindow(false);
		(CButton*)GetDlgItem(checkWeLink)->ShowWindow(false);
		setSHA1Disp(false, true);
	}
}

void page3downloadDlg::clearCardDownloadInfoDisp()
{	page3edtpcscBLE.SetWindowText(_T(""));

	page3edtpcscSn.SetWindowText(_T(""));
	page3edtpcscStatus.SetWindowText(_T(""));

	page3edtpcscSHA1_1.SetWindowText(_T(""));
	page3edtpcscSHA1_2.SetWindowText(_T(""));
	page3edtpcscSHA1_3.SetWindowText(_T(""));
	page3edtpcscSHA1_4.SetWindowText(_T(""));
	page3edtpcscSHA1_5.SetWindowText(_T(""));

	((CButton*)GetDlgItem(page3radioMT1))->SetCheck(false);
	((CButton*)GetDlgItem(page3radioMT211))->SetCheck(false);
	((CButton*)GetDlgItem(page3radioMT222A))->SetCheck(false);
	((CButton*)GetDlgItem(page3radioMT222C))->SetCheck(false);
}

void page3downloadDlg::setCardDownloadDisp(boolean bootloadStatus, boolean enableDownlaodeorBootBtnFlag)
{
	page3btnpcscBoot.ShowWindow(enableDownlaodeorBootBtnFlag);
	page3btnpcscBoot.SetWindowText(bootloadStatus?_T("��ʼ����"): _T("�����Ƭ"));

	setSHA1Disp(bootloadStatus, false);
	setTypeDisp(bootloadStatus, false);
	setSnDisp(bootloadStatus, false);

	page3edtpcscCosFile.ShowWindow(bootloadStatus);
	page3btnpcscOpenFile.ShowWindow(bootloadStatus);
	page3btnpcscDownload.ShowWindow(bootloadStatus);
	page3pcscprocess1.ShowWindow(bootloadStatus);
}
void page3downloadDlg::getCardDownloadInfo()
{
	boolean dispSha1Flag = true;
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();	

	clearCardDownloadInfoDisp();

	//Get Card Type
	if ( pDlg->gAtrCosType == _T("MT1_Boot"))
	{
		setCardDownloadDisp(true, true);
		radioFlag = _T("MT1");
	}
	else if (pDlg->gAtrCosType == _T("MT2_Boot"))
	{
		setCardDownloadDisp(true, true);
	}
	else 
	{
		radioFlag = _T("");
		if ((pDlg->gAtrCosType == _T("CS.JCOS"))
			|| (pDlg->gAtrCosType == _T("MT2_COS"))
			|| (pDlg->gAtrCosType == _T("MT2_Wlt"))
			|| (pDlg->gAtrCosType == _T("MT222_Nat+"))
			|| (pDlg->gAtrCosType == _T("MT211_Nat+"))
			|| (pDlg->gAtrCosType == _T("SIM_Nat+"))
			|| (pDlg->gAtrCosType == _T("MT222_SKF"))
			|| (pDlg->gAtrCosType == _T("MT211SKF"))
			|| (pDlg->gAtrCosType == _T("SIM_SKF"))

			|| (pDlg->gAtrCosType == _T("MT1_COS"))
			|| (pDlg->gAtrCosType == _T("MT1_SKF"))
			|| (pDlg->gAtrCosType == _T("�п�COS"))
			)
		{
			setCardDownloadDisp(false, true);
		}
		//else if ((pDlg->gAtrCosType == _T("δ֪��Ƭ")) || (pDlg->gAtrCosType == _T("��Ƭ�ѶϿ�")) || (pDlg->gAtrCosType == _T("")))
		else
		{
			setCardDownloadDisp(false, false);
		}
	}
	setAppDisp();
}
void page3downloadDlg::initDownloadPage()
{
	readpage3Sha1List();
	getCardDownloadInfo();
}



boolean page3downloadDlg::Getpage3SelwithSha1Data(LPCTSTR sha1,int *retSel)
{
	int nSel=0;
	char retFlag = 0;
	// ���ļ�
	CStdioFile file;
	file.Open(_T("./SHA1_List.csv"), CFile::modeRead);
	CString str;
	while (file.ReadString(str))
	{
		str = str.Trim(_T(" "));
		CString substr[6];
		int count = 0;
		int index = str.Find(_T(","));
		while (index != -1 && count < 6)
		{
			substr[count++] = str.Left(index);
			str = str.Right(str.GetLength() - index - 1);
			index = str.Find(_T(","));
		}
		substr[count++] = str;
		
		CString stmp;
		stmp.Format(_T("%s"), substr[0]);

		if (0 == lstrcmp(stmp, sha1))
		{
			file.Close();
			*retSel = nSel-1;//ȥ����һ�б�����
			return TRUE;
		}
		nSel++;
	}
	file.Close();
	return FALSE;
}
boolean page3downloadDlg::Getpage3Sha1DataWithSel(CString *sha1, int inSel)
{
	int nSel = 0;
	char retFlag = 0;
	// ���ļ�
	CStdioFile file;
	*sha1 = _T("");
	file.Open(_T("./SHA1_List.csv"), CFile::modeRead);
	CString str;
	while (file.ReadString(str))
	{
		nSel++;
		if(nSel<(inSel+1) +1)
			continue;

		str = str.Trim(_T(" "));
		CString substr[6];
		int count = 0;
		int index = str.Find(_T(","));
		while (index != -1 && count < 6)
		{
			substr[count++] = str.Left(index);
			str = str.Right(str.GetLength() - index - 1);
			index = str.Find(_T(","));
		}
		substr[count++] = str;

		CString stmp;
		stmp.Format(_T("%s"), substr[0]);
		*sha1 = stmp;
		file.Close();
		return TRUE;
	}
	file.Close();
	return FALSE;
}

void page3downloadDlg::Loadpage3Sha1List()
{
	page3combopcscSha1List1.ResetContent();
	page3combopcscSha1List2.ResetContent();
	page3combopcscSha1List3.ResetContent();
	page3combopcscSha1List4.ResetContent();
	page3combopcscSha1List5.ResetContent();

	int nSel=0;

	// ���ļ�
	CStdioFile file;
	file.Open(_T("./SHA1_List.csv"), CFile::modeRead);
	CString str;
	while (file.ReadString(str))
	{
		str = str.Trim(_T(" "));
		CString substr[6];
		int count = 0;
		int index = str.Find(_T(","));
		while (index != -1 && count <6)
		{
			substr[count++] = str.Left(index);
			str = str.Right(str.GetLength() - index - 1);
			index = str.Find(_T(","));
		}
		substr[count++] = str;

		if (nSel > 0)
		{
			page3combopcscSha1List1.InsertString(-1, substr[1]);
			page3combopcscSha1List2.InsertString(-1, substr[1]);
			page3combopcscSha1List3.InsertString(-1, substr[1]);
			page3combopcscSha1List4.InsertString(-1, substr[1]);
			page3combopcscSha1List5.InsertString(-1, substr[1]);
		}
		nSel++;
	}
	file.Close();
}
void page3downloadDlg::OnCbnSelchangepage3combosha1list1()
{
	CString strSha1;
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = page3combopcscSha1List1.GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	if(Getpage3Sha1DataWithSel(&strSha1, nSel))
		page3edtpcscSHA1_1.SetWindowText(strSha1);
}
void page3downloadDlg::OnCbnSelchangepage3combosha1list2()
{
	CString strSha1;
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = page3combopcscSha1List2.GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	if (Getpage3Sha1DataWithSel(&strSha1, nSel))
		page3edtpcscSHA1_2.SetWindowText(strSha1);
}
void page3downloadDlg::OnCbnSelchangepage3combosha1list3()
{
	CString strSha1;
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = page3combopcscSha1List3.GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	if (Getpage3Sha1DataWithSel(&strSha1, nSel))
		page3edtpcscSHA1_3.SetWindowText(strSha1);
}

void page3downloadDlg::OnCbnSelchangepage3combosha1list4()
{
	CString strSha1;
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = page3combopcscSha1List4.GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	if (Getpage3Sha1DataWithSel(&strSha1, nSel))
		page3edtpcscSHA1_4.SetWindowText(strSha1);
}
void page3downloadDlg::OnCbnSelchangepage3combosha1list5()
{
	CString strSha1;
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = page3combopcscSha1List5.GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	if (Getpage3Sha1DataWithSel(&strSha1, nSel))
		page3edtpcscSHA1_5.SetWindowText(strSha1);
}


//GetPathName	����ѡ���ļ�������·��
//GetFileName	����ѡ���ļ����ļ���
//GetFileExt	����ѡ���ļ�����չ�ļ���
//GetFileTitle	����ѡ���ļ��ı���
//GetNextPathName	������һ��ѡ���ļ�������·��



void page3downloadDlg::OnBnClickedpage3btnopenfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_fName, FileTitle;
	CString Filter;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//char Filter[] = " �����ļ�(*.*)|*.*|| ";// char Filter[]="ͼ�ļ�(*.png)|*.png|ͼ�ļ�(*.jpg)|*.jpg||";
	//Get Card Type

	if ((pDlg->gAtrCosType != _T("MT1_Boot"))
		&& (pDlg->gAtrCosType != _T("MT2_Boot")))
	{
		MessageBox(_T("��⣺�˿�Ƭ��������COS��"));
		return;
	}

	if (pDlg->gAtrCosType == _T("MT1_Boot"))
		Filter = _T("MT1 COS�ű��ļ�(*.mt1)|*.mt1||");
	else //if (0 == lstrcmp(pDlg->gAtrCosType, _T("MT2_Boot")))
		Filter = _T("MT2 COS�ű��ļ�(*.mt2)|*.mt2||");

	CFileDialog dlgOpen(TRUE, 0, 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, (LPCTSTR)Filter, NULL);
	if (dlgOpen.DoModal() == IDOK)
	{
		m_fName = dlgOpen.GetPathName();//·������
		//FileTitle = dlgOpen.GetFileName(); 
		FileTitle = dlgOpen.GetFileTitle();// ȡ��Ҫ�ָ���ļ�����������·������չ����
	}
	else
		return;
	//MessageBox(m_fName);
	//MessageBox(FileTitle);	
	page3edtpcscCosFile.SetWindowText(m_fName);
	//if ((FileTitle.Find(_T("JOS")) != std::string::npos)
	//	|| (FileTitle.Find(_T("jos")) != std::string::npos)
	//	|| (FileTitle.Find(_T("JCOS")) != std::string::npos)
	//	|| (FileTitle.Find(_T("jcos")) != std::string::npos)
	//	)//Java Card��COS�ű�
	//{
	//	setSHA1Disp(false,true);
	//}
	//else
	//{
	//	setSHA1Disp(true,true);
	//}
	setAppDisp();
}

/*
* ��ȡ�ļ�����
* @param road �ļ�·��
*/

int getFileLine(CString road)
{
	CStdioFile myFile;
	CFileException fileException;

	if (myFile.Open(road, CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText | CFile::modeReadWrite), &fileException)
	{
		CString strContent;
		int order = 0;
		while (myFile.ReadString(strContent))
		{
			order++;
		}

		myFile.Close();
		return order;
	}
	else
	{
		myFile.Close();
		return 0;
	}
}



boolean page3downloadDlg::DownloadAndWriteInfo()
{
	CStdioFile file;
	CString str = " ";
	CString sAPDU, sSW;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString filePath, openInfo;
	boolean is1stStringFlag = true;
	int fileLines, index = 0;
	CString sStatus;
	byte writeFlag = 0;
	CString thisStr;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	UpdateData(TRUE);//�Ӵ��ڱ༭���ж�������

	page3edtpcscCosFile.GetWindowText(filePath);
	if (filePath == _T(""))
	{
		MessageBox(_T("δѡ��COS�ļ�����ѡ��COS�ļ���"));
		return false;
	}
	int filePathLen = filePath.GetLength();
	if (filePathLen < 5)
	{
		MessageBox(_T("δѡ��COS�ļ�����ѡ��COS�ļ���"));
		return false;
	}
	CString strResult = filePath.Right(4);
	if (pDlg->gAtrCosType == _T("MT1_Boot"))
	{
		if (strResult != _T(".mt1"))
		{
			MessageBox(_T("��ѡ����ȷ��������MT1����COS�ļ���"));
			return false;
		}
	}
	else if (pDlg->gAtrCosType == _T("MT2_Boot"))
	{
		if (strResult != _T(".mt2"))
		{
			MessageBox(_T("��ѡ����ȷ��������MT2����COS�ļ���"));
			return false;
		}
	}

	fileLines = getFileLine(filePath);
	if (fileLines == 0)
	{
		MessageBox(_T("�򿪽ű��ļ�ʧ�ܣ����飡"));
		return false;
	}

	if (!file.Open(filePath, CFile::modeRead)) {
		//MessageBox(_T("�򿪽ű��ļ�ʧ��"), _T("��ʾ"),  MB_ICONWARNING);//���ļ�
		openInfo = _T("�򿪽ű��ļ�ʧ�ܣ����飡");
		MessageBox(openInfo);
		return false;
	}

	//////////////////////////////////////
	if ((((CButton*)GetDlgItem(checkCardType))->GetCheck() == 1)
		&&(pDlg->gAtrCosType == _T("MT2_Boot"))
		)
	{		
		if((radioFlag != _T("MT211"))
			&& (radioFlag != _T("MT222A"))
			&& (radioFlag != _T("MT222C"))
			)
		{
			MessageBox(_T("��ѡ�����ͣ�"));
			return false;
		}
		writeFlag |= 1 << 0;
		if (radioFlag != _T("MT211"))
		{
			//��ҪдMAC����ȡMAC��ַ
			if ((((CButton*)GetDlgItem(checkMAC))->GetCheck() == 1)
				&&( 5 != page3edtpcscBLE.GetWindowTextLength())
				)
			{
				MessageBox(_T("BLE��MAC��ַ���Ȳ���ȷ��\r\n������MAC��ַ�ĵ�5λ��"));
				return false;
			}
			writeFlag |= 1 << 1;
		}
	}

	//��ҪдSN
	if (((CButton*)GetDlgItem(checkSN))->GetCheck() == 1)
	{
		if (16 != page3edtpcscSn.GetWindowTextLength())
		{
			MessageBox(_T("SN���Ȳ���ȷ��\r\n������16Ϊ���ֵ�SN��"));
			return false;
		}
		writeFlag |= 1 << 2;
	}

	if ((((CButton*)GetDlgItem(checkSha1))->GetCheck() == 1)
		&&(-1 != filePath.Find(_T("SmartCOS")))
		)
	{
		//��ҪдSHA1
		if (40 != page3edtpcscSHA1_1.GetWindowTextLength())
		{
			MessageBox(_T("��1��SHA1���Ȳ���ȷ��\r\n������20�ֽڵ�SHA1ֵ��"));
			return false;
		}
		if (40 != page3edtpcscSHA1_2.GetWindowTextLength())
		{
			MessageBox(_T("��2��SHA1���Ȳ���ȷ��\r\n������20�ֽڵ�SHA1ֵ��"));
			return false;
		}
		if (40 != page3edtpcscSHA1_3.GetWindowTextLength())
		{
			MessageBox(_T("��3��SHA1���Ȳ���ȷ��\r\n������20�ֽڵ�SHA1ֵ��"));
			return false;
		}
		if (40 != page3edtpcscSHA1_4.GetWindowTextLength())
		{
			MessageBox(_T("��4��SHA1���Ȳ���ȷ��\r\n������20�ֽڵ�SHA1ֵ��"));
			return false;
		}
		if (40 != page3edtpcscSHA1_5.GetWindowTextLength())
		{
			MessageBox(_T("��5��SHA1���Ȳ���ȷ��\r\n������20�ֽڵ�SHA1ֵ��"));
			return false;
		}
		writeFlag |= 1 << 3;
	}

	if (((CButton*)GetDlgItem(checkSHouse))->GetCheck() == 1)
		writeFlag |= 1 << 4;
	if (((CButton*)GetDlgItem(checkWeLink))->GetCheck() == 1)
		writeFlag |= 1 << 5;
	//////////////////////////////////////

	UpdateData(TRUE);
	page3pcscprocess1.SetRange32(0, fileLines);//�趨�������ؼ��ķ�Χ�����޺�����
	if(fileLines>100)
		page3pcscprocess1.SetPos(fileLines/100);
	else
		page3pcscprocess1.SetPos(1);

	sStatus.Format(_T("Loadding %d%%"), 1);
	page3edtpcscStatus.SetWindowText(sStatus);
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);
	UpdateWindow();

	//���ж�ȡ�ַ���
	while (file.ReadString(str))
	{
		if (pDlg->gAtrCosType == _T("MT2_Boot"))
		{
			if (is1stStringFlag)
			{
				is1stStringFlag = false;
				if (str.Mid(0, 6) != _T("[apdu]"))
				{
					MessageBox(_T("MT2�ű��ļ�����ȷ"));
					return false;
				}
				else
				{
					//MessageBox(_T("MT2�ű��ļ���ȷ"));
				}
			}
			else
			{
				if (str.Mid(0, 12) == _T("Reset_Card()"))
				{
					//MessageBox(_T("��λ��Ƭ"));
				}
				else if (str.Mid(0, 5) == _T("apdu="))
				{
					//����APDU
					str.Remove(_T(' '));//ɾ���ո�����еĻ���
					sAPDU = str.Mid(5, str.Find(_T(",")) - 5);//��ȡ��APDU����
					APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
					RespLen = 256 + 2;
					::memset(Resp, 0, RespLen);
					if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
					{
						page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
						page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
						MessageBox(pDlg->Reader.GetError());
						return false;
					}
					sSW = str.Mid(str.Find(_T(",0x")) + 3, 4);//��ȡ��SW����
					//MessageBox(sSW);
					if (pDlg->Reader.HexToStr(Resp, 2) != sSW)
					{
						page3edtpcscStatus.SetWindowText(_T("���ع�����ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
						page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
						MessageBox(_T("���ع�����ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
						return false;
					}
				}
				else
				{
					//�ո�ȣ��Թ�
					//MessageBox(_T("�ո�ȣ��Թ�"));
				}
			}
		}
		else if (pDlg->gAtrCosType == _T("MT1_Boot"))
		{
			if (is1stStringFlag)
			{
				is1stStringFlag = false;
				if (str.Mid(0, 6) != _T("#THD86"))
				{
				MessageBox(_T("MT1�ű��ļ�����ȷ"));
				return false;
				}
				else
				{
				//MessageBox(_T("MT1�ű��ļ���ȷ"));
				}
			}
			else
			{
			if (str.Mid(0, 5) == _T("f 00F"))
			{
				//����APDU
				str.Remove(_T(' '));//ɾ���ո�����еĻ���
				sAPDU = str.Mid(1, str.GetLength());//��ȡ��APDU����
				APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
				RespLen = 256 + 2;
				::memset(Resp, 0, RespLen);
				if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
				{
					page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
					page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					MessageBox(pDlg->Reader.GetError());
					return false;
				}
				if (pDlg->Reader.HexToStr(Resp, 2) != _T("9000"))
				{
					page3edtpcscStatus.SetWindowText(_T("���ع�����ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					MessageBox(_T("���ع�����ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					return false;
				}
			}
			else
			{
				//MessageBox(_T("MT1�ű��ļ���ȷ"));
			}
			}
		}
		if (index > (fileLines / 100))
		{
			UpdateData(TRUE);
			if ((index + fileLines / 100) < fileLines)
				page3pcscprocess1.SetPos(index + fileLines / 100);
			else
				page3pcscprocess1.SetPos(fileLines - 2);
			//������ô������Ϊ�˽�������ʾ��һ���������⴦�������й��ϴ��һ��
			sStatus.Format(_T("Loadding %d%%"), (index * 100 / fileLines));
			page3edtpcscStatus.SetWindowText(sStatus);
			page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

			UpdateData(FALSE);
			UpdateWindow();
		}
		index++;

		//MFC ѭ����������Ľ���취
		//1. ���߳̽����
		// �ɷ���Ϣ
		MSG msg;
		if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
		//�����������:�ѿ�ʼ��ť�е���Щѭ�����ֵ���д��һ�����߳�, �ڰ�ť�Ĵ������в������߳�, ���߳̾Ͳ�����Ϊѭ����������Ϣ��.
		//�μ���https://blog.csdn.net/weixin_34107739/article/details/85560124?utm_medium=distribute.pc_relevant_download.none-task-blog-baidujs-2.nonecase&depth_1-utm_source=distribute.pc_relevant_download.none-task-blog-baidujs-2.nonecase

	}

	UpdateData(TRUE);
	page3pcscprocess1.SetPos(fileLines);
	sStatus.Format(_T("Congratulations, 100%% loaded."));
	page3edtpcscStatus.SetWindowText(sStatus);
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);
	UpdateWindow();

	/////////////////////////////////////////////////////////////////
	if (0 != writeFlag)
	{
		CString bleMac, sppMac, macStr, javaMacStr,snStr, sha1Str1, sha1Str2, sha1Str3, sha1Str4, sha1Str5, sha1_5Str;
		byte macData[12];
		CString cardTypeStr;

		CString sAPDU, sAPDU2;
		byte APDU[5 + 256];
		byte Resp[256 + 2];
		byte readMacFlag = 0;
		DWORD APDULen = 0;
		DWORD RespLen = 256 + 2;


		if (radioFlag == _T("MT211"))
			cardTypeStr = _T("4D5400323131");
		else if (radioFlag == _T("MT222A"))
			cardTypeStr = _T("4D5432323241");
		else if (radioFlag == _T("MT222C"))
			cardTypeStr = _T("4D5432323243");

		//��Ƭ��λ
		pDlg->reConnectForContinue();

		if (writeFlag & (1 << 1))
		{
			page3edtpcscBLE.GetWindowText(bleMac);
			bleMac = _T("D05F647") + bleMac;
			pDlg->Reader.StrToHex(bleMac, macData);
			macData[3] += 0x08;
			pDlg->Reader.StrToHex(bleMac, macData + 6);
			javaMacStr.Format(_T("%s"), pDlg->Reader.HexToStr(macData, 12));
			byte tempData;
			for(int j = 0; j < 3; j++)
			{
				tempData = macData[j];
				macData[j] = macData[5-j];
				macData[5-j] = tempData;

				tempData = macData[6+j];
				macData[6+j] = macData[6+5 - j];
				macData[6+5 - j] = tempData;
			}
			macStr.Format(_T("%s"), pDlg->Reader.HexToStr(macData, 12));
		}
		if (writeFlag & (1 << 2))
		{
			page3edtpcscSn.GetWindowText(snStr);
		}
		if (writeFlag & (1 << 3))
		{
			page3edtpcscSHA1_1.GetWindowText(sha1Str1);
			page3edtpcscSHA1_2.GetWindowText(sha1Str2);
			page3edtpcscSHA1_3.GetWindowText(sha1Str3);
			page3edtpcscSHA1_4.GetWindowText(sha1Str4);
			page3edtpcscSHA1_5.GetWindowText(sha1Str5);
			sha1_5Str = sha1Str1 + sha1Str2 + sha1Str3 + sha1Str4 + sha1Str5;
		}
		if ((pDlg->gAtrCosType == _T("MT2_COS"))|| (pDlg->gAtrCosType == _T("MT2_Wlt")))
		{
			//дtype��MAC��дSN��SHA1
			//дSN��MAC��SHA1
			if ((writeFlag & ((1 << 1)| (1 << 2)| (1 << 3))) == ((1 << 1) | (1 << 2) | (1 << 3)))
			{
				sAPDU.Format(_T("%s %s %s %s"), _T("9881000078"), snStr, macStr, sha1_5Str);
				APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
				RespLen = 256 + 2;
				::memset(Resp, 0, RespLen);
				if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
				{
					page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
					page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					MessageBox(pDlg->Reader.GetError());
					return false;
				}
				if (Resp[0] != 0x90)
				{
					MessageBox(_T("SetCardInfoִ��д��SNʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					return false;
				}
			}
			else
			{
				//дMAC
				if (writeFlag & (1 << 1))
				{
					sAPDU.Format(_T("%s %s"), _T("988102000C"), macStr);
					APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
					RespLen = 256 + 2;
					::memset(Resp, 0, RespLen);
					if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
					{
						page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
						page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
						MessageBox(pDlg->Reader.GetError());
						return false;
					}
					if (Resp[0] != 0x90)
					{
						MessageBox(_T("SetCardInfoִ��д��MACʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
						return false;
					}
				}
				//дSN
				if (writeFlag & (1 << 2))
				{					
					sAPDU.Format(_T("%s %s"), _T("9881010008"), snStr);
					APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
					RespLen = 256 + 2;
					::memset(Resp, 0, RespLen);
					if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
					{
						page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
						page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
						MessageBox(pDlg->Reader.GetError());
						return false;
					}
					if (Resp[0] != 0x90)
					{
						MessageBox(_T("SetCardInfoִ��д��SNʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
						return false;
					}
				}
				//SHA1
				if (writeFlag & (1 << 3))
				{
					sAPDU.Format(_T("%s %s"), _T("9881030064"), sha1_5Str);
					APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
					RespLen = 256 + 2;
					::memset(Resp, 0, RespLen);
					if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
					{
						page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
						page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
						MessageBox(pDlg->Reader.GetError());
						return false;
					}
					if (Resp[0] != 0x90)
					{
						MessageBox(_T("SetCardInfoִ��д��Sha1ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
						return false;
					}
				}
			}
			//type
			if (writeFlag & (1 << 0))
			{
				sAPDU.Format(_T("%s %s"), _T("98814D0006"), cardTypeStr);
				APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
				RespLen = 256 + 2;
				::memset(Resp, 0, RespLen);
				if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
				{
					page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
					page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					MessageBox(pDlg->Reader.GetError());
					return false;
				}
				if (Resp[0] != 0x90)
				{
					MessageBox(_T("SetCardInfoִ��д�뿨����ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					return false;
				}
			}
		}
		else if (pDlg->gAtrCosType == _T("MT1_COS"))
		{
			//дSN
			if (writeFlag & (1 << 2))
			{
				sAPDU.Format(_T("%s %s"), _T("9881010008"), snStr);
				APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
				RespLen = 256 + 2;
				::memset(Resp, 0, RespLen);
				if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
				{
					page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
					page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					MessageBox(pDlg->Reader.GetError());
					return false;
				}
				if (Resp[0] != 0x90)
				{
					MessageBox(_T("SetCardInfoִ��д��SNʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					return false;
				}
			}
			//SHA1
			if (writeFlag & (1 << 3))
			{
				sAPDU.Format(_T("%s %s"), _T("9881030064"), sha1_5Str);
				APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
				RespLen = 256 + 2;
				::memset(Resp, 0, RespLen);
				if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
				{
					page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
					page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					MessageBox(pDlg->Reader.GetError());
					return false;
				}
				if (Resp[0] != 0x90)
				{
					MessageBox(_T("SetCardInfoִ��д��Sha1ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					return false;
				}
			}
		}
		else if (pDlg->gAtrCosType == _T("CS.JCOS"))
		{
			//дtype��MAC��SN
			//дMAC
			if (writeFlag & (1 << 1))
			{//SPP_MAC+BLE_MAC
				sAPDU.Format(_T("%s %s"), _T("180101040C"), javaMacStr);

				APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
				RespLen = 256 + 2;
				::memset(Resp, 0, RespLen);
				if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
				{
					page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
					page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					MessageBox(pDlg->Reader.GetError());
					return false;
				}
				if (Resp[0] != 0x90)
				{
					MessageBox(_T("SetCardInfoִ��д��MACʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					return false;
				}
			}
			//дSN
			if (writeFlag & (1 << 2))
			{
				sAPDU.Format(_T("%s %s"), _T("1801010108"), snStr);
				APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
				RespLen = 256 + 2;
				::memset(Resp, 0, RespLen);
				if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
				{
					page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
					page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					MessageBox(pDlg->Reader.GetError());
					return false;
				}
				if (Resp[0] != 0x90)
				{
					MessageBox(_T("SetCardInfoִ��д��SNʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					return false;
				}
			}
			//type
			if (writeFlag & (1 << 0))
			{
				sAPDU.Format(_T("%s %s"), _T("1801010004"), cardTypeStr.Right(8));
				APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
				RespLen = 256 + 2;
				::memset(Resp, 0, RespLen);
				if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
				{
					page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
					page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					MessageBox(pDlg->Reader.GetError());
					return false;
				}
				if (Resp[0] != 0x90)
				{
					MessageBox(_T("SetCardInfoִ��д�뿨����ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					return false;
				}

			}
			page3edtpcscStatus.SetWindowText(_T("��ϲ���� SetCardInfoִ�гɹ���"));
			page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		if ((writeFlag & (1 << 4))//checkSHouse
			|| (writeFlag & (1 << 5)))//WeLink
		{
			CString authKey = _T("4D462D45544B4D462D45544B4D462D45");//MF���ⲿ��֤��Կ	

			//���ȱ��봴��MF
			if (!processScript(_T("Init MF")))
			{
				page3edtpcscStatus.SetWindowText(_T("Init MF ʧ��"));
				page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				return false;
			}

			//�����Ҫ��ʼ��ţ�ܰ�ȫ��
			if (writeFlag & (1 << 4))//SHouse
			{
				//MT2
				//�����жϿ�Ƭ��û��ִ�й����˻�����Native+��MF�Ƿ���ڣ�
				//�����Ƭ�Ѿ�ִ�й����˻�������Native+��MF���ڣ�����������Ҫͨ��MF���ⲿ��֤���ɼ���ִ��
				if (checkMF())
				{
					//��Ҫִ�У��ⲿ��֤
					//�����ⲿ��֤��Կ
					if (!ExAuth(authKey))
					{
						MessageBox(_T("�ⲿ��֤ʧ�ܣ�\r\n�޷�д�뿨Ƭ��Ϣ��"));
						page3edtpcscStatus.SetWindowText(_T("�ⲿ��֤ʧ�ܣ��޷�д�뿨Ƭ��Ϣ��"));
						return false;
					}
				}

				//��ȫ��
				if (!processScript(_T("Init Security House")))
				{
					MessageBox(_T("�ⲿ��֤ʧ�ܣ�\r\n�޷�д�뿨Ƭ��Ϣ��"));
					page3edtpcscStatus.SetWindowText(_T("Init Security Houseʧ��"));
					return false;
				}
			}

			//�����Ҫ��ʼ����ΪWeLink
			if (writeFlag & (1 << 5))//WeLink
			{
				//MT2
				//�����жϿ�Ƭ��û��ִ�й����˻�����Native+��MF�Ƿ���ڣ�
				//�����Ƭ�Ѿ�ִ�й����˻�������Native+��MF���ڣ�����������Ҫͨ��MF���ⲿ��֤���ɼ���ִ��
				if (checkMF())
				{
					//��Ҫִ�У��ⲿ��֤
					//�����ⲿ��֤��Կ
					if (!ExAuth(authKey))
					{
						MessageBox(_T("�ⲿ��֤ʧ�ܣ�\r\n�޷�д�뿨Ƭ��Ϣ��"));
						page3edtpcscStatus.SetWindowText(_T("�ⲿ��֤ʧ�ܣ��޷�д�뿨Ƭ��Ϣ��"));
						return false;
					}
				}
				//Welink
				if (!processScript(_T("Init WeLink")))
				{
					MessageBox(_T("�ⲿ��֤ʧ�ܣ�\r\n�޷�д�뿨Ƭ��Ϣ��"));
					page3edtpcscStatus.SetWindowText(_T("Init WeLinkʧ��"));
					return false;
				}
			}
		}
	}
	MessageBox(_T("��ϲ������Ƭ���سɹ���"));
	return TRUE;
}

boolean page3downloadDlg::checkMF()
{
	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//�жϿ�Ƭ��û��ִ�й����˻�����Native+��MF�Ƿ���ڣ�
	sAPDU = "18A40000023F00";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return FALSE;
	}

	//�����Ƭ�Ѿ�ִ�й����˻�������Native+��MF���ڣ�����������Ҫͨ��MF���ⲿ��֤���ɼ���ִ��
	if ((Resp[0] == 0x61) || (Resp[0] == 0x90))
		return TRUE;
	else
		return FALSE;
}

boolean page3downloadDlg::ExAuth(CString authKey)
{
	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;
	unsigned char key[16] = { 0 };

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	pDlg->Reader.StrToHex(authKey, key);

	//��ȡ�����
	sAPDU = "1884000008";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return FALSE;
	}
	if (RespLen != 10)
	{
		MessageBox(_T("��ȡ�����ʧ�ܣ��˳�"));
		return FALSE;
	}
	Resp[8] = 0;

	//authKey ������֤����
	//SM4�㷨
	sm4_context ctx;
	CString outS;
	//encrypt standard testing vector
	sm4_setkey_enc(&ctx, key);
	sm4_crypt_ecb(&ctx, 1, 16, Resp, APDU + 5);
	//outS = pDlg->Reader.HexToStr(output, 16);

	//ִ���ⲿ��ָ֤��
	sAPDU = "1882000010";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU) + 16;
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return FALSE;
	}
	if (Resp[0] == 0x90)
		return TRUE;
	else
		return FALSE;
}
boolean page3downloadDlg::processScript(CString scriptFlag)
{
	CString sDispStatus = _T("");
	CString sDispFalg;

	CString sAPDU;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;

	CString sStatus;
	int apduNums, thisPos, percent;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	if (scriptFlag == _T("Init Security House"))
	{
		sDispFalg = _T("Init Security House");
		apduNums = sizeof(bAPDU_SecurityHouse) / sizeof(bAPDU_SecurityHouse[0]);
	}
	else if (scriptFlag == _T("Init WeLink"))
	{
		sDispFalg = _T("Init WeLink");
		apduNums = sizeof(bAPDU_WeLink) / sizeof(bAPDU_WeLink[0]);
	}
	else //if (scriptFlag == _T("Init MF"))
	{
		sDispFalg = _T("Init MF");
		apduNums = sizeof(bAPDU_MF) / sizeof(bAPDU_MF[0]);
	}


	UpdateData(TRUE);
	page3pcscprocess1.SetRange32(0, apduNums);//�趨�������ؼ��ķ�Χ�����޺�����
	thisPos = 0;
	page3pcscprocess1.SetPos(thisPos);
	percent = thisPos * 100 / apduNums;
	sStatus.Format(_T("%d%%"), percent);
	page3edtpcscStatus.SetWindowText(sStatus);
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);
	UpdateWindow();


	sDispStatus = sDispFalg;
	pDlg->lbpcscActiveReader.SetWindowText(sDispStatus);
	//MessageBox(sDispStatus);

	int count = 0;
	for (count = 0; count < apduNums; count++)
	{	//cosdata[count]���ŵ��ǵ���APDU
		if (scriptFlag == _T("Init MF"))
		{
			sAPDU.Format(_T("%s"), bAPDU_MF[count]);
		}
		else if (scriptFlag == _T("Init Security House"))
		{
			sAPDU.Format(_T("%s"), bAPDU_SecurityHouse[count]);
		}
		else if (scriptFlag == _T("Init WeLink"))
		{
			sAPDU.Format(_T("%s"), bAPDU_WeLink[count]);
		}
		else
		{
			MessageBox(_T("���ýű����������ڣ��˳����У�"));
			return false;
		}

		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			sDispStatus = _T("����APDUʧ�ܣ�\r\nSW=") + pDlg->Reader.GetError();
			pDlg->lbpcscActiveReader.SetWindowText(sDispStatus);
			return false;
		}
		if (((Resp[0] != 0x90) && (Resp[0] != 0x61)) || (RespLen != 2))
		{
			sDispStatus = _T("����APDUʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
			pDlg->lbpcscActiveReader.SetWindowText(sDispStatus);
			return false;
		}

		UpdateData(TRUE);
		thisPos = count + 1;
		page3pcscprocess1.SetPos(thisPos);
		percent = thisPos * 100 / apduNums;
		sStatus.Format(_T("%d%%"), percent);
		page3edtpcscStatus.SetWindowText(sStatus);
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		UpdateWindow();


		//MFC ѭ����������Ľ���취
		//1. ���߳̽����
		// �ɷ���Ϣ
		MSG msg;
		if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
		//�����������:�ѿ�ʼ��ť�е���Щѭ�����ֵ���д��һ�����߳�, �ڰ�ť�Ĵ������в������߳�, ���߳̾Ͳ�����Ϊѭ����������Ϣ��.
		//�μ���https://blog.csdn.net/weixin_34107739/article/details/85560124?utm_medium=distribute.pc_relevant_download.none-task-blog-baidujs-2.nonecase&depth_1-utm_source=distribute.pc_relevant_download.none-task-blog-baidujs-2.nonecase
	}
	sDispStatus = sDispFalg + _T("�ɹ���");
	pDlg->lbpcscActiveReader.SetWindowText(sDispStatus);
	return true;
}
LRESULT page3downloadDlg::OnMsg(WPARAM wp, LPARAM lp)
{
	page3pcscprocess1.SetPos((int)wp);
	return 1L;
}


////////////////////////////////////////////////////////////////////////////////

boolean page3downloadDlg::MakeSmartCos2Bootloader(CString authKey)
{//��SmartCOS���뵽BootLoader������MT1��MT2����������authKeyֵ��һ��
	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;
	CString sKey;
	unsigned char key[16] = { 0 };

	page3edtpcscStatus.SetWindowText(_T(""));
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	pDlg->Reader.StrToHex(authKey, key);

	//��ȡ�����
	sAPDU = "1884000010";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return FALSE;
	}
	if (RespLen != 18)
	{
		MessageBox(_T("��ȡ�����ʧ�ܣ��˳�"));
		page3edtpcscStatus.SetWindowText(_T("��ȡ�����ʧ�ܣ��˳�"));
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return FALSE;
	}
	Resp[16] = 0;

	//authKey ������֤����
	//SM4�㷨
	sm4_context ctx;
	CString outS;
	sm4_setkey_enc(&ctx, key);
	sm4_crypt_ecb(&ctx, 1, 16, Resp, APDU + 5);

	//ִ���ⲿ��ָ֤��
	sAPDU = "98D0000010";//������MF��SKF�û��ռ�
	//sAPDU = "98D0010110";//���Ҳ���MF��SKF�û��ռ�
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU) + 16;
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return FALSE;
	}
	if (Resp[0] != 0x90)
	{
		MessageBox(_T("Bootָ��ִ��ʧ�ܣ�"));
		page3edtpcscStatus.SetWindowText(_T("Bootָ��ִ��ʧ�ܣ�"));
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return FALSE;
	}
	MessageBox(_T("��Ƭ�Ѿ�����BootLoader������������COS��"));
	page3edtpcscStatus.SetWindowText(_T("��Ƭ�Ѿ�����BootLoader������������COS��"));
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	return TRUE;
}
boolean page3downloadDlg::MakeJCos2Bootloader()
{//��Java Card COS���뵽BootLoader
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	CString sAPDU, sAPDU2;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;

	page3edtpcscStatus.SetWindowText(_T(""));
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	sAPDU.Format(_T("%s"), _T("1840040100"));
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return false;
	}
	if (Resp[0] == 0x6D)
	{//����һ�¼��ܷ�ʽ��
		sAPDU.Format(_T("%s"), _T("1801030010"));
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		::memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return false;
		}
		if (RespLen != 18)
		{
			MessageBox(_T("Bootָ��ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page3edtpcscStatus.SetWindowText(_T("Bootָ��ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return false;
		}

		Resp[16] = 0;
		CString authKey = "43534D54324C65617665746F426F6F74";
		byte key[16];
		pDlg->Reader.StrToHex(authKey, key);

		sAPDU.Format(_T("%s"), _T("1801040010"));
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		//authKey ������֤����
		//SM4�㷨
		sm4_context ctx;
		CString outS;
		sm4_setkey_enc(&ctx, key);
		sm4_crypt_ecb(&ctx, 1, 16, Resp, APDU + 5);
		APDULen += 16;

		RespLen = 256 + 2;
		::memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return false;
		}
		if (Resp[0] != 0x90)
		{
			MessageBox(_T("Bootָ��ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page3edtpcscStatus.SetWindowText(_T("Bootָ��ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return false;
		}

	}
	else if (Resp[0] != 0x90)
	{
		MessageBox(_T("Bootָ��ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.SetWindowText(_T("Bootָ��ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return false;
	}
	MessageBox(_T("��Ƭ�Ѿ�����BootLoader������������COS��"));
	page3edtpcscStatus.SetWindowText(_T("��Ƭ�Ѿ�����BootLoader������������COS��"));
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	return true;
}
boolean page3downloadDlg::MakeZKCos2Bootloader()
{//���п���COS���뵽BootLoader
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;
	CString sKey;
	unsigned char thisKey[16] = { 0x83,0xC4,0x59,0x26,0xA7,0xF6,0xDF,0x1B,0x85,0x2D,0x90,0xAE,0x1E,0xBC,0x47,0x03};
	unsigned char uidPadData[16] = { 0,0,0,0,0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0,0,0,0 };
	unsigned char outData[16];
	//��ȡuid��4�ֽڣ�
	sAPDU.Format(_T("%s"), _T("FEFE010104"));
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return false;
	}
	if ((RespLen != 6) || (Resp[4] != 0x90))
	{
		MessageBox(_T("Bootָ���һ��ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.SetWindowText(_T("Bootָ���һ��ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return false;
	}
	//uid�����Respǰ4�ֽ�
	//uidPadData = uid + 0x0011223344556677 + uid
	memcpy(uidPadData, Resp,4);
	memcpy(uidPadData+12, Resp, 4);
	//ʹ����Կ0x83C45926A7F6DF1B852D90AE1EBC4703����uidPadData
	desFunc.Encrypt(DES_2, thisKey, 16, uidPadData, outData);

	sAPDU.Format(_T("%s"), _T("FEFE020210") + pDlg->Reader.HexToStr(outData, 16));
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return false;
	}
	if ((RespLen != 2) || (Resp[0] != 0x90))
	{
		MessageBox(_T("Bootָ��ڶ���ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.SetWindowText(_T("Bootָ��ڶ���ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return false;
	}

	sAPDU.Format(_T("%s"), _T("FEFE000010") + pDlg->Reader.HexToStr(outData, 16));
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page3edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return false;
	}
	if ((RespLen != 2) || (Resp[0] != 0x90))
	{
		MessageBox(_T("Bootָ�������ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.SetWindowText(_T("Bootָ�������ִ��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return false;
	}

	page3edtpcscStatus.SetWindowText(_T("��Ƭ�Ѿ�����BootLoader������������COS��"));
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	return true;
}

void page3downloadDlg::OnBnClickedpage3btnboot()
{
	boolean retStatus=false;
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//Get Card Type
	if (pDlg->gAtrCosType == _T("CS.JCOS"))
	{
		pDlg->reConnect();

		retStatus = MakeJCos2Bootloader();
	}
	else if ((pDlg->gAtrCosType == _T("MT1_COS"))
		|| (pDlg->gAtrCosType == _T("MT1_SKF"))

		|| (pDlg->gAtrCosType == _T("MT2_COS"))
		|| (pDlg->gAtrCosType == _T("MT2_Wlt"))
		|| (pDlg->gAtrCosType == _T("MT222_Nat+"))
		|| (pDlg->gAtrCosType == _T("MT211_Nat+"))
		|| (pDlg->gAtrCosType == _T("SIM_Nat+"))
		|| (pDlg->gAtrCosType == _T("MT222_SKF"))
		|| (pDlg->gAtrCosType == _T("MT211SKF"))
		|| (pDlg->gAtrCosType == _T("SIM_SKF"))
		)
	{
		CString MT1_BOOT_AUTHKEY = _T("43534D54314C65617665746F426F6F74");
		CString MT2_BOOT_AUTHKEY = _T("43534D54324C65617665746F426F6F74");

		retStatus = MakeSmartCos2Bootloader((pDlg->gAtrCosType.Mid(0, 3) == _T("MT1"))? MT1_BOOT_AUTHKEY : MT2_BOOT_AUTHKEY);
	}
	else if (pDlg->gAtrCosType == _T("�п�COS"))
	{
		retStatus = MakeZKCos2Bootloader();
	}
	else if ((pDlg->gAtrCosType == _T("MT2_Boot"))
		|| (pDlg->gAtrCosType == _T("MT1_Boot")))
	{
		retStatus = DownloadAndWriteInfo();
	}
	else
	{
		MessageBox(_T("��ǰ��Ƭ�ǣ�") + pDlg->gAtrCosType + _T("����֧�ֱ�ҳ�������"));
		return;
	}
	if(retStatus)
	{
		pDlg->reConnect();
	}
}


void page3downloadDlg::OnBnClickedpage3radiomt222a()
{
	radioFlag = _T("MT222A");
	setTypeDisp(true, false);
}


void page3downloadDlg::OnBnClickedpage3radiomt222c()
{
	radioFlag = _T("MT222C");
	setTypeDisp(true, false);
}


void page3downloadDlg::OnBnClickedpage3radiomt211()
{
	radioFlag = _T("MT211");
	setTypeDisp(true, false);
}



void page3downloadDlg::CheckInputDataLength(int editIDC, DWORD maxLen)
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CEdit* pEdit = (CEdit*)GetDlgItem(editIDC);
	CString strContent;
	pEdit->GetWindowText(strContent);

	DWORD dwNum = 0;

	dwNum = strContent.GetLength();

	if (dwNum > maxLen)
	{
		SetDlgItemText(editIDC, strContent.Left(maxLen));
		pEdit->SetSel(strContent.GetLength(), strContent.GetLength());//������������λ�� ָ�����           
	}
	UpdateData(FALSE);
}

void page3downloadDlg::OnChangePage3edtble()
{
	CheckInputDataLength(page3edtBLE, 5);
}


void page3downloadDlg::OnChangePage3edtsn()
{
	CheckInputDataLength(page3edtSn, 16);
}


void page3downloadDlg::OnChangePage3edtsha11()
{
	CheckInputDataLength(page3edtSHA1_1, 40);
}


void page3downloadDlg::OnChangePage3edtsha12()
{
	CheckInputDataLength(page3edtSHA1_2, 40);
}


void page3downloadDlg::OnChangePage3edtsha13()
{
	CheckInputDataLength(page3edtSHA1_3, 40);
}


void page3downloadDlg::OnChangePage3edtsha14()
{
	CheckInputDataLength(page3edtSHA1_4, 40);
}


void page3downloadDlg::OnChangePage3edtsha15()
{
	CheckInputDataLength(page3edtSHA1_5, 40);
}
