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

	CButton page3btnpcscBoot;
	CButton page3btnpcscOpenFile;
	CButton page3btnpcscDownload;
	CButton page3btnpcscDownload_writeInfo;
	CProgressCtrl page3pcscprocess1;

	CEdit page3edtpcscCosFile;

	CEdit page3edtpcscStatus;



protected:
	MY_FUNCTION desFunc;
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	afx_msg void getCardDownloadInfo();
	afx_msg void setCardDownloadDisp(boolean bootloadStatus, boolean enableDownlaodeorBootBtnFlag);


	afx_msg boolean DownloadAndWriteInfo();
	afx_msg LRESULT OnMsg(WPARAM wParam, LPARAM lParam);
	afx_msg boolean MakeSmartCos2Bootloader(CString authKey);
	afx_msg boolean MakeJCos2Bootloader();
	afx_msg boolean MakeZKCos2Bootloader();
	afx_msg boolean checkMF();
	afx_msg boolean ExAuth(CString authKey);


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void initDownloadPage();
	afx_msg void OnBnClickedpage3btnopenfile();
	afx_msg void OnBnClickedpage3btnboot();
	afx_msg void CheckInputDataLength(int editIDC, DWORD maxLen);
	afx_msg void OnChangePage3edtble();
};
