#pragma once

#include "PCSCReader.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "..\desÔ´Âë\my_function.h"

// PAGE2_CardInfo
class page4AppletLOADDlg : public CDialogEx
{
	//DECLARE_DYNAMIC(PAGE2_CardInfo)

public:
	page4AppletLOADDlg(CWnd* pParent = nullptr);   


	enum { IDD = IDD_PAGE4_CapLoadandInstall};

	CListBox page4listpcsc;

	CEdit page4edtpcscCapFile;
	CEdit page4edtpcscStatus;

	CEdit page4edtpcscISD;
	CEdit page4edtpcscS_ENC;
	CEdit page4edtpcscS_MAC;
	CEdit page4edtpcscDEK;

	CComboBox page4comboxpcscAid;

	CButton page4btnpcscGetCardStatus;
	CButton page4btnpcscLoadandInstall;
	CButton page4btnpcscOpenFile;
	CProgressCtrl page4pcscprocess1;


protected:
	MY_FUNCTION desFunc;
	virtual void DoDataExchange(CDataExchange* pDX);    

	afx_msg void getJavaCardInfo();
	afx_msg void setAppletLoadDisp(boolean bootloadStatus);
	afx_msg byte javaCardAuth();
	afx_msg void AddJavaCardinfo(CString s); 
	afx_msg void dispCSJavaCardInfo();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void initAppletLOADPage();
	afx_msg void OnBnClickedpage4btnopenfile();
	afx_msg void OnBnClickedpage4btnloadandinstall();
	afx_msg void OnCbnSelchangepage4comboxaid();
	afx_msg void OnBnClickedpage4btngetcardstatus();
	afx_msg void CheckInputDataLength(int editIDC, DWORD maxLen);
	afx_msg void OnChangePage4edtisd();
	afx_msg void OnChangePage4edtdek();
	afx_msg void OnChangePage4edtsEnc();
	afx_msg void OnChangePage4edtsMac();
	afx_msg void OnEditchangePage4comboxaid();
};
