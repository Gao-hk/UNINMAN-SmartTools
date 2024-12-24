#pragma once

#include "PCSCReader.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

// PAGE1_APDU 对话框
class page1ApduDlg : public CDialogEx
{
	//DECLARE_DYNAMIC(PAGE1_APDU)

public:
	page1ApduDlg(CWnd* pParent = nullptr);   // 标准构造函数
	

	enum { IDD = IDD_PAGE1_APDU };

	CButton btnpcscExe;

	CListBox lstpcscHis;
	CEdit edtpcscAPDU;
	CEdit edtpcscResult;

	



	void AddLog(CString s);
	void AddHis(CString s);



protected:
	//PCSCReader* Reader;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnBnClickedbtnexe();
	afx_msg void OnLbnSelchangelsthis();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void initAPDUPage();
};
