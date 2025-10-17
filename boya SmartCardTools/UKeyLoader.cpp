// UKeyLoader.cpp: 实现文件
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


// UKeyLoader 对话框

IMPLEMENT_DYNAMIC(UKeyLoader, CDialogEx)

UKeyLoader::UKeyLoader(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE_UKeyOTA, pParent)
{

}

UKeyLoader::~UKeyLoader()
{
}

void UKeyLoader::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, btnOpenUKeyBin, btnpcscOpenUKeyBin);
	DDX_Control(pDX, btnGenCipherBinSCT, btnpcscGenCipherBinSCT);

	DDX_Control(pDX, edtCosFile_UkeyBin, edtpcscCosFile_UKeyBin);
	DDX_Control(pDX, edtUKeyOTAStatus, edtpcscUKeyOTAStatus);

	DDX_Control(pDX, ukeyOTAprocess, pcscukeyOTAprocess);
}


BEGIN_MESSAGE_MAP(UKeyLoader, CDialogEx)
	ON_BN_CLICKED(btnOpenUKeyBin, &UKeyLoader::OnBnClickedbtnopenukeybin)
	ON_BN_CLICKED(btnGenCipherBinSCT, &UKeyLoader::OnBnClickedbtngencipherbinsct)
END_MESSAGE_MAP()


// UKeyLoader 消息处理程序


void UKeyLoader::OnBnClickedbtnopenukeybin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_fName, FileTitle;
	CString Filter;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	Filter = _T("UKEY固件文件(*.bin)|*.bin||");

	CFileDialog dlgOpen(TRUE, 0, 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, (LPCTSTR)Filter, NULL);
	if (dlgOpen.DoModal() == IDOK)
	{
		m_fName = dlgOpen.GetPathName();//路径名称
		//FileTitle = dlgOpen.GetFileName(); 
		FileTitle = dlgOpen.GetFileTitle();// 取得要分割的文件名（不包含路径、扩展名）
	}
	else
		return;

	edtpcscCosFile_UKeyBin.SetWindowText(m_fName);
}


void InvertUint16(unsigned short* dBuf, unsigned short* srcBuf)
{
	int i;
	unsigned short tmp[4] = { 0 };
	for (i = 0; i < 16; i++)
	{
		if (srcBuf[0] & (1 << i))
			tmp[0] |= 1 << (15 - i);
	}
	dBuf[0] = tmp[0];
}

/****************************Info**********************************************
* Name: CRC-16/X25 x16+x12+x5+1
* Width: 16
* Poly: 0x1021
* Init: 0xFFFF
* Refin: True
* Refout: True
* Xorout: 0xFFFF
*****************************************************************************/
unsigned short CRC16_X25(unsigned char* data, unsigned int datalen)
{
	unsigned short wCRCin = 0xFFFF;
	unsigned short wCPoly = 0x1021;
	InvertUint16(&wCPoly, &wCPoly);
	while (datalen--)
	{
		wCRCin ^= *(data++);
		for (int i = 0; i < 8; i++)
		{
			if (wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ wCPoly;
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin ^ 0xFFFF);
}
extern unsigned char LoaderAuthKey[];
boolean UKeyLoader::GenUKEYfirmwarecipher()
{
	//CStdioFile file;
	byte APDU_Header[7] = { 0x80,0x0F,0x00,0x00,0x00,0x00,0x00 };
	DWORD APDULen = 0;
	CString filePath, filePath1, filePath2, filePath3;
	CString sStrAPDU;
	unsigned char checkApdu[17] = { 0x80,0x0F,0xFF,0xFD,0x00,0x00,0x0A };
	unsigned short crc16Result;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	UpdateData(TRUE);//从窗口编辑框中读入数据

	edtpcscCosFile_UKeyBin.GetWindowText(filePath);
	if (filePath == _T(""))
	{
		MessageBox(_T("未选择bin文件，请选择bin文件！"));
		return false;
	}
	int filePathLen = filePath.GetLength();
	if (filePathLen < 8)
	{
		MessageBox(_T("未选择bin文件，请选择bin文件！"));
		return false;
	}

	if (filePath.Right(8) == _T("AppA.bin"))
	{
		APDU_Header[2] = 0x00;//‘00’为APPA固件数据

		checkApdu[7] = 0x00;
		checkApdu[8] = 0x40;
		checkApdu[9] = 0x48;
		checkApdu[10] = 0x00;
	}
	else if (filePath.Right(8) == _T("AppB.bin"))
	{
		APDU_Header[2] = 0x01;//‘01’为APPB固件数据

		checkApdu[7] = 0x00;
		checkApdu[8] = 0x41;
		checkApdu[9] = 0xD8;
		checkApdu[10] = 0x00;
	}
	else
	{
		MessageBox(_T("请选择正确的适用于UKEY的bin文件！"));
		return false;
	}

	//使用fseek和ftell函数定位到文件末尾，然后使用fread函数读取整个文件内容
	FILE* file = fopen(filePath, "rb");  // 以二进制只读方式打开文件
	if (file == NULL) {
		printf("无法打开bin文件\n");
		return false;
	}

	fseek(file, 0, SEEK_END);  // 定位到文件末尾
	long fileSize = ftell(file);  // 获取文件大小
	fseek(file, 0, SEEK_SET);  // 重新定位到文件开头

	unsigned char* buffer = (unsigned char*)malloc(fileSize + 16);  // 动态分配内存缓冲区，+16是用于非Block整数倍长度时填充FF使用
	if (buffer == NULL) {
		printf("内存分配失败\n");
		return false;
	}

	size_t bytesRead = fread(buffer, sizeof(unsigned char), fileSize, file);  // 读取整个文件内容
	if (bytesRead != fileSize) {
		printf("读取文件失败\n");
		free(buffer);
		return false;
	}
	fclose(file);

	checkApdu[11] = 0xFF & (fileSize >> 24);
	checkApdu[12] = 0xFF & (fileSize >> 16);
	checkApdu[13] = 0xFF & (fileSize >> 8);
	checkApdu[14] = 0xFF & (fileSize >> 0);


	// 处理读取到的字节数据
	// 将明文数据写到新的hex文件中
	filePath1 = filePath.Left(filePath.GetLength() - 4) + ".hex";
	FILE* file1 = fopen(filePath1, "w");  // 以写入方式打开hex文件，同时清除文件内容
	if (file1 == NULL) {
		printf("无法打开文件\n");
		return -1;
	}
	fclose(file1);
	file1 = fopen(filePath1, "a+"); //以附加的方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。(EOF符保留)
	fprintf(file1, pDlg->Reader.HexToStr(buffer, fileSize));
	fclose(file1);

	//填充之前计算CRC值
	crc16Result = CRC16_X25(buffer, fileSize);
	checkApdu[15] = 0xFF & (crc16Result >> 0);//高低字节交换
	checkApdu[16] = 0xFF & (crc16Result >> 8);

	// 加密数据,//SM4算法
	sm4_context ctx;
	CString outS;
	//encrypt standard testing vector
	sm4_setkey_enc(&ctx, LoaderAuthKey);
	if (fileSize % 16)
	{
		unsigned int fillLen = 16 - fileSize % 16;
		memset(buffer + fileSize, 0xFF, fillLen);
		fileSize += fillLen;
	}
	//填充之后
	sm4_crypt_ecb(&ctx, 1, fileSize, buffer, buffer);	//密文放到原位置

	//将密文数据写到新的bybin文件中
	filePath2 = filePath.Left(filePath.GetLength() - 4) + ".bybin";
	FILE* file2 = fopen(filePath2, "wb");  // 以二进制写入方式打开bybin文件，同时清除文件内容
	if (file2 == NULL) {
		printf("无法打开文件\n");
		return false;
	}
	fwrite(buffer, sizeof(unsigned char), fileSize, file2);
	fclose(file2);



	//将密文数据转换成APDU写到新的APDU脚本bysct文件中
	filePath3 = filePath.Left(filePath.GetLength() - 4) + "_APDU.bysct";
	FILE* file3 = fopen(filePath3, "w");  // 以写入方式打开bysct文件，同时清除文件内容
	if (file3 == NULL) {
		printf("无法打开文件\n");
		return -1;
	}
	fclose(file3);

	file3 = fopen(filePath3, "a+"); //以附加的方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。(EOF符保留)

	long index;
	unsigned  short thisLength = 8 * 1024;
	APDU_Header[3] = 0;
	for (index = 0; index + thisLength < fileSize; )
	{
		APDU_Header[3]++;
		APDU_Header[4] = 0x00;
		APDU_Header[5] = thisLength / 256;
		APDU_Header[6] = thisLength % 256;
		sStrAPDU = pDlg->Reader.HexToStr(APDU_Header, 7);
		sStrAPDU += pDlg->Reader.HexToStr(buffer + index, thisLength);
		fprintf(file3, sStrAPDU + "\n");
		index += thisLength;
	}

	//if (index < fileSize)
	{
		thisLength = fileSize - index;
		APDU_Header[3] = 0;	//尾包数据
		APDU_Header[4] = 0x00;
		APDU_Header[5] = thisLength / 256;
		APDU_Header[6] = thisLength % 256;
		sStrAPDU = pDlg->Reader.HexToStr(APDU_Header, 7);
		sStrAPDU += pDlg->Reader.HexToStr(buffer + index, thisLength);
		fprintf(file3, sStrAPDU + "\n");
	}

	//CheckData APDU
	sStrAPDU = pDlg->Reader.HexToStr(checkApdu, 17);
	fprintf(file3, sStrAPDU);

	fclose(file3);

	free(buffer);

	/////////////////////////////////////////////////////////////////
	MessageBox(_T("恭喜您！\n\n用UKEY固件bin文件生成UEKY固件密文bin文件、UEKY OTA Loader APDU文件成功！"));
	return TRUE;
}

void UKeyLoader::OnBnClickedbtngencipherbinsct()
{
	GenUKEYfirmwarecipher();
}
