//Download by http://www.NewXing.com
// progress.h : main header file for the PROGRESS application
//

#if !defined(AFX_PROGRESS_H__DB3A5AA7_6278_4B57_8D84_898593B2B3BA__INCLUDED_)
#define AFX_PROGRESS_H__DB3A5AA7_6278_4B57_8D84_898593B2B3BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProgressApp:
// See progress.cpp for the implementation of this class
//

class CProgressApp : public CWinApp
{
public:
	CProgressApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProgressApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESS_H__DB3A5AA7_6278_4B57_8D84_898593B2B3BA__INCLUDED_)
