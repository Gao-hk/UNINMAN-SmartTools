// PAGE1_APDU.cpp: 实现文件
//

//#include "pch.h"
#include "PAGE1_APDU.h"
#include "stdafx.h"
#include "CSmartToolDlg.h"
#include "afxdialogex.h"

// PAGE1_APDU 对话框

page1ApduDlg::page1ApduDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(page1ApduDlg::IDD, pParent)
{
	
}


void page1ApduDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, btnExe, btnpcscExe);
	DDX_Control(pDX, lstHis, lstpcscHis);
	DDX_Control(pDX, edtAPDU, edtpcscAPDU);
	DDX_Control(pDX, edtexeResult, edtpcscResult);
}


BEGIN_MESSAGE_MAP(page1ApduDlg, CDialogEx)
	ON_BN_CLICKED(btnExe, &page1ApduDlg::OnBnClickedbtnexe)
	ON_LBN_SELCHANGE(lstHis, &page1ApduDlg::OnLbnSelchangelsthis)
END_MESSAGE_MAP()


// PAGE1_APDU 消息处理程序

void page1ApduDlg::initAPDUPage()
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//Get Card Type
	if (((pDlg->Reader.ActiveReader() == ""))  
		|| (0 == lstrcmp(pDlg->gAtrCosType, _T("卡片已断开"))))
	{
		edtpcscResult.SetReadOnly(TRUE);    //设置为只读状态
		edtpcscAPDU.SetReadOnly(TRUE);    //设置为只读状态

		lstpcscHis.EnableWindow(false);
		btnpcscExe.EnableWindow(false);
	}
	else 
	{
		edtpcscResult.SetReadOnly(false);    //设置为读写状态
		edtpcscAPDU.SetReadOnly(false);    //设置为读写状态

		lstpcscHis.EnableWindow(TRUE);
		btnpcscExe.EnableWindow(TRUE);
	}
}

void page1ApduDlg::AddLog(CString s)
{
	CString orgText;
	edtpcscResult.GetWindowText(orgText);
	orgText += s + _T("\r\n");
	edtpcscResult.SetWindowText(orgText);
	edtpcscResult.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}

void page1ApduDlg::AddHis(CString s)
{
	int Index = lstpcscHis.FindString(0, s);
	if (Index < 0)
	{
		lstpcscHis.AddString(s);
	}
}

void page1ApduDlg::OnBnClickedbtnexe()//Button：执行
{
	// TODO:  在此添加控件通知处理程序代码
	CString sAPDU;
	byte APDU[1000];
	byte Resp[1000];
	DWORD APDULen = 0;
	DWORD RespLen = 1000;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	edtpcscAPDU.GetWindowText(sAPDU);
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	if (APDULen == 0)
	{
		AddLog(_T("APDU解析错误"));
		return;
	}
	memset(Resp, 0, 1000);
	AddLog(_T("执行：") + sAPDU);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		AddLog(pDlg->Reader.GetError());
		return;
	}
	AddHis(sAPDU);
	AddLog(_T("返回：") + pDlg->Reader.HexToStr(Resp, RespLen));
}


void page1ApduDlg::OnLbnSelchangelsthis()//APDU List
{
	// TODO:  在此添加控件通知处理程序代码
	CString SelAPDU;
	int selIndex = lstpcscHis.GetCurSel();
	if (selIndex < 0)return;
	lstpcscHis.GetText(selIndex, SelAPDU);
	edtpcscAPDU.SetWindowText(SelAPDU);
}
