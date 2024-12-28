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
#include<io.h>   //C语言头文件
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



// PAGE2_download 对话框

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


#define WM_UPDATEDATA WM_USER + 1999 //定义事件

BEGIN_MESSAGE_MAP(page3downloadDlg, CDialogEx)
	ON_MESSAGE(WM_UPDATEDATA, &page3downloadDlg::OnMsg)   //让事件关联程序

	ON_BN_CLICKED(page3btnOpenFile, &page3downloadDlg::OnBnClickedpage3btnopenfile)
	ON_BN_CLICKED(page3btnBoot, &page3downloadDlg::OnBnClickedpage3btnboot)
END_MESSAGE_MAP()




void page3downloadDlg::setCardDownloadDisp(boolean bootloadStatus, boolean enableDownlaodeorBootBtnFlag)
{
	page3btnpcscBoot.ShowWindow(enableDownlaodeorBootBtnFlag);
	page3btnpcscBoot.SetWindowText(bootloadStatus?_T("开始下载"): _T("清除卡片"));

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
		//else if ((pDlg->gAtrCosType == _T("未知卡片")) || (pDlg->gAtrCosType == _T("卡片已断开")) || (pDlg->gAtrCosType == _T("")))
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



//GetPathName	返回选定文件的完整路径
//GetFileName	返回选定文件的文件名
//GetFileExt	返回选定文件的扩展文件名
//GetFileTitle	返回选定文件的标题
//GetNextPathName	返回下一个选定文件的完整路径



void page3downloadDlg::OnBnClickedpage3btnopenfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_fName, FileTitle;
	CString Filter;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//char Filter[] = " 所有文件(*.*)|*.*|| ";// char Filter[]="图文件(*.png)|*.png|图文件(*.jpg)|*.jpg||";
	//Get Card Type

	if ((pDlg->gAtrCosType != _T("M25_Boot")))
	{
		MessageBox(_T("糟糕：此卡片不能下载COS！"));
		return;
	}

	Filter = _T("COS脚本文件(*.sfm25)|*.sfm25||");

	CFileDialog dlgOpen(TRUE, 0, 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, (LPCTSTR)Filter, NULL);
	if (dlgOpen.DoModal() == IDOK)
	{
		m_fName = dlgOpen.GetPathName();//路径名称
		//FileTitle = dlgOpen.GetFileName(); 
		FileTitle = dlgOpen.GetFileTitle();// 取得要分割的文件名（不包含路径、扩展名）
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
	//	)//Java Card的COS脚本
	//{
	//	setSHA1Disp(false,true);
	//}
	//else
	//{
	//	setSHA1Disp(true,true);
	//}
}

/*
* 获取文件行数
* @param road 文件路径
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

	UpdateData(TRUE);//从窗口编辑框中读入数据

	page3edtpcscCosFile.GetWindowText(filePath);
	if (filePath == _T(""))
	{
		MessageBox(_T("未选择COS文件，请选择COS文件！"));
		return false;
	}
	int filePathLen = filePath.GetLength();
	if (filePathLen < 5)
	{
		MessageBox(_T("未选择COS文件，请选择COS文件！"));
		return false;
	}
	CString strResult = filePath.Right(6);
	if (pDlg->gAtrCosType == _T("M25_Boot"))
	{
		if (strResult != _T(".sfm25"))
		{
			MessageBox(_T("请选择正确的适用于SFM25卡的COS文件！"));
			return false;
		}
	}

	fileLines = getFileLine(filePath);
	if (fileLines == 0)
	{
		MessageBox(_T("打开脚本文件失败，请检查！"));
		return false;
	}

	if (!file.Open(filePath, CFile::modeRead)) {
		//MessageBox(_T("打开脚本文件失败"), _T("提示"),  MB_ICONWARNING);//打开文件
		openInfo = _T("打开脚本文件失败，请检查！");
		MessageBox(openInfo);
		return false;
	}
	 
	//////////////////////////////////////

	UpdateData(TRUE);
	page3pcscprocess1.SetRange32(0, fileLines);//设定进度条控件的范围的下限和上限
	if(fileLines>100)
		page3pcscprocess1.SetPos(fileLines/100);
	else
		page3pcscprocess1.SetPos(1);

	sStatus.Format(_T("Loadding %d%%"), 1);
	page3edtpcscStatus.SetWindowText(sStatus);
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);
	UpdateWindow();

	//逐行读取字符串
	while (file.ReadString(str))
	{
		if (pDlg->gAtrCosType == _T("M25_Boot"))
		{
			if (is1stStringFlag)
			{
				is1stStringFlag = false;
				if (str.Mid(0, 6) != _T("[apdu]"))
				{
					MessageBox(_T("COS脚本文件不正确"));
					return false;
				}
				else
				{
					//MessageBox(_T("MT2脚本文件正确"));
				}
			}
			else
			{
				if (str.Mid(0, 12) == _T("Reset_Card()"))
				{
					//MessageBox(_T("复位卡片"));
				}
				else if (str.Mid(0, 5) == _T("apdu="))
				{
					//处理APDU
					str.Remove(_T(' '));//删除空格（如果有的话）
					sAPDU = str.Mid(5, str.Find(_T(",")) - 5);//截取到APDU数据
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
					sSW = str.Mid(str.Find(_T(",0x")) + 3, 4);//截取到SW数据
					//MessageBox(sSW);
					if (pDlg->Reader.HexToStr(Resp, 2) != sSW)
					{
						page3edtpcscStatus.SetWindowText(_T("下载过程中失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
						page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
						MessageBox(_T("下载过程中失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
						return false;
					}
				}
				else
				{
					//空格等，略过
					//MessageBox(_T("空格等，略过"));
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
			//上面这么处理是为了进度条显示不一致做的特殊处理，处理后感官上大概一致
			sStatus.Format(_T("Loadding %d%%"), (index * 100 / fileLines));
			page3edtpcscStatus.SetWindowText(sStatus);
			page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

			UpdateData(FALSE);
			UpdateWindow();
		}
		index++;

		//MFC 循环界面假死的解决办法
		//1. 单线程解决：
		// 派发消息
		MSG msg;
		if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
		//其他解决方法:把开始按钮中的那些循环部分单独写成一个子线程, 在按钮的处理函数中产生子线程, 主线程就不会因为循环而阻塞消息了.
		//参见：https://blog.csdn.net/weixin_34107739/article/details/85560124?utm_medium=distribute.pc_relevant_download.none-task-blog-baidujs-2.nonecase&depth_1-utm_source=distribute.pc_relevant_download.none-task-blog-baidujs-2.nonecase

	}

	UpdateData(TRUE);
	page3pcscprocess1.SetPos(fileLines);
	sStatus.Format(_T("Congratulations, 100%% loaded."));
	page3edtpcscStatus.SetWindowText(sStatus);
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);
	UpdateWindow();

	/////////////////////////////////////////////////////////////////
	
	MessageBox(_T("恭喜您！卡片下载成功！"));
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

	//判断卡片有没有执行过个人化（即Native+的MF是否存在）
	sAPDU = "18A40000023F00";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return FALSE;
	}

	//如果卡片已经执行过个人化处理（即Native+的MF存在），则须首先要通过MF的外部认证方可继续执行
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

	//获取随机数
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
		MessageBox(_T("获取随机数失败！退出"));
		return FALSE;
	}
	Resp[8] = 0;

	//authKey 计算认证数据
	//SM4算法
	sm4_context ctx;
	CString outS;
	//encrypt standard testing vector
	sm4_setkey_enc(&ctx, key);
	sm4_crypt_ecb(&ctx, 1, 16, Resp, APDU + 5);
	//outS = pDlg->Reader.HexToStr(output, 16);

	//执行外部认证指令
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
	page3pcscprocess1.SetRange32(0, apduNums);//设定进度条控件的范围的下限和上限
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
	{	//cosdata[count]里存放的是单条APDU
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
			MessageBox(_T("调用脚本参数不存在，退出运行！"));
			return false;
		}

		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			sDispStatus = _T("发送APDU失败！\r\nSW=") + pDlg->Reader.GetError();
			pDlg->lbpcscActiveReader.SetWindowText(sDispStatus);
			return false;
		}
		if (((Resp[0] != 0x90) && (Resp[0] != 0x61)) || (RespLen != 2))
		{
			sDispStatus = _T("发送APDU失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
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


		//MFC 循环界面假死的解决办法
		//1. 单线程解决：
		// 派发消息
		MSG msg;
		if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
		//其他解决方法:把开始按钮中的那些循环部分单独写成一个子线程, 在按钮的处理函数中产生子线程, 主线程就不会因为循环而阻塞消息了.
		//参见：https://blog.csdn.net/weixin_34107739/article/details/85560124?utm_medium=distribute.pc_relevant_download.none-task-blog-baidujs-2.nonecase&depth_1-utm_source=distribute.pc_relevant_download.none-task-blog-baidujs-2.nonecase
	}
	sDispStatus = sDispFalg + _T("成功！");
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
{//从SmartCOS进入到BootLoader，包括MT1和MT2卡，区别是authKey值不一样
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

	//获取随机数
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
		MessageBox(_T("获取随机数失败！退出"));
		page3edtpcscStatus.SetWindowText(_T("获取随机数失败！退出"));
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return FALSE;
	}
	Resp[16] = 0;

	//authKey 计算认证数据
	//SM4算法
	sm4_context ctx;
	CString outS;
	sm4_setkey_enc(&ctx, key);
	sm4_crypt_ecb(&ctx, 1, 16, Resp, APDU + 5);

	//执行外部认证指令
	sAPDU = "99D0000010";//不擦除MF及SKF用户空间
	//sAPDU = "99D0010110";//并且擦除MF及SKF用户空间
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
		MessageBox(_T("Boot指令执行失败！"));
		page3edtpcscStatus.SetWindowText(_T("Boot指令执行失败！"));
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return FALSE;
	}
	MessageBox(_T("卡片已经进入BootLoader，请重新下载COS！"));
	page3edtpcscStatus.SetWindowText(_T("卡片已经进入BootLoader，请重新下载COS！"));
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	return TRUE;
}
boolean page3downloadDlg::MakeJCos2Bootloader()
{//从Java Card COS进入到BootLoader
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
	{//再试一下加密方式的
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
			MessageBox(_T("Boot指令执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page3edtpcscStatus.SetWindowText(_T("Boot指令执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return false;
		}

		Resp[16] = 0;
		CString authKey = "43534D54324C65617665746F426F6F74";
		byte key[16];
		pDlg->Reader.StrToHex(authKey, key);

		sAPDU.Format(_T("%s"), _T("1801040010"));
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		//authKey 计算认证数据
		//SM4算法
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
			MessageBox(_T("Boot指令执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page3edtpcscStatus.SetWindowText(_T("Boot指令执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return false;
		}

	}
	else if (Resp[0] != 0x90)
	{
		MessageBox(_T("Boot指令执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.SetWindowText(_T("Boot指令执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return false;
	}
	MessageBox(_T("卡片已经进入BootLoader，请重新下载COS！"));
	page3edtpcscStatus.SetWindowText(_T("卡片已经进入BootLoader，请重新下载COS！"));
	page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	return true;
}
boolean page3downloadDlg::MakeZKCos2Bootloader()
{//从中卡的COS进入到BootLoader
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
	//读取uid（4字节）
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
		MessageBox(_T("Boot指令第一步执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.SetWindowText(_T("Boot指令第一步执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return false;
	}
	//uid存放在Resp前4字节
	//uidPadData = uid + 0x0011223344556677 + uid
	memcpy(uidPadData, Resp,4);
	memcpy(uidPadData+12, Resp, 4);
	//使用密钥0x83C45926A7F6DF1B852D90AE1EBC4703加密uidPadData
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
		MessageBox(_T("Boot指令第二步执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.SetWindowText(_T("Boot指令第二步执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
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
		MessageBox(_T("Boot指令第三步执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.SetWindowText(_T("Boot指令第三步执行失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page3edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return false;
	}

	page3edtpcscStatus.SetWindowText(_T("卡片已经进入BootLoader，请重新下载COS！"));
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
		MessageBox(_T("当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		return;
	}
	if(retStatus)
	{
		pDlg->reConnect();
	}
}


void page3downloadDlg::CheckInputDataLength(int editIDC, DWORD maxLen)
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CEdit* pEdit = (CEdit*)GetDlgItem(editIDC);
	CString strContent;
	pEdit->GetWindowText(strContent);

	DWORD dwNum = 0;

	dwNum = strContent.GetLength();

	if (dwNum > maxLen)
	{
		SetDlgItemText(editIDC, strContent.Left(maxLen));
		pEdit->SetSel(strContent.GetLength(), strContent.GetLength());//重设给光标设置位置 指向最后           
	}
	UpdateData(FALSE);
}


