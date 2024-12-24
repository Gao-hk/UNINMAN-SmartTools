#pragma once

#include "PCSCReader.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "..\des源码\my_function.h"

// PAGE2_CardInfo 对话??
class page3downloadDlg : public CDialogEx
{
	//DECLARE_DYNAMIC(PAGE2_CardInfo)

public:
	page3downloadDlg(CWnd* pParent = nullptr);   // 标准构造函数


	enum { IDD = IDD_PAGE3_Download };
	CString radioFlag;


	CComboBox page3combopcscSha1List1;
	CComboBox page3combopcscSha1List2;
	CComboBox page3combopcscSha1List3;
	CComboBox page3combopcscSha1List4;
	CComboBox page3combopcscSha1List5;

	CButton page3btnpcscBoot;
	CButton page3btnpcscOpenFile;
	CButton page3btnpcscDownload;
	CButton page3btnpcscDownload_writeInfo;
	CProgressCtrl page3pcscprocess1;

	CEdit page3edtpcscCosFile;

	CEdit page3edtpcscBLE;
	CEdit page3edtpcscSPP;
	CEdit page3edtpcscSn;
	CEdit page3edtpcscStatus;

	CEdit page3edtpcscSHA1_1;
	CEdit page3edtpcscSHA1_2;
	CEdit page3edtpcscSHA1_3;
	CEdit page3edtpcscSHA1_4;
	CEdit page3edtpcscSHA1_5;


protected:
	MY_FUNCTION desFunc;
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void setSHA1Disp(boolean dispFlag, boolean clearCheckSha1Flag);
	afx_msg void setTypeDisp(boolean dispFlag, boolean clearCheckTypeFlag);
	afx_msg void setMacDisp(boolean dispFlag);
	afx_msg void setSnDisp(boolean dispFlag, boolean clearCheckSnFlag);
	afx_msg void setAppDisp();

	afx_msg void Loadpage3Sha1List(); 
	afx_msg void getCardDownloadInfo();
	afx_msg void clearCardDownloadInfoDisp();
	afx_msg void setCardDownloadDisp(boolean bootloadStatus, boolean enableDownlaodeorBootBtnFlag);
	afx_msg void OnCbnSelchangepage3combosha1list1();
	afx_msg void OnCbnSelchangepage3combosha1list2();
	afx_msg void OnCbnSelchangepage3combosha1list3();
	afx_msg void OnCbnSelchangepage3combosha1list4();
	afx_msg void OnCbnSelchangepage3combosha1list5();

	afx_msg boolean Getpage3SelwithSha1Data(LPCTSTR sha1, int* retSel);
	afx_msg boolean Getpage3Sha1DataWithSel(CString* sha1, int inSel);

	afx_msg boolean DownloadAndWriteInfo();
	afx_msg LRESULT OnMsg(WPARAM wParam, LPARAM lParam);
	afx_msg boolean MakeSmartCos2Bootloader(CString authKey);
	afx_msg boolean MakeJCos2Bootloader();
	afx_msg boolean MakeZKCos2Bootloader();
	afx_msg boolean processScript(CString scriptFlag);
	afx_msg boolean checkMF();
	afx_msg boolean ExAuth(CString authKey);


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void initDownloadPage();
	afx_msg int readpage3Sha1List();
	afx_msg void OnBnClickedwriteinfo();
	afx_msg void OnBnClickedpage3btnopenfile();
	afx_msg void OnBnClickedpage3btnboot();
	afx_msg void OnBnClickedpage3radiomt222a();
	afx_msg void OnBnClickedpage3radiomt222c();
	afx_msg void OnBnClickedpage3radiomt211();
	afx_msg void CheckInputDataLength(int editIDC, DWORD maxLen);
	afx_msg void OnChangePage3edtble();
	afx_msg void OnChangePage3edtsn();
	afx_msg void OnChangePage3edtsha11();
	afx_msg void OnChangePage3edtsha12();
	afx_msg void OnChangePage3edtsha13();
	afx_msg void OnChangePage3edtsha14();
	afx_msg void OnChangePage3edtsha15();
};
