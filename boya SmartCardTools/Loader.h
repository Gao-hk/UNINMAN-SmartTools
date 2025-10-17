#pragma once
#include "afxdialogex.h"


// Loader 对话框

class Loader : public CDialogEx
{
	DECLARE_DYNAMIC(Loader)

public:
	Loader(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Loader();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE_CardOTA };
#endif

	CButton btnpcscOpenFile_sfm25;
	CButton btnpcscGenCipherSCT;
	CButton btnpcscOpenFile_bysct;
	CButton btnpcscGetCosVer;
	CButton btnpcscVersionRollback;
	CButton btnpcscFirmwareUpdate;

	CEdit edtpcscCosFile_sfm25;
	CEdit edtpcscCosFile_bysct;
	CEdit edtpcscCardOTAStatus;

	CProgressCtrl pcsccardOTAprocess;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedsfm25();
	afx_msg void OnBnClickedbysct();
	afx_msg void OnBnClickedbtngenciphersct();
	afx_msg void OnBnClickedbtngetcosver();
	afx_msg void OnBnClickedbtnversionrollback();
	afx_msg void OnBnClickedbtnfirmwareupdate();

	afx_msg boolean Genfirmwarecipher();
	afx_msg boolean Download_Firmwarecipher();
};
