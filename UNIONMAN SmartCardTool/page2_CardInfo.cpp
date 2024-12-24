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
#include<io.h>   //C����ͷ�ļ�
#include<iostream>   //for system();


#include "tchar.h"
#include   "ATLCONV.H"


#include   "..\SM4\sm4.h"




// PAGE2_CardInfo �Ի���

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





// PAGE2_CardInfo ��Ϣ�������

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
		((CButton*)GetDlgItem(radioMT1))->SetCheck(TRUE); //ѡ��
		radioFlag = _T("MT1");
		((CButton*)GetDlgItem(radioMT1))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222A))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222C))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT211))->EnableWindow(false);

		edtpcscBLE.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		edtpcscSPP.SetReadOnly(TRUE);    //����Ϊֻ��״̬

		edtpcscSn.SetReadOnly(false);    //����Ϊ��д״̬

		edtpcscSHA1_1.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_2.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_3.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_4.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_5.SetReadOnly(false);    //����Ϊ��д״̬

		edtpcscAuthKey.SetReadOnly(false);    //����Ϊ��д״̬

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
		((CButton*)GetDlgItem(radioMT1))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT1))->EnableWindow(false);

		((CButton*)GetDlgItem(radioMT222A))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT222C))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT211))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT222A))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT222C))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT211))->SetCheck(FALSE); //��ѡ��

		edtpcscSn.SetReadOnly(false);    //����Ϊ��д״̬

		edtpcscSHA1_1.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_2.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_3.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_4.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_5.SetReadOnly(false);    //����Ϊ��д״̬

		edtpcscAuthKey.SetReadOnly(false);    //����Ϊ��д״̬

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
		((CButton*)GetDlgItem(radioMT1))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT222A))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT222C))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT211))->SetCheck(FALSE); //��ѡ��

		((CButton*)GetDlgItem(radioMT1))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222A))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222C))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT211))->EnableWindow(false);

		edtpcscBLE.SetReadOnly(FALSE);    //����Ϊ��д״̬
		edtpcscSPP.SetReadOnly(FALSE);    //����Ϊ��д״̬
		edtpcscBLE.SetReadOnly(FALSE);    //����Ϊ��д״̬
		edtpcscSPP.SetReadOnly(FALSE);    //����Ϊ��д״̬

		edtpcscSn.SetReadOnly(false);    //����Ϊ��д״̬

		edtpcscSHA1_1.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_2.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_3.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_4.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_5.SetReadOnly(false);    //����Ϊ��д״̬

		edtpcscAuthKey.SetReadOnly(false);    //����Ϊ��д״̬

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
		((CButton*)GetDlgItem(radioMT1))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT222A))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT222C))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT211))->SetCheck(FALSE); //��ѡ��

		((CButton*)GetDlgItem(radioMT1))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222A))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT222C))->EnableWindow(false);
		((CButton*)GetDlgItem(radioMT211))->EnableWindow(false);

		edtpcscBLE.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		edtpcscSPP.SetReadOnly(TRUE);    //����Ϊֻ��״̬

		edtpcscSn.SetReadOnly(false);    //����Ϊ��д״̬

		edtpcscSHA1_1.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_2.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_3.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_4.SetReadOnly(false);    //����Ϊ��д״̬
		edtpcscSHA1_5.SetReadOnly(false);    //����Ϊ��д״̬

		edtpcscAuthKey.SetReadOnly(false);    //����Ϊ��д״̬

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
		((CButton*)GetDlgItem(radioMT1))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT1))->EnableWindow(false);

		((CButton*)GetDlgItem(radioMT222A))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT222C))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT211))->EnableWindow(true);
		((CButton*)GetDlgItem(radioMT222A))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT222C))->SetCheck(FALSE); //��ѡ��
		((CButton*)GetDlgItem(radioMT211))->SetCheck(FALSE); //��ѡ��

		edtpcscBLE.SetReadOnly(FALSE);    //����Ϊ��д״̬
		edtpcscSPP.SetReadOnly(FALSE);    //����Ϊ��д״̬

		edtpcscSn.SetReadOnly(false);    //����Ϊ��д״̬

		edtpcscSHA1_1.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		edtpcscSHA1_2.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		edtpcscSHA1_3.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		edtpcscSHA1_4.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		edtpcscSHA1_5.SetReadOnly(TRUE);    //����Ϊֻ��״̬

		edtpcscAuthKey.SetReadOnly(TRUE);    //����Ϊֻ��״̬

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

		edtpcscBLE.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		edtpcscSPP.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		
		edtpcscSn.SetReadOnly(TRUE);    //����Ϊֻ��״̬

		edtpcscSHA1_1.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		edtpcscSHA1_2.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		edtpcscSHA1_3.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		edtpcscSHA1_4.SetReadOnly(TRUE);    //����Ϊֻ��״̬
		edtpcscSHA1_5.SetReadOnly(TRUE);    //����Ϊֻ��״̬

		edtpcscAuthKey.SetReadOnly(TRUE);    //����Ϊֻ��״̬

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

	//��edtpcscAuthKey���ݴ浽outS
	edtpcscAuthKey.GetWindowText(sKey);
	if (32 != sKey.GetLength())
	{
		MessageBox(_T("��������ȷ���ȣ�16�ֽڣ���AuthKey���ݣ�"));
		return FALSE;
	}

	pDlg->Reader.StrToHex(sKey, key);

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
	sm4_crypt_ecb(&ctx, 1, 16, Resp, APDU+5);
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

void page2CardInfoDlg::OnBnClickedbtnGet()//Button��Get
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString sAPDU,sAPDU2;
	byte APDU[5+256];
	byte Resp[256+2];
	byte readMacFlag=0;
	DWORD APDULen = 0;
	DWORD RespLen = 256+2;
	CString statusStr;

	//�����һ�λ�ȡ����Ϣ
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
			((CButton*)GetDlgItem(radioMT211))->SetCheck(TRUE); //ѡ��
			//edtpcscBLE.SetReadOnly(TRUE);    //����Ϊֻ��״̬
			//edtpcscSPP.SetReadOnly(TRUE);    //����Ϊֻ��״̬
			edtpcscBLE.ShowWindow(FALSE);
			edtpcscSPP.ShowWindow(FALSE);
			radioFlag = _T("MT211");
			break;

		case 'A':
			((CButton*)GetDlgItem(radioMT222A))->SetCheck(TRUE); //ѡ��
			//edtpcscBLE.SetReadOnly(FALSE);    //����Ϊ��д״̬
			//edtpcscSPP.SetReadOnly(FALSE);    //����Ϊ��д״̬
			edtpcscBLE.ShowWindow(TRUE);
			edtpcscSPP.ShowWindow(TRUE);
			readMacFlag = 1;
			radioFlag = _T("MT222A");
			break;

		case 'C':
			((CButton*)GetDlgItem(radioMT222C))->SetCheck(TRUE); //ѡ��
			//edtpcscBLE.SetReadOnly(FALSE);    //����Ϊ��д״̬
			//edtpcscSPP.SetReadOnly(FALSE);    //����Ϊ��д״̬
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
			statusStr = _T("GetCardInfo��ȡCOS�汾��ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
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
			statusStr = _T("GetCardInfo��ȡSNʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
			edtpcscStatus.SetWindowText(statusStr);
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(statusStr);
			return;
		}

		edtpcscSn.SetWindowText(pDlg->Reader.HexToStr(Resp, 8));		

		//��MACֵ
		if (!readMacFlag)
		{
			edtpcscStatus.SetWindowText(_T("��ѯ��ǰ��Ƭ��Ϣ�ɹ���"));
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
			statusStr = _T("GetCardInfo��ȡMACʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
			edtpcscStatus.SetWindowText(statusStr);
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(statusStr);
			return;
		}

		edtpcscSPP.SetWindowText(pDlg->Reader.HexToStr(Resp, 6));
		edtpcscBLE.SetWindowText(pDlg->Reader.HexToStr(Resp + 6, 6));

		edtpcscStatus.SetWindowText(_T("��ѯ��ǰ��Ƭ��Ϣ�ɹ���"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);


		if ((radioFlag == _T("MT222A"))
			|| (radioFlag == _T("MT222C"))
			)
		{
			//��������
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
				statusStr = _T("��������ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
				edtpcscStatus.SetWindowText(statusStr);
				edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				MessageBox(statusStr);
				return;
			}
			edtpcscStatus.SetWindowText(_T("��ѯ��ǰ��Ƭ��Ϣ�ɹ������������ɹ������������źš�"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		return;
	}
	else if (pDlg->gAtrCosType == _T("MT1_COS"))
	{
		((CButton*)GetDlgItem(radioMT1))->SetCheck(TRUE); //ѡ��
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
			((CButton*)GetDlgItem(radioMT211))->SetCheck(TRUE); //ѡ��
			//edtpcscBLE.SetReadOnly(TRUE);    //����Ϊֻ��״̬
			//edtpcscSPP.SetReadOnly(TRUE);    //����Ϊֻ��״̬
			radioFlag = _T("MT211");
			edtpcscBLE.ShowWindow(FALSE);
			edtpcscSPP.ShowWindow(FALSE);
			break;

		case '2':
			switch (Resp[5])
			{
			case 'A':
				((CButton*)GetDlgItem(radioMT222A))->SetCheck(TRUE); //ѡ��
				//edtpcscBLE.SetReadOnly(FALSE);    //����Ϊ��д״̬
				//edtpcscSPP.SetReadOnly(FALSE);    //����Ϊ��д״̬
				readMacFlag = 1;
				radioFlag = _T("MT222A");
				edtpcscBLE.ShowWindow(TRUE);
				edtpcscSPP.ShowWindow(TRUE);
				break;

			case 'C':
				((CButton*)GetDlgItem(radioMT222C))->SetCheck(TRUE); //ѡ��
				//edtpcscBLE.SetReadOnly(FALSE);    //����Ϊ��д״̬
				//edtpcscSPP.SetReadOnly(FALSE);    //����Ϊ��д״̬
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
		//MessageBox(_T("�Բ���\r\n��ǰ��Ƭ�ǣ�") + pDlg->gAtrCosType + _T("����֧�ֱ�ҳ�������"));
		radioFlag = _T("");

		edtpcscStatus.SetWindowText(_T("�Բ��� ��ǰ��Ƭ�ǣ�") + pDlg->gAtrCosType + _T("����֧�ֱ�ҳ�������"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}
	//ȷ��Native+Ӧ����û�н��й����˻�
	//�����Ƭ�Ѿ�ִ�й����˻�������Native+��MF���ڣ�

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

	//��SHA1ֵ
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

	//SHA1List Comboxͬ��
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

	//��MACֵ
	if (!readMacFlag)
	{
		edtpcscStatus.SetWindowText(_T("��ѯ��ǰ��Ƭ��Ϣ�ɹ���"));
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

	edtpcscStatus.SetWindowText(_T("��ѯ��ǰ��Ƭ��Ϣ�ɹ���"));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);


	//if ((radioFlag == _T("MT222A"))
	//	|| (radioFlag == _T("MT222C"))
	//	)
	{
		//��������
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
			statusStr = _T("��������ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2);
			edtpcscStatus.SetWindowText(statusStr);
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(statusStr);
			return;
		}
		edtpcscStatus.SetWindowText(_T("��ѯ��ǰ��Ƭ��Ϣ�ɹ������������ɹ������������źš�"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
}


void page2CardInfoDlg::OnBnClickedbtnSet()//Button��Set
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	edtpcscStatus.SetWindowText(_T(""));
	edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	//Get Card Type
	if (pDlg->gAtrCosType == _T("CS.JCOS"))
	{
		//MT2		
		if (16 != edtpcscSn.GetWindowTextLength())
		{
			MessageBox(_T("SN�ĳ��Ȳ���ȷ��\r\n������16λSN��"));
			return;
		}

		CString bleMac, sppMac, macStr, snStr, sha1Str1, sha1Str2, sha1Str3, sha1Str4, sha1Str5, sha1_5Str;
		

		CString sAPDU, sAPDU2;
		byte APDU[5 + 256];
		byte Resp[256 + 2];
		byte readMacFlag = 0;
		DWORD APDULen = 0;
		DWORD RespLen = 256 + 2;
		//д��CardInfo
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
			MessageBox(_T("SetCardInfoִ��д��SNʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			return;
		}
		if (0 == lstrcmp(radioFlag, _T("MT211")))
		{
			//����ҪдMAC
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
				MessageBox(_T("SetCardInfoִ��д�뿨����ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}

			//MessageBox(_T("��ϲ����\r\nSetCardInfoִ�гɹ���"));

			edtpcscStatus.SetWindowText(_T("��ϲ���� SetCardInfoִ�гɹ���"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		else
		{
			byte macData[12];
			//��ҪдMAC����ȡMAC��ַ
			if (12 != edtpcscBLE.GetWindowTextLength())
			{
				MessageBox(_T("BLE��MAC��ַ���Ȳ���ȷ��\r\n������6�ֽڵ�MAC��ֵַ��"));
				return;
			}
			if (12 != edtpcscSPP.GetWindowTextLength())
			{
				MessageBox(_T("SPP��MAC��ַ���Ȳ���ȷ��\r\n������6�ֽڵ�MAC��ֵַ��"));
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
				MessageBox(_T("SetCardInfoִ��д��MACʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
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
				MessageBox(_T("SetCardInfoִ��д�뿨����ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}
			//MessageBox(_T("��ϲ����\r\nSetCardInfoִ�гɹ���"));

			edtpcscStatus.SetWindowText(_T("��ϲ���� SetCardInfoִ�гɹ���"));
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
		//�����жϿ�Ƭ��û��ִ�й����˻�����Native+��MF�Ƿ���ڣ�
		//�����Ƭ�Ѿ�ִ�й����˻�������Native+��MF���ڣ�����������Ҫͨ��MF���ⲿ��֤���ɼ���ִ��
		if (checkMF())
		{
			//��Ҫִ�У��ⲿ��֤
			//�����ⲿ��֤��Կ
			CString authKey;
			if(!ExAuth(authKey))
			{
				MessageBox(_T("�ⲿ��֤ʧ�ܣ�\r\n�޷�д�뿨Ƭ��Ϣ��"));
				return;
			}
		}

		if (16 != edtpcscSn.GetWindowTextLength())
		{
			MessageBox(_T("SN�ĳ��Ȳ���ȷ��\r\n������16λSN��"));
			return;
		}
		if (40 != edtpcscSHA1_1.GetWindowTextLength())
		{
			MessageBox(_T("��1��SHA1ֵ�ĳ��Ȳ���ȷ��\r\n������20�ֽڵ�SHA1ֵ��"));
			return;
		}
		if (40 != edtpcscSHA1_2.GetWindowTextLength())
		{
			MessageBox(_T("��2��SHA1ֵ�ĳ��Ȳ���ȷ��\r\n������20�ֽڵ�SHA1ֵ��"));
			return;
		}
		if (40 != edtpcscSHA1_3.GetWindowTextLength())
		{
			MessageBox(_T("��3��SHA1ֵ�ĳ��Ȳ���ȷ��\r\n������20�ֽڵ�SHA1ֵ��"));
			return;
		}
		if (40 != edtpcscSHA1_4.GetWindowTextLength())
		{
			MessageBox(_T("��4��SHA1ֵ�ĳ��Ȳ���ȷ��\r\n������20�ֽڵ�SHA1ֵ��"));
			return;
		}
		if (40 != edtpcscSHA1_5.GetWindowTextLength())
		{
			MessageBox(_T("��5��SHA1ֵ�ĳ��Ȳ���ȷ��\r\n������20�ֽڵ�SHA1ֵ��"));
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
		//д��CardInfo
		if ((radioFlag == _T("MT1"))
			|| (radioFlag == _T("MT211"))
			|| (pDlg->gAtrCosType == _T("MT211_Nat+"))
			|| (pDlg->gAtrCosType == _T("MT211_SKF"))
			|| (pDlg->gAtrCosType == _T("SIM_Nat+"))
			|| (pDlg->gAtrCosType == _T("SIM_SKF"))
			)
		{
			//����ҪдMAC
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
				MessageBox(_T("SetCardInfoִ��д��SNʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
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
				MessageBox(_T("SetCardInfoִ��д��SHA1ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
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
					MessageBox(_T("SetCardInfoִ��д�뿨����ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
					return;
				}
			}
			//MessageBox(_T("��ϲ����\r\nSetCardInfoִ�гɹ���"));

			edtpcscStatus.SetWindowText(_T("��ϲ���� SetCardInfoִ�гɹ���"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
		else
		{
			byte macData[12];
			//��ҪдMAC����ȡMAC��ַ
			if (12 != edtpcscBLE.GetWindowTextLength())
			{
				MessageBox(_T("BLE��MAC��ַ���Ȳ���ȷ��\r\n������6�ֽڵ�MAC��ֵַ��"));
				return;
			}
			if (12 != edtpcscSPP.GetWindowTextLength())
			{
				MessageBox(_T("SPP��MAC��ַ���Ȳ���ȷ��\r\n������6�ֽڵ�MAC��ֵַ��"));
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
				MessageBox(_T("SetCardInfoִ��д��SNʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
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
				MessageBox(_T("SetCardInfoִ��д�뿨����ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				return;
			}
			//MessageBox(_T("��ϲ����\r\nSetCardInfoִ�гɹ���"));

			edtpcscStatus.SetWindowText(_T("��ϲ���� SetCardInfoִ�гɹ���"));
			edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		}
	}
	else
	{
		MessageBox(_T("�Բ���\r\n��ǰ��Ƭ�ǣ�") + pDlg->gAtrCosType + _T("����֧�ֱ�ҳ�������"));

		edtpcscStatus.SetWindowText(_T("�Բ��� ��ǰ��Ƭ�ǣ�") + pDlg->gAtrCosType + _T("����֧�ֱ�ҳ�������"));
		edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}	
}

boolean page2CardInfoDlg::GetSelwithSha1Data(LPCTSTR sha1,int *retSel)
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
boolean page2CardInfoDlg::GetSha1DataWithSel(CString *sha1, int inSel)
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


std::wstring AnsiToUnicode(const std::string& strAnsi)
{
	//��ȡת������Ľ��ջ�������С
	int  nUnicodeLen = ::MultiByteToWideChar(CP_ACP,
		0,
		strAnsi.c_str(),
		-1,
		NULL,
		0);
	//����ָ����С���ڴ�
	wchar_t* pUnicode = new wchar_t[nUnicodeLen + 1];
	memset((void*)pUnicode, 0, (nUnicodeLen + 1) * sizeof(wchar_t));

	//ת��
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

	// ���ļ�
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
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = combopcscSha1List1.GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	if(GetSha1DataWithSel(&strSha1, nSel))
		edtpcscSHA1_1.SetWindowText(strSha1);
}
void page2CardInfoDlg::OnCbnSelchangecombosha1list2()
{
	CString strSha1;
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = combopcscSha1List2.GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	if (GetSha1DataWithSel(&strSha1, nSel))
		edtpcscSHA1_2.SetWindowText(strSha1);
}
void page2CardInfoDlg::OnCbnSelchangecombosha1list3()
{
	CString strSha1;
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = combopcscSha1List3.GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	if (GetSha1DataWithSel(&strSha1, nSel))
		edtpcscSHA1_3.SetWindowText(strSha1);
}

void page2CardInfoDlg::OnCbnSelchangecombosha1list4()
{
	CString strSha1;
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = combopcscSha1List4.GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	if (GetSha1DataWithSel(&strSha1, nSel))
		edtpcscSHA1_4.SetWindowText(strSha1);
}
void page2CardInfoDlg::OnCbnSelchangecombosha1list5()
{
	CString strSha1;
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = combopcscSha1List5.GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	if (GetSha1DataWithSel(&strSha1, nSel))
		edtpcscSHA1_5.SetWindowText(strSha1);
}

void page2CardInfoDlg::OnBnClickedradiomt1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MT1�������ÿ����ͣ����Բ���Ҫ�κβ���
	radioFlag = _T("MT1");

	edtpcscBLE.ShowWindow(FALSE);
	edtpcscSPP.ShowWindow(FALSE);
}


void page2CardInfoDlg::OnBnClickedradiomt211()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//((CButton*)GetDlgItem(radioMT211))->SetCheck(TRUE); //ѡ��
	radioFlag = _T("MT211");
	//edtpcscBLE.SetReadOnly(TRUE);    //����Ϊֻ��״̬
	//edtpcscSPP.SetReadOnly(TRUE);    //����Ϊֻ��״̬
	edtpcscBLE.ShowWindow(FALSE);    
	edtpcscSPP.ShowWindow(FALSE);
}


void page2CardInfoDlg::OnBnClickedradiomt222a()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//((CButton*)GetDlgItem(radioMT222A))->SetCheck(TRUE); //ѡ��
	radioFlag = _T("MT222A");
	//edtpcscBLE.SetReadOnly(FALSE);    //����Ϊ��д״̬
	//edtpcscSPP.SetReadOnly(FALSE);    //����Ϊ��д״̬
	edtpcscBLE.ShowWindow(TRUE);
	edtpcscSPP.ShowWindow(TRUE);
}


void page2CardInfoDlg::OnBnClickedradiomt222c()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//((CButton*)GetDlgItem(radioMT222C))->SetCheck(TRUE); //ѡ��
	radioFlag = _T("MT222C"); 
	//edtpcscBLE.SetReadOnly(FALSE);    //����Ϊ��д״̬
	//edtpcscSPP.SetReadOnly(FALSE);    //����Ϊ��д״̬
	edtpcscBLE.ShowWindow(TRUE);
	edtpcscSPP.ShowWindow(TRUE);
}


void page2CardInfoDlg::CheckInputDataLength(int editIDC, DWORD maxLen)
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
