#include "stdafx.h"
#include "afxdialogex.h"
#include <windows.h>
#include "pageNativePlus.h"
#include <string.h>

#include "CSmartToolDlg.h"

using namespace std;

pageNativePlus theApp;

#if 1
//遍历，扩展所有节点  
void   ExpandTree(CTreeCtrl* pTreeCtrl, HTREEITEM   hitem)
{
	if (!hitem)
		return;
	HTREEITEM   tmpHitem = hitem;
	pTreeCtrl->Expand(tmpHitem, TVE_EXPAND);
	tmpHitem = pTreeCtrl->GetNextItem(tmpHitem, TVGN_CHILD);
	while (tmpHitem = pTreeCtrl->GetNextItem(tmpHitem, TVGN_NEXT))
	{
		pTreeCtrl->Expand(tmpHitem, TVE_EXPAND);
		ExpandTree(pTreeCtrl, pTreeCtrl->GetNextItem(tmpHitem, TVGN_CHILD));
	}
}

//使用 ExpandTree(pTreeCtrl, pTreeCtrl->GetRootItem()); 展开所有节点

#else
//1.展开所有子节点
void ExpandTree(CTreeCtrl* pTreeCtrl, HTREEITEM hItem)
{
	HTREEITEM hChild, hNext, hParent;

	if ((!hItem) || (!pTreeCtrl))
		return;
	//存在则展开节点  
	pTreeCtrl->Expand(hItem, TVE_EXPAND);

	hChild = pTreeCtrl->GetNextItem(hItem, TVGN_CHILD);
	if (hChild)
	{//如果有子节点，展开子节点  
		ExpandTree(pTreeCtrl, hChild);
	}
	else
	{//没有子节点，寻找其兄弟节点  
		hNext = pTreeCtrl->GetNextItem(hItem, TVGN_NEXT);
		if (hNext)
		{//存在兄弟节点  
			ExpandTree(pTreeCtrl, hNext);
		}
		else
		{//不存在兄弟节点，继续找父节点  
			hParent = pTreeCtrl->GetParentItem(hItem);
			hNext = pTreeCtrl->GetNextItem(hParent, TVGN_NEXT);
			if (hNext)
				ExpandTree(pTreeCtrl, hNext);
		}
	}
}
#endif

//2.收起所有子节点
void CollapseTree(CTreeCtrl* pTreeCtrl, HTREEITEM hItem)
{
	HTREEITEM hChild, hNext, hParent;

	if ((!hItem) || (!pTreeCtrl))
		return;
	//存在则收起节点  
	pTreeCtrl->Expand(hItem, TVE_COLLAPSE);

	hChild = pTreeCtrl->GetNextItem(hItem, TVGN_CHILD);
	if (hChild)
	{//如果有子节点，收起子节点  
		CollapseTree(pTreeCtrl, hChild);
	}
	else
	{//没有子节点，寻找其兄弟节点  
		hNext = pTreeCtrl->GetNextItem(hItem, TVGN_NEXT);
		if (hNext)
		{//存在兄弟节点  
			CollapseTree(pTreeCtrl, hNext);
		}
		else
		{//不存在兄弟节点，继续找父节点  
			hParent = pTreeCtrl->GetParentItem(hItem);
			hNext = pTreeCtrl->GetNextItem(hParent, TVGN_NEXT);
			if (hNext)
				CollapseTree(pTreeCtrl, hNext);
		}
	}
}




pageNativePlus::pageNativePlus(CWnd* pParent /*=nullptr*/)
	: CDialogEx(pageNativePlus::IDD, pParent)
{

}


void pageNativePlus::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_FILE_TREE, m_fileTree);
	//DDX_Control(pDX, btnExe, btnpcscExe);
}
#define  IDM_TREEUPDATE 10001
#define IDM_TREEDELETE 10002

BEGIN_MESSAGE_MAP(pageNativePlus, CDialogEx)
	ON_BN_CLICKED(btnGetNativePlusFileList, &pageNativePlus::OnBnClickedbtngetnativeplusfilelist)
	ON_BN_CLICKED(IDC_BUTTON1, &pageNativePlus::OnBnClickedBtnDelete)
	ON_NOTIFY(TVN_SELCHANGED, IDC_FILE_TREE, &pageNativePlus::OnSelchangedFileTree)

	ON_NOTIFY(NM_RCLICK, IDC_FILE_TREE, &pageNativePlus::OnRclickFileTree)
	
	
	ON_COMMAND(ID_CreateKey, &pageNativePlus::CreateKeyFile)
	ON_COMMAND(ID_CreateBinary, &pageNativePlus::CreateBinary)
	ON_COMMAND(ID_CreateRecord, &pageNativePlus::CreateRecord)
	ON_COMMAND(ID_CreateADF, &pageNativePlus::CreateADF)
	ON_COMMAND(ID_IDR_OPENMF, &pageNativePlus::OpenMF)
	ON_COMMAND(ID_IDR_DELMF, &pageNativePlus::DelMF)
	ON_COMMAND(ID_CreateKeyInADF, &pageNativePlus::OnCreatekeyinadf)
	ON_COMMAND(ID_CreateBinaryInADF, &pageNativePlus::OnCreatebinaryinadf)
	ON_COMMAND(ID_CreateRecordInADF, &pageNativePlus::OnCreaterecordinadf)
	ON_COMMAND(ID_OpenADF, &pageNativePlus::OnOpenadf)
	ON_COMMAND(ID_DelADF, &pageNativePlus::OnDeladf)
	ON_COMMAND(ID_CreateRsaPub, &pageNativePlus::OnCreatersapub)
	ON_COMMAND(ID_CreateRsaPri, &pageNativePlus::OnCreatersapri)
	ON_COMMAND(ID_CreateSM2Pub, &pageNativePlus::OnCreatesm2pub)
	ON_COMMAND(ID_CreateSM2Pri, &pageNativePlus::OnCreatesm2pri)
	ON_COMMAND(ID_CreateCert, &pageNativePlus::OnCreatecert)
	ON_COMMAND(ID_CreateRsaPubInADF, &pageNativePlus::OnCreatersapubinadf)
	ON_COMMAND(ID_CreateCertInADF, &pageNativePlus::OnCreatecertinadf)
	ON_COMMAND(ID_CreateRsaPriInADF, &pageNativePlus::OnCreatersapriinadf)
	ON_COMMAND(ID_CreateSM2PubInADF, &pageNativePlus::OnCreatesm2pubinadf)
	ON_COMMAND(ID_CreateSM2PriInADF, &pageNativePlus::OnCreatesm2priinadf)
	ON_COMMAND(ID_IDR_OPEN_FILE, &pageNativePlus::OnIdrOpenFile)
	ON_COMMAND(ID_IDR_READ_FILE, &pageNativePlus::OnIdrReadFile)
	ON_COMMAND(ID_IDR_WRITE_FILE, &pageNativePlus::OnIdrWriteFile)
	ON_COMMAND(ID_IDR_DELETE_FILE, &pageNativePlus::OnIdrDeleteFile)
END_MESSAGE_MAP()



void pageNativePlus::initNativePlusage()
{
	
}


int BytesToInt(const unsigned char* bytes, const int length)
{
	int num = 0;
	for (int i = 0; i < length; i++)
	{
		int offset = i * 8;
		num |= (bytes[i] & 0xFF) << offset;
	}
	return num;
}

CString ToChar(byte bNum)
{
	char cTemp;
	if (bNum < 10)
	{
		cTemp = bNum + 0x30;
	}
	else
	{
		cTemp = bNum + 0x37;
	}
	return (CString)cTemp;
}

byte toHex(char a, char b)
{
	byte bTempA;
	byte bTempB;

	if (a < 0x3A)
	{
		bTempA = a - 0x30;
	}
	else
	{
		bTempA = a - 0x37;
	}

	if (b < 0x3A)
	{
		bTempB = b - 0x30;
	}
	else
	{
		bTempB = b - 0x37;
	}
	return byte(bTempA * 0x10 + bTempB);
}

CString HexToStr(byte* bByte, UINT iLength)
{
	UINT iIndex;
	CString outStr;

	for (iIndex = 0; iIndex < iLength; iIndex++)
	{
		outStr += ToChar(bByte[iIndex] >> 4 & 0x0F);
		outStr += ToChar(bByte[iIndex] & 0x0F);
	}

	return outStr;
}

int StrToHex(CString inStr, byte* pByte)
{
	UINT iIndex, iLength;

	inStr.Remove('\r');
	inStr.Remove('\n');
	inStr.Remove(' ');
	inStr.Remove('	');
	inStr.MakeUpper();
	iLength = inStr.GetLength();

	// length check 
	if (inStr.IsEmpty() || iLength % 2 == 0x01)
	{
		pByte = 0x00;
		return 0;
	}

	// change
	for (iIndex = 0; iIndex < iLength / 2; iIndex++)
	{
		if ((inStr.GetAt(iIndex * 2) > 'F') || inStr.GetAt(iIndex * 2 + 1) > 'F')
			return 0;
		pByte[iIndex] = toHex((char)inStr.GetAt(iIndex * 2), (char)inStr.GetAt(iIndex * 2 + 1));
	}
	return iIndex;
}

//Native+应用中的基本文件类型的定义
#define DF                      0x18
#define ADF                     0x18
#define EF                      0x19
#define FILE_BINARY             0x08//二进制文件
#define FILE_CLC_RCD            0x0E//循环记录文件
#define FILE_FIX_RCD            0x0A//定长记录文件
#define FILE_TLV_RCD            0x0C//变长记录文件
#define KEY_FILE                0x1F//密钥文件
#define FCI_FILE				0x0F
#define CERTIFICATE_FILE        0x1E
#define PRIVATE_FILE        	0x1D
#define PUBLICK_FILE            0x1C
#define SM2_PRIVATE_FILE    	0x1B
#define SM2_PUBLICK_FILE		0x1A
#define SYMMETRIC_KEY_FILE		0x10
#define DBA_KEY_FILE           	0x11
#define KEY_1121_FILE          	0x12
#define SM9_KEY_FILE    		0x13

void pageNativePlus::OnBnClickedbtngetnativeplusfilelist()
{
	//首先清除文件列表显示
	m_fileTree.DeleteAllItems();

	//读取文件列表
	byte fileListData[1024 * 10] = { 0 };
	int fileListDataLen = 0;
	// TODO:  在此添加控件通知处理程序代码
	CString sAPDU, sAPDU2;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString statusStr;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();	

	//读卡片内文件列表
	ReadFileListLab:
	sAPDU2 = "9801000000";
	APDULen = pDlg->Reader.StrToHex(sAPDU2, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if(RespLen !=2 )
	{
		MessageBox("返回结果长度不正确！");
		return;
	}
	else if ((Resp[0] == 0x6F)&& (Resp[1] == 0))
	{
		MessageBox("此卡片Nattive+_APP还没有执行过个人化（没有创建过文件）！");
		return;
	}
	else if (Resp[0] != 0x61)
	{
		MessageBox("返回SW不正确！");
		return;
	}

	sAPDU2 = "18C0000000";
	APDULen = pDlg->Reader.StrToHex(sAPDU2, APDU);
	APDU[4] = Resp[1];
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if (RespLen != 2+ APDU[4])
	{
		MessageBox("返回结果长度不正确！");
		return;
	}
	else if( ((Resp[APDU[4] + 0] == 0x90) && (Resp[APDU[4] + 1] == 0x00))
	  ||((Resp[APDU[4] + 0] == 0x6A)&& (Resp[APDU[4] + 1] == 0x9E)))
	{
		memcpy(fileListData + fileListDataLen, Resp, RespLen - 2);
		fileListDataLen += RespLen - 2;

		if ((Resp[APDU[4] + 0] == 0x6A) && (Resp[APDU[4] + 1] == 0x9E))
			goto ReadFileListLab;
	}
	else
	{
		MessageBox("返回SW不正确！");
		return;
	}

	//此时数据都在fileListData中，长度为fileListDataLen
	if(fileListData[0] != 0x18)
	{
		MessageBox("返回数据不正确！");
		return;
	}

	////////////////////////////////////
#define ICON_MAX_NUM	11
	HICON hIcon[ICON_MAX_NUM];		//图标句柄数组
	HTREEITEM hRoot=NULL;	//树的根节点的句柄
	HTREEITEM hCataItem = NULL;	//可表示任何一分类节点的句柄
	HTREEITEM hArtItem = NULL;	//可表示任何一文章节点的句柄

	//加载9个图标，并将它们的句柄保存到数组
	hIcon[0] = AfxGetApp()->LoadIcon(IDI_ICON_IWORK);
	hIcon[1] = AfxGetApp()->LoadIcon(IDI_ICON_FOLDER);
	hIcon[2] = AfxGetApp()->LoadIcon(IDI_ICON_KEY2);
	hIcon[3] = AfxGetApp()->LoadIcon(IDI_ICON_KEY);
	hIcon[4] = AfxGetApp()->LoadIcon(IDI_ICON_KEYPAIR);
	hIcon[5] = AfxGetApp()->LoadIcon(IDI_ICON_BIN);
	hIcon[6] = AfxGetApp()->LoadIcon(IDI_ICON_TXT);
	hIcon[7] = AfxGetApp()->LoadIcon(IDI_ICON_RECORD1);
	hIcon[8] = AfxGetApp()->LoadIcon(IDI_ICON_RECORD2);
	hIcon[9] = AfxGetApp()->LoadIcon(IDI_ICON_KEYPAIR2);
	hIcon[10] = AfxGetApp()->LoadIcon(IDI_ICON_CERT);

	//创建图像序列CImageList对象
	m_imageList.Create(32, 32, ILC_COLOR32, ICON_MAX_NUM, ICON_MAX_NUM);
	//将9个图标添加到图标序列
	for (int i = 0; i < ICON_MAX_NUM; i++)
	{
		m_imageList.Add(hIcon[i]);
	}

	//为属性控件设置图像序列
	m_fileTree.SetImageList(&m_imageList, TVSIL_NORMAL);

	CString thisTitleStr,thisNameStr;
	byte thisStrData[32];
	byte fileType,thisDataLen,thisOffset=0;
	int dispNo;
	USHORT fid;
	byte underAdfFlag = 0,thisIsAdfFla=0;
	int itemNo=0;//MF = 0;	ADF = 0xXX000000;	EF = XX(fileType)XXXX

	while (thisOffset < fileListDataLen)
	{
		fileType = fileListData[thisOffset++];

		thisDataLen = fileListData[thisOffset++];

		thisTitleStr = HexToStr(&fileListData[thisOffset], 2);

		fid = fileListData[thisOffset] * 256 + fileListData[thisOffset + 1];
		thisOffset += 2;

		thisIsAdfFla = 0;
		switch (fileType)
		{

		case DF:
			//case ADF:
			if (fid == 0x3F00)
			{
				dispNo = 0;//MF
				thisTitleStr += _T("(MF");
			}
			else
			{
				dispNo = 1;//DF\ADF
				thisTitleStr += _T("(ADF");
			}

			if (thisDataLen > 2)
			{
				memset(thisStrData, 0, 32);
				memcpy(thisStrData, &fileListData[thisOffset], thisDataLen - 2);
				thisNameStr = thisStrData;
				thisTitleStr += _T(":") + thisNameStr;
				thisOffset += thisDataLen - 2;
			}
			thisTitleStr += _T(")");

			thisIsAdfFla = 1;
			break;

		case EF:
			dispNo = 6;
			thisTitleStr += _T("(FCI文件)");
			break;
		case FCI_FILE:
			dispNo = 6;
			thisTitleStr += _T("(普通EF文件)");
			break;
		case CERTIFICATE_FILE:
			dispNo = 10;
			thisTitleStr += _T("(证书文件)");
			break;
		case FILE_BINARY:
			dispNo = 5;
			thisTitleStr += _T("(Binary)");
			break;
		case FILE_CLC_RCD:
			dispNo = 7;
			thisTitleStr += _T("(循环记录文件)");
			break;
		case FILE_FIX_RCD:
			dispNo = 7;
			thisTitleStr += _T("(定长记录文件)");
			break;
		case FILE_TLV_RCD:
			dispNo = 7;
			thisTitleStr += _T("(变长记录文件)");
			break;
		case KEY_FILE:
			dispNo = 2;
			thisTitleStr += _T("(KEY文件)");
			break;
		case PRIVATE_FILE:
			dispNo = 4;
			thisTitleStr += _T("(RSA私钥文件)");
			break;
		case PUBLICK_FILE:
			dispNo = 4;
			thisTitleStr += _T("(RSA公钥文件)");
			break;
		case SM2_PRIVATE_FILE:
			dispNo = 9;
			thisTitleStr += _T("(SM2私钥文件)");
			break;
		case SM2_PUBLICK_FILE:
			dispNo = 9;
			thisTitleStr += _T("(SM2公钥文件)");
			break;
		case SYMMETRIC_KEY_FILE:
			dispNo = 3;
			thisTitleStr += _T("(对称密钥文件)");
			break;
		case DBA_KEY_FILE:
			dispNo = 3;
			thisTitleStr += _T("(DBA密钥文件)");
			break;
		case KEY_1121_FILE:
			dispNo = 3;
			thisTitleStr += _T("(1121工作密钥文件)");
			break;
		case SM9_KEY_FILE:
			dispNo = 3;
			thisTitleStr += _T("(SM9密钥文件)");
			break;

		default:
			MessageBox("返回结果中有数据不正确！");
			return;
		}
		//插入根节点或者子节点
		if (thisIsAdfFla)
		{
			if (fid == 0x3F00)
			{
				hRoot = m_fileTree.InsertItem(thisTitleStr, dispNo, dispNo, TVI_ROOT);
				itemNo = 0;
				m_fileTree.SetItemData(hRoot, itemNo);
			}
			else
			{
				hCataItem = m_fileTree.InsertItem(thisTitleStr, dispNo, dispNo, hRoot, TVI_LAST);
				itemNo = (itemNo & 0xFF000000) + 0x01000000;
				m_fileTree.SetItemData(hCataItem, itemNo);
				underAdfFlag = 1;
			}
		}
		else
		{
			hArtItem = m_fileTree.InsertItem(thisTitleStr, dispNo, dispNo, underAdfFlag ? hCataItem : hRoot, TVI_LAST);

			itemNo = (itemNo & 0xFF00FFFF) | (fileType<<16);
			
			m_fileTree.SetItemData(hArtItem, itemNo);
		}
		itemNo++;		
	}	

	ExpandTree(&m_fileTree, m_fileTree.GetRootItem()); //展开所有节点
}


void pageNativePlus::OnBnClickedBtnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hItem = m_fileTree.GetSelectedItem();
	if (hItem == NULL)
	{
		AfxMessageBox(_T("请选择一个节点"));
		return;
	}
	//取得节点的父节点
	HTREEITEM hParent = m_fileTree.GetParentItem(hItem);
	//删除节点
	m_fileTree.DeleteItem(hItem);
	//选中其父节点
	m_fileTree.SelectItem(hParent);
	m_fileTree.Select(hParent, TVGN_DROPHILITE);

}


void pageNativePlus::OnSelchangedFileTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	HTREEITEM hItem = m_fileTree.GetSelectedItem();
	if (hItem != NULL)
	{
		m_fileTree.Select(hItem, TVGN_DROPHILITE);
		CString strtext = m_fileTree.GetItemText(hItem);
		StrToHex(strtext.Left(4), gSelectFidByte);
	}

	*pResult = 0;
}
void pageNativePlus::OnRclickFileTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
		//动态加载菜单
	CMenu menu[3];
	menu[0].LoadMenu(IDR_MENU_MF);
	menu[1].LoadMenu(IDR_MENU_ADF);
	menu[2].LoadMenu(IDR_MENU_FILE);
	CPoint pt;
	//pt = GetCurrentMessage()->pt;   //获取当前鼠标点击消息的坐标点
	GetCursorPos(&pt);
	m_fileTree.ScreenToClient(&pt);   //将鼠标的屏幕坐标，转换成树形控件的客户区坐标
	UINT uFlags = 0;
	HTREEITEM hItem = m_fileTree.HitTest(pt, &uFlags); //然后做点击测试
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))     //如果点击的位置是在节点位置上面
	{
		m_fileTree.SelectItem(hItem);
		//根据不同类型的节点弹出菜单
		CMenu* psubmenu = NULL;
		int itemNo = m_fileTree.GetItemData(hItem);
		m_fileTree.ClientToScreen(&pt);
		//int itemNo = 0;//MF = 0;	ADF = 0xXX000000;	EF = XX(fileType)XXXX
		if (itemNo == 0)//MF
		{
			psubmenu = menu[0].GetSubMenu(0);

			m_bitmap_openFolder.LoadBitmap(IDB_BITMAP_OPEN_FILE);
			m_bitmap_delFolder.LoadBitmap(IDB_BITMAP_DEL);

			psubmenu->SetMenuItemBitmaps(ID_IDR_OPENMF, MF_BYCOMMAND, &m_bitmap_openFolder, &m_bitmap_openFolder);
			psubmenu->SetMenuItemBitmaps(ID_IDR_DELMF, MF_BYCOMMAND, &m_bitmap_delFolder, &m_bitmap_delFolder);	


			m_bitmap_newFile.LoadBitmap(IDB_BITMAP_NEW_FILE);
			m_bitmap_newFolder.LoadBitmap(IDB_BITMAP_NEW_FOLDER);

			m_bitmap_newKeyFile.LoadBitmap(IDB_BITMAP_NEW_KEY);
			m_bitmap_newKeyPairFile.LoadBitmap(IDB_BITMAP_NEW_KEYPAIR);
			m_bitmap_newRecordFile.LoadBitmap(IDB_BITMAP_NEW_RECORD);
			m_bitmap_newCertFile.LoadBitmap(IDB_BITMAP_NEW_CERT);


			psubmenu->SetMenuItemBitmaps(ID_CreateKey, MF_BYCOMMAND, &m_bitmap_newKeyFile, &m_bitmap_newKeyFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateBinary, MF_BYCOMMAND, &m_bitmap_newFile, &m_bitmap_newFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateRecord, MF_BYCOMMAND, &m_bitmap_newRecordFile, &m_bitmap_newRecordFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateADF, MF_BYCOMMAND, &m_bitmap_newFolder, &m_bitmap_newFolder);
			psubmenu->SetMenuItemBitmaps(ID_CreateRsaPub, MF_BYCOMMAND, &m_bitmap_newKeyPairFile, &m_bitmap_newKeyPairFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateRsaPri, MF_BYCOMMAND, &m_bitmap_newKeyPairFile, &m_bitmap_newKeyPairFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateSM2Pub, MF_BYCOMMAND, &m_bitmap_newKeyPairFile, &m_bitmap_newKeyPairFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateSM2Pri, MF_BYCOMMAND, &m_bitmap_newKeyPairFile, &m_bitmap_newKeyPairFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateCert, MF_BYCOMMAND, &m_bitmap_newCertFile, &m_bitmap_newCertFile);
		}
		else if ((itemNo & 0x00FFFFFF) == 0)//ADF
		{
			psubmenu = menu[1].GetSubMenu(0);

			m_bitmap_openFolder.LoadBitmap(IDB_BITMAP_OPEN_FILE);
			m_bitmap_delFolder.LoadBitmap(IDB_BITMAP_DEL);

			psubmenu->SetMenuItemBitmaps(ID_OpenADF, MF_BYCOMMAND, &m_bitmap_openFolder, &m_bitmap_openFolder);
			psubmenu->SetMenuItemBitmaps(ID_DelADF, MF_BYCOMMAND, &m_bitmap_delFolder, &m_bitmap_delFolder);

			m_bitmap_newFile.LoadBitmap(IDB_BITMAP_NEW_FILE);

			m_bitmap_newKeyFile.LoadBitmap(IDB_BITMAP_NEW_KEY);
			m_bitmap_newKeyPairFile.LoadBitmap(IDB_BITMAP_NEW_KEYPAIR);
			m_bitmap_newRecordFile.LoadBitmap(IDB_BITMAP_NEW_RECORD);
			m_bitmap_newCertFile.LoadBitmap(IDB_BITMAP_NEW_CERT);

			psubmenu->SetMenuItemBitmaps(ID_CreateKeyInADF, MF_BYCOMMAND, &m_bitmap_newKeyFile, &m_bitmap_newKeyFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateBinaryInADF, MF_BYCOMMAND, &m_bitmap_newFile, &m_bitmap_newFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateRecordInADF, MF_BYCOMMAND, &m_bitmap_newRecordFile, &m_bitmap_newRecordFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateRsaPubInADF, MF_BYCOMMAND, &m_bitmap_newKeyPairFile, &m_bitmap_newKeyPairFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateRsaPriInADF, MF_BYCOMMAND, &m_bitmap_newKeyPairFile, &m_bitmap_newKeyPairFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateSM2PubInADF, MF_BYCOMMAND, &m_bitmap_newKeyPairFile, &m_bitmap_newKeyPairFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateSM2PriInADF, MF_BYCOMMAND, &m_bitmap_newKeyPairFile, &m_bitmap_newKeyPairFile);
			psubmenu->SetMenuItemBitmaps(ID_CreateCertInADF, MF_BYCOMMAND, &m_bitmap_newCertFile, &m_bitmap_newCertFile);
		}
		else//EF
		{
			m_bitmap_openFile.LoadBitmap(IDB_BITMAP_OPEN_FILE);
			m_bitmap_readFile.LoadBitmap(IDB_BITMAP_READ);
			m_bitmap_writeFile.LoadBitmap(IDB_BITMAP_WRITE);
			m_bitmap_delFile.LoadBitmap(IDB_BITMAP_DEL);

			switch ((itemNo >> 16) & 0xFF)
			{
			case EF:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case FCI_FILE:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case CERTIFICATE_FILE:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case FILE_BINARY:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case FILE_CLC_RCD:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case FILE_FIX_RCD:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case FILE_TLV_RCD:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case KEY_FILE:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case PRIVATE_FILE:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case PUBLICK_FILE:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case SM2_PRIVATE_FILE:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case SM2_PUBLICK_FILE:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case SYMMETRIC_KEY_FILE:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case DBA_KEY_FILE:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case KEY_1121_FILE:
				psubmenu = menu[2].GetSubMenu(0);
				break;
			case SM9_KEY_FILE:
				psubmenu = menu[2].GetSubMenu(0);
				break;

			default:
				MessageBox("itemNo不正确！");
				return;
			}

			psubmenu->SetMenuItemBitmaps(ID_IDR_OPEN_FILE, MF_BYCOMMAND, &m_bitmap_openFile, &m_bitmap_openFile);
			psubmenu->SetMenuItemBitmaps(ID_IDR_READ_FILE, MF_BYCOMMAND, &m_bitmap_readFile, &m_bitmap_readFile);
			psubmenu->SetMenuItemBitmaps(ID_IDR_WRITE_FILE, MF_BYCOMMAND, &m_bitmap_writeFile, &m_bitmap_writeFile);
			psubmenu->SetMenuItemBitmaps(ID_IDR_DELETE_FILE, MF_BYCOMMAND, &m_bitmap_delFile, &m_bitmap_delFile);
		}
		psubmenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}



	*pResult = 0;
}

#if 0

//A flag indicating the type of relation to hItem.This flag can be one of the following values :
//
//TVGN_CARET   Retrieves the currently selected item.
//
//TVGN_CHILD   Retrieves the first child item of the item specified by the hItem parameter.
//
//TVGN_DROPHILITE   Retrieves the item that is the target of a drag - and -drop operation.
//
//TVGN_FIRSTVISIBLE   Retrieves the first visible item.
//
//TVGN_LASTVISIBLE   Retrieves the last expanded item in the tree.This does not retrieve the last item visible in the tree - view window.
//
//TVGN_NEXT   Retrieves the next sibling item.
//
//TVGN_NEXTVISIBLE   Retrieves the next visible item that follows the specified item.
//
//TVGN_PARENT   Retrieves the parent of the specified item.
//
//TVGN_PREVIOUS   Retrieves the previous sibling item.
//
//TVGN_PREVIOUSVISIBLE   Retrieves the first visible item that precedes the specified item.
//
//TVGN_ROOT   Retrieves the first child item of the root item of which the specified item is a part.

void CTreeCtrlDemoDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText;
	GetDlgItemText(IDC_EDT_TEXT, strText);
	if (strText.GetLength() == 0)
	{
		AfxMessageBox(_T("请输入文本"));
		return;
	}
	//获取当前所选节点
	HTREEITEM hItem = m_tree.GetSelectedItem();
	//如果没有选中，则添加根节点
	if (hItem == NULL)
		hItem = TVI_ROOT;
	//节点数据
	TVINSERTSTRUCT ts = { 0 };
	//新节点的父节点
	ts.hParent = hItem;
	//新节点添加在同级节点的最后
	ts.hInsertAfter = TVI_LAST;
	//新节点的文本
	ts.item.pszText = (LPTSTR)(LPCTSTR)strText;
	//让文本成员有效
	ts.item.mask = TVIF_TEXT;
	//添加新节点
	HTREEITEM hNewItem = m_tree.InsertItem(&ts);
	//选中新节点
	m_tree.SelectItem(hNewItem);
	//确保新节点在可视范围内
	m_tree.EnsureVisible(hNewItem);
}
void CTreeCtrlDemoDlg::OnBnClickedBtnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取当前选中的节点
	HTREEITEM hItem = m_tree.GetSelectedItem();
	if (hItem == NULL)
	{
		AfxMessageBox(_T("请选择一个节点"));
		return;
	}
	CString strText;
	GetDlgItemText(IDC_EDT_TEXT, strText);
	if (strText.GetLength() == 0)
	{
		AfxMessageBox(_T("请输入文本"));
		return;
	}
	//修改节点文本
	m_tree.SetItemText(hItem, strText);
}

//删除某个节点的子节点，下面提供两种方法：
void CFileView::DelAllChildOfItem(HTREEITEM hItem)
{
	BOOL bRet = FALSE;
	HTREEITEM hChildItem = NULL;
	while (TRUE)
	{
		bRet = m_Tree.ItemHasChildren(hItem);
		if (!bRet)//没有孩子
		{
			break;
		}
		else
		{
			hChildItem = m_Tree.GetChildItem(hItem);
			m_Tree.DeleteItem(hChildItem);
		}
	}
	return;

	/*
	方法二：
	if (m_Tree.ItemHasChildren(hItem))
	{
		HTREEITEM hNextItem=NULL;
		HTREEITEM hChildItem=m_Tree.GetChildItem(hItem);
		while (hChildItem!=NULL)
		{
			hNextItem=m_Tree.GetNextItem(hChildItem,TVGN_NEXT);
			m_Tree.DeleteItem(hChildItem);
			hChildItem=hNextItem;
		}
	}
	*/
}
//定义一个递归函数, 传入一个节点, 函数如下:
BOOL DelItem(CTreeCtrl treeCtrl, HTREEITEM hItem)
{
	if (!treeCtrl.ItemHasChildren(hItem))
	{
		return FALSE;
	}
	HTREEITEM hChild = treeCtrl.GetChildItem(hItem);
	do
	{
		if (treeCtrl.ItemHasChildren(hChild))
		{
			DelItem(treeCtrl, hChild);
		}
		else
		{
			treeCtrl.DeleteItem(hChild);
		}
		hChild = treeCtrl.GetNextSiblingItem(hChild);
	} while (hChild != NULL);
}


//CTreeCtrl控件中递归删除节点
HTREEITEM CMyTree::DelChild(HTREEITEM hItem)
{
	HTREEITEM hPare = NULL;
	if (!ItemHasChildren(hItem))
	{
		if (m_iCount >= 0)
			m_iCount--; //静态成员变量
		hPare = GetParentItem(hItem);
		TRACE("Delete: %s/n", GetItemText(hItem));
		DeleteItem(hItem);
		return (m_iCount >= 0) ? DelChild(hPare) : NULL;

	}
	else
	{
		++m_iCount;
		TRACE("Node:%s/n", GetItemText(hItem));
		return DelChild(GetNextItem(hItem, TVGN_CHILD));
	}

}

#endif




void pageNativePlus::CreateKeyFile()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is CreateKeyFile");
}


void pageNativePlus::CreateBinary()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is CreateBinary");
}


void pageNativePlus::CreateRecord()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is CreateRecord");
}


void pageNativePlus::CreateADF()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is CreateADF");
}


void pageNativePlus::OpenMF()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OpenMF");
}


void pageNativePlus::DelMF()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is DelMF");
}


void pageNativePlus::OnCreatekeyinadf()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatekeyinadf");
}


void pageNativePlus::OnCreatebinaryinadf()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatebinaryinadf");
}


void pageNativePlus::OnCreaterecordinadf()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreaterecordinadf");
}


void pageNativePlus::OnOpenadf()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnOpenadf");
}


void pageNativePlus::OnDeladf()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnDeladf");
}



void pageNativePlus::OnCreatersapub()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatersapub");
}


void pageNativePlus::OnCreatersapri()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatersapri");
}


void pageNativePlus::OnCreatesm2pub()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatesm2pub");
}


void pageNativePlus::OnCreatesm2pri()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatesm2pri");
}


void pageNativePlus::OnCreatecert()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatecert");
}


void pageNativePlus::OnCreatersapubinadf()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatersapubinadf");
}


void pageNativePlus::OnCreatecertinadf()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatecertinadf");
}


void pageNativePlus::OnCreatersapriinadf()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatersapriinadf");
}


void pageNativePlus::OnCreatesm2pubinadf()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatesm2pubinadf");
}


void pageNativePlus::OnCreatesm2priinadf()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnCreatesm2priinadf");
}


void pageNativePlus::OnIdrOpenFile()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnIdrOpenFile");
}


void pageNativePlus::OnIdrReadFile()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnIdrReadFile");
}


void pageNativePlus::OnIdrWriteFile()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnIdrWriteFile");
}


void pageNativePlus::OnIdrDeleteFile()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("This is OnIdrDeleteFile");
}
