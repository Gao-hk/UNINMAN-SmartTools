
// PCSCReaderDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPCSCReaderDemoApp: 
// �йش����ʵ�֣������ PCSCReaderDemo.cpp
//

class CPCSCReaderDemoApp : public CWinApp
{
public:
	CPCSCReaderDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPCSCReaderDemoApp theApp;