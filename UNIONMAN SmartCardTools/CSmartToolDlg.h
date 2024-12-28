
// PCSC Reader DemoDlg.h :
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "PCSCReader.h"
#include "PAGE2_CardInfo.h"
#include "PAGE3_download.h"
#include "page4_AppletLoad.h"
#include "PAGE1_APDU.h"
#include "pageNativePlus.h"
#include "Loader.h"
#include "UKeyLoader.h"



// CSmartToolDlg
class CSmartToolDlg : public CDialogEx
{
public:
	CSmartToolDlg(CWnd* pParent = NULL);	

	enum { IDD = IDD_SMARTTOOL_DIALOG	};

	CTabCtrl	m_tab;
	PCSCReader Reader;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	


protected:
	HICON m_hIcon;

	page1ApduDlg m_page1;
	page2CardInfoDlg m_page2;
	pageNativePlus m_page3;
	page3downloadDlg m_page4;
	page4AppletLOADDlg m_page5;
	Loader m_page6;
	UKeyLoader m_page7;

	boolean flag_page1=false;
	boolean flag_page2 = false;
	boolean flag_page3 = false;
	boolean flag_page4 = false;
	boolean flag_page5 = false;


	void SetDlgStatus();
	void LoadReaders();
	void LoadReadersList();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	CString gAtrCosType;
	CButton btnpcsReaders;
	CButton btnpcscReset;
	CComboBox comboReaderList;
	CListBox lstpcscReaders;
	afx_msg void OnBnClickedbtnreset();
	CStatic lbpcscActiveReader;
	afx_msg boolean GetgAtrCosType(CString &ATR);
	afx_msg void OnCbnSelchangecomboreaderlist();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CButton btnpcscConnect;
	afx_msg void reConnect();
	afx_msg void reConnectForContinue();
	afx_msg void OnBnClickedbtnconnect();
	afx_msg void OnDropdownComboreaderlist();
};
