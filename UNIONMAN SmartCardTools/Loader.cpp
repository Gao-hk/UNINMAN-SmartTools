// Loader.cpp: 实现文件
//

#include "stdafx.h"
//#include "pch.h"
#include "afxdialogex.h"
#include "CSmartToolDlg.h"

#include "afxwin.h"
#include "afxcmn.h"

#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include<io.h>   //C语言头文件
#include<iostream>   //for system();
#include <stdio.h>


#include "tchar.h"
#include   "ATLCONV.H"
//#include "Thread.h"
#include   "..\SM4\sm4.h"


// Loader 对话框

IMPLEMENT_DYNAMIC(Loader, CDialogEx)

Loader::Loader(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE_CardOTA, pParent)
{

}

Loader::~Loader()
{
}

void Loader::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, btnOpenFile_sfm25, btnpcscOpenFile_sfm25);
	DDX_Control(pDX, btnGenCipherSCT, btnpcscGenCipherSCT);
	DDX_Control(pDX, btnOpenFile_bysct, btnpcscOpenFile_bysct);
	DDX_Control(pDX, btnGetCosVer, btnpcscGetCosVer);
	DDX_Control(pDX, btnVersionRollback, btnpcscVersionRollback);
	DDX_Control(pDX, btnFirmwareUpdate, btnpcscFirmwareUpdate);

	DDX_Control(pDX, edtCosFile_sfm25, edtpcscCosFile_sfm25);
	DDX_Control(pDX, edtCosFile_bysct, edtpcscCosFile_bysct);
	DDX_Control(pDX, edtCardOTAStatus, edtpcscCardOTAStatus);

	DDX_Control(pDX, cardOTAprocess, pcsccardOTAprocess);
}


BEGIN_MESSAGE_MAP(Loader, CDialogEx)
	ON_BN_CLICKED(btnOpenFile_sfm25, &Loader::OnBnClickedsfm25)
	ON_BN_CLICKED(btnOpenFile_bysct, &Loader::OnBnClickedbysct)
	ON_BN_CLICKED(btnGenCipherSCT, &Loader::OnBnClickedbtngenciphersct)
	ON_BN_CLICKED(btnGetCosVer, &Loader::OnBnClickedbtngetcosver)
	ON_BN_CLICKED(btnVersionRollback, &Loader::OnBnClickedbtnversionrollback)
	ON_BN_CLICKED(btnFirmwareUpdate, &Loader::OnBnClickedbtnfirmwareupdate)
END_MESSAGE_MAP()


// Loader 消息处理程序


void Loader::OnBnClickedsfm25()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_fName, FileTitle;
	CString Filter;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

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

	edtpcscCosFile_sfm25.SetWindowText(m_fName);
}


void Loader::OnBnClickedbysct()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_fName, FileTitle;
	CString Filter;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	Filter = _T("固件密文脚本文件(*.bysct)|*.bysct||");

	CFileDialog dlgOpen(TRUE, 0, 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, (LPCTSTR)Filter, NULL);
	if (dlgOpen.DoModal() == IDOK)
	{
		m_fName = dlgOpen.GetPathName();//路径名称
		//FileTitle = dlgOpen.GetFileName(); 
		FileTitle = dlgOpen.GetFileTitle();// 取得要分割的文件名（不包含路径、扩展名）
	}
	else
		return;

	edtpcscCosFile_bysct.SetWindowText(m_fName);
}


/*
* 获取文件行数
* @param road 文件路径
*/

int getFileTotalLine(CString road)
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

CString gST1FirmwareFilePathNameStr;
#define write_boyaST1_APDU(...)	\
do	\
{	\
	FILE * fp = fopen(gST1FirmwareFilePathNameStr + "_APDU.bysct", "a+");	\
	if(fp)	\
	{	\
		fprintf(fp, __VA_ARGS__);	\
		fprintf(fp, "\n");	\
		fclose(fp);	\
	}	\
} while (0);

#define write_boyaST1_BIPAPDU(...)	\
do	\
{	\
	FILE * fp = fopen(gST1FirmwareFilePathNameStr + "_BIPAPDU.bysct", "a+");	\
	if(fp)	\
	{	\
		fprintf(fp, __VA_ARGS__);	\
		fprintf(fp, "\n");	\
		fclose(fp);	\
	}	\
} while (0);


#define write_boyaST1_Firmware(...)	\
do	\
{	\
	FILE * fp = fopen(gST1FirmwareFilePathNameStr + ".byhex", "a+");	\
	if(fp)	\
	{	\
		fprintf(fp, __VA_ARGS__);	\
		fprintf(fp, "\n");	\
		fclose(fp);	\
	}	\
} while (0);


#define clear_boyaST1_Files()	\
do	\
{	\
	FILE * fp1 = fopen(gST1FirmwareFilePathNameStr + "_APDU.bysct", "w");	\
	FILE * fp2 = fopen(gST1FirmwareFilePathNameStr + "_BIPAPDU.bysct", "w");	\
	FILE * fp3 = fopen(gST1FirmwareFilePathNameStr + ".byhex", "w");	\
		fclose(fp1);	\
		fclose(fp2);	\
		fclose(fp3);	\
} while (0);

unsigned char checkSum(unsigned char* pData, unsigned int dataLen)
{
	unsigned char checkSumData = 0;
	for (unsigned int i = 0; i < dataLen; i++)
	{
		checkSumData += pData[i];
	}

	checkSumData = 0xFF - checkSumData + 1;
	return checkSumData;
}
unsigned char LoaderAuthKey[] = "LoaderAuthKeySM4";
unsigned char gIndex = 0;
boolean Loader::Genfirmwarecipher()
{
	CStdioFile file;
	CString str = " ";
	CString sAPDU, sSW;
	byte APDU[5 + 256 + 128];
	byte BIPAPDU[6 + 512 + 128];
	byte Resp[256 + 2 + 128];
	unsigned short pageNo;
	boolean needWriteBIPAPDUdataLenInCheck = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString filePath, openInfo;
	boolean is1stStringFlag = true;
	int fileLines, index = 0;
	CString sStatus;
	byte writeFlag = 0;
	CString thisStr;
	CString strVer = "";
	int dataLen, leftLen;
	int addLen;
	byte P1, P2;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	UpdateData(TRUE);//从窗口编辑框中读入数据

	gST1FirmwareFilePathNameStr = "";
	edtpcscCosFile_sfm25.GetWindowText(filePath);
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

	if (filePath.Right(6) != _T(".sfm25"))
	{
		MessageBox(_T("请选择正确的适用于sfm25卡的COS文件！"));
		return false;
	}

	fileLines = getFileTotalLine(filePath);
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

	gST1FirmwareFilePathNameStr = filePath.Left(filePath.GetLength()-6);
	//////////////////////////////////////

	clear_boyaST1_Files();	//清空待生成密文Hex及脚本

	//////////////////////////////////////

	UpdateData(TRUE);
	pcsccardOTAprocess.SetRange32(0, fileLines);//设定进度条控件的范围的下限和上限
	if (fileLines > 100)
		pcsccardOTAprocess.SetPos(fileLines / 100);
	else
		pcsccardOTAprocess.SetPos(1);

	sStatus.Format(_T("Executing %d%%"), 1);
	edtpcscCardOTAStatus.SetWindowText(sStatus);
	edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);
	UpdateWindow();

	//逐行读取字符串
	while (file.ReadString(str))
	{
		if (is1stStringFlag)
		{
			is1stStringFlag = false;
			if (str.Mid(0, 6) != _T("[apdu]"))
			{
				MessageBox(_T("sfm25脚本文件不正确"));
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
			else if (str.Mid(0, 9) == _T("[Version:"))
			{
				strVer = str;
			}
			else if (str.Mid(0, 5) == _T("apdu="))
			{
				//处理APDU
				str.Remove(_T(' '));//删除空格（如果有的话）
				sAPDU = str.Mid(5, str.Find(_T(",")) - 5);//截取到APDU数据
				APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);

				//CLA=BX && INS=7X，下载固件数据APDU
				if (((APDU[0] & 0xF0) == 0xB0) && ((APDU[1] & 0xF0) == 0x70))
				{
					if (0x00E0 == APDU[2] * 256 + APDU[3])
					{ //写入存于地址A固件标志
						write_boyaST1_APDU("[AppA]" + strVer);
						write_boyaST1_APDU("apdu=800F00E000");
						gIndex = 0;
						write_boyaST1_BIPAPDU("[AppA]" + strVer);
						write_boyaST1_Firmware("[AppA]" + strVer);
					}
					else if (0x0400 == APDU[2] * 256 + APDU[3])
					{ //写入存于地址B固件标志
						write_boyaST1_APDU("[AppB]" + strVer);
						write_boyaST1_APDU("apdu=800F040000");
						gIndex = 0;
						write_boyaST1_BIPAPDU("[AppB]" + strVer);
						write_boyaST1_Firmware("[AppB]" + strVer);
					}

#define DATA_OFFSET 7
					//这里需要做的工作：
					// 1、将APDU中数据提取出来：CLA_L与INS_L组成最后一字节数据
					APDU[APDULen] = (APDU[0] & 0x0F) * 16 + (APDU[1] & 0x0F);
					P1 = APDU[2];
					P2 = APDU[3];
					dataLen = APDU[4] + 1;
					leftLen = dataLen % 16;
					if (leftLen)
					{
						addLen = 16 - leftLen;
						::memset(APDU + 5 + dataLen, 0xFF, addLen);
						dataLen += addLen;
						APDU[4] += addLen;
						APDULen += addLen;
					}

					// 2、加密数据
					// //SM4算法
					sm4_context ctx;
					CString outS;
					//encrypt standard testing vector
					sm4_setkey_enc(&ctx, LoaderAuthKey);
					sm4_crypt_ecb(&ctx, 1, dataLen, APDU + 5, Resp + DATA_OFFSET);	//密文放到Resp

					// 3.1、重新组成boya贴膜卡的Loader的APDU
					APDU[0] = 0x80;
#if 0
					//INS_L:lastdata_H
					APDU[1] = 0xF0 | ((Resp[DATA_OFFSET + dataLen - 1] >> 4) & 0x0F);
					//P1_H:lastdata_L
					APDU[2] = (P1 & 0x0F) | ((Resp[DATA_OFFSET + dataLen - 1] & 0x0F) * 16);
					APDU[3] = P2;
#else
					APDU[1] = 0x0F;
					APDU[2] = Resp[DATA_OFFSET + dataLen - 1];
					APDU[3] = gIndex;
					gIndex++;

#endif
					//APDU[4] = APDU[4];
					::memcpy(APDU + 5, Resp + DATA_OFFSET, dataLen - 1);

					write_boyaST1_APDU("apdu=" + pDlg->Reader.HexToStr(APDU, APDULen));

					BIPAPDU[0] = 0x80;
					BIPAPDU[1] = 0x0F;
					pageNo = ((P1 & 0x0F) * 256 + P2) / 2;
					BIPAPDU[2] = pageNo >> 8;
					BIPAPDU[3] = pageNo & 0xFF;

					if (0 == (P2 % 2))
					{//前半Page不用写
						BIPAPDU[4] = dataLen >> 8;
						BIPAPDU[5] = dataLen & 0xFF;
						::memcpy(BIPAPDU + 6, Resp + DATA_OFFSET, dataLen);
						needWriteBIPAPDUdataLenInCheck = dataLen;
					}
					else
					{//后半Page写入BIPAPDU
						BIPAPDU[4] += dataLen >> 8;
						BIPAPDU[5] += dataLen & 0xFF;
						::memcpy(BIPAPDU + 6 + 256, Resp + DATA_OFFSET, dataLen);

						write_boyaST1_BIPAPDU("apdu=" + pDlg->Reader.HexToStr(BIPAPDU, 6 + BIPAPDU[4] * 256 + BIPAPDU[5]));
						needWriteBIPAPDUdataLenInCheck = 0;
					}

					// 3.2、重新组成用于存放在服务器的固件升级包文件
					//数据格式：":" + dataLen(2Bytes) + startAddress(4Bytes) + "00" + data + checkSum(1Byte)						
					Resp[0] = dataLen / 0x100;
					Resp[1] = dataLen % 0x100;

					Resp[2] = 0x00;
					Resp[3] = P1;
					Resp[4] = P2;
					Resp[5] = 0x00;

					Resp[6] = 0x00;

					Resp[DATA_OFFSET + dataLen] = checkSum(Resp, DATA_OFFSET + dataLen);

					write_boyaST1_Firmware(":" + pDlg->Reader.HexToStr(Resp, DATA_OFFSET + dataLen + 1));
				}
				//CLA=BF && INS=42，校验数据
				else if ((APDU[0] == 0xBF) && (APDU[1] == 0x42))
				{
					//这里需要做的工作：
					// 1、重新组成boya贴膜卡的Loader的APDU
					APDU[0] = 0x80;
					APDU[1] = 0x0F;
					APDU[2] = 0xFF;
					APDU[3] = 0xFD;

					write_boyaST1_APDU("apdu=" + pDlg->Reader.HexToStr(APDU, APDULen) + "\n");

					if (needWriteBIPAPDUdataLenInCheck)
					{
						write_boyaST1_BIPAPDU("apdu=" + pDlg->Reader.HexToStr(BIPAPDU, 6 + needWriteBIPAPDUdataLenInCheck));
						needWriteBIPAPDUdataLenInCheck = 0;
					}
					BIPAPDU[0] = 0x80;
					BIPAPDU[1] = 0x0F;
					BIPAPDU[2] = 0xFF;
					BIPAPDU[3] = 0xFD;
					BIPAPDU[4] = 0x00;
					BIPAPDU[5] = 0x06;
					::memcpy(BIPAPDU + 6, APDU + 5, 6);

					write_boyaST1_BIPAPDU("apdu=" + pDlg->Reader.HexToStr(BIPAPDU, 6 + 6) + "\n");

					// 2、重新组成用于存放在服务器的固件升级包文件
					//数据格式：":" + dataLen(2Bytes) + startAddress(4Bytes) + "01" +checkSum(1Byte)
					write_boyaST1_Firmware(":00000000000001FF");	//结束

					write_boyaST1_Firmware("[CRC]");	//校验命令标志
					Resp[0] = 0x00;
					Resp[1] = 0x06;

					Resp[2] = 0x00;
					Resp[3] = 0x00;
					Resp[4] = 0x00;
					Resp[5] = 0x00;

					Resp[6] = 0x0C;

					memcpy(Resp + DATA_OFFSET, APDU + 5, 6);

					Resp[DATA_OFFSET + 6] = checkSum(Resp, DATA_OFFSET + 6);

					//数据格式：":" + dataLen(2Bytes) + startAddress(4Bytes) + "0C" +checkSum(1Byte)
					write_boyaST1_Firmware(":" + pDlg->Reader.HexToStr(Resp, DATA_OFFSET + 6 + 1)); //CRC
					write_boyaST1_Firmware(":00000000000001FF\n");	//结束
				}
			}
			else
			{
				//空格等，略过
				//MessageBox(_T("空格等，略过"));
			}
		}

		if (index > (fileLines / 100))
		{
			UpdateData(TRUE);
			if ((index + fileLines / 100) < fileLines)
				pcsccardOTAprocess.SetPos(index + fileLines / 100);
			else
				pcsccardOTAprocess.SetPos(fileLines - 2);
			//上面这么处理是为了进度条显示不一致做的特殊处理，处理后感官上大概一致
			sStatus.Format(_T("Executing %d%%"), (index * 100 / fileLines));
			edtpcscCardOTAStatus.SetWindowText(sStatus);
			edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
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
	pcsccardOTAprocess.SetPos(fileLines);
	sStatus.Format(_T("Congratulations! 100%% executed."));
	edtpcscCardOTAStatus.SetWindowText(sStatus);
	edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);
	UpdateWindow();

	/////////////////////////////////////////////////////////////////
	MessageBox(_T("恭喜您！\n\n用固件脚本生成固件密文Hex、固件密文脚本成功！"));
	return TRUE;
}
void Loader::OnBnClickedbtngenciphersct()
{
	// TODO: 在此添加控件通知处理程序代码
	Genfirmwarecipher();
}


void Loader::OnBnClickedbtngetcosver()
{	CStdioFile file;
	CString str = " ";
	CString sAPDU, sSW;
	byte APDU[5 + 256 + 128];
	byte Resp[256 + 2 + 128];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString filePath, openInfo;
	CString sStatus;
	byte writeFlag = 0;
	CString thisStr;

	byte cosFirmwareINFO[0x1E];

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	////////////////////
	//处理APDU
	sAPDU = "990FFFFF1E";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		UpdateData(TRUE);
		sStatus = pDlg->Reader.GetError();
		edtpcscCardOTAStatus.SetWindowText(sStatus);
		edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		MessageBox(sStatus);
		return;
	}
	if ((RespLen != 0x1E + 2)
		|| ("9000" != pDlg->Reader.HexToStr(Resp + 0x1E, 2)))
	{
		UpdateData(TRUE);
		sStatus = _T("获取固件信息命令 GetFirmwareInfo失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
		edtpcscCardOTAStatus.SetWindowText(sStatus);
		edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		MessageBox(sStatus);
		return;
	}

	memcpy(cosFirmwareINFO, Resp, 0x1E);
	char strCore[16] = { 0 };
	char strAppFlag[64] = { 0 };
	memcpy(strCore, cosFirmwareINFO, 8);
	memcpy(strAppFlag, cosFirmwareINFO + 10, 20);

	if (0 == memcmp(strAppFlag, "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 20))
	{
		memcpy(strAppFlag, "固件成功更新后未重启，请重启！", 30);
	}
	else
	{
		if (0 == memcmp(strAppFlag, "\xFF\xFF\xFF\xFF", 4))
		{
			memcpy(strAppFlag, "LoaderCOS", 9);
		}
		else
		{
			strAppFlag[4] = 0x00;//取前4字节即可
		}
	}



	thisStr = _T("获取固件信息成功！\n");
	thisStr = thisStr + _T("\n安全芯片型号：") + strCore;
	thisStr = thisStr + _T("\n当前固件版本：V") + pDlg->Reader.HexToStr(cosFirmwareINFO + 8, 1) + "." + pDlg->Reader.HexToStr(cosFirmwareINFO + 9, 1);
	thisStr = thisStr + _T("\n当前固件标志：") + strAppFlag;

	UpdateData(TRUE);
	sStatus = _T("获取固件信息成功:") + pDlg->Reader.HexToStr(cosFirmwareINFO, 14);
	edtpcscCardOTAStatus.SetWindowText(sStatus);
	edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);

	MessageBox(thisStr);
}


void Loader::OnBnClickedbtnversionrollback()
{
	// TODO: 在此添加控件通知处理程序代码
	CStdioFile file;
	CString str = " ";
	CString sAPDU, sSW;
	byte APDU[5 + 256 + 128];
	byte Resp[256 + 2 + 128];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString sStatus;
	CString thisStr;

	byte cosFirmwareINFO[0x1E];

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	////////////////////
	//处理APDU
	sAPDU = "990FFFFF1E";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		UpdateData(TRUE);
		sStatus = pDlg->Reader.GetError();
		edtpcscCardOTAStatus.SetWindowText(sStatus);
		edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		MessageBox(sStatus);
		return;
	}
	if ((RespLen != 0x1E + 2)
		|| ("9000" != pDlg->Reader.HexToStr(Resp + 0x1E, 2)))
	{
		UpdateData(TRUE);
		sStatus = _T("获取固件信息命令 GetFirmwareInfo失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
		edtpcscCardOTAStatus.SetWindowText(sStatus);
		edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		MessageBox(sStatus);
		return;
	}

	memcpy(cosFirmwareINFO, Resp, 0x1E);

	sAPDU = "990FFFFC10";
	pDlg->Reader.StrToHex(sAPDU, APDU);
	// 计算鉴权数据
	// //SM4算法
	sm4_context ctx;
	CString outS;
	//encrypt standard testing vector
	sm4_setkey_enc(&ctx, LoaderAuthKey);
	sm4_crypt_ecb(&ctx, 1, 16, cosFirmwareINFO + 0x0E, APDU + 5);
	APDULen = 0x15;
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		UpdateData(TRUE);
		sStatus = pDlg->Reader.GetError();
		edtpcscCardOTAStatus.SetWindowText(sStatus);
		edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		MessageBox(sStatus);
		return;
	}
	if ((RespLen != 2)
		|| ("9000" != pDlg->Reader.HexToStr(Resp, 2)))
	{
		UpdateData(TRUE);
		sStatus = _T("固件版本回退命令 VersionRollback 失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
		edtpcscCardOTAStatus.SetWindowText(sStatus);
		edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		MessageBox(sStatus);
		return;
	}

	UpdateData(TRUE);
	sStatus = _T("固件版本回退命令 VersionRollback 成功！设备重启后生效。");
	edtpcscCardOTAStatus.SetWindowText(sStatus);
	edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);

	MessageBox(_T("固件版本回退命令 VersionRollback 成功！\n\n设备重启后生效。"));
}


boolean Loader::Download_Firmwarecipher()
{
	CStdioFile file;
	CString str = " ";
	CString sAPDU, sSW;
	byte APDU[5 + 256 + 128];
	byte Resp[256 + 2 + 128];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString filePath, openInfo;
	boolean is1stStringFlag = true;
	int fileLines, index = 0;
	CString sStatus;
	byte writeFlag = 0;
	CString thisStr;

	byte cosFirmwareINFO[0x1E];

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	UpdateData(TRUE);//从窗口编辑框中读入数据

	edtpcscCosFile_bysct.GetWindowText(filePath);
	if (filePath == _T(""))
	{
		MessageBox(_T("未选择固件密文脚本文件，请选择固件密文脚本文件！"));
		return false;
	}
	int filePathLen = filePath.GetLength();
	if (filePathLen < 5)
	{
		MessageBox(_T("未选择固件密文脚本文件，请选择固件密文脚本文件！"));
		return false;
	}

	if (filePath.Right(6) != _T(".bysct"))
	{
		MessageBox(_T("请选择正确的适用于sfm25卡的固件密文脚本文件！"));
		return false;
	}

	fileLines = getFileTotalLine(filePath);
	if (fileLines == 0)
	{
		MessageBox(_T("打开固件密文脚本文件失败，请检查！"));
		return false;
	}

	fileLines /= 2; //分为A\B版，所以一分为二

	if (!file.Open(filePath, CFile::modeRead)) {
		//MessageBox(_T("打开脚本文件失败"), _T("提示"),  MB_ICONWARNING);//打开文件
		openInfo = _T("打开固件密文脚本文件失败，请检查！");
		MessageBox(openInfo);
		return false;
	}

	//////////////////////////////////////



	//////////////////////////////////////

	UpdateData(TRUE);
	pcsccardOTAprocess.SetRange32(0, fileLines);//设定进度条控件的范围的下限和上限
	if (fileLines > 100)
		pcsccardOTAprocess.SetPos(fileLines / 100);
	else
		pcsccardOTAprocess.SetPos(1);

	sStatus.Format(_T("Loadding %d%%"), 1);
	edtpcscCardOTAStatus.SetWindowText(sStatus);
	edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);
	UpdateWindow();
	////////////////////
	//首先进行鉴权处理
	//处理APDU
	sAPDU = "990FFFFF1E";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		UpdateData(TRUE);
		sStatus = pDlg->Reader.GetError();
		edtpcscCardOTAStatus.SetWindowText(sStatus);
		edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		MessageBox(sStatus);
		return false;
	}
	if ((RespLen != 0x1E + 2)
		|| ("9000" != pDlg->Reader.HexToStr(Resp + 0x1E, 2)))
	{
		UpdateData(TRUE);
		sStatus = _T("获取固件信息命令 GetFirmwareInfo失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
		edtpcscCardOTAStatus.SetWindowText(sStatus);
		edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		MessageBox(sStatus);
		return false;
	}

	memcpy(cosFirmwareINFO, Resp, 0x1E);

	if (0 == memcmp(cosFirmwareINFO + 10, "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 20))
	{
		UpdateData(TRUE);
		sStatus = _T("固件成功更新后未重启，请勿再次更新！\r\n\r\n如果一定要更新，请重启后再重试！");
		edtpcscCardOTAStatus.SetWindowText(sStatus);
		edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		MessageBox(sStatus);
		return false;
	}

	sAPDU = "990FFFFE10";
	pDlg->Reader.StrToHex(sAPDU, APDU);
	// 计算鉴权数据
	// //SM4算法
	sm4_context ctx;
	CString outS;
	//encrypt standard testing vector
	sm4_setkey_enc(&ctx, LoaderAuthKey);
	sm4_crypt_ecb(&ctx, 1, 16, cosFirmwareINFO + 0x0E, APDU + 5);
	APDULen = 0x15;
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		UpdateData(TRUE);
		sStatus = pDlg->Reader.GetError();
		edtpcscCardOTAStatus.SetWindowText(sStatus);
		edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		MessageBox(sStatus);
		return false;
	}
	if ((RespLen != 2)
		|| ("9000" != pDlg->Reader.HexToStr(Resp, 2)))
	{
		UpdateData(TRUE);
		sStatus = _T("鉴权命令 Authentication失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
		edtpcscCardOTAStatus.SetWindowText(sStatus);
		edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		UpdateData(FALSE);
		MessageBox(sStatus);
		return false;
	}

	//MessageBox(_T("鉴权命令 Authentication通过！"));

	///////////////////

	boolean runScriptFlag = false;
	//逐行读取字符串
	while (file.ReadString(str))
	{
		if (is1stStringFlag)
		{
			is1stStringFlag = false;
			if ((str.Mid(0, 6) != _T("[AppA]")) && (str.Mid(0, 6) != _T("[AppB]")))
			{
				UpdateData(TRUE);
				sStatus = _T("固件密文脚本文件不正确");
				edtpcscCardOTAStatus.SetWindowText(sStatus);
				edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				UpdateData(FALSE);
				MessageBox(sStatus);
				return false;
			}
			else
			{
				if ((str.Mid(0, 6) == _T("[AppA]")) && (0 != memcmp(cosFirmwareINFO + 0x0A, "AppA", 4)))
				{
					runScriptFlag = true;
				}
				else if ((str.Mid(0, 6) == _T("[AppB]")) && (0 == memcmp(cosFirmwareINFO + 0x0A, "AppA", 4)))
				{
					runScriptFlag = true;
				}
			}
		}
		else if (!runScriptFlag)
		{
			if ((str.Mid(0, 6) == _T("[AppA]")) && (0 != memcmp(cosFirmwareINFO + 0x0A, "AppA", 4)))
			{
				runScriptFlag = true;
			}
			else if ((str.Mid(0, 6) == _T("[AppB]")) && (0 == memcmp(cosFirmwareINFO + 0x0A, "AppA", 4)))
			{
				runScriptFlag = true;
			}
			else
			{
				continue;
			}
		}
		else
		{
			if ((str.Mid(0, 6) == _T("[AppA]")) || (str.Mid(0, 6) == _T("[AppB]")))
			{
				runScriptFlag = false;
			}
			else if (str.Mid(0, 5) == _T("apdu="))
			{
				//处理APDU
				str.Remove(_T(' '));//删除空格（如果有的话）
				sAPDU = str.Mid(5, str.GetLength() - 5);// str.Mid(5, str.Find(_T(",")) - 5);//截取到APDU数据
				APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);

				APDU[0] |= 0x19;	

				//MessageBox(_T("等一下"));

				RespLen = 256 + 2;
				::memset(Resp, 0, RespLen);
				if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
				{
					UpdateData(TRUE);
					edtpcscCardOTAStatus.SetWindowText(pDlg->Reader.GetError());
					edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					UpdateData(FALSE);
					MessageBox(pDlg->Reader.GetError());
					return false;
				}
				//MessageBox(sSW);
				if ("9000" != pDlg->Reader.HexToStr(Resp, 2))
				{
					UpdateData(TRUE);
					sStatus = _T("下载过程中失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
					edtpcscCardOTAStatus.SetWindowText(sStatus);
					edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					UpdateData(FALSE);
					MessageBox(sStatus);
					return false;
				}
			}
			else
			{
				//空格等，略过
				//MessageBox(_T("空格等，略过"));
			}
		}

		if (index > (fileLines / 100))
		{
			UpdateData(TRUE);
			if ((index + fileLines / 100) < fileLines)
				pcsccardOTAprocess.SetPos(index + fileLines / 100);
			else
				pcsccardOTAprocess.SetPos(fileLines - 2);
			//上面这么处理是为了进度条显示不一致做的特殊处理，处理后感官上大概一致
			sStatus.Format(_T("Loadding %d%%"), (index * 100 / fileLines));
			edtpcscCardOTAStatus.SetWindowText(sStatus);
			edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

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
	pcsccardOTAprocess.SetPos(fileLines);
	sStatus.Format(_T("Congratulations! 100%% loaded."));
	edtpcscCardOTAStatus.SetWindowText(sStatus);
	edtpcscCardOTAStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);
	UpdateWindow();

	/////////////////////////////////////////////////////////////////
	MessageBox(_T("恭喜您！卡片固件更新成功！\n\n重启设备后生效。"));
	return TRUE;
}
void Loader::OnBnClickedbtnfirmwareupdate()
{
	Download_Firmwarecipher();
}
