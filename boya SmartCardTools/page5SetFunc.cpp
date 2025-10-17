// page5SetFunc.cpp: 实现文件
//
#include "stdafx.h"
//#include "pch.h"
#include "afxwin.h"
#include "afxdialogex.h"
#include "page5SetFunc.h"
#include "CSmartToolDlg.h"
#include   "..\SM4\sm4.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include<io.h>   //C语言头文件
#include<iostream>   //for system();


#include "tchar.h"
#include   "ATLCONV.H"

#include <algorithm>
#include <cctype>

// page5SetFunc 对话框


page5SetFuncDlg::page5SetFuncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(page5SetFuncDlg::IDD, pParent)
{

}

//page5SetFuncDlg::~page5SetFuncDlg()
//{
//}

void page5SetFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_TIMER_HH, edtTimerHH);
	DDX_Control(pDX, IDC_EDIT_TIMER_MM, edtTimerMM);
	DDX_Control(pDX, IDC_EDIT_TIMER_SS, edtTimerSS);

	DDX_Control(pDX, IDC_EDIT_COUNTRY_1, edtCountry[0]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_2, edtCountry[1]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_3, edtCountry[2]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_4, edtCountry[3]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_5, edtCountry[4]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_6, edtCountry[5]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_7, edtCountry[6]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_8, edtCountry[7]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_9, edtCountry[8]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_10, edtCountry[9]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_11, edtCountry[10]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_12, edtCountry[11]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_13, edtCountry[12]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_14, edtCountry[13]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_15, edtCountry[14]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_16, edtCountry[15]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_17, edtCountry[16]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_18, edtCountry[17]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_19, edtCountry[18]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_20, edtCountry[19]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_21, edtCountry[20]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_22, edtCountry[21]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_23, edtCountry[22]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_24, edtCountry[23]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_25, edtCountry[24]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_26, edtCountry[25]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_27, edtCountry[26]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_28, edtCountry[27]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_29, edtCountry[28]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_30, edtCountry[29]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_31, edtCountry[30]);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_32, edtCountry[31]);

	DDX_Control(pDX, IDC_EDIT_MCC_1, edtMCC[0]);
	DDX_Control(pDX, IDC_EDIT_MCC_2, edtMCC[1]);
	DDX_Control(pDX, IDC_EDIT_MCC_3, edtMCC[2]);
	DDX_Control(pDX, IDC_EDIT_MCC_4, edtMCC[3]);
	DDX_Control(pDX, IDC_EDIT_MCC_5, edtMCC[4]);
	DDX_Control(pDX, IDC_EDIT_MCC_6, edtMCC[5]);
	DDX_Control(pDX, IDC_EDIT_MCC_7, edtMCC[6]);
	DDX_Control(pDX, IDC_EDIT_MCC_8, edtMCC[7]);
	DDX_Control(pDX, IDC_EDIT_MCC_9, edtMCC[8]);
	DDX_Control(pDX, IDC_EDIT_MCC_10, edtMCC[9]);
	DDX_Control(pDX, IDC_EDIT_MCC_11, edtMCC[10]);
	DDX_Control(pDX, IDC_EDIT_MCC_12, edtMCC[11]);
	DDX_Control(pDX, IDC_EDIT_MCC_13, edtMCC[12]);
	DDX_Control(pDX, IDC_EDIT_MCC_14, edtMCC[13]);
	DDX_Control(pDX, IDC_EDIT_MCC_15, edtMCC[14]);
	DDX_Control(pDX, IDC_EDIT_MCC_16, edtMCC[15]);
	DDX_Control(pDX, IDC_EDIT_MCC_17, edtMCC[16]);
	DDX_Control(pDX, IDC_EDIT_MCC_18, edtMCC[17]);
	DDX_Control(pDX, IDC_EDIT_MCC_19, edtMCC[18]);
	DDX_Control(pDX, IDC_EDIT_MCC_20, edtMCC[19]);
	DDX_Control(pDX, IDC_EDIT_MCC_21, edtMCC[20]);
	DDX_Control(pDX, IDC_EDIT_MCC_22, edtMCC[21]);
	DDX_Control(pDX, IDC_EDIT_MCC_23, edtMCC[22]);
	DDX_Control(pDX, IDC_EDIT_MCC_24, edtMCC[23]);
	DDX_Control(pDX, IDC_EDIT_MCC_25, edtMCC[24]);
	DDX_Control(pDX, IDC_EDIT_MCC_26, edtMCC[25]);
	DDX_Control(pDX, IDC_EDIT_MCC_27, edtMCC[26]);
	DDX_Control(pDX, IDC_EDIT_MCC_28, edtMCC[27]);
	DDX_Control(pDX, IDC_EDIT_MCC_29, edtMCC[28]);
	DDX_Control(pDX, IDC_EDIT_MCC_30, edtMCC[29]);
	DDX_Control(pDX, IDC_EDIT_MCC_31, edtMCC[30]);
	DDX_Control(pDX, IDC_EDIT_MCC_32, edtMCC[31]);

	DDX_Control(pDX, IDC_EDIT_IP_1, edtIP[0]);
	DDX_Control(pDX, IDC_EDIT_IP_2, edtIP[1]);
	DDX_Control(pDX, IDC_EDIT_IP_3, edtIP[2]);
	DDX_Control(pDX, IDC_EDIT_IP_4, edtIP[3]);
	DDX_Control(pDX, IDC_EDIT_IP_5, edtIP[4]);
	DDX_Control(pDX, IDC_EDIT_IP_6, edtIP[5]);
	DDX_Control(pDX, IDC_EDIT_IP_7, edtIP[6]);
	DDX_Control(pDX, IDC_EDIT_IP_8, edtIP[7]);
	DDX_Control(pDX, IDC_EDIT_IP_9, edtIP[8]);
	DDX_Control(pDX, IDC_EDIT_IP_10, edtIP[9]);
	DDX_Control(pDX, IDC_EDIT_IP_11, edtIP[10]);
	DDX_Control(pDX, IDC_EDIT_IP_12, edtIP[11]);
	DDX_Control(pDX, IDC_EDIT_IP_13, edtIP[12]);
	DDX_Control(pDX, IDC_EDIT_IP_14, edtIP[13]);
	DDX_Control(pDX, IDC_EDIT_IP_15, edtIP[14]);
	DDX_Control(pDX, IDC_EDIT_IP_16, edtIP[15]);
	DDX_Control(pDX, IDC_EDIT_IP_17, edtIP[16]);
	DDX_Control(pDX, IDC_EDIT_IP_18, edtIP[17]);
	DDX_Control(pDX, IDC_EDIT_IP_19, edtIP[18]);
	DDX_Control(pDX, IDC_EDIT_IP_20, edtIP[19]);
	DDX_Control(pDX, IDC_EDIT_IP_21, edtIP[20]);
	DDX_Control(pDX, IDC_EDIT_IP_22, edtIP[21]);
	DDX_Control(pDX, IDC_EDIT_IP_23, edtIP[22]);
	DDX_Control(pDX, IDC_EDIT_IP_24, edtIP[23]);
	DDX_Control(pDX, IDC_EDIT_IP_25, edtIP[24]);
	DDX_Control(pDX, IDC_EDIT_IP_26, edtIP[25]);
	DDX_Control(pDX, IDC_EDIT_IP_27, edtIP[26]);
	DDX_Control(pDX, IDC_EDIT_IP_28, edtIP[27]);
	DDX_Control(pDX, IDC_EDIT_IP_29, edtIP[28]);
	DDX_Control(pDX, IDC_EDIT_IP_30, edtIP[29]);
	DDX_Control(pDX, IDC_EDIT_IP_31, edtIP[30]);
	DDX_Control(pDX, IDC_EDIT_IP_32, edtIP[31]);
}


BEGIN_MESSAGE_MAP(page5SetFuncDlg, CDialogEx)
//	ON_BN_CLICKED(page5DevAuthBtn, &page5SetFuncDlg::OnClickedPage5devauthbtn)
ON_BN_CLICKED(page5GetSwitchStatus, &page5SetFuncDlg::OnBnClickedpage5getswitchstatus)
ON_BN_CLICKED(page5SetSwitchStatus, &page5SetFuncDlg::OnBnClickedpage5setswitchstatus)
ON_BN_CLICKED(page5GetMCCIP, &page5SetFuncDlg::OnBnClickedpage5getmccip)
ON_BN_CLICKED(page5SetMCCIP, &page5SetFuncDlg::OnBnClickedpage5setmccip)
ON_BN_CLICKED(page5GetTimer, &page5SetFuncDlg::OnBnClickedpage5gettimer)
ON_BN_CLICKED(page5SetTimer, &page5SetFuncDlg::OnBnClickedpage5settimer)
ON_BN_CLICKED(page5CloseTimer, &page5SetFuncDlg::OnBnClickedpage5closetimer)
ON_BN_CLICKED(page5FillClearOriginalMCCIP, &page5SetFuncDlg::OnBnClickedpage5fillclearoriginalmccip)
ON_BN_CLICKED(page5ClearMCCIP, &page5SetFuncDlg::OnBnClickedpage5clearmccip)
END_MESSAGE_MAP()


// page5SetFunc 消息处理程序





void page5SetFuncDlg::initSetFuncPage()
{
	
}

boolean page5SetFuncDlg::SKF_DevAuth(CString authKey)
{
	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;
	CString sKey;
	unsigned char key[16] = { 0 };
	BYTE thisRandom[16];

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	pDlg->Reader.StrToHex(authKey, key);

	//取8字节随机数，后补8字节00至16字节
	sAPDU = "9950000008";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
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
	::memcpy(thisRandom, Resp, 8);
	::memset(thisRandom + 8, 0, 8);

	//authKey 计算认证数据
	//SM4算法
	sm4_context ctx;
	CString outS;
	//encrypt standard testing vector
	sm4_setkey_enc(&ctx, key);
	sm4_crypt_ecb(&ctx, 1, 16, thisRandom, APDU + 5);

	//执行设备认证指令
	sAPDU = "9910000010";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU) + 16;
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return FALSE;
	}
	if (Resp[0] != 0x90)
		return FALSE;
	else
		return TRUE;
}

// IDC_CHECK_S2S_SWITCH
// IDC_CHECK_S2S_SM4_SWITCH
// IDC_CHECK_BINDING_SWITCH
// IDC_CHECK_BIDA_SWITCH
// IDC_CHECK_P2P_SETIP_SWITCH
// IDC_CHECK_OTP_SWITCH
// IDC_CHECK_PROVIDE_LOCALINFO_SWITCH
// IDC_CHECK_SIM_LOG_SWITCH
// IDC_CHECK_MCC_IP_POOL_SWITCH
// IDC_CHECK_REPORTING_LOCATION_SWITCH

void page5SetFuncDlg::OnBnClickedpage5getswitchstatus()
{
	//首先清除状态
	((CButton*)GetDlgItem(IDC_CHECK_S2S_SWITCH))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_S2S_SM4_SWITCH))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_BINDING_SWITCH))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_BIDA_SWITCH))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_P2P_SETIP_SWITCH))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_OTP_SWITCH))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_PROVIDE_LOCALINFO_SWITCH))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_SIM_LOG_SWITCH))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_MCC_IP_POOL_SWITCH))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_REPORTING_LOCATION_SWITCH))->SetCheck(0);

	//=============================================================

	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;
	BYTE Le = 0;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//获取可选功能状态APDU
	Lab_GetSwitchStatusAgain:
	sAPDU = "9901001300";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	APDU[4] = Le;
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if (Le == 0)
	{
		if (RespLen != 2)
		{
			MessageBox(_T("糟糕！\n\n获取可选功能状态执行失败！退出"));
			return;
		}
		if (Resp[0] != 0x6C)
		{
			MessageBox(_T("糟糕！\n\n获取可选功能状态执行失败！退出"));
			return;
		}
		else
		{
			Le = Resp[1];
			goto Lab_GetSwitchStatusAgain;
		}
	}
	else
	{
		if (Resp[RespLen-2] != 0x90)
		{
			MessageBox(_T("糟糕！\n\n获取可选功能状态执行失败！退出"));
			return;
		}
	}

	MessageBox(_T("恭喜您！\n\n获取可选功能状态执行成功！"));

	//=============================================================

	((CButton*)GetDlgItem(IDC_CHECK_S2S_SWITCH))->SetCheck(Resp[2]);
	((CButton*)GetDlgItem(IDC_CHECK_S2S_SM4_SWITCH))->SetCheck(Resp[5]);
	((CButton*)GetDlgItem(IDC_CHECK_BINDING_SWITCH))->SetCheck(Resp[8]);
	((CButton*)GetDlgItem(IDC_CHECK_BIDA_SWITCH))->SetCheck(Resp[11]);
	((CButton*)GetDlgItem(IDC_CHECK_P2P_SETIP_SWITCH))->SetCheck(Resp[14]);
	((CButton*)GetDlgItem(IDC_CHECK_OTP_SWITCH))->SetCheck(Resp[17]);
	((CButton*)GetDlgItem(IDC_CHECK_PROVIDE_LOCALINFO_SWITCH))->SetCheck(Resp[20]);
	((CButton*)GetDlgItem(IDC_CHECK_SIM_LOG_SWITCH))->SetCheck(Resp[23]);
	((CButton*)GetDlgItem(IDC_CHECK_MCC_IP_POOL_SWITCH))->SetCheck(Resp[26]);
	((CButton*)GetDlgItem(IDC_CHECK_REPORTING_LOCATION_SWITCH))->SetCheck(Resp[29]);
}


void page5SetFuncDlg::OnBnClickedpage5setswitchstatus()
{
	CString AUTHKEY = _T("31323334353637383132333435363738");
	if (FALSE == SKF_DevAuth(AUTHKEY))
	{
		MessageBox(_T("糟糕！\n\n设备认证指令执行失败，无法继续执行设置可选功能操作!"));
		return;
	}
	//=============================================================

	BYTE switchStatusDB[30] = { 0x01,0x01,0,0x02,0x01,0,0x03,0x01,0,0x04,0x01,0,0x05,0x01,0,0x06,0x01,0,0x07,0x01,0,0x08,0x01,0,0x09,0x01,0,0x0A,0x01,0 };
	if (((CButton*)GetDlgItem(IDC_CHECK_S2S_SWITCH))->GetCheck() == 1)
		switchStatusDB[2] = 1; 
	if (((CButton*)GetDlgItem(IDC_CHECK_S2S_SM4_SWITCH))->GetCheck() == 1)
		switchStatusDB[5] = 1;
	if (((CButton*)GetDlgItem(IDC_CHECK_BINDING_SWITCH))->GetCheck() == 1)
		switchStatusDB[8] = 1;
	if (((CButton*)GetDlgItem(IDC_CHECK_BIDA_SWITCH))->GetCheck() == 1)
		switchStatusDB[11] = 1;
	if (((CButton*)GetDlgItem(IDC_CHECK_P2P_SETIP_SWITCH))->GetCheck() == 1)
		switchStatusDB[14] = 1;
	if (((CButton*)GetDlgItem(IDC_CHECK_OTP_SWITCH))->GetCheck() == 1)
		switchStatusDB[17] = 1;
	if (((CButton*)GetDlgItem(IDC_CHECK_PROVIDE_LOCALINFO_SWITCH))->GetCheck() == 1)
		switchStatusDB[20] = 1;
	if (((CButton*)GetDlgItem(IDC_CHECK_SIM_LOG_SWITCH))->GetCheck() == 1)
		switchStatusDB[23] = 1;
	if (((CButton*)GetDlgItem(IDC_CHECK_MCC_IP_POOL_SWITCH))->GetCheck() == 1)
		switchStatusDB[26] = 1;
	if (((CButton*)GetDlgItem(IDC_CHECK_REPORTING_LOCATION_SWITCH))->GetCheck() == 1)
		switchStatusDB[29] = 1;

	//=============================================================

	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//设置可选功能状态APDU
	sAPDU = "998113001E";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	::memcpy(APDU+5, switchStatusDB, 30);
	APDULen += 30;
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if( (RespLen != 2)
		||(Resp[0] != 0x90)
	)
	{
		MessageBox(_T("糟糕！\n\n设置可选功能状态执行失败！退出"));
		return;
	}
	MessageBox(_T("恭喜您！\n\n设置可选功能状态执行成功！"));
}

int gLengthTest = 0;
int AnsiToUCS2Data(const std::string& strAnsi, BYTE * pbOutDB)
{
	//获取转换所需的接收缓冲区大小
	int  nUnicodeLen = ::MultiByteToWideChar(CP_ACP,
		0,
		strAnsi.c_str(),
		-1,
		NULL,
		0);

	if (1 >= nUnicodeLen)
		return 0;

	int ucs2dataLen = (nUnicodeLen - 1) * 2;

	if (NULL == pbOutDB)	//只求UCS2数据长度
		return ucs2dataLen;

	//分配指定大小的内存
	wchar_t* pUnicode = new wchar_t[nUnicodeLen + 1];
	::memset((void*)pUnicode, 0, (nUnicodeLen + 1) * sizeof(wchar_t));

	//转换
	::MultiByteToWideChar(CP_ACP,
		0,
		strAnsi.c_str(),
		-1,
		(LPWSTR)pUnicode,
		nUnicodeLen);

	for (int i = 0; i < ucs2dataLen / 2; i++)
	{//wchar_t是小端模式，需转成大端模式输出
		pbOutDB[2 * i] = *((BYTE*)pUnicode + 2 * i + 1);
		pbOutDB[2 * i + 1] = *((BYTE*)pUnicode + 2 * i);
	}

	delete[]pUnicode;

	return ucs2dataLen;
}

void page5SetFuncDlg::ClearMCC_IP_POOL()
{
	for (int i = 0; i < 32; i++)
	{
		edtCountry[i].SetWindowText(_T(""));
		edtMCC[i].SetWindowText(_T(""));
		edtIP[i].SetWindowText(_T(""));
	}
}

void page5SetFuncDlg::OnBnClickedpage5getmccip()
{
	ClearMCC_IP_POOL();
	//=============================================================
	CString dispErrStr;
	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;
	byte apdu_P1 = 0x00;
	byte apdu_Le = 0x00;
	unsigned short thisDataLen = 0;
	unsigned short totalDataLen = 0;
	BYTE mcc_ip_pool_Data[16 * 128] = { 0 };

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	Lab_Get_MCC_IP_POOL:
	//获取MCC_IP_POOL的APDU
	sAPDU = "9901001400";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	APDU[2] = apdu_P1;
	APDU[4] = apdu_Le;
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if (RespLen % 16 != 2)
	{
		MessageBox(_T("糟糕！\n\n获取MCC_IP_POOL的APDU执行失败！退出"));
		return;
	}
	if (RespLen == 2){//没有数据返回
		if (Resp[0] == 0x6C) {
			apdu_Le = Resp[1];	//根据返回的剩余长度重新获取
			goto Lab_Get_MCC_IP_POOL;
		}

		if (Resp[0] != 0x90) {
			if (Resp[0] == 0x6B) {
				if (0 == apdu_P1) {
					dispErrStr.Format(_T("糟糕！\n\nMCC_IP_POOL中为空！退出"));
					MessageBox(dispErrStr);
					return;
				}
				//APDU都根据返回的6CXX获取或者Le=0获取，如果返回6B00，只能是Le去获取的，此时说明已经没有数据了
			}
			else {
				dispErrStr.Format(_T("SW =0x%02X%02X\n\n糟糕！\n\n获取MCC_IP_POOL的APDU执行失败！退出"), Resp[0], Resp[1]);
				MessageBox(dispErrStr);
				return;
			}
		}
		//只有SW时不应该返回9000
	}
	else {//有数据返回
		thisDataLen = (apdu_Le == 0) ? 256 : apdu_Le;
		::memcpy(mcc_ip_pool_Data + totalDataLen, Resp, thisDataLen);
		totalDataLen += thisDataLen;
		if (apdu_Le == 0) {	//本次返回256字节数据，偏移地址+256后继续获取
			apdu_P1++;
			goto Lab_Get_MCC_IP_POOL;
		}
		//最后不足256字节的数据已获取
	}
	//此时数组mcc_ip_pool_Data中的数据长度是totalDataLen
	dispErrStr.Format(_T("恭喜您！\n\n获取MCC_IP_POOL结束！一共获取到%d个MCC_IP组合。"), totalDataLen/16);
	if (totalDataLen / 16 > 32) {
		dispErrStr += _T("\n本界面只提供显示前32个MCC_IP组合");
	}		
	MessageBox(dispErrStr);

	//=========================================

	int index = 0;
	while(index * 16 < totalDataLen){
		//1、前10字节为COUNTRY的UCS2编码数据
		wchar_t ucs2String[6] = { 0 };	//比实际最大长度多一个置0作为结尾
		for (int i = 0; i < 5; i++)	{//wchar_t是小端模式，需将大端模式转换
			*((BYTE*)ucs2String + 2 * i + 1) = mcc_ip_pool_Data[index*16 + 2 * i];
			*((BYTE*)ucs2String + 2 * i) = mcc_ip_pool_Data[index*16 + 2 * i + 1];
		}
		// 使用CString构造函数
		CString cStrCountry(ucs2String);

		//2、接下来2字节为MCC，需要将其转换成10进制后再显示
		unsigned short mcc = mcc_ip_pool_Data[index * 16 + 10] * 256 + mcc_ip_pool_Data[index * 16 + 11];
		CString cStrMCC;
		cStrMCC.Format(_T("%d"), mcc);

		//3、最后4字节为IP地址，需要将其转换成10进制后再显示
		byte ipDB[4];
		::memcpy(ipDB, &mcc_ip_pool_Data[index * 16 + 12], 4);
		CString cStrIP;
		cStrIP.Format(_T("%d.%d.%d.%d"), ipDB[0], ipDB[1], ipDB[2], ipDB[3]);

		if (index < 32) {	//工具界面只提供显示前32个MCC_IP组合
			edtCountry[index].SetWindowText(cStrCountry);
			edtMCC[index].SetWindowText(cStrMCC);
			edtIP[index].SetWindowText(cStrIP);
		}

		index++;
	}
		
}

CString gDispStr;
bool CheckIpCString(const CString& str, byte ipData[4]) {
	bool foundDot = false; // 标记是否已找到'.'
	byte dotNum = 0;
	byte dotInDataIndex = 0;
	unsigned short ushIpData[4];
	if (str[0] == '.')
		return false;
	if (str[str.GetLength()-1] == '.')
		return false;
	::memset(ushIpData, 0 , sizeof(ushIpData));
	for (int i = 0; i < str.GetLength(); ++i) {
		if (str[i] == '.') {
			dotNum++;
			if (dotNum > 3) {	//dotNum==3
				return false;
			}
			continue; // 跳过当前循环迭代
		}
		if (!isdigit(str[i])) { // 如果不是数字，返回false
			return false;
		}
		ushIpData[dotNum] *= 10;
		ushIpData[dotNum] += str[i] - '0';
	}

	if (dotNum != 3) {	//dotNum==3
		return false;
	}
	for (int i = 0; i < 4; i++)
	{
		if (ushIpData[i] > 255)
		{
			gDispStr.Format(_T("IP[%d] = %d > 255\n"), i, ushIpData[i]);
			return false;
		}
		ipData[i] = ushIpData[i];
	}
	return true; // 所有字符都是数字且在中间有3个'.'
}

void page5SetFuncDlg::OnBnClickedpage5setmccip()
{
	CString countryStr, mccStr, ipStr;
	CString dispStr2, dispStr;
	int i;
	BYTE countryUSC2Len;
	BYTE mccLen;
	BYTE ipLen;
	BYTE noDataNum = 0;
	BYTE mcc_ip_pool_Data[16 * 128] = { 0 };
	BYTE mcc_ip_num = 0;
	int mccIPDataLen = 0;

	//Country\MCC\IP
	for (i = 0; i < 32; i++)
	{
		std::string strCountry;

		//----获取输入的值----
		edtCountry[i].GetWindowText(countryStr);	//需要转成UCS2后判断
		countryStr.Remove(' ');
		countryStr.Remove('	');
		strCountry = CStringA(countryStr).GetString();
		countryUSC2Len = AnsiToUCS2Data(strCountry, NULL);

		edtMCC[i].GetWindowText(mccStr);
		mccStr.Remove(' ');
		mccStr.Remove('	');
		mccLen = strlen(mccStr);

		edtIP[i].GetWindowText(ipStr);
		ipStr.Remove(' ');
		ipStr.Remove('	');
		ipLen = strlen(ipStr);

		//----判断输入的合法性----

		//1、有无空白检查
		if (0 == countryUSC2Len)
		{
			if (mccLen || ipLen)
			{
				dispStr.Format(_T("No%d 未填写完整：国家名称未填写！退出。"), 1 + i);
				MessageBox(dispStr);
				return;
			}
			noDataNum++;
			continue;
		}

		if (0 == mccLen)
		{
			dispStr.Format(_T("No%d 未填写完整：MCC未填写！退出。"), 1 + i);
			MessageBox(dispStr);
			return;
		}

		if (0 == ipLen)
		{
			dispStr.Format(_T("No%d 未填写完整：IP未填写！退出。"), 1 + i);
			MessageBox(dispStr);
			return;
		}
		//2、长度是否超出检查
		if (10 < countryUSC2Len)
		{
			dispStr.Format(_T("No%d 国家名称长度超出5个字符！退出。"), 1 + i);
			MessageBox(dispStr);
			return;
		}
		if (3 < mccLen)
		{
			dispStr.Format(_T("No%d MCC长度超出3个字符！退出。"), 1 + i);
			MessageBox(dispStr);
			return;
		}
		if (15 < ipLen)
		{
			dispStr.Format(_T("No%d IP地址长度超出15个字符！退出。"), 1 + i);
			MessageBox(dispStr);
			return;
		}
		if (7 > ipLen)
		{
			dispStr.Format(_T("No%d IP地址长度不足7个字符！退出。"), 1 + i);
			MessageBox(dispStr);
			return;
		}
		//3、输入内容检查
		//countryUSC2 这里不做检查
		//mccStr检查
		std::string stdStr(mccStr); // 将CString转换为std::string
		if (std::all_of(stdStr.begin(), stdStr.end(), ::isdigit)) {
			// 字符串全部由数字组成
		}
		else {
			// 字符串包含非数字字符
			dispStr.Format(_T("No%d MCC中包含非数字字符！退出。"), 1 + i);
			MessageBox(dispStr);
			return;
		}
		
		//ipStr检查
		byte ipData[4];
		gDispStr = "";
		if (!CheckIpCString(ipStr, ipData)) {
			// 字符串不符合IP地址格式
			dispStr.Format(_T("No%d IP地址字符串不符合IP地址格式！退出。"), 1 + i);
			MessageBox(gDispStr + dispStr );
			return;

		}
		//dispStr.Format(_T("No%d IP = %d. %d. %d. %d。"), 1 + i, ipData[0], ipData[1], ipData[2], ipData[3]);
		//MessageBox(dispStr);
		
		//数据已经符合要求
		//Contry,10Bytes
		countryUSC2Len = AnsiToUCS2Data(strCountry, mcc_ip_pool_Data + mccIPDataLen);
		mccIPDataLen += 10;
		//MCC,2Bytes
		int mcc = atoi(mccStr);
		mcc_ip_pool_Data[mccIPDataLen++] = mcc>>8;
		mcc_ip_pool_Data[mccIPDataLen++] = mcc;
		//IP,4Bytes
		mcc_ip_pool_Data[mccIPDataLen++] = ipData[0];
		mcc_ip_pool_Data[mccIPDataLen++] = ipData[1];
		mcc_ip_pool_Data[mccIPDataLen++] = ipData[2];
		mcc_ip_pool_Data[mccIPDataLen++] = ipData[3];
	}

	if(32 == noDataNum)
	{
		dispStr.Format(_T("32个全部未填写！退出。"));
		MessageBox(dispStr);
		return;
	}

	//IP地址池待写入数据总长度=mccIPDataLen，数据在数组mcc_ip_pool_Data中

	//=============================================================

	CString dispErrStr;
	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	byte apdu_P2 = 0x00;
	byte thiswriteDataLen;
	unsigned short offset = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 1000;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	while (mccIPDataLen)
	{
		//设置MCC列表APDU
		sAPDU = "99811400";
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		if (mccIPDataLen + 2 > 256)	{
			thiswriteDataLen = 240;
		}
		else {
			thiswriteDataLen = mccIPDataLen;
		}
		APDU[4] = 2 + thiswriteDataLen;
		APDU[5] = (offset >> 8) & 0xFF;
		APDU[6] = offset & 0xFF;
		::memcpy(&APDU[5 + 2], mcc_ip_pool_Data + offset, thiswriteDataLen);
		APDULen = 5 + APDU[4];
		RespLen = 256 + 2;
		::memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			MessageBox(pDlg->Reader.GetError());
			return;
		}
		if (RespLen != 2)
		{
			MessageBox(_T("糟糕！\n\n设置MCC列表APDU执行失败！退出"));
			return;
		}
		if (Resp[0] == 0x6B)
		{
			MessageBox(_T("糟糕！\n\n设置MCC列表时地址溢出！退出"));
			return;
		}
		if (Resp[0] != 0x90)
		{
			dispErrStr.Format(_T("SW =0x%02X%02X\n\n糟糕！\n\n设置MCC列表APDU执行失败！退出"), Resp[0], Resp[1]);
			MessageBox(dispErrStr);
			return;
		}
		mccIPDataLen -= thiswriteDataLen;
		offset += thiswriteDataLen;
	}

	MessageBox(_T("恭喜您！\n\n设置MCC列表成功！退出"));

}


void page5SetFuncDlg::OnBnClickedpage5gettimer()
{
	//清除定时间时间显示信息
	edtTimerHH.SetWindowText(_T(""));
	edtTimerMM.SetWindowText(_T(""));
	edtTimerSS.SetWindowText(_T(""));
	//=============================================================

	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//获取定时自动上传位置信息功能的时间间隔APDU
	sAPDU = "990100C106";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if ((RespLen != 8)
		|| (Resp[RespLen-2] != 0x90)
		)
	{
		MessageBox(_T("糟糕！\n\n获取定时时间APDU执行失败！退出"));
		return;
	}
	for (int i = 0; i < 6; i++)
	{
		if ((Resp[i] < '0') || (Resp[i] > '9'))
		{
			MessageBox(_T("恭喜您！\n\n获取定时时间执行成功！\n\n但是您的安芯卡当前还没有设置定时时间。"));
			return;
		}
	}
	MessageBox(_T("恭喜您！\n\n获取定时时间执行成功！"));

	Resp[6] = 0;
	CString stringHHMMSS = (CString)Resp;

	edtTimerHH.SetWindowText(stringHHMMSS.Left(2));
	edtTimerMM.SetWindowText(stringHHMMSS.Mid(2,2));
	edtTimerSS.SetWindowText(stringHHMMSS.Right(2));
}


void page5SetFuncDlg::OnBnClickedpage5settimer()
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	CString hhStr, mmStr, ssStr;
	char hhmmssDB[16];

	edtTimerHH.GetWindowText(hhStr);
	edtTimerMM.GetWindowText(mmStr);
	edtTimerSS.GetWindowText(ssStr);

	hhStr.Remove(' ');
	hhStr.Remove('	');
	mmStr.Remove(' ');
	mmStr.Remove('	');
	ssStr.Remove(' ');
	ssStr.Remove('	');

	//1、输入长度检查
	if (2 < hhStr.GetLength())
	{
		MessageBox(_T("糟糕！\n\n定时时间Hour的长度不能超过2！退出"));
		return;
	}
	if (0 == hhStr.GetLength())
	{
		MessageBox(_T("糟糕！\n\n定时时间Hour还没有输入！退出"));
		return;
	}
	if (2 < mmStr.GetLength())
	{
		MessageBox(_T("糟糕！\n\n定时时间Min的长度不能超过2！退出"));
		return;
	}
	if (0 == mmStr.GetLength())
	{
		MessageBox(_T("糟糕！\n\n定时时间Min还没有输入！退出"));
		return;
	}
	if (2 < ssStr.GetLength())
	{
		MessageBox(_T("糟糕！\n\n定时时间Sec的长度不能超过2！退出"));
		return;
	}
	if (0 == ssStr.GetLength())
	{
		MessageBox(_T("糟糕！\n\n定时时间Sec的还没有输入！退出"));
		return;
	}

	if (hhStr.GetLength() == 1)
		hhStr = '0' + hhStr;
	if (mmStr.GetLength() == 1)
		mmStr = '0' + mmStr;
	if (ssStr.GetLength() == 1)
		ssStr = '0' + ssStr;

	strcpy(hhmmssDB, hhStr);
	strcpy(hhmmssDB+2, mmStr);
	strcpy(hhmmssDB+4, ssStr);

	for (int i = 0; i < 6; i++)
	{
		if((hhmmssDB[i] < '0') || (hhmmssDB[i] > '9'))
		{
			MessageBox(_T("糟糕！\n\n输入了非数字字符，请重新输入！退出"));
			return;
		}
	}

	if ((hhmmssDB[0] & 0x0F) * 10 + (hhmmssDB[1] & 0x0F) > 23)
	{
		MessageBox(_T("糟糕！\n\n定时时间Hour不能大于23，请重新输入！退出"));
		return;
	}

	if ((hhmmssDB[2] & 0x0F) * 10 + (hhmmssDB[3] & 0x0F) > 59)
	{
		MessageBox(_T("糟糕！\n\n定时时间Min不能大于59，请重新输入！退出"));
		return;
	}

	if ((hhmmssDB[4] & 0x0F) * 10 + (hhmmssDB[5] & 0x0F) > 59)
	{
		MessageBox(_T("糟糕！\n\n定时时间Sec不能大于59，请重新输入！退出"));
		return;
	}

	//=============================================================

	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;

	//获取定时自动上传位置信息功能的时间间隔APDU
	sAPDU = "9981C10006FFFFFFFFFFFF";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	::memcpy(APDU+5, hhmmssDB, 6);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if (RespLen != 2)
	{
		MessageBox(_T("糟糕！\n\n设置定时时间APDU执行失败！退出"));
		return;
	}
	if ((Resp[0] == 0x6A) && (Resp[1] == 0x81))
	{
		MessageBox(_T("通过S2S自动上报位置信息功能未打开！\n\n此时不支持设置定时时间APDU！退出"));
		return;
	}
	MessageBox(_T("恭喜您！\n\n设置定时时间执行成功！"));
}


void page5SetFuncDlg::OnBnClickedpage5closetimer()
{
	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//获取定时自动上传位置信息功能的时间间隔APDU
	sAPDU = "9981C10006FFFFFFFFFFFF";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if (RespLen != 2)
	{
		MessageBox(_T("糟糕！\n\n关闭定时器APDU执行失败！退出"));
		return;
	}
	if ((Resp[0] == 0x6A)&& (Resp[1] == 0x81))
	{
		MessageBox(_T("通过S2S自动上报位置信息功能未打开！\n\n此时不支持关闭定时器APDU！退出"));
		return;
	}
	MessageBox(_T("恭喜您！\n\n关闭定时器执行成功！"));
}

bool gFillOrClearOriginalFlag = false;
void page5SetFuncDlg::OnBnClickedpage5fillclearoriginalmccip()
{
	
	if (TRUE == gFillOrClearOriginalFlag) {
		int index = 0;
		while (index < 32) {
			edtCountry[index].SetWindowText("");
			edtMCC[index].SetWindowText("");
			edtIP[index].SetWindowText("");
			index++;
		}
		gFillOrClearOriginalFlag = FALSE;
	}
	else {
		edtCountry[0].SetWindowText("中国");
		edtMCC[0].SetWindowText("460");
		edtIP[0].SetWindowText("180.101.22.46");

		edtCountry[1].SetWindowText("德国1");
		edtMCC[1].SetWindowText("262");
		edtIP[1].SetWindowText("8.209.96.113");
		edtCountry[2].SetWindowText("德国2");
		edtMCC[2].SetWindowText("262");
		edtIP[2].SetWindowText("8.211.17.138");

		edtCountry[3].SetWindowText("英国1");
		edtMCC[3].SetWindowText("234");
		edtIP[3].SetWindowText("8.208.84.19");
		edtCountry[4].SetWindowText("英国2");
		edtMCC[4].SetWindowText("234");
		edtIP[4].SetWindowText("8.208.118.108");

		edtCountry[5].SetWindowText("美国1");
		edtMCC[5].SetWindowText("310");
		edtIP[5].SetWindowText("47.251.73.13");
		edtCountry[6].SetWindowText("美国2");
		edtMCC[6].SetWindowText("310");
		edtIP[6].SetWindowText("47.251.170.206");
		edtCountry[7].SetWindowText("美国3");
		edtMCC[7].SetWindowText("310");
		edtIP[7].SetWindowText("47.85.35.25");
		edtCountry[8].SetWindowText("美国4");
		edtMCC[8].SetWindowText("310");
		edtIP[8].SetWindowText("47.253.248.123");

		edtCountry[9].SetWindowText("加拿大1");
		edtMCC[9].SetWindowText("302");
		edtIP[9].SetWindowText("47.77.36.77");
		edtCountry[10].SetWindowText("加拿大2");
		edtMCC[10].SetWindowText("302");
		edtIP[10].SetWindowText("47.77.35.201");
		edtCountry[11].SetWindowText("加拿大3");
		edtMCC[11].SetWindowText("302");
		edtIP[11].SetWindowText("47.77.77.166");
		edtCountry[12].SetWindowText("加拿大4");
		edtMCC[12].SetWindowText("302");
		edtIP[12].SetWindowText("47.77.72.128");

		edtCountry[13].SetWindowText("墨西哥1");
		edtMCC[13].SetWindowText("334");
		edtIP[13].SetWindowText("47.87.14.75");
		edtCountry[14].SetWindowText("墨西哥2");
		edtMCC[14].SetWindowText("334");
		edtIP[14].SetWindowText("47.87.13.17");

		edtCountry[15].SetWindowText("中国香港1");
		edtMCC[15].SetWindowText("454");
		edtIP[15].SetWindowText("8.223.54.82");
		edtCountry[16].SetWindowText("中国香港2");
		edtMCC[16].SetWindowText("454");
		edtIP[16].SetWindowText("8.223.43.98");

		edtCountry[17].SetWindowText("日本1");
		edtMCC[17].SetWindowText("440");
		edtIP[17].SetWindowText("8.222.91.149");
		edtCountry[18].SetWindowText("日本2");
		edtMCC[18].SetWindowText("440");
		edtIP[18].SetWindowText("8.222.76.222");

		edtCountry[19].SetWindowText("新加坡1");
		edtMCC[19].SetWindowText("525");
		edtIP[19].SetWindowText("8.219.245.128");
		edtCountry[20].SetWindowText("新加坡2");
		edtMCC[20].SetWindowText("525");
		edtIP[20].SetWindowText("47.237.100.128");

		edtCountry[21].SetWindowText("马来西亚1");
		edtMCC[21].SetWindowText("502");
		edtIP[21].SetWindowText("47.254.247.12");
		edtCountry[22].SetWindowText("马来西亚2");
		edtMCC[22].SetWindowText("502");
		edtIP[22].SetWindowText("47.250.178.77");

		edtCountry[23].SetWindowText("印尼1");
		edtMCC[23].SetWindowText("510");
		edtIP[23].SetWindowText("8.215.41.77");
		edtCountry[24].SetWindowText("印尼2");
		edtMCC[24].SetWindowText("510");
		edtIP[24].SetWindowText("8.215.52.62");

		edtCountry[25].SetWindowText("菲律宾1");
		edtMCC[25].SetWindowText("515");
		edtIP[25].SetWindowText("8.212.162.44");
		edtCountry[26].SetWindowText("菲律宾2");
		edtMCC[26].SetWindowText("515");
		edtIP[26].SetWindowText("8.220.184.214");

		edtCountry[27].SetWindowText("韩国1");
		edtMCC[27].SetWindowText("450");
		edtIP[27].SetWindowText("8.220.193.7");
		edtCountry[28].SetWindowText("韩国2");
		edtMCC[28].SetWindowText("450");
		edtIP[28].SetWindowText("8.220.217.31");

		edtCountry[29].SetWindowText("泰国1");
		edtMCC[29].SetWindowText("520");
		edtIP[29].SetWindowText("8.213.193.166");
		edtCountry[30].SetWindowText("泰国2");
		edtMCC[30].SetWindowText("520");
		edtIP[30].SetWindowText("8.213.228.213");

		int index = 31;
		while (index < 32) {
			edtCountry[index].SetWindowText("");
			edtMCC[index].SetWindowText("");
			edtIP[index].SetWindowText("");
			index++;
		}

		gFillOrClearOriginalFlag = TRUE;
	}
}


void page5SetFuncDlg::OnBnClickedpage5clearmccip()
{
	CString dispErrStr;
	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	byte apdu_P2 = 0x00;
	byte thiswriteDataLen;
	unsigned short offset = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 1000;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//清空MCC列表APDU
	sAPDU = "9981140002FFFF";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	::memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if (RespLen != 2)
	{
		MessageBox(_T("糟糕！\n\n清空MCC列表APDU执行失败！退出"));
		return;
	}
	if (Resp[0] != 0x90)
	{
		dispErrStr.Format(_T("SW =0x%02X%02X\n\n糟糕！\n\n清空MCC列表APDU执行失败！退出"), Resp[0], Resp[1]);
		MessageBox(dispErrStr);
		return;
	}

	MessageBox(_T("恭喜您！\n\n清空MCC列表成功！退出"));

	int index = 0;
	while (index < 32) {
		edtCountry[index].SetWindowText("");
		edtMCC[index].SetWindowText("");
		edtIP[index].SetWindowText("");
		index++;
	}
	gFillOrClearOriginalFlag = FALSE;
}
