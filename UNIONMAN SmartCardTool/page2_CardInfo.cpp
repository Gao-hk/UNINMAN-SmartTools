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

	DDX_Control(pDX, edtBLE, edtpcscBLE);
	DDX_Control(pDX, edtSPP, edtpcscSPP);
	
	DDX_Control(pDX, edtAuthKey, edtpcscAuthKey);

	DDX_Control(pDX, edtSHA1_1, edtpcscSHA1_1);
	DDX_Control(pDX, edtSHA1_2, edtpcscSHA1_2);
	DDX_Control(pDX, edtSHA1_3, edtpcscSHA1_3);
	DDX_Control(pDX, edtSHA1_4, edtpcscSHA1_4);
	DDX_Control(pDX, edtSHA1_5, edtpcscSHA1_5);

	
	DDX_Control(pDX, comboSha1List1, combopcscSha1List1);
	DDX_Control(pDX, comboSha1List2, combopcscSha1List2);
	DDX_Control(pDX, comboSha1List3, combopcscSha1List3);
	DDX_Control(pDX, comboSha1List4, combopcscSha1List4);
	DDX_Control(pDX, comboSha1List5, combopcscSha1List5);

	DDX_Control(pDX, edtCosVer, edtpcscCosVer);
	DDX_Control(pDX, edtSn, edtpcscSn);
	DDX_Control(pDX, edtStatus, edtpcscStatus);
}


BEGIN_MESSAGE_MAP(page2CardInfoDlg, CDialogEx)
	ON_BN_CLICKED(btnGet, &page2CardInfoDlg::OnBnClickedbtnGet)
	ON_BN_CLICKED(btnSet, &page2CardInfoDlg::OnBnClickedbtnSet)
	ON_CBN_SELCHANGE(comboSha1List1, &page2CardInfoDlg::OnCbnSelchangecombosha1list1)
	ON_CBN_SELCHANGE(comboSha1List2, &page2CardInfoDlg::OnCbnSelchangecombosha1list2)
	ON_CBN_SELCHANGE(comboSha1List3, &page2CardInfoDlg::OnCbnSelchangecombosha1list3)
	ON_CBN_SELCHANGE(comboSha1List4, &page2CardInfoDlg::OnCbnSelchangecombosha1list4)
	ON_CBN_SELCHANGE(comboSha1List5, &page2CardInfoDlg::OnCbnSelchangecombosha1list5)

	ON_BN_CLICKED(radioMT1, &page2CardInfoDlg::OnBnClickedradiomt1)
	ON_BN_CLICKED(radioMT211, &page2CardInfoDlg::OnBnClickedradiomt211)
	ON_BN_CLICKED(radioMT222A, &page2CardInfoDlg::OnBnClickedradiomt222a)
	ON_BN_CLICKED(radioMT222C, &page2CardInfoDlg::OnBnClickedradiomt222c)
	ON_EN_CHANGE(edtBLE, &page2CardInfoDlg::OnChangeEdtble)
	ON_EN_CHANGE(edtAuthKey, &page2CardInfoDlg::OnChangeEdtauthkey)
	ON_EN_CHANGE(edtSHA1_1, &page2CardInfoDlg::OnChangeEdtsha11)
	ON_EN_CHANGE(edtSHA1_2, &page2CardInfoDlg::OnChangeEdtsha12)
	ON_EN_CHANGE(edtSHA1_3, &page2CardInfoDlg::OnChangeEdtsha13)
	ON_EN_CHANGE(edtSHA1_4, &page2CardInfoDlg::OnChangeEdtsha14)
	ON_EN_CHANGE(edtSHA1_5, &page2CardInfoDlg::OnChangeEdtsha15)
	ON_EN_CHANGE(edtSn, &page2CardInfoDlg::OnChangeEdtsn)
	ON_EN_CHANGE(edtSPP, &page2CardInfoDlg::OnChangeEdtspp)
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

int page2CardInfoDlg::readSha1List()
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	const char* filepath2 = pDlg->sha1filepath;// "SHA1_List.csv";

	combopcscSha1List1.ResetContent();
	combopcscSha1List2.ResetContent();
	combopcscSha1List3.ResetContent();
	combopcscSha1List4.ResetContent();
	combopcscSha1List5.ResetContent();

	struct _stat info;
	_stat(filepath2, &info);
	int fileSize = info.st_size;
	char insertFlag=0;


	// 读文件
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
			combopcscSha1List1.InsertString(-1, substr[1]);
			combopcscSha1List2.InsertString(-1, substr[1]);
			combopcscSha1List3.InsertString(-1, substr[1]);
			combopcscSha1List4.InsertString(-1, substr[1]);
			combopcscSha1List5.InsertString(-1, substr[1]);
		}
	}
	file.Close();

	return 0;
}
void page2CardInfoDlg::getCardTypeInfo()
{
	edtpcscBLE.SetWindowText(_T(""));
	edtpcscSPP.SetWindowText(_T(""));

	edtpcscCosVer.SetWindowText(_T(""));
	edtpcscSn.SetWindowText(_T(""));
	edtpcscStatus.SetWindowText(_T(""));

	edtpcscSHA1_1.SetWindowText(_T(""));
	edtpcscSHA1_2.SetWindowText(_T(""));
	edtpcscSHA1_3.SetWindowText(_T(""));
	edtpcscSHA1_4.SetWindowText(_T(""));
	edtpcscSHA1_5.SetWindowText(_T(""));

	edtpcscAuthKey.SetWindowText(_T("4D462D45544B4D462D45544B4D462D45"));//"MF-ETKMF-ETKMF-E"

	edtpcscAuthKey.ShowWindow(TRUE);

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	((CButton*)GetDlgItem(radioMT1))->SetCheck(false);
	((CButton*)GetDlgItem(radioMT211))->SetCheck(false);
	((CButton*)GetDlgItem(radioMT222A))->SetCheck(false);
	((CButton*)GetDlgItem(radioMT222C))->SetCheck(false);
	//Get Card Type
	if ((pDlg->gAtrCosType == _T("MT1_COS"))
		|| (pDlg->gAtrCosType == _T("MT1_SKF"))
		)
	{
		((CButton*)GetDlgItem(radioMT1))->SetCheck(TRUE); //选上
		radioFlag = _T("MT1");
		((CButton*)GetDlgItem(radioMT1))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222A))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222C))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT211))->EnableWindow(false);

		edtpcscBLE.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSPP.SetReadOnly(TRUE);    //设置为只读状态

		edtpcscSn.SetReadOnly(false);    //设置为读写状态

		edtpcscSHA1_1.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_2.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_3.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_4.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_5.SetReadOnly(false);    //设置为读写状态

		edtpcscAuthKey.SetReadOnly(false);    //设置为读写状态

		combopcscSha1List1.EnableWindow(TRUE);
		combopcscSha1List2.EnableWindow(TRUE);
		combopcscSha1List3.EnableWindow(TRUE);
		combopcscSha1List4.EnableWindow(TRUE);
		combopcscSha1List5.EnableWindow(TRUE);

		btnpcscGet.EnableWindow(TRUE);
		btnpcscSet.EnableWindow(TRUE);
	}
	else if ((pDlg->gAtrCosType == _T("MT2_COS"))|| (pDlg->gAtrCosType == _T("MT2_Wlt")))
	{
		((CButton*)GetDlgItem(radioMT1))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT1))->EnableWindow(false);

		((CButton*)GetDlgItem(radioMT222A))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT222C))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT211))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT222A))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT222C))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT211))->SetCheck(FALSE); //不选上

		edtpcscSn.SetReadOnly(false);    //设置为读写状态

		edtpcscSHA1_1.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_2.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_3.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_4.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_5.SetReadOnly(false);    //设置为读写状态

		edtpcscAuthKey.SetReadOnly(false);    //设置为读写状态

		combopcscSha1List1.EnableWindow(TRUE);
		combopcscSha1List2.EnableWindow(TRUE);
		combopcscSha1List3.EnableWindow(TRUE);
		combopcscSha1List4.EnableWindow(TRUE);
		combopcscSha1List5.EnableWindow(TRUE);

		btnpcscGet.EnableWindow(TRUE);
		btnpcscSet.EnableWindow(TRUE);
	}
	else if ((pDlg->gAtrCosType == _T("MT222_Nat+")) || (pDlg->gAtrCosType == _T("MT222_SKF")))
	{
		((CButton*)GetDlgItem(radioMT1))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT222A))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT222C))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT211))->SetCheck(FALSE); //不选上

		((CButton*)GetDlgItem(radioMT1))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222A))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222C))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT211))->EnableWindow(false);

		edtpcscBLE.SetReadOnly(FALSE);    //设置为读写状态
		edtpcscSPP.SetReadOnly(FALSE);    //设置为读写状态
		edtpcscBLE.SetReadOnly(FALSE);    //设置为读写状态
		edtpcscSPP.SetReadOnly(FALSE);    //设置为读写状态

		edtpcscSn.SetReadOnly(false);    //设置为读写状态

		edtpcscSHA1_1.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_2.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_3.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_4.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_5.SetReadOnly(false);    //设置为读写状态

		edtpcscAuthKey.SetReadOnly(false);    //设置为读写状态

		combopcscSha1List1.EnableWindow(TRUE);
		combopcscSha1List2.EnableWindow(TRUE);
		combopcscSha1List3.EnableWindow(TRUE);
		combopcscSha1List4.EnableWindow(TRUE);
		combopcscSha1List5.EnableWindow(TRUE);

		btnpcscGet.EnableWindow(TRUE);
		btnpcscSet.EnableWindow(TRUE);
	}
	else if ((pDlg->gAtrCosType == _T("MT211_Nat+")) || (pDlg->gAtrCosType == _T("MT211_SKF"))
	|| (pDlg->gAtrCosType == _T("SIM_Nat+")) || (pDlg->gAtrCosType == _T("SIM_SKF"))
	)
	{
		((CButton*)GetDlgItem(radioMT1))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT222A))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT222C))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT211))->SetCheck(FALSE); //不选上

		((CButton*)GetDlgItem(radioMT1))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222A))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222C))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT211))->EnableWindow(false);

		edtpcscBLE.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSPP.SetReadOnly(TRUE);    //设置为只读状态

		edtpcscSn.SetReadOnly(false);    //设置为读写状态

		edtpcscSHA1_1.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_2.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_3.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_4.SetReadOnly(false);    //设置为读写状态
		edtpcscSHA1_5.SetReadOnly(false);    //设置为读写状态

		edtpcscAuthKey.SetReadOnly(false);    //设置为读写状态

		combopcscSha1List1.EnableWindow(TRUE);
		combopcscSha1List2.EnableWindow(TRUE);
		combopcscSha1List3.EnableWindow(TRUE);
		combopcscSha1List4.EnableWindow(TRUE);
		combopcscSha1List5.EnableWindow(TRUE);

		btnpcscGet.EnableWindow(TRUE);
		btnpcscSet.EnableWindow(TRUE);
	}
	else if (pDlg->gAtrCosType == _T("CS.JCOS"))
	{
		((CButton*)GetDlgItem(radioMT1))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT1))->EnableWindow(false);

		((CButton*)GetDlgItem(radioMT222A))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT222C))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT211))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT222A))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT222C))->SetCheck(FALSE); //不选上
		((CButton*)GetDlgItem(radioMT211))->SetCheck(FALSE); //不选上

		edtpcscBLE.SetReadOnly(FALSE);    //设置为读写状态
		edtpcscSPP.SetReadOnly(FALSE);    //设置为读写状态

		edtpcscSn.SetReadOnly(false);    //设置为读写状态

		edtpcscSHA1_1.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA1_2.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA1_3.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA1_4.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA1_5.SetReadOnly(TRUE);    //设置为只读状态

		edtpcscAuthKey.SetReadOnly(TRUE);    //设置为只读状态

		combopcscSha1List1.EnableWindow(false);
		combopcscSha1List2.EnableWindow(false);
		combopcscSha1List3.EnableWindow(false);
		combopcscSha1List4.EnableWindow(false);
		combopcscSha1List5.EnableWindow(false);

		btnpcscGet.EnableWindow(TRUE);
		btnpcscSet.EnableWindow(TRUE);

		edtpcscAuthKey.ShowWindow(false);
	}
	else
	{
		radioFlag = _T("");
		((CButton*)GetDlgItem(radioMT1))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222A))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222C))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT211))->EnableWindow(false);

		edtpcscBLE.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSPP.SetReadOnly(TRUE);    //设置为只读状态
		
		edtpcscSn.SetReadOnly(TRUE);    //设置为只读状态

		edtpcscSHA1_1.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA1_2.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA1_3.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA1_4.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscSHA1_5.SetReadOnly(TRUE);    //设置为只读状态

		edtpcscAuthKey.SetReadOnly(TRUE);    //设置为只读状态

		combopcscSha1List1.EnableWindow(false);
		combopcscSha1List2.EnableWindow(false);
		combopcscSha1List3.EnableWindow(false);
		combopcscSha1List4.EnableWindow(false);
		combopcscSha1List5.EnableWindow(false);

		btnpcscGet.EnableWindow(false);
		btnpcscSet.EnableWindow(false);

		edtpcscAuthKey.ShowWindow(false);
	}
}

void page2CardInfoDlg::initCardInfoPage()
{
	readSha1List();
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

boolean page2CardInfoDlg::ExAuth(CString authKey)
{
	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;
	CString sKey;
	unsigned char key[16] = { 0 };

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//将edtpcscAuthKey数据存到outS
	edtpcscAuthKey.GetWindowText(sKey);
	if (32 != sKey.GetLength())
	{
		MessageBox(_T("请输入正确长度（16字节）的AuthKey数据！"));
		return FALSE;
	}

	pDlg->Reader.StrToHex(sKey, key);

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
	sm4_crypt_ecb(&ctx, 1, 16, Resp, APDU+5);
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

void page2CardInfoDlg::OnBnClickedbtnGet()//Button：Get
{
	// TODO:  在此添加控件通知处理程序代码
	CString sAPDU,sAPDU2;
	byte APDU[5+256];
	byte Resp[256+2];
	byte readMacFlag=0;
	DWORD APDULen = 0;
	DWORD RespLen = 256+2;
	CString statusStr;

	//清除上一次获取的信息
	initCardInfoPage();
	edtpcscStatus.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();


	//Get Card Type
	if (pDlg->gAtrCosType == _T("CS.JCOS"))
	{
		sAPDU = "1801000004";
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
		switch (Resp[3])
		{
		case '1':
			((CButton*)GetDlgItem(radioMT211))->SetCheck(TRUE); //选上
			//edtpcscBLE.SetReadOnly(TRUE);    //设置为只读状态
			//edtpcscSPP.SetReadOnly(TRUE);    //设置为只读状态
			edtpcscBLE.ShowWindow(FALSE);
			edtpcscSPP.ShowWindow(FALSE);
			radioFlag = _T("MT211");
			break;

		case 'A':
			((CButton*)GetDlgItem(radioMT222A))->SetCheck(TRUE); //选上
			//edtpcscBLE.SetReadOnly(FALSE);    //设置为读写状态
			//edtpcscSPP.SetReadOnly(FALSE);    //设置为读写状态
			edtpcscBLE.ShowWindow(TRUE);
			edtpcscSPP.ShowWindow(TRUE);
			readMacFlag = 1;
			radioFlag = _T("MT222A");
			break;

		case 'C':
			((CButton*)GetDlgItem(radioMT222C))->SetCheck(TRUE); //选上
			//edtpcscBLE.SetReadOnly(FALSE);    //设置为读写状态
			//edtpcscSPP.SetReadOnly(FALSE);    //设置为读写状态
			edtpcscBLE.ShowWindow(TRUE);
			edtpcscSPP.ShowWindow(TRUE);
			readMacFlag = 1;
			radioFlag = _T("MT222C");
			break;
		}
		//Get COS Ver
		sAPDU = "1801000204";
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			edtpcscSHA1_1.SetWindowText(pDlg->Reader.GetError());
			edtpcscSHA1_1.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
		if (Resp[4] != 0x90)
		{
			statusStr = _T("GetCardInfo读取COS版本号失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
			edtpcscStatus.SetWindowText(statusStr);
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(statusStr);
			return;
		}
		edtpcscCosVer.SetWindowText(_T("CS_JCOS V") + pDlg->Reader.HexToStr(Resp, 1) + _T(".") + pDlg->Reader.HexToStr(Resp + 1, 1) + _T(".") + pDlg->Reader.HexToStr(Resp + 2, 2));

		//Get SN
		sAPDU = "1801000108";
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
		if (Resp[8] != 0x90)
		{
			statusStr = _T("GetCardInfo读取SN失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
			edtpcscStatus.SetWindowText(statusStr);
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(statusStr);
			return;
		}

		edtpcscSn.SetWindowText(pDlg->Reader.HexToStr(Resp, 8));		

		//读MAC值
		if (!readMacFlag)
		{
			edtpcscStatus.SetWindowText(_T("查询当前卡片信息成功！"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}

		sAPDU = "180100040C";
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
		if (Resp[12] != 0x90)
		{
			statusStr = _T("GetCardInfo读取MAC失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
			edtpcscStatus.SetWindowText(statusStr);
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(statusStr);
			return;
		}

		edtpcscSPP.SetWindowText(pDlg->Reader.HexToStr(Resp, 6));
		edtpcscBLE.SetWindowText(pDlg->Reader.HexToStr(Resp + 6, 6));

		edtpcscStatus.SetWindowText(_T("查询当前卡片信息成功！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);


		if ((radioFlag == _T("MT222A"))
			|| (radioFlag == _T("MT222C"))
			)
		{
			//加载蓝牙
			sAPDU = "1806000000";
			APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
			RespLen = 256 + 2;
			memset(Resp, 0, RespLen);
			if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
			{
				edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
				edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				return;
			}
			if (Resp[0] != 0x90)
			{
				statusStr = _T("加载蓝牙失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
				edtpcscStatus.SetWindowText(statusStr);
				edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				MessageBox(statusStr);
				return;
			}
			edtpcscStatus.SetWindowText(_T("查询当前卡片信息成功！加载蓝牙成功，请检查蓝牙信号。"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		return;
	}
	else if (pDlg->gAtrCosType == _T("MT1_COS"))
	{
		((CButton*)GetDlgItem(radioMT1))->SetCheck(TRUE); //选上
		radioFlag = _T("MT1");

		edtpcscBLE.ShowWindow(FALSE);
		edtpcscSPP.ShowWindow(FALSE);
	}
	else if ((pDlg->gAtrCosType == _T("MT222_Nat+"))
	|| (pDlg->gAtrCosType == _T("MT222_SKF"))
	)
	{
		readMacFlag = 1;
		edtpcscBLE.ShowWindow(TRUE);
		edtpcscSPP.ShowWindow(TRUE);
	}
	else if ((pDlg->gAtrCosType == _T("MT211_Nat+"))
	|| (pDlg->gAtrCosType == _T("MT211_SKF"))
	)
	{
		readMacFlag = 0;
		edtpcscBLE.ShowWindow(FALSE);
		edtpcscSPP.ShowWindow(FALSE);
	}
	else if ((pDlg->gAtrCosType == _T("SIM_Nat+"))
	|| (pDlg->gAtrCosType == _T("SIM_SKF"))
	)
	{
		readMacFlag = 0;
		edtpcscBLE.ShowWindow(FALSE);
		edtpcscSPP.ShowWindow(FALSE);
	}
	else if ((pDlg->gAtrCosType == _T("MT2_COS"))|| (pDlg->gAtrCosType == _T("MT2_Wlt")))
	{
		sAPDU = "9801004D06";
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
		switch (Resp[4])
		{
		case '1':
			((CButton*)GetDlgItem(radioMT211))->SetCheck(TRUE); //选上
			//edtpcscBLE.SetReadOnly(TRUE);    //设置为只读状态
			//edtpcscSPP.SetReadOnly(TRUE);    //设置为只读状态
			radioFlag = _T("MT211");
			edtpcscBLE.ShowWindow(FALSE);
			edtpcscSPP.ShowWindow(FALSE);
			break;

		case '2':
			switch (Resp[5])
			{
			case 'A':
				((CButton*)GetDlgItem(radioMT222A))->SetCheck(TRUE); //选上
				//edtpcscBLE.SetReadOnly(FALSE);    //设置为读写状态
				//edtpcscSPP.SetReadOnly(FALSE);    //设置为读写状态
				readMacFlag = 1;
				radioFlag = _T("MT222A");
				edtpcscBLE.ShowWindow(TRUE);
				edtpcscSPP.ShowWindow(TRUE);
				break;

			case 'C':
				((CButton*)GetDlgItem(radioMT222C))->SetCheck(TRUE); //选上
				//edtpcscBLE.SetReadOnly(FALSE);    //设置为读写状态
				//edtpcscSPP.SetReadOnly(FALSE);    //设置为读写状态
				readMacFlag = 1;
				radioFlag = _T("MT222C");
				edtpcscBLE.ShowWindow(TRUE);
				edtpcscSPP.ShowWindow(TRUE);
				break;
			}
			break;
		}
	}
	else
	{
		//MessageBox(_T("对不起！\r\n当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		radioFlag = _T("");

		edtpcscStatus.SetWindowText(_T("对不起！ 当前卡片是：") + pDlg->gAtrCosType + _T("，不支持本页面操作！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}
	//确认Native+应用有没有进行过个人化
	//如果卡片已经执行过个人化处理（即Native+的MF存在）

	//Get COS Ver
	sAPDU = "9801000202";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		edtpcscSHA1_1.SetWindowText(pDlg->Reader.GetError());
		edtpcscSHA1_1.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}
	switch (Resp[0])
	{
	case 0x21:
	case 0x22:
		edtpcscCosVer.SetWindowText(_T("CS_SmartCOS V") + pDlg->Reader.HexToStr(Resp, 1) + _T(".") + pDlg->Reader.HexToStr(Resp+1, 1));
		break;
	default:
		edtpcscCosVer.SetWindowText(_T("V") + pDlg->Reader.HexToStr(Resp, 1) + _T(".") + pDlg->Reader.HexToStr(Resp+1, 1));
		break;
	}

	//Get SN
	sAPDU = "9801000108";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}
	
	edtpcscSn.SetWindowText(pDlg->Reader.HexToStr(Resp,8));

	//读SHA1值
	sAPDU2 = "9801000564";
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

	edtpcscSHA1_1.SetWindowText(stringText1);
	edtpcscSHA1_2.SetWindowText(stringText2);
	edtpcscSHA1_3.SetWindowText(stringText3);
	edtpcscSHA1_4.SetWindowText(stringText4);
	edtpcscSHA1_5.SetWindowText(stringText5);

	//SHA1List Combox同步
	LoadSha1List();
	int thisSel;
	if (GetSelwithSha1Data(stringText1, &thisSel))
		combopcscSha1List1.SetCurSel(thisSel);

	if (GetSelwithSha1Data(stringText2, &thisSel))
		combopcscSha1List2.SetCurSel(thisSel);

	if (GetSelwithSha1Data(stringText3, &thisSel))
		combopcscSha1List3.SetCurSel(thisSel);

	if (GetSelwithSha1Data(stringText4, &thisSel))
		combopcscSha1List4.SetCurSel(thisSel);

	if (GetSelwithSha1Data(stringText5, &thisSel))
		combopcscSha1List5.SetCurSel(thisSel);

	//读MAC值
	if (!readMacFlag)
	{
		edtpcscStatus.SetWindowText(_T("查询当前卡片信息成功！"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	sAPDU = "980100040C";
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	edtpcscSPP.SetWindowText(swapBigEndandLittleEnd(Resp, 6));
	edtpcscBLE.SetWindowText(swapBigEndandLittleEnd(Resp+6, 6));

	edtpcscStatus.SetWindowText(_T("查询当前卡片信息成功！"));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);


	//if ((radioFlag == _T("MT222A"))
	//	|| (radioFlag == _T("MT222C"))
	//	)
	{
		//加载蓝牙
		sAPDU = "98FD000000";
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
		if (Resp[0] != 0x90)
		{
			statusStr = _T("加载蓝牙失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
			edtpcscStatus.SetWindowText(statusStr);
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(statusStr);
			return;
		}
		edtpcscStatus.SetWindowText(_T("查询当前卡片信息成功！加载蓝牙成功，请检查蓝牙信号。"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
}


void page2CardInfoDlg::OnBnClickedbtnSet()//Button：Set
{
	// TODO:  在此添加控件通知处理程序代码

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	edtpcscStatus.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	//Get Card Type
	if (pDlg->gAtrCosType == _T("CS.JCOS"))
	{
		//MT2		
		if (16 != edtpcscSn.GetWindowTextLength())
		{
			MessageBox(_T("SN的长度不正确，\r\n请输入16位SN！"));
			return;
		}

		CString bleMac, sppMac, macStr, snStr, sha1Str1, sha1Str2, sha1Str3, sha1Str4, sha1Str5, sha1_5Str;
		

		CString sAPDU, sAPDU2;
		byte APDU[5 + 256];
		byte Resp[256 + 2];
		byte readMacFlag = 0;
		DWORD APDULen = 0;
		DWORD RespLen = 256 + 2;
		//写入CardInfo
		//SN 
		edtpcscSn.GetWindowText(snStr);
		sAPDU.Format(_T("%s %s"), _T("1801010108"), snStr);
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
			MessageBox(_T("SetCardInfo执行写入SN失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			return;
		}
		if (0 == lstrcmp(radioFlag, _T("MT211")))
		{
			//不需要写MAC
			//CardType
			sAPDU.Format(_T("%s %s"), _T("1801010004"), _T("00323131"));

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
				MessageBox(_T("SetCardInfo执行写入卡类型失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}

			//MessageBox(_T("恭喜您！\r\nSetCardInfo执行成功！"));

			edtpcscStatus.SetWindowText(_T("恭喜您！ SetCardInfo执行成功！"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		else
		{
			byte macData[12];
			//需要写MAC，读取MAC地址
			if (12 != edtpcscBLE.GetWindowTextLength())
			{
				MessageBox(_T("BLE的MAC地址长度不正确，\r\n请输入6字节的MAC地址值！"));
				return;
			}
			if (12 != edtpcscSPP.GetWindowTextLength())
			{
				MessageBox(_T("SPP的MAC地址长度不正确，\r\n请输入6字节的MAC地址值！"));
				return;
			}
			edtpcscBLE.GetWindowText(bleMac);
			edtpcscSPP.GetWindowText(sppMac);
			pDlg->Reader.StrToHex(sppMac, macData);
			pDlg->Reader.StrToHex(bleMac, macData+6);

			macStr.Format(_T("%s %s"), sppMac, bleMac);

			//SPP_MAC+BLE_MAC
			sAPDU.Format(_T("%s %s"), _T("180101040C"),  macStr);

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
				MessageBox(_T("SetCardInfo执行写入MAC失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}
			//CardType
			sAPDU.Format(_T("%s %s"), _T("1801010004"), (0 == lstrcmp(radioFlag, _T("MT222C"))) ? _T("32323243") : _T("32323241"));

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
				MessageBox(_T("SetCardInfo执行写入卡类型失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}
			//MessageBox(_T("恭喜您！\r\nSetCardInfo执行成功！"));

			edtpcscStatus.SetWindowText(_T("恭喜您！ SetCardInfo执行成功！"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
	}
	else if ((pDlg->gAtrCosType == _T("MT1_COS"))
		||(pDlg->gAtrCosType == _T("MT2_COS"))
		|| (pDlg->gAtrCosType == _T("MT2_Wlt"))
		|| (pDlg->gAtrCosType == _T("MT222_Nat+"))
		|| (pDlg->gAtrCosType == _T("MT211_Nat+"))
		|| (pDlg->gAtrCosType == _T("SIM_Nat+"))
		|| (pDlg->gAtrCosType == _T("MT222_SKF"))
		|| (pDlg->gAtrCosType == _T("MT211_SKF"))
		|| (pDlg->gAtrCosType == _T("SIM_SKF"))
		)
	{
		//MT2
		//首先判断卡片有没有执行过个人化（即Native+的MF是否存在）
		//如果卡片已经执行过个人化处理（即Native+的MF存在），则须首先要通过MF的外部认证方可继续执行
		if (checkMF())
		{
			//需要执行：外部认证
			//输入外部认证密钥
			CString authKey;
			if(!ExAuth(authKey))
			{
				MessageBox(_T("外部认证失败，\r\n无法写入卡片信息！"));
				return;
			}
		}

		if (16 != edtpcscSn.GetWindowTextLength())
		{
			MessageBox(_T("SN的长度不正确，\r\n请输入16位SN！"));
			return;
		}
		if (40 != edtpcscSHA1_1.GetWindowTextLength())
		{
			MessageBox(_T("第1组SHA1值的长度不正确，\r\n请输入20字节的SHA1值！"));
			return;
		}
		if (40 != edtpcscSHA1_2.GetWindowTextLength())
		{
			MessageBox(_T("第2组SHA1值的长度不正确，\r\n请输入20字节的SHA1值！"));
			return;
		}
		if (40 != edtpcscSHA1_3.GetWindowTextLength())
		{
			MessageBox(_T("第3组SHA1值的长度不正确，\r\n请输入20字节的SHA1值！"));
			return;
		}
		if (40 != edtpcscSHA1_4.GetWindowTextLength())
		{
			MessageBox(_T("第4组SHA1值的长度不正确，\r\n请输入20字节的SHA1值！"));
			return;
		}
		if (40 != edtpcscSHA1_5.GetWindowTextLength())
		{
			MessageBox(_T("第5组SHA1值的长度不正确，\r\n请输入20字节的SHA1值！"));
			return;
		}
		CString bleMac,sppMac,macStr,snStr,sha1Str1, sha1Str2, sha1Str3, sha1Str4, sha1Str5, sha1_5Str;
		edtpcscSn.GetWindowText(snStr);
		edtpcscSHA1_1.GetWindowText(sha1Str1);
		edtpcscSHA1_2.GetWindowText(sha1Str2);
		edtpcscSHA1_3.GetWindowText(sha1Str3);
		edtpcscSHA1_4.GetWindowText(sha1Str4);
		edtpcscSHA1_5.GetWindowText(sha1Str5);
		
		sha1_5Str.Format(_T("%s %s %s %s %s"), sha1Str1, sha1Str2, sha1Str3, sha1Str4, sha1Str5);

		CString sAPDU, sAPDU2;
		byte APDU[5 + 256];
		byte Resp[256 + 2];
		byte readMacFlag = 0;
		DWORD APDULen = 0;
		DWORD RespLen = 256 + 2;
		//写入CardInfo
		if ((radioFlag == _T("MT1"))
			|| (radioFlag == _T("MT211"))
			|| (pDlg->gAtrCosType == _T("MT211_Nat+"))
			|| (pDlg->gAtrCosType == _T("MT211_SKF"))
			|| (pDlg->gAtrCosType == _T("SIM_Nat+"))
			|| (pDlg->gAtrCosType == _T("SIM_SKF"))
			)
		{
			//不需要写MAC
			//SN 
			sAPDU.Format(_T("%s %s"), _T("9881010008"), snStr);
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
				MessageBox(_T("SetCardInfo执行写入SN失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}

			//SHA1_5
			sAPDU.Format(_T("%s %s"), _T("9881030064"), sha1_5Str);
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
			if (radioFlag == _T("MT211"))
			{
				//CardType
				sAPDU.Format(_T("%s %s"), _T("98814D0005"), _T("4D54323131"));

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
					MessageBox(_T("SetCardInfo执行写入卡类型失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					return;
				}
			}
			//MessageBox(_T("恭喜您！\r\nSetCardInfo执行成功！"));

			edtpcscStatus.SetWindowText(_T("恭喜您！ SetCardInfo执行成功！"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		else
		{
			byte macData[12];
			//需要写MAC，读取MAC地址
			if (12 != edtpcscBLE.GetWindowTextLength())
			{
				MessageBox(_T("BLE的MAC地址长度不正确，\r\n请输入6字节的MAC地址值！"));
				return;
			}
			if (12 != edtpcscSPP.GetWindowTextLength())
			{
				MessageBox(_T("SPP的MAC地址长度不正确，\r\n请输入6字节的MAC地址值！"));
				return;
			}
			edtpcscBLE.GetWindowText(bleMac);
			edtpcscSPP.GetWindowText(sppMac);
			pDlg->Reader.StrToHex(sppMac, macData+6);
			pDlg->Reader.StrToHex(bleMac, macData);

			macStr = swapBigEndandLittleEnd(macData, 12);

			//SN + SPP_MAC+BLE_MAC + SHA1_5
			sAPDU.Format(_T("%s %s %s %s"), _T("9881000078"), snStr, macStr, sha1_5Str);

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
				MessageBox(_T("SetCardInfo执行写入SN失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}
			//CardType
			sAPDU.Format(_T("%s %s"), _T("98814D0006"), (0 == lstrcmp(radioFlag, _T("MT222C")))? _T("4D5432323243"): _T("4D5432323241"));

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
				MessageBox(_T("SetCardInfo执行写入卡类型失败！\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}
			//MessageBox(_T("恭喜您！\r\nSetCardInfo执行成功！"));

			edtpcscStatus.SetWindowText(_T("恭喜您！ SetCardInfo执行成功！"));
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

boolean page2CardInfoDlg::GetSelwithSha1Data(LPCTSTR sha1,int *retSel)
{
	int nSel=0;
	char retFlag = 0;
	// 读文件
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
			*retSel = nSel-1;//去除第一行标题栏
			return TRUE;
		}
		nSel++;
	}
	file.Close();
	return FALSE;
}
boolean page2CardInfoDlg::GetSha1DataWithSel(CString *sha1, int inSel)
{
	int nSel = 0;
	char retFlag = 0;
	// 读文件
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
void page2CardInfoDlg::LoadSha1List()
{
	combopcscSha1List1.ResetContent();
	combopcscSha1List2.ResetContent();
	combopcscSha1List3.ResetContent();
	combopcscSha1List4.ResetContent();
	combopcscSha1List5.ResetContent();

	int nSel=0;

	// 读文件
	CStdioFile file;
	file.Open(_T("./SHA1_List.csv"), CFile::modeRead);
	CString str;
	while (file.ReadString(str))
	{
		str = str.Trim(_T(" "));
		CString substr[4];
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
			combopcscSha1List1.InsertString(-1, substr[1]);
			combopcscSha1List2.InsertString(-1, substr[1]);
			combopcscSha1List3.InsertString(-1, substr[1]);
			combopcscSha1List4.InsertString(-1, substr[1]);
			combopcscSha1List5.InsertString(-1, substr[1]);
		}
		nSel++;
	}
	file.Close();
}
void page2CardInfoDlg::OnCbnSelchangecombosha1list1()
{
	CString strSha1;
	int nSel;
	// 获取组合框控件的列表框中选中项的索引
	nSel = combopcscSha1List1.GetCurSel();
	// 根据选中项索引获取该项字符串
	if(GetSha1DataWithSel(&strSha1, nSel))
		edtpcscSHA1_1.SetWindowText(strSha1);
}
void page2CardInfoDlg::OnCbnSelchangecombosha1list2()
{
	CString strSha1;
	int nSel;
	// 获取组合框控件的列表框中选中项的索引
	nSel = combopcscSha1List2.GetCurSel();
	// 根据选中项索引获取该项字符串
	if (GetSha1DataWithSel(&strSha1, nSel))
		edtpcscSHA1_2.SetWindowText(strSha1);
}
void page2CardInfoDlg::OnCbnSelchangecombosha1list3()
{
	CString strSha1;
	int nSel;
	// 获取组合框控件的列表框中选中项的索引
	nSel = combopcscSha1List3.GetCurSel();
	// 根据选中项索引获取该项字符串
	if (GetSha1DataWithSel(&strSha1, nSel))
		edtpcscSHA1_3.SetWindowText(strSha1);
}

void page2CardInfoDlg::OnCbnSelchangecombosha1list4()
{
	CString strSha1;
	int nSel;
	// 获取组合框控件的列表框中选中项的索引
	nSel = combopcscSha1List4.GetCurSel();
	// 根据选中项索引获取该项字符串
	if (GetSha1DataWithSel(&strSha1, nSel))
		edtpcscSHA1_4.SetWindowText(strSha1);
}
void page2CardInfoDlg::OnCbnSelchangecombosha1list5()
{
	CString strSha1;
	int nSel;
	// 获取组合框控件的列表框中选中项的索引
	nSel = combopcscSha1List5.GetCurSel();
	// 根据选中项索引获取该项字符串
	if (GetSha1DataWithSel(&strSha1, nSel))
		edtpcscSHA1_5.SetWindowText(strSha1);
}

void page2CardInfoDlg::OnBnClickedradiomt1()
{
	// TODO: 在此添加控件通知处理程序代码
	//MT1不用设置卡类型，所以不需要任何操作
	radioFlag = _T("MT1");

	edtpcscBLE.ShowWindow(FALSE);
	edtpcscSPP.ShowWindow(FALSE);
}


void page2CardInfoDlg::OnBnClickedradiomt211()
{
	// TODO: 在此添加控件通知处理程序代码
	//((CButton*)GetDlgItem(radioMT211))->SetCheck(TRUE); //选上
	radioFlag = _T("MT211");
	//edtpcscBLE.SetReadOnly(TRUE);    //设置为只读状态
	//edtpcscSPP.SetReadOnly(TRUE);    //设置为只读状态
	edtpcscBLE.ShowWindow(FALSE);    
	edtpcscSPP.ShowWindow(FALSE);
}


void page2CardInfoDlg::OnBnClickedradiomt222a()
{
	// TODO: 在此添加控件通知处理程序代码
	//((CButton*)GetDlgItem(radioMT222A))->SetCheck(TRUE); //选上
	radioFlag = _T("MT222A");
	//edtpcscBLE.SetReadOnly(FALSE);    //设置为读写状态
	//edtpcscSPP.SetReadOnly(FALSE);    //设置为读写状态
	edtpcscBLE.ShowWindow(TRUE);
	edtpcscSPP.ShowWindow(TRUE);
}


void page2CardInfoDlg::OnBnClickedradiomt222c()
{
	// TODO: 在此添加控件通知处理程序代码
	//((CButton*)GetDlgItem(radioMT222C))->SetCheck(TRUE); //选上
	radioFlag = _T("MT222C"); 
	//edtpcscBLE.SetReadOnly(FALSE);    //设置为读写状态
	//edtpcscSPP.SetReadOnly(FALSE);    //设置为读写状态
	edtpcscBLE.ShowWindow(TRUE);
	edtpcscSPP.ShowWindow(TRUE);
}


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

void page2CardInfoDlg::OnChangeEdtble()
{
	CheckInputDataLength(edtBLE, 12);
}


void page2CardInfoDlg::OnChangeEdtauthkey()
{
	CheckInputDataLength(edtAuthKey, 32);
}


void page2CardInfoDlg::OnChangeEdtsha11()
{
	CheckInputDataLength(edtSHA1_1, 40);
}


void page2CardInfoDlg::OnChangeEdtsha12()
{
	CheckInputDataLength(edtSHA1_2, 40);
}


void page2CardInfoDlg::OnChangeEdtsha13()
{
	CheckInputDataLength(edtSHA1_3, 40);
}


void page2CardInfoDlg::OnChangeEdtsha14()
{
	CheckInputDataLength(edtSHA1_4, 40);
}


void page2CardInfoDlg::OnChangeEdtsha15()
{
	CheckInputDataLength(edtSHA1_5, 40);
}


void page2CardInfoDlg::OnChangeEdtsn()
{
	CheckInputDataLength(edtSn, 16);
}


void page2CardInfoDlg::OnChangeEdtspp()
{
	CheckInputDataLength(edtSPP, 12);
}
