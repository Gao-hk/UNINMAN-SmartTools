#pragma once
#include "afxdialogex.h"
#include "resource.h"


// page5SetFunc 对话框

class page5SetFuncDlg : public CDialogEx
{
	//DECLARE_DYNAMIC(page5SetFuncDlg)

public:
	page5SetFuncDlg(CWnd* pParent = nullptr);   // 标准构造函数

	enum { IDD = IDD_PAGE5_SetFunc };

	CEdit edtTimerHH;
	CEdit edtTimerMM;
	CEdit edtTimerSS;

	CEdit edtCountry[32];
	CEdit edtMCC[32];
	CEdit edtIP[32];
	CEdit edtSetStartID;

	CListBox lstMccIp;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnClickedPage5devauthbtn();
	afx_msg void initSetFuncPage();
	afx_msg boolean SKF_DevAuth(CString authKey);
	afx_msg void OnBnClickedpage5getswitchstatus();
	afx_msg void OnBnClickedpage5setswitchstatus();
	afx_msg void OnBnClickedpage5getmccip();
	afx_msg void OnBnClickedpage5setmccip();
	afx_msg void OnBnClickedpage5gettimer();
	afx_msg void OnBnClickedpage5settimer();
	afx_msg void OnBnClickedpage5closetimer();
	afx_msg void ClearMCC_IP_POOL();
	afx_msg void OnBnClickedpage5fillclearoriginalmccip();
	afx_msg void OnBnClickedpage5clearmccip();
};
