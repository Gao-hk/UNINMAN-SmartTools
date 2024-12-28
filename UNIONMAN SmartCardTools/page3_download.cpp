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
	
	DDX_Control(pDX, page3edtStatus, page3edtpcscStatus);
	DDX_Control(pDX, page3edtCosFile, page3edtpcscCosFile);

	DDX_Control(pDX, page3btnOpenFile, page3btnpcscOpenFile);
	DDX_Control(pDX, page3btnBoot,page3btnpcscBoot);
	DDX_Control(pDX, page3process1,page3pcscprocess1);
}


#define WM_UPDATEDATA WM_USER + 1999 //�����¼�

BEGIN_MESSAGE_MAP(page3downloadDlg, CDialogEx)
	ON_MESSAGE(WM_UPDATEDATA, &page3downloadDlg::OnMsg)   //���¼���������

	ON_BN_CLICKED(page3btnOpenFile, &page3downloadDlg::OnBnClickedpage3btnopenfile)
	ON_BN_CLICKED(page3btnBoot, &page3downloadDlg::OnBnClickedpage3btnboot)
END_MESSAGE_MAP()




void page3downloadDlg::setCardDownloadDisp(boolean bootloadStatus, boolean enableDownlaodeorBootBtnFlag)
{
	page3btnpcscBoot.ShowWindow(enableDownlaodeorBootBtnFlag);
	page3btnpcscBoot.SetWindowText(bootloadStatus?_T("��ʼ����"): _T("�����Ƭ"));

	page3edtpcscCosFile.ShowWindow(bootloadStatus);
	page3btnpcscOpenFile.ShowWindow(bootloadStatus);
	page3btnpcscDownload.ShowWindow(bootloadStatus);
	page3pcscprocess1.ShowWindow(bootloadStatus);
}
void page3downloadDlg::getCardDownloadInfo()
{
	boolean dispSha1Flag = true;
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();	


	//Get Card Type
	if ( pDlg->gAtrCosType == _T("M25_Boot"))
	{
		setCardDownloadDisp(true, true);
	}
	else 
	{
		radioFlag = _T("");
		if ((pDlg->gAtrCosType == _T("boya_V2"))
			|| (pDlg->gAtrCosType == _T("boyaSIM"))
			|| (pDlg->gAtrCosType == _T("boyaLOD"))
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
}
void page3downloadDlg::initDownloadPage()
{
	getCardDownloadInfo();
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

	if ((pDlg->gAtrCosType != _T("M25_Boot")))
	{
		MessageBox(_T("��⣺�˿�Ƭ��������COS��"));
		return;
	}

	Filter = _T("COS�ű��ļ�(*.sfm25)|*.sfm25||");

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
	CString strResult = filePath.Right(6);
	if (pDlg->gAtrCosType == _T("M25_Boot"))
	{
		if (strResult != _T(".sfm25"))
		{
			MessageBox(_T("��ѡ����ȷ��������SFM25����COS�ļ���"));
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
		if (pDlg->gAtrCosType == _T("M25_Boot"))
		{
			if (is1stStringFlag)
			{
				is1stStringFlag = false;
				if (str.Mid(0, 6) != _T("[apdu]"))
				{
					MessageBox(_T("COS�ű��ļ�����ȷ"));
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
	sAPDU = "99D0000010";//������MF��SKF�û��ռ�
	//sAPDU = "99D0010110";//���Ҳ���MF��SKF�û��ռ�
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
	if ((pDlg->gAtrCosType == _T("boya_V2"))
		|| (pDlg->gAtrCosType == _T("boyaSIM"))
		|| (pDlg->gAtrCosType == _T("boyaLOD"))
		)
	{
		CString MT2_BOOT_AUTHKEY = _T("43534D54324C65617665746F426F6F74");

		retStatus = MakeSmartCos2Bootloader(MT2_BOOT_AUTHKEY);
	}
	else if ((pDlg->gAtrCosType == _T("M25_Boot")))
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


