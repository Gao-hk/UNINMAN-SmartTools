#pragma once
#include "afxdialogex.h"


// UKeyLoader 对话框

class UKeyLoader : public CDialogEx
{
	DECLARE_DYNAMIC(UKeyLoader)

public:
	UKeyLoader(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UKeyLoader();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE_UKeyOTA };
#endif

	CButton btnpcscOpenUKeyBin;
	CButton btnpcscGenCipherBinSCT;

	CEdit edtpcscCosFile_UKeyBin;
	CEdit edtpcscUKeyOTAStatus;

	CProgressCtrl pcscukeyOTAprocess;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbtnopenukeybin();
	afx_msg void OnBnClickedbtngencipherbinsct();
	afx_msg boolean GenUKEYfirmwarecipher();
};
