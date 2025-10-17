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

	CEdit edtpcscCosVer;
	CEdit edtpcscSn;
	CEdit edtpcscStatus;


	CEdit edtpcscCosIP;
	CEdit edtpcscIP11;
	CEdit edtpcscIP12;
	CEdit edtpcscIP13;
	CEdit edtpcscIP14;
	CEdit edtpcscIP15;
	CEdit edtpcscIP21;
	CEdit edtpcscIP22;
	CEdit edtpcscIP23;
	CEdit edtpcscIP24;
	CEdit edtpcscIP25;

	CEdit edtpcscSHA_00;
	CEdit edtpcscSHA_10;
	CEdit edtpcscSHA_20;
	CEdit edtpcscSHA_30;
	CEdit edtpcscSHA_40;
	CEdit edtpcscSHA_50;

	CEdit edtpcscSHA_01;
	CEdit edtpcscSHA_11;
	CEdit edtpcscSHA_21;
	CEdit edtpcscSHA_31;
	CEdit edtpcscSHA_41;
	CEdit edtpcscSHA_51;

	CEdit edtpcscSHA_02;
	CEdit edtpcscSHA_12;
	CEdit edtpcscSHA_22;
	CEdit edtpcscSHA_32;
	CEdit edtpcscSHA_42;
	CEdit edtpcscSHA_52;

	CEdit edtpcscSHA_03;
	CEdit edtpcscSHA_13;
	CEdit edtpcscSHA_23;
	CEdit edtpcscSHA_33;
	CEdit edtpcscSHA_43;
	CEdit edtpcscSHA_53;	

	CEdit edtpcscSHA_04;
	CEdit edtpcscSHA_05;

	CButton btnpcscGet;
	CButton btnpcscSet;

	CButton btnpcscGetVer;
	CButton btnpcscGetSN;
	CButton btnpcscSetSN;

	CButton btnpcscGetIP;
	CButton btnpcscSetIP;

	CButton btnpcscGetSHAList;
	CButton btnpcscSetSHAList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg boolean checkMF();
	afx_msg boolean SKF_DevAuth(CString authKey);
	afx_msg void OnBnClickedbtnGet();
	afx_msg void OnBnClickedbtnSet();

	afx_msg CString swapBigEndandLittleEnd(byte* bByte, UINT iLength);
	afx_msg void getCardTypeInfo();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void initCardInfoPage();
	afx_msg void CheckInputDataLength(int editIDC, DWORD maxLen);
	afx_msg void OnChangeEdtauthkey();
	afx_msg void OnChangeEdtsha_10();
	afx_msg void OnChangeEdtsha_20();
	afx_msg void OnChangeEdtsha_30();
	afx_msg void OnChangeEdtsha_40();
	afx_msg void OnChangeEdtsha_50();

	afx_msg void OnChangeEdtsha_11();
	afx_msg void OnChangeEdtsha_21();
	afx_msg void OnChangeEdtsha_31();
	afx_msg void OnChangeEdtsha_41();
	afx_msg void OnChangeEdtsha_51();

	afx_msg void OnChangeEdtsha_12();
	afx_msg void OnChangeEdtsha_22();
	afx_msg void OnChangeEdtsha_32();
	afx_msg void OnChangeEdtsha_42();
	afx_msg void OnChangeEdtsha_52();

	afx_msg void OnChangeEdtsha_13();
	afx_msg void OnChangeEdtsha_23();
	afx_msg void OnChangeEdtsha_33();
	afx_msg void OnChangeEdtsha_43();
	afx_msg void OnChangeEdtsha_53();

	afx_msg void OnChangeEdtsn();
	//afx_msg void OnChangeEdtspp();
	afx_msg void OnBnClickedbtngetver();
	afx_msg void OnBnClickedbtngetsn();
	afx_msg void OnBnClickedbtnsetsn();

	afx_msg bool checkEdtSHA1_FillWithFF();
	afx_msg bool checkEdtSHA1();
	afx_msg bool checkEdtSHA256();
	afx_msg void OnBnClickedbtngetshalist();
	afx_msg void OnBnClickedbtnsetshalist();
	afx_msg void OnBnClickedbtngetip();
	afx_msg void OnBnClickedbtnsetip();
};
