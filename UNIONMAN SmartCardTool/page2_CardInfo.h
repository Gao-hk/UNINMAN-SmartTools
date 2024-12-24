#pragma once

#include "PCSCReader.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

// PAGE2_CardInfo 对话框
class page2CardInfoDlg : public CDialogEx
{
	//DECLARE_DYNAMIC(PAGE2_CardInfo)

public:
	page2CardInfoDlg(CWnd* pParent = nullptr);   // 标准构造函数


	enum { IDD = IDD_PAGE2_CardInfo };

	CEdit edtpcscBLE;
	CEdit edtpcscSPP;
	CEdit edtpcscCosVer;
	CEdit edtpcscSn;
	CEdit edtpcscStatus;

	CEdit edtpcscAuthKey;

	CEdit edtpcscSHA1_1;
	CEdit edtpcscSHA1_2;
	CEdit edtpcscSHA1_3;
	CEdit edtpcscSHA1_4;
	CEdit edtpcscSHA1_5;
	

	CComboBox combopcscSha1List1;
	CComboBox combopcscSha1List2;
	CComboBox combopcscSha1List3;
	CComboBox combopcscSha1List4;
	CComboBox combopcscSha1List5;

	CButton btnpcscGet;
	CButton btnpcscSet;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CString radioFlag;
	afx_msg boolean checkMF();
	afx_msg boolean ExAuth(CString authKey);
	afx_msg void OnBnClickedbtnGet();
	afx_msg void OnBnClickedbtnSet();

	afx_msg CString swapBigEndandLittleEnd(byte* bByte, UINT iLength);
	afx_msg int readSha1List();
	afx_msg void getCardTypeInfo();
	afx_msg void LoadSha1List();
	afx_msg void OnCbnSelchangecombosha1list1();
	afx_msg void OnCbnSelchangecombosha1list2();
	afx_msg void OnCbnSelchangecombosha1list3();
	afx_msg void OnCbnSelchangecombosha1list4();
	afx_msg void OnCbnSelchangecombosha1list5();

	afx_msg boolean GetSelwithSha1Data(LPCTSTR sha1, int* retSel);
	afx_msg boolean GetSha1DataWithSel(CString* sha1, int inSel);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void initCardInfoPage();
	afx_msg void OnBnClickedradiomt1();
	afx_msg void OnBnClickedradiomt211();
	afx_msg void OnBnClickedradiomt222a();
	afx_msg void OnBnClickedradiomt222c();
	afx_msg void CheckInputDataLength(int editIDC, DWORD maxLen);
	afx_msg void OnChangeEdtble();
	afx_msg void OnChangeEdtauthkey();
	afx_msg void OnChangeEdtsha11();
	afx_msg void OnChangeEdtsha12();
	afx_msg void OnChangeEdtsha13();
	afx_msg void OnChangeEdtsha14();
	afx_msg void OnChangeEdtsha15();
	afx_msg void OnChangeEdtsn();
	afx_msg void OnChangeEdtspp();
};
