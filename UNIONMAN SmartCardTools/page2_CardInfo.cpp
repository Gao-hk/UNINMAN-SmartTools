#include "stdafx.h"
#include "page2_CardInfo.h"
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


#include   "..\SM4\sm4.h"




// PAGE2_CardInfo 对话框

page2CardInfoDlg::page2CardInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(page2CardInfoDlg::IDD, pParent)
{

}


void page2CardInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, btnGet, btnpcscGet);
	DDX_Control(pDX, btnSet, btnpcscSet);


	DDX_Control(pDX, btnGetVer, btnpcscGetVer);
	DDX_Control(pDX, btnSetSN, btnpcscGetSN);
	DDX_Control(pDX, btnGetSN, btnpcscSetSN);
	DDX_Control(pDX, btnSetSHAList, btnpcscGetSHAList);
	DDX_Control(pDX, btnGetSHAList, btnpcscSetSHAList);

	
	DDX_Control(pDX, edtSHA_00, edtpcscSHA_00);
	DDX_Control(pDX, edtSHA_10, edtpcscSHA_10);
	DDX_Control(pDX, edtSHA_20, edtpcscSHA_20);
	DDX_Control(pDX, edtSHA_30, edtpcscSHA_30);
	DDX_Control(pDX, edtSHA_40, edtpcscSHA_40);
	DDX_Control(pDX, edtSHA_50, edtpcscSHA_50);

	DDX_Control(pDX, edtSHA_01, edtpcscSHA_01);
	DDX_Control(pDX, edtSHA_11, edtpcscSHA_11);
	DDX_Control(pDX, edtSHA_21, edtpcscSHA_21);
	DDX_Control(pDX, edtSHA_31, edtpcscSHA_31);
	DDX_Control(pDX, edtSHA_41, edtpcscSHA_41);
	DDX_Control(pDX, edtSHA_51, edtpcscSHA_51);

	DDX_Control(pDX, edtSHA_02, edtpcscSHA_02);
	DDX_Control(pDX, edtSHA_12, edtpcscSHA_12);
	DDX_Control(pDX, edtSHA_22, edtpcscSHA_22);
	DDX_Control(pDX, edtSHA_32, edtpcscSHA_32);
	DDX_Control(pDX, edtSHA_42, edtpcscSHA_42);
	DDX_Control(pDX, edtSHA_52, edtpcscSHA_52);

	DDX_Control(pDX, edtSHA_03, edtpcscSHA_03);
	DDX_Control(pDX, edtSHA_13, edtpcscSHA_13);
	DDX_Control(pDX, edtSHA_23, edtpcscSHA_23);
	DDX_Control(pDX, edtSHA_33, edtpcscSHA_33);
	DDX_Control(pDX, edtSHA_43, edtpcscSHA_43);
	DDX_Control(pDX, edtSHA_53, edtpcscSHA_53);

	DDX_Control(pDX, edtCosVer, edtpcscCosVer);
	DDX_Control(pDX, edtSn, edtpcscSn);
	DDX_Control(pDX, edtStatus, edtpcscStatus);

	DDX_Control(pDX, btnGetIP, btnpcscGetIP);
	DDX_Control(pDX, btnSetIP, btnpcscSetIP);	

	DDX_Control(pDX, edtCosIP, edtpcscCosIP);
	DDX_Control(pDX, edtIP_11, edtpcscIP11);
	DDX_Control(pDX, edtIP_12, edtpcscIP12);
	DDX_Control(pDX, edtIP_13, edtpcscIP13);
	DDX_Control(pDX, edtIP_14, edtpcscIP14);
	DDX_Control(pDX, edtIP_15, edtpcscIP15);
	DDX_Control(pDX, edtIP_21, edtpcscIP21);
	DDX_Control(pDX, edtIP_22, edtpcscIP22);
	DDX_Control(pDX, edtIP_23, edtpcscIP23);
	DDX_Control(pDX, edtIP_24, edtpcscIP24);
	DDX_Control(pDX, edtIP_25, edtpcscIP25);
}


BEGIN_MESSAGE_MAP(page2CardInfoDlg, CDialogEx)
	ON_BN_CLICKED(btnGet, &page2CardInfoDlg::OnBnClickedbtnGet)
	ON_BN_CLICKED(btnSet, &page2CardInfoDlg::OnBnClickedbtnSet)

	ON_EN_CHANGE(edtAuthKey, &page2CardInfoDlg::OnChangeEdtauthkey)

	ON_EN_CHANGE(edtSHA_10, &page2CardInfoDlg::OnChangeEdtsha_10)
	ON_EN_CHANGE(edtSHA_20, &page2CardInfoDlg::OnChangeEdtsha_20)
	ON_EN_CHANGE(edtSHA_30, &page2CardInfoDlg::OnChangeEdtsha_30)
	ON_EN_CHANGE(edtSHA_40, &page2CardInfoDlg::OnChangeEdtsha_40)
	ON_EN_CHANGE(edtSHA_50, &page2CardInfoDlg::OnChangeEdtsha_50)

	ON_EN_CHANGE(edtSHA_11, &page2CardInfoDlg::OnChangeEdtsha_11)
	ON_EN_CHANGE(edtSHA_21, &page2CardInfoDlg::OnChangeEdtsha_21)
	ON_EN_CHANGE(edtSHA_31, &page2CardInfoDlg::OnChangeEdtsha_31)
	ON_EN_CHANGE(edtSHA_41, &page2CardInfoDlg::OnChangeEdtsha_41)
	ON_EN_CHANGE(edtSHA_51, &page2CardInfoDlg::OnChangeEdtsha_51)

	ON_EN_CHANGE(edtSHA_12, &page2CardInfoDlg::OnChangeEdtsha_12)
	ON_EN_CHANGE(edtSHA_22, &page2CardInfoDlg::OnChangeEdtsha_22)
	ON_EN_CHANGE(edtSHA_32, &page2CardInfoDlg::OnChangeEdtsha_32)
	ON_EN_CHANGE(edtSHA_42, &page2CardInfoDlg::OnChangeEdtsha_42)
	ON_EN_CHANGE(edtSHA_52, &page2CardInfoDlg::OnChangeEdtsha_52)

	ON_EN_CHANGE(edtSHA_13, &page2CardInfoDlg::OnChangeEdtsha_13)
	ON_EN_CHANGE(edtSHA_23, &page2CardInfoDlg::OnChangeEdtsha_23)
	ON_EN_CHANGE(edtSHA_33, &page2CardInfoDlg::OnChangeEdtsha_33)
	ON_EN_CHANGE(edtSHA_43, &page2CardInfoDlg::OnChangeEdtsha_43)
	ON_EN_CHANGE(edtSHA_53, &page2CardInfoDlg::OnChangeEdtsha_53)

	ON_EN_CHANGE(edtSn, &page2CardInfoDlg::OnChangeEdtsn)
	ON_BN_CLICKED(btnGetVer, &page2CardInfoDlg::OnBnClickedbtngetver)
	ON_BN_CLICKED(btnGetSN, &page2CardInfoDlg::OnBnClickedbtngetsn)
	ON_BN_CLICKED(btnSetSN, &page2CardInfoDlg::OnBnClickedbtnsetsn)
	ON_BN_CLICKED(btnGetSHAList, &page2CardInfoDlg::OnBnClickedbtngetshalist)
	ON_BN_CLICKED(btnSetSHAList, &page2CardInfoDlg::OnBnClickedbtnsetshalist)
	ON_BN_CLICKED(btnGetIP, &page2CardInfoDlg::OnBnClickedbtngetip)
	ON_BN_CLICKED(btnSetIP, &page2CardInfoDlg::OnBnClickedbtnsetip)
END_MESSAGE_MAP()





// PAGE2_CardInfo 消息处理程序

CString page2CardInfoDlg::swapBigEndandLittleEnd(byte* bByte, UINT iLength)
{
	byte* pValue = new byte[iLength+1];
	UINT j;
	char dataTemp;
	for (j = 0; j < iLength/2; j++)
	{
		dataTemp = bByte[j];
		pValue[j] = bByte[iLength - 1 - j];
		pValue[iLength - 1 - j] = dataTemp;
	}
	pValue[iLength] = 0;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();
	CString retStr= pDlg->Reader.HexToStr(pValue,iLength);
	delete[]pValue;
	return retStr;
}

void page2CardInfoDlg::getCardTypeInfo()
{
	edtpcscCosVer.SetWindowText(_T(""));
	edtpcscSn.SetWindowText(_T(""));
	edtpcscStatus.SetWindowText(_T(""));

	edtpcscSHA_10.SetWindowText(_T(""));
	edtpcscSHA_20.SetWindowText(_T(""));
	edtpcscSHA_30.SetWindowText(_T(""));
	edtpcscSHA_40.SetWindowText(_T(""));
	edtpcscSHA_50.SetWindowText(_T(""));

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();
	//Get Card Type
if ((pDlg->gAtrCosType == _T("boya_V2")) 
	|| (pDlg->gAtrCosType == _T("boyaSIM")) 
	//|| (pDlg->gAtrCosType == _T("boyaLOD"))
	)
	{
		edtpcscSn.SetReadOnly(false);    //设置为读写状态

		edtpcscSHA_10.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA_20.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA_30.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA_40.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA_50.SetReadOnly(false);    //设置为读写状态

		btnpcscGet.EnableWindow(TRUE);
		btnpcscSet.EnableWindow(TRUE);
		btnpcscGetVer.EnableWindow(TRUE);
		btnpcscGetSN.EnableWindow(TRUE);
		btnpcscSetSN.EnableWindow(TRUE);
		btnpcscGetSHAList.EnableWindow(TRUE);
		btnpcscSetSHAList.EnableWindow(TRUE);
	}
	else
	{		
		edtpcscSn.SetReadOnly(TRUE);    //设置为只读状态

		edtpcscSHA_10.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA_20.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA_30.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA_40.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA_50.SetReadOnly(TRUE);    //设置为只读状态

		btnpcscGet.EnableWindow(false);
		btnpcscSet.EnableWindow(false);
		btnpcscGetVer.EnableWindow(false);
		btnpcscGetSN.EnableWindow(false);
		btnpcscSetSN.EnableWindow(false);
		btnpcscGetSHAList.EnableWindow(false);
		btnpcscSetSHAList.EnableWindow(false);
	}
}

void page2CardInfoDlg::initCardInfoPage()
{
	//readSha1List();
	getCardTypeInfo();
}

boolean page2CardInfoDlg::checkMF()
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


void page2CardInfoDlg::OnBnClickedbtnGet()//Button：Get
{
	CString sAPDU,sAPDU2;
	byte APDU[5+256];
	byte Resp[256+2];
	byte readMacFlag=0;
	DWORD APDULen = 0;
	DWORD RespLen = 256+2;
	CString statusStr;
	CString strVer, strVerDisp;

	//清除上一次获取的信息
	edtpcscSHA_10.SetWindowText(_T(""));
	edtpcscSHA_20.SetWindowText(_T(""));
	edtpcscSHA_30.SetWindowText(_T(""));
	edtpcscSHA_40.SetWindowText(_T(""));
	edtpcscSHA_50.SetWindowText(_T(""));

	edtpcscStatus.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//Card Type
	if ((pDlg->gAtrCosType == _T("boya_V2")) || (pDlg->gAtrCosType == _T("boyaSIM")))
	{
	}
	else if (pDlg->gAtrCosType == _T("boyaLOD"))
	{
	}
	else
	{
		edtpcscStatus.SetWindowText(_T("对不起！ 当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	//读SHA1值
	sAPDU2 = "9901000564";
	APDULen = pDlg->Reader.StrToHex(sAPDU2, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}
	CString stringText1 = pDlg->Reader.HexToStr(Resp, 20);
	CString stringText2 = pDlg->Reader.HexToStr(Resp + 20, 20);
	CString stringText3 = pDlg->Reader.HexToStr(Resp + 40, 20);
	CString stringText4 = pDlg->Reader.HexToStr(Resp + 60, 20);
	CString stringText5 = pDlg->Reader.HexToStr(Resp + 80, 20);

	edtpcscSHA_10.SetWindowText(stringText1);
	edtpcscSHA_20.SetWindowText(stringText2);
	edtpcscSHA_30.SetWindowText(stringText3);
	edtpcscSHA_40.SetWindowText(stringText4);
	edtpcscSHA_50.SetWindowText(stringText5);

	edtpcscStatus.SetWindowText(_T("查询当前卡片SHA1信息成功！"));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}


bool page2CardInfoDlg::checkEdtSHA1_FillWithFF(void)
{
	if(0 == edtpcscSHA_10.GetWindowTextLength())
		edtpcscSHA_10.SetWindowText(_T("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"));
	if (0 == edtpcscSHA_20.GetWindowTextLength())
		edtpcscSHA_20.SetWindowText(_T("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"));
	if (0 == edtpcscSHA_30.GetWindowTextLength())
		edtpcscSHA_30.SetWindowText(_T("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"));
	if (0 == edtpcscSHA_40.GetWindowTextLength())
		edtpcscSHA_40.SetWindowText(_T("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"));
	if (0 == edtpcscSHA_50.GetWindowTextLength())
		edtpcscSHA_50.SetWindowText(_T("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"));

	if (40 != edtpcscSHA_10.GetWindowTextLength())
	{
		MessageBox(_T("Tag =‘10’的SHA1值长度不正确，\r\n请输入20字节的SHA1值！"));
		return false;
	}
	if (40 != edtpcscSHA_20.GetWindowTextLength())
	{
		MessageBox(_T("Tag =‘20’的SHA1值长度不正确，\r\n请输入20字节的SHA1值！"));
		return false;
	}
	if (40 != edtpcscSHA_30.GetWindowTextLength())
	{
		MessageBox(_T("Tag =‘30’的SHA1值长度不正确，\r\n请输入20字节的SHA1值！"));
		return false;
	}
	if (40 != edtpcscSHA_40.GetWindowTextLength())
	{
		MessageBox(_T("Tag =‘40’的SHA1值长度不正确，\r\n请输入20字节的SHA1值！"));
		return false;
	}
	if (40 != edtpcscSHA_50.GetWindowTextLength())
	{
		MessageBox(_T("Tag =‘50’的SHA1值长度不正确，\r\n请输入20字节的SHA1值！"));
		return false;
	}
	return true;
}

bool page2CardInfoDlg::checkEdtSHA1(void)
{
	if ((40 != edtpcscSHA_10.GetWindowTextLength()) && (0 != edtpcscSHA_10.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘10’的SHA1值长度不正确，\r\n请输入20字节的SHA1值！"));
		return false;
	}
	if ((40 != edtpcscSHA_20.GetWindowTextLength()) && (0 != edtpcscSHA_20.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘20’的SHA1值长度不正确，\r\n请输入20字节的SHA1值！"));
		return false;
	}
	if ((40 != edtpcscSHA_30.GetWindowTextLength()) && (0 != edtpcscSHA_30.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘30’的SHA1值长度不正确，\r\n请输入20字节的SHA1值！"));
		return false;
	}
	if ((40 != edtpcscSHA_40.GetWindowTextLength()) && (0 != edtpcscSHA_40.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘40’的SHA1值长度不正确，\r\n请输入20字节的SHA1值！"));
		return false;
	}
	if ((40 != edtpcscSHA_50.GetWindowTextLength()) && (0 != edtpcscSHA_50.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘50’的SHA1值长度不正确，\r\n请输入20字节的SHA1值！"));
		return false;
	}
	return true;
}

bool page2CardInfoDlg::checkEdtSHA256(void)
{
	if ((64 != edtpcscSHA_11.GetWindowTextLength()) && (0 != edtpcscSHA_11.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘11’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}
	if ((64 != edtpcscSHA_12.GetWindowTextLength()) && (0 != edtpcscSHA_12.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘12’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}
	if ((64 != edtpcscSHA_13.GetWindowTextLength()) && (0 != edtpcscSHA_13.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘13’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}

	if ((64 != edtpcscSHA_21.GetWindowTextLength()) && (0 != edtpcscSHA_21.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘21’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}
	if ((64 != edtpcscSHA_22.GetWindowTextLength()) && (0 != edtpcscSHA_22.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘22’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}
	if ((64 != edtpcscSHA_23.GetWindowTextLength()) && (0 != edtpcscSHA_23.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘23’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}

	if ((64 != edtpcscSHA_31.GetWindowTextLength()) && (0 != edtpcscSHA_31.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘31’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}
	if ((64 != edtpcscSHA_32.GetWindowTextLength()) && (0 != edtpcscSHA_32.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘32’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}
	if ((64 != edtpcscSHA_33.GetWindowTextLength()) && (0 != edtpcscSHA_33.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘33’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}

	if ((64 != edtpcscSHA_41.GetWindowTextLength()) && (0 != edtpcscSHA_41.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘41’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}
	if ((64 != edtpcscSHA_42.GetWindowTextLength()) && (0 != edtpcscSHA_42.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘42’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}
	if ((64 != edtpcscSHA_43.GetWindowTextLength()) && (0 != edtpcscSHA_43.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘43’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}

	if ((64 != edtpcscSHA_51.GetWindowTextLength()) && (0 != edtpcscSHA_51.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘51’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}
	if ((64 != edtpcscSHA_52.GetWindowTextLength()) && (0 != edtpcscSHA_52.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘52’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}
	if ((64 != edtpcscSHA_53.GetWindowTextLength()) && (0 != edtpcscSHA_53.GetWindowTextLength()))
	{
		MessageBox(_T("Tag =‘53’的SHA256值长度不正确，\r\n请输入32字节的SHA256值！"));
		return false;
	}

	return true;
}

void page2CardInfoDlg::OnBnClickedbtnSet()//Button：Set
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	edtpcscStatus.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	//Get Card Type
	if ((pDlg->gAtrCosType == _T("boya_V2"))
		|| (pDlg->gAtrCosType == _T("boyaSIM"))
		|| (pDlg->gAtrCosType == _T("boyaLOD"))
		)
	{
		if (false == checkEdtSHA1_FillWithFF())
			return;
		
		CString bleMac, sppMac, macStr, sha1Str1, sha1Str2, sha1Str3, sha1Str4, sha1Str5, sha1_5Str;
		edtpcscSHA_10.GetWindowText(sha1Str1);
		edtpcscSHA_20.GetWindowText(sha1Str2);
		edtpcscSHA_30.GetWindowText(sha1Str3);
		edtpcscSHA_40.GetWindowText(sha1Str4);
		edtpcscSHA_50.GetWindowText(sha1Str5);

		sha1_5Str.Format(_T("%s %s %s %s %s"), sha1Str1, sha1Str2, sha1Str3, sha1Str4, sha1Str5);

		CString sAPDU, sAPDU2;
		byte APDU[5 + 256];
		byte Resp[256 + 2];
		byte readMacFlag = 0;
		DWORD APDULen = 0;
		DWORD RespLen = 256 + 2;
		
		//SHA1_5
		sAPDU.Format(_T("%s %s"), _T("9981030064"), sha1_5Str);
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return;
		}
		if (Resp[0] != 0x90)
		{
			MessageBox(_T("SetCardInfo执行写入SHA1失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			return;
		}
		
		//MessageBox(_T("恭喜您！\r\nSetCardInfo执行成功！"));

		edtpcscStatus.SetWindowText(_T("恭喜您！ SetSHA1执行成功！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	else
	{
		MessageBox(_T("对不起！\r\n当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));

		edtpcscStatus.SetWindowText(_T("对不起！ 当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
}

std::wstring AnsiToUnicode(const std::string& strAnsi)
{
	//获取转换所需的接收缓冲区大小
	int  nUnicodeLen = ::MultiByteToWideChar(CP_ACP,
		0,
		strAnsi.c_str(),
		-1,
		NULL,
		0);
	//分配指定大小的内存
	wchar_t* pUnicode = new wchar_t[nUnicodeLen + 1];
	memset((void*)pUnicode, 0, (nUnicodeLen + 1) * sizeof(wchar_t));

	//转换
	::MultiByteToWideChar(CP_ACP,
		0,
		strAnsi.c_str(),
		-1,
		(LPWSTR)pUnicode,
		nUnicodeLen);

	std::wstring  strUnicode;
	strUnicode = (wchar_t*)pUnicode;
	delete[]pUnicode;

	return strUnicode;
}

extern void AnsiToUtf8(char* lpcszStr, char* lpwszStr);
extern void Utf8ToAnsi(char* lpcszStr, char* lpwszStr);

void page2CardInfoDlg::CheckInputDataLength(int editIDC, DWORD maxLen)
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
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
}

void page2CardInfoDlg::OnChangeEdtauthkey()
{
	CheckInputDataLength(edtAuthKey, 32);
}

void page2CardInfoDlg::OnChangeEdtsha_10()
{
	CheckInputDataLength(edtSHA_10, 40);
}
void page2CardInfoDlg::OnChangeEdtsha_20()
{
	CheckInputDataLength(edtSHA_20, 40);
}
void page2CardInfoDlg::OnChangeEdtsha_30()
{
	CheckInputDataLength(edtSHA_30, 40);
}
void page2CardInfoDlg::OnChangeEdtsha_40()
{
	CheckInputDataLength(edtSHA_40, 40);
}
void page2CardInfoDlg::OnChangeEdtsha_50()
{
	CheckInputDataLength(edtSHA_50, 40);
}


void page2CardInfoDlg::OnChangeEdtsha_11()
{
	CheckInputDataLength(edtSHA_11, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_21()
{
	CheckInputDataLength(edtSHA_21, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_31()
{
	CheckInputDataLength(edtSHA_31, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_41()
{
	CheckInputDataLength(edtSHA_41, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_51()
{
	CheckInputDataLength(edtSHA_51, 64);
}

void page2CardInfoDlg::OnChangeEdtsha_12()
{
	CheckInputDataLength(edtSHA_12, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_22()
{
	CheckInputDataLength(edtSHA_22, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_32()
{
	CheckInputDataLength(edtSHA_32, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_42()
{
	CheckInputDataLength(edtSHA_42, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_52()
{
	CheckInputDataLength(edtSHA_52, 64);
}

void page2CardInfoDlg::OnChangeEdtsha_13()
{
	CheckInputDataLength(edtSHA_13, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_23()
{
	CheckInputDataLength(edtSHA_23, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_33()
{
	CheckInputDataLength(edtSHA_33, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_43()
{
	CheckInputDataLength(edtSHA_43, 64);
}
void page2CardInfoDlg::OnChangeEdtsha_53()
{
	CheckInputDataLength(edtSHA_53, 64);
}

void page2CardInfoDlg::OnChangeEdtsn()
{
	CheckInputDataLength(edtSn, 16);
}

void page2CardInfoDlg::OnBnClickedbtngetver()
{
	// TODO:  在此添加控件通知处理程序代码
	CString sAPDU, sAPDU2;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString statusStr;
	CString strVer, strVerDisp;

	//清除上一次获取的信息
	edtpcscCosVer.SetWindowText(_T(""));
	edtpcscStatus.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();


	//Card Type
	if ((pDlg->gAtrCosType == _T("boya_V2")) || (pDlg->gAtrCosType == _T("boyaSIM")))
	{
		//Get COS Ver
		sAPDU = "9901000206";
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
		if (RespLen == 2)
		{
			sAPDU = "9901000202";
			APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
			RespLen = 256 + 2;
			memset(Resp, 0, RespLen);
			if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
			{
				edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
				edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				return;
			}
			strVerDisp = _T("boyaSmartCOS V") + pDlg->Reader.HexToStr(Resp, 1) + _T(".") + pDlg->Reader.HexToStr(Resp + 1, 1);
		}
		else
		{
			//ST1_Firmware_0.2.4_20241021
			//ST1_Firmware_0.2.4_RC01_20241021

			strVer = pDlg->Reader.HexToStr(Resp, 6);
			strVerDisp = _T("ST1_Firmware_") + strVer.Left(1) + _T(".") + strVer.Mid(1, 1) + _T(".") + strVer.Mid(2, 1) + _T("_");
			if (strVer.Mid(3, 1) != '0')
				strVerDisp = strVerDisp + _T("RC0") + strVer.Mid(3, 1) + _T("_");
			strVerDisp = strVerDisp + strVer.Mid(4, 8);
		}
		edtpcscCosVer.SetWindowText(strVerDisp);
	}
	else if (pDlg->gAtrCosType == _T("boyaLOD"))
	{
		strVerDisp = _T("boyaLoader V") + pDlg->Reader.HexToStr(Resp, 1) + _T(".") + pDlg->Reader.HexToStr(Resp + 1, 1);
		edtpcscCosVer.SetWindowText(strVerDisp);
	}
	else
	{
		edtpcscStatus.SetWindowText(_T("对不起！ 当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	edtpcscStatus.SetWindowText(_T("查询当前卡片Ver信息成功！"));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}

void page2CardInfoDlg::OnBnClickedbtngetsn()
{
	// TODO:  在此添加控件通知处理程序代码
	CString sAPDU, sAPDU2;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString statusStr;
	CString strVer, strVerDisp;

	//清除上一次获取的信息
	edtpcscSn.SetWindowText(_T(""));
	edtpcscStatus.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();


	//Card Type
	if ((pDlg->gAtrCosType == _T("boya_V2")) || (pDlg->gAtrCosType == _T("boyaSIM")))
	{
	}
	else if (pDlg->gAtrCosType == _T("boyaLOD"))
	{
	}
	else
	{
		edtpcscStatus.SetWindowText(_T("对不起！ 当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	//Get SN
	sAPDU = "9901000108";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	edtpcscSn.SetWindowText(pDlg->Reader.HexToStr(Resp, 8));

	edtpcscStatus.SetWindowText(_T("查询当前卡片SN信息成功！"));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}

void page2CardInfoDlg::OnBnClickedbtnsetsn()
{
	// TODO:  在此添加控件通知处理程序代码

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	edtpcscStatus.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	//Get Card Type
	if ((pDlg->gAtrCosType == _T("boya_V2"))
		|| (pDlg->gAtrCosType == _T("boyaSIM"))
		|| (pDlg->gAtrCosType == _T("boyaLOD"))
		)
	{
		if ((16 != edtpcscSn.GetWindowTextLength())&& (8 != edtpcscSn.GetWindowTextLength()))
		{
			MessageBox(_T("SN的长度不正确，\r\n请输入完整的16位SN，或者8位的ID！"));
			return;
		}
		CString snStr;
		edtpcscSn.GetWindowText(snStr);

		CString sAPDU, sAPDU2;
		byte APDU[5 + 256];
		byte Resp[256 + 2];
		byte readMacFlag = 0;
		DWORD APDULen = 0;
		DWORD RespLen = 256 + 2;
		//SN 
		if (16 == edtpcscSn.GetWindowTextLength())
		{
			sAPDU.Format(_T("%s %s"), _T("9981010008"), snStr);
			APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
			RespLen = 256 + 2;
			memset(Resp, 0, RespLen);
			if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
			{
				edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
				edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				MessageBox(pDlg->Reader.GetError());
				return;
			}
			if (Resp[0] != 0x90)
			{
				MessageBox(_T("SetCardInfo执行SetSN失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}
			edtpcscStatus.SetWindowText(_T("恭喜您！ SetSN执行成功！"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		else
		{
			sAPDU.Format(_T("%s %s"), _T("998110000588"), snStr);
			APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
			RespLen = 256 + 2;
			memset(Resp, 0, RespLen);
			if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
			{
				edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
				edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				MessageBox(pDlg->Reader.GetError());
				return;
			}
			if ((Resp[0] != 0x61) || (Resp[1] != 0x08))
			{
				MessageBox(_T("SetCardInfo执行SetRandomSN失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}
			edtpcscStatus.SetWindowText(_T("恭喜您！ SetRandomSN执行成功！"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}		
	}
	else
	{
		MessageBox(_T("对不起！\r\n当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));

		edtpcscStatus.SetWindowText(_T("对不起！ 当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
}

void page2CardInfoDlg::OnBnClickedbtngetshalist()
{
	CString sAPDU, sAPDU2;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString statusStr;
	CString strVer, strVerDisp;

	//清除上一次获取的信息
	edtpcscSHA_00.SetWindowText(_T(""));
	edtpcscSHA_10.SetWindowText(_T(""));
	edtpcscSHA_20.SetWindowText(_T(""));
	edtpcscSHA_30.SetWindowText(_T(""));
	edtpcscSHA_40.SetWindowText(_T(""));
	edtpcscSHA_50.SetWindowText(_T(""));

	edtpcscSHA_01.SetWindowText(_T(""));
	edtpcscSHA_11.SetWindowText(_T(""));
	edtpcscSHA_21.SetWindowText(_T(""));
	edtpcscSHA_31.SetWindowText(_T(""));
	edtpcscSHA_41.SetWindowText(_T(""));
	edtpcscSHA_51.SetWindowText(_T(""));

	edtpcscSHA_02.SetWindowText(_T(""));
	edtpcscSHA_12.SetWindowText(_T(""));
	edtpcscSHA_22.SetWindowText(_T(""));
	edtpcscSHA_32.SetWindowText(_T(""));
	edtpcscSHA_42.SetWindowText(_T(""));
	edtpcscSHA_52.SetWindowText(_T(""));

	edtpcscSHA_03.SetWindowText(_T(""));
	edtpcscSHA_13.SetWindowText(_T(""));
	edtpcscSHA_23.SetWindowText(_T(""));
	edtpcscSHA_33.SetWindowText(_T(""));
	edtpcscSHA_43.SetWindowText(_T(""));
	edtpcscSHA_53.SetWindowText(_T(""));

	edtpcscStatus.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//Card Type
	if ((pDlg->gAtrCosType == _T("boya_V2")) || (pDlg->gAtrCosType == _T("boyaSIM")))
	{
	}
	else if (pDlg->gAtrCosType == _T("boyaLOD"))
	{
	}
	else
	{
		edtpcscStatus.SetWindowText(_T("对不起！ 当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	//读SHAList值
	byte SHAListTLV[2048];
	int SHAListTLV_Len = 0;

	sAPDU2 = "9901000600";

	Continue_GetSHAList_Label:
	APDULen = pDlg->Reader.StrToHex(sAPDU2, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	if (RespLen == 2)
	{
		if (Resp[0] != 0x6C)
		{
			MessageBox(_T("执行读SHAList失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			return;
		}
		APDU[4] = Resp[1];
		RespLen = 256 + 2;
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
	}
	memcpy(SHAListTLV + SHAListTLV_Len, Resp, RespLen-2);
	SHAListTLV_Len += RespLen - 2;
	if (256 == RespLen - 2)
	{
		sAPDU2 = "9901000700";
		goto Continue_GetSHAList_Label;
	}

	//开始处理TLV结构的SHAList数据
	int index = 0;
	byte thisTag, thisLen;
	CString stringSHA;

	while (index < SHAListTLV_Len)
	{
		thisTag = SHAListTLV[index++];
		thisLen = SHAListTLV[index++];
		stringSHA = pDlg->Reader.HexToStr(SHAListTLV + index, thisLen);
		index += thisLen;

		switch (thisTag)
		{
		case 0x00:
			edtpcscSHA_00.SetWindowText(stringSHA);
			break;

		case 0x01:
			edtpcscSHA_01.SetWindowText(stringSHA);
			break;

		case 0x02:
			edtpcscSHA_02.SetWindowText(stringSHA);
			break;

		case 0x03:
			edtpcscSHA_03.SetWindowText(stringSHA);
			break;

		case 0x10:
			edtpcscSHA_10.SetWindowText(stringSHA);
			break;

		case 0x11:
			edtpcscSHA_11.SetWindowText(stringSHA);
			break;

		case 0x12:
			edtpcscSHA_12.SetWindowText(stringSHA);
			break;

		case 0x13:
			edtpcscSHA_13.SetWindowText(stringSHA);
			break;

		case 0x20:
			edtpcscSHA_20.SetWindowText(stringSHA);
			break;

		case 0x21:
			edtpcscSHA_21.SetWindowText(stringSHA);
			break;

		case 0x22:
			edtpcscSHA_22.SetWindowText(stringSHA);
			break;

		case 0x23:
			edtpcscSHA_23.SetWindowText(stringSHA);
			break;

		case 0x30:
			edtpcscSHA_30.SetWindowText(stringSHA);
			break;

		case 0x31:
			edtpcscSHA_31.SetWindowText(stringSHA);
			break;

		case 0x32:
			edtpcscSHA_32.SetWindowText(stringSHA);
			break;

		case 0x33:
			edtpcscSHA_33.SetWindowText(stringSHA);
			break;

		case 0x40:
			edtpcscSHA_40.SetWindowText(stringSHA);
			break;

		case 0x41:
			edtpcscSHA_41.SetWindowText(stringSHA);
			break;

		case 0x42:
			edtpcscSHA_42.SetWindowText(stringSHA);
			break;

		case 0x43:
			edtpcscSHA_43.SetWindowText(stringSHA);
			break;

		case 0x50:
			edtpcscSHA_50.SetWindowText(stringSHA);
			break;

		case 0x51:
			edtpcscSHA_51.SetWindowText(stringSHA);
			break;

		case 0x52:
			edtpcscSHA_52.SetWindowText(stringSHA);
			break;

		case 0x53:
			edtpcscSHA_53.SetWindowText(stringSHA);
			break;
		}
	}

	edtpcscStatus.SetWindowText(_T("查询当前卡片SHA1信息成功！"));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}

void page2CardInfoDlg::OnBnClickedbtnsetshalist()
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	edtpcscStatus.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	//Get Card Type
	if ((pDlg->gAtrCosType == _T("boya_V2"))
		|| (pDlg->gAtrCosType == _T("boyaSIM"))
		|| (pDlg->gAtrCosType == _T("boyaLOD"))
		)
	{
		if (false == checkEdtSHA1())
			return;
		if (false == checkEdtSHA256())
			return;

		CString sAPDU, sAPDU2;
		byte APDU[5 + 256];
		byte Resp[256 + 2];
		byte readMacFlag = 0;
		DWORD APDULen = 0;
		DWORD RespLen = 256 + 2;
		sAPDU.Format(_T("%s"), _T("99810600"));
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);		

		//开始获取SHAList数据，组成TLV
		byte SHAListTLV[2048];
		int SHAListTLVLen = 0;
		int index;
		byte thisTag;
		byte thisLen;
		CString thisStr;

		thisTag = 0x10;	//从10开始
		index = 0;	//从0开始
		//SHAList

		while (0xFF != thisTag)
		{
			switch (thisTag)
			{
			case 0x10:
				if (40 == edtpcscSHA_10.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 20;
					edtpcscSHA_10.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV+index);
					index += thisLen;
				}
				thisTag = 0x11;
				break;

			case 0x11:
				if (64 == edtpcscSHA_11.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_11.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x12;
				break;

			case 0x12:
				if (64 == edtpcscSHA_12.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_12.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x13;
				break;

			case 0x13:
				if (64 == edtpcscSHA_13.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_13.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x20;
				break;

			case 0x20:
				if (40 == edtpcscSHA_20.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 20;
					edtpcscSHA_20.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x21;
				break;

			case 0x21:
				if (64 == edtpcscSHA_21.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_21.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x22;
				break;

			case 0x22:
				if (64 == edtpcscSHA_22.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_22.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x23;
				break;

			case 0x23:
				if (64 == edtpcscSHA_23.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_23.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x30;
				break;

			case 0x30:
				if (40 == edtpcscSHA_30.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 20;
					edtpcscSHA_30.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x31;
				break;

			case 0x31:
				if (64 == edtpcscSHA_31.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_31.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x32;
				break;

			case 0x32:
				if (64 == edtpcscSHA_32.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_32.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x33;
				break;

			case 0x33:
				if (64 == edtpcscSHA_33.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_33.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x40;
				break;

			case 0x40:
				if (40 == edtpcscSHA_40.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 20;
					edtpcscSHA_40.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x41;
				break;

			case 0x41:
				if (64 == edtpcscSHA_41.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_41.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x42;
				break;

			case 0x42:
				if (64 == edtpcscSHA_42.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_42.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x43;
				break;

			case 0x43:
				if (64 == edtpcscSHA_43.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_43.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x50;
				break;

			case 0x50:
				if (40 == edtpcscSHA_50.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 20;
					edtpcscSHA_50.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x51;
				break;

			case 0x51:
				if (64 == edtpcscSHA_51.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_51.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x52;
				break;

			case 0x52:
				if (64 == edtpcscSHA_52.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_52.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0x53;
				break;

			case 0x53:
				if (64 == edtpcscSHA_53.GetWindowTextLength())
				{
					SHAListTLV[index++] = thisTag;
					SHAListTLV[index++] = thisLen = 32;
					edtpcscSHA_53.GetWindowText(thisStr);
					pDlg->Reader.StrToHex(thisStr, SHAListTLV + index);
					index += thisLen;
				}
				thisTag = 0xFF;//本次循环执行完后退出
				break;
			}

			if (index > 255 - 32 + 2)
			{
				APDU[4] = index;
				APDULen = 5 + APDU[4];
				memcpy(APDU + 5, SHAListTLV, APDU[4]);
				RespLen = 256 + 2;
				memset(Resp, 0, RespLen);
				if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
				{
					edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
					edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
					MessageBox(pDlg->Reader.GetError());
					return;
				}
				if (Resp[0] != 0x90)
				{
					MessageBox(_T("执行Set SHAList失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					return;
				}
				index = 0;	//从0开始
			}
		}

		if (index)
		{
			APDU[4] = index;
			APDULen = 5 + APDU[4];
			memcpy(APDU + 5, SHAListTLV, APDU[4]);
			RespLen = 256 + 2;
			memset(Resp, 0, RespLen);
			if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
			{
				edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
				edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				MessageBox(pDlg->Reader.GetError());
				return;
			}
			if (Resp[0] != 0x90)
			{
				MessageBox(_T("执行Set SHAList失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}
			index = 0;
			edtpcscStatus.SetWindowText(_T("恭喜您！ SetSHA1执行成功！"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		else
		{
			MessageBox(_T("未执行SetSHA1：\r\n\r\n还没有设置SHA1、SHA256"));
			return;
		}
	}
	else
	{
		MessageBox(_T("对不起！\r\n当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));

		edtpcscStatus.SetWindowText(_T("对不起！ 当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
}


CString Hex2DecStr(int value)
{
	char str[8];
	CString dispStr;
	_itoa_s(value, str, 8, 10); // 第三个参数是目标字符串的大小，10代表十进制
	dispStr = str;
	return dispStr;
}


void page2CardInfoDlg::OnBnClickedbtngetip()
{
	CString sAPDU, sAPDU2;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString statusStr;
	CString strVer, strVerDisp;

	//清除上一次获取的信息
	edtpcscCosIP.SetWindowText(_T(""));
	edtpcscIP11.SetWindowText(_T(""));
	edtpcscIP12.SetWindowText(_T(""));
	edtpcscIP13.SetWindowText(_T(""));
	edtpcscIP14.SetWindowText(_T(""));
	edtpcscIP15.SetWindowText(_T(""));
	edtpcscIP21.SetWindowText(_T(""));
	edtpcscIP22.SetWindowText(_T(""));
	edtpcscIP23.SetWindowText(_T(""));
	edtpcscIP24.SetWindowText(_T(""));
	edtpcscIP25.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();


	//Card Type
	if ((pDlg->gAtrCosType == _T("boya_V2")) || (pDlg->gAtrCosType == _T("boyaSIM")))
	{
	}
	else if (pDlg->gAtrCosType == _T("boyaLOD"))
	{
	}
	else
	{
		edtpcscStatus.SetWindowText(_T("对不起！ 当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	//Get IP
	sAPDU = "9901001110";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}
	if (RespLen == 2)
	{
		CString disp = _T("执行读GetIP失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
		MessageBox(disp);
		edtpcscStatus.SetWindowText(disp);
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}
	if ((Resp[0] == 0xA5) && (Resp[1] == 0x5A))
	{
		//不显示固件自带的IP地址
		//显示IP1
		edtpcscIP11.SetWindowText(Hex2DecStr(Resp[2]));
		edtpcscIP12.SetWindowText(Hex2DecStr(Resp[3]));
		edtpcscIP13.SetWindowText(Hex2DecStr(Resp[4]));
		edtpcscIP14.SetWindowText(Hex2DecStr(Resp[5]));
		edtpcscIP15.SetWindowText(Hex2DecStr(Resp[6]*256+ Resp[7]));
		if ((Resp[8 + 0] == 0xA5) && (Resp[8 + 1] == 0x5A))
		{
			//显示IP2
			edtpcscIP11.SetWindowText(Hex2DecStr(Resp[8 + 2]));
			edtpcscIP12.SetWindowText(Hex2DecStr(Resp[8 + 3]));
			edtpcscIP13.SetWindowText(Hex2DecStr(Resp[8 + 4]));
			edtpcscIP14.SetWindowText(Hex2DecStr(Resp[8 + 5]));
			edtpcscIP15.SetWindowText(Hex2DecStr(Resp[8 + 6] * 256 + Resp[8 + 7]));
		}
	}
	else
	{
		//显示固件自带的IP地址，180.101.22.46:7777
		edtpcscCosIP.SetWindowText(_T("180.101.22.46:7777"));
	}	

	edtpcscStatus.SetWindowText(_T("查询当前卡片IP地址信息成功！"));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}


CString decToHex1(char* decStr)
{
	int dec = atoi(decStr);
	CString hexStr;

	hexStr.Format("%02x", dec);
	return hexStr;
}
CString decToHex2(char* decStr)
{
	int dec = atoi(decStr);
	CString hexStr;

	hexStr.Format("%04x", dec);
	return hexStr;
}


CString getOnePartOfIP(CString strIP)
{
	return decToHex1(strIP.GetBuffer(strIP.GetLength()));
}
CString getPORT(CString strPORT)
{
	return decToHex2(strPORT.GetBuffer(strPORT.GetLength()));
}

void page2CardInfoDlg::OnBnClickedbtnsetip()
{
	CString strIP11, strIP12, strIP13, strIP14, strPort1;
	CString strIP21, strIP22, strIP23, strIP24, strPort2;

	CString sAPDU, sAPDU2;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString statusStr;
	CString strIP = "";
	bool setIP2Flag = false;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	edtpcscStatus.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	//Get Card Type
	if ((pDlg->gAtrCosType == _T("boya_V2"))
		|| (pDlg->gAtrCosType == _T("boyaSIM"))
		|| (pDlg->gAtrCosType == _T("boyaLOD"))
		)
	{
		if ( (0 == edtpcscIP11.GetWindowTextLength()) 
			|| (0 == edtpcscIP12.GetWindowTextLength())
			|| (0 == edtpcscIP13.GetWindowTextLength())
			|| (0 == edtpcscIP14.GetWindowTextLength())
			|| (0 == edtpcscIP15.GetWindowTextLength())
			)
		{
			MessageBox(_T("请输入IP1地址、PORT！"));
			return;
		}

		edtpcscIP11.GetWindowText(strIP11);
		edtpcscIP12.GetWindowText(strIP12);
		edtpcscIP13.GetWindowText(strIP13);
		edtpcscIP14.GetWindowText(strIP14);
		edtpcscIP15.GetWindowText(strPort1);

		APDU[0] = 0x99;
		APDU[1] = 0x81;
		APDU[2] = 0x11;
		APDU[3] = 0x00;
		APDU[4] = 0x06;
		strIP = getOnePartOfIP(strIP11) + getOnePartOfIP(strIP12) + getOnePartOfIP(strIP13) + getOnePartOfIP(strIP14) + getPORT(strPort1);

		if ((0 == edtpcscIP21.GetWindowTextLength())
			|| (0 == edtpcscIP22.GetWindowTextLength())
			|| (0 == edtpcscIP23.GetWindowTextLength())
			|| (0 == edtpcscIP24.GetWindowTextLength())
			|| (0 == edtpcscIP25.GetWindowTextLength())
			)
		{
		}
		else
		{
			edtpcscIP21.GetWindowText(strIP21);
			edtpcscIP22.GetWindowText(strIP22);
			edtpcscIP23.GetWindowText(strIP23);
			edtpcscIP24.GetWindowText(strIP24);
			edtpcscIP25.GetWindowText(strPort2);

			APDU[4] += 6;
			strIP += getOnePartOfIP(strIP21) + getOnePartOfIP(strIP22) + getOnePartOfIP(strIP23) + getOnePartOfIP(strIP24) + getPORT(strPort2);
		}
	
		APDULen = 5 + pDlg->Reader.StrToHex(strIP, APDU + 5);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return;
		}
		if (Resp[0] != 0x61)
		{
			MessageBox(_T("执行SetIP失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			return;
		}
		edtpcscStatus.SetWindowText(_T("恭喜您！ SetIP执行成功！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	else
	{
		MessageBox(_T("对不起！\r\n当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));

		edtpcscStatus.SetWindowText(_T("对不起！ 当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
}
