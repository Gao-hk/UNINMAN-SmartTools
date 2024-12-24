#pragma once

#include "PCSCReader.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <afxdialogex.h>
class pageNativePlus :
    public CDialogEx
{
public:
    pageNativePlus(CWnd* pParent = nullptr);   // 标准构造函数

	enum { IDD = IDD_PAGE_Native_PLUS    };

    DECLARE_MESSAGE_MAP()

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
    CImageList m_imageList;
    CTreeCtrl m_fileTree;
    byte gSelectFidByte[2];

    CBitmap m_bitmap_new;
    CBitmap m_bitmap_newFolder;
    CBitmap m_bitmap_openFolder;
    CBitmap m_bitmap_delFolder;
    CBitmap m_bitmap_newFile;

    CBitmap m_bitmap_newKeyFile;
    CBitmap m_bitmap_newKeyPairFile;
    CBitmap m_bitmap_newRecordFile;
    CBitmap m_bitmap_newCertFile;

    CBitmap m_bitmap_openFile;
    CBitmap m_bitmap_readFile;
    CBitmap m_bitmap_writeFile;
    CBitmap m_bitmap_delFile;

    afx_msg void initNativePlusage();
    afx_msg void OnBnClickedbtngetnativeplusfilelist();
    afx_msg void OnBnClickedBtnDelete();
    afx_msg void OnSelchangedFileTree(NMHDR* pNMHDR, LRESULT* pResult);

    afx_msg void OnRclickFileTree(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void CreateKeyFile();
    afx_msg void CreateBinary();
    afx_msg void CreateRecord();
    afx_msg void CreateADF();
    afx_msg void OpenMF();
    afx_msg void DelMF();
    afx_msg void OnCreatekeyinadf();
    afx_msg void OnCreatebinaryinadf();
    afx_msg void OnCreaterecordinadf();
    afx_msg void OnOpenadf();
    afx_msg void OnDeladf();

    afx_msg void OnCreatersapub();
    afx_msg void OnCreatersapri();
    afx_msg void OnCreatesm2pub();
    afx_msg void OnCreatesm2pri();
    afx_msg void OnCreatecert();
    afx_msg void OnCreatersapubinadf();
    afx_msg void OnCreatecertinadf();
    afx_msg void OnCreatersapriinadf();
    afx_msg void OnCreatesm2pubinadf();
    afx_msg void OnCreatesm2priinadf();
    afx_msg void OnIdrOpenFile();
    afx_msg void OnIdrReadFile();
    afx_msg void OnIdrWriteFile();
    afx_msg void OnIdrDeleteFile();
};


