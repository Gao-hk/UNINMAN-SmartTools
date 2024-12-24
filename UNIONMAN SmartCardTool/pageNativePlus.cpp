#include "stdafx.h"
#include "afxdialogex.h"
#include <windows.h>
#include "pageNativePlus.h"
#include <string.h>

#include "CSmartToolDlg.h"

using namespace std;

pageNativePlus theApp;

#if 1
//��������չ���нڵ�  
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

//ʹ�� ExpandTree(pTreeCtrl, pTreeCtrl->GetRootItem()); չ�����нڵ�

#else
//1.չ�������ӽڵ�
void ExpandTree(CTreeCtrl* pTreeCtrl, HTREEITEM hItem)
{
	HTREEITEM hChild, hNext, hParent;

	if ((!hItem) || (!pTreeCtrl))
		return;
	//������չ���ڵ�  
	pTreeCtrl->Expand(hItem, TVE_EXPAND);

	hChild = pTreeCtrl->GetNextItem(hItem, TVGN_CHILD);
	if (hChild)
	{//������ӽڵ㣬չ���ӽڵ�  
		ExpandTree(pTreeCtrl, hChild);
	}
	else
	{//û���ӽڵ㣬Ѱ�����ֵܽڵ�  
		hNext = pTreeCtrl->GetNextItem(hItem, TVGN_NEXT);
		if (hNext)
		{//�����ֵܽڵ�  
			ExpandTree(pTreeCtrl, hNext);
		}
		else
		{//�������ֵܽڵ㣬�����Ҹ��ڵ�  
			hParent = pTreeCtrl->GetParentItem(hItem);
			hNext = pTreeCtrl->GetNextItem(hParent, TVGN_NEXT);
			if (hNext)
				ExpandTree(pTreeCtrl, hNext);
		}
	}
}
#endif

//2.���������ӽڵ�
void CollapseTree(CTreeCtrl* pTreeCtrl, HTREEITEM hItem)
{
	HTREEITEM hChild, hNext, hParent;

	if ((!hItem) || (!pTreeCtrl))
		return;
	//����������ڵ�  
	pTreeCtrl->Expand(hItem, TVE_COLLAPSE);

	hChild = pTreeCtrl->GetNextItem(hItem, TVGN_CHILD);
	if (hChild)
	{//������ӽڵ㣬�����ӽڵ�  
		CollapseTree(pTreeCtrl, hChild);
	}
	else
	{//û���ӽڵ㣬Ѱ�����ֵܽڵ�  
		hNext = pTreeCtrl->GetNextItem(hItem, TVGN_NEXT);
		if (hNext)
		{//�����ֵܽڵ�  
			CollapseTree(pTreeCtrl, hNext);
		}
		else
		{//�������ֵܽڵ㣬�����Ҹ��ڵ�  
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

//Native+Ӧ���еĻ����ļ����͵Ķ���
#define DF                      0x18
#define ADF                     0x18
#define EF                      0x19
#define FILE_BINARY             0x08//�������ļ�
#define FILE_CLC_RCD            0x0E//ѭ����¼�ļ�
#define FILE_FIX_RCD            0x0A//������¼�ļ�
#define FILE_TLV_RCD            0x0C//�䳤��¼�ļ�
#define KEY_FILE                0x1F//��Կ�ļ�
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
	//��������ļ��б���ʾ
	m_fileTree.DeleteAllItems();

	//��ȡ�ļ��б�
	byte fileListData[1024 * 10] = { 0 };
	int fileListDataLen = 0;
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString sAPDU, sAPDU2;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;
	CString statusStr;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();	

	//����Ƭ���ļ��б�
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
		MessageBox("���ؽ�����Ȳ���ȷ��");
		return;
	}
	else if ((Resp[0] == 0x6F)&& (Resp[1] == 0))
	{
		MessageBox("�˿�ƬNattive+_APP��û��ִ�й����˻���û�д������ļ�����");
		return;
	}
	else if (Resp[0] != 0x61)
	{
		MessageBox("����SW����ȷ��");
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
		MessageBox("���ؽ�����Ȳ���ȷ��");
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
		MessageBox("����SW����ȷ��");
		return;
	}

	//��ʱ���ݶ���fileListData�У�����ΪfileListDataLen
	if(fileListData[0] != 0x18)
	{
		MessageBox("�������ݲ���ȷ��");
		return;
	}

	////////////////////////////////////
#define ICON_MAX_NUM	11
	HICON hIcon[ICON_MAX_NUM];		//ͼ��������
	HTREEITEM hRoot=NULL;	//���ĸ��ڵ�ľ��
	HTREEITEM hCataItem = NULL;	//�ɱ�ʾ�κ�һ����ڵ�ľ��
	HTREEITEM hArtItem = NULL;	//�ɱ�ʾ�κ�һ���½ڵ�ľ��

	//����9��ͼ�꣬�������ǵľ�����浽����
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

	//����ͼ������CImageList����
	m_imageList.Create(32, 32, ILC_COLOR32, ICON_MAX_NUM, ICON_MAX_NUM);
	//��9��ͼ����ӵ�ͼ������
	for (int i = 0; i < ICON_MAX_NUM; i++)
	{
		m_imageList.Add(hIcon[i]);
	}

	//Ϊ���Կؼ�����ͼ������
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
			thisTitleStr += _T("(FCI�ļ�)");
			break;
		case FCI_FILE:
			dispNo = 6;
			thisTitleStr += _T("(��ͨEF�ļ�)");
			break;
		case CERTIFICATE_FILE:
			dispNo = 10;
			thisTitleStr += _T("(֤���ļ�)");
			break;
		case FILE_BINARY:
			dispNo = 5;
			thisTitleStr += _T("(Binary)");
			break;
		case FILE_CLC_RCD:
			dispNo = 7;
			thisTitleStr += _T("(ѭ����¼�ļ�)");
			break;
		case FILE_FIX_RCD:
			dispNo = 7;
			thisTitleStr += _T("(������¼�ļ�)");
			break;
		case FILE_TLV_RCD:
			dispNo = 7;
			thisTitleStr += _T("(�䳤��¼�ļ�)");
			break;
		case KEY_FILE:
			dispNo = 2;
			thisTitleStr += _T("(KEY�ļ�)");
			break;
		case PRIVATE_FILE:
			dispNo = 4;
			thisTitleStr += _T("(RSA˽Կ�ļ�)");
			break;
		case PUBLICK_FILE:
			dispNo = 4;
			thisTitleStr += _T("(RSA��Կ�ļ�)");
			break;
		case SM2_PRIVATE_FILE:
			dispNo = 9;
			thisTitleStr += _T("(SM2˽Կ�ļ�)");
			break;
		case SM2_PUBLICK_FILE:
			dispNo = 9;
			thisTitleStr += _T("(SM2��Կ�ļ�)");
			break;
		case SYMMETRIC_KEY_FILE:
			dispNo = 3;
			thisTitleStr += _T("(�Գ���Կ�ļ�)");
			break;
		case DBA_KEY_FILE:
			dispNo = 3;
			thisTitleStr += _T("(DBA��Կ�ļ�)");
			break;
		case KEY_1121_FILE:
			dispNo = 3;
			thisTitleStr += _T("(1121������Կ�ļ�)");
			break;
		case SM9_KEY_FILE:
			dispNo = 3;
			thisTitleStr += _T("(SM9��Կ�ļ�)");
			break;

		default:
			MessageBox("���ؽ���������ݲ���ȷ��");
			return;
		}
		//������ڵ�����ӽڵ�
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

	ExpandTree(&m_fileTree, m_fileTree.GetRootItem()); //չ�����нڵ�
}


void pageNativePlus::OnBnClickedBtnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM hItem = m_fileTree.GetSelectedItem();
	if (hItem == NULL)
	{
		AfxMessageBox(_T("��ѡ��һ���ڵ�"));
		return;
	}
	//ȡ�ýڵ�ĸ��ڵ�
	HTREEITEM hParent = m_fileTree.GetParentItem(hItem);
	//ɾ���ڵ�
	m_fileTree.DeleteItem(hItem);
	//ѡ���丸�ڵ�
	m_fileTree.SelectItem(hParent);
	m_fileTree.Select(hParent, TVGN_DROPHILITE);

}


void pageNativePlus::OnSelchangedFileTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		//��̬���ز˵�
	CMenu menu[3];
	menu[0].LoadMenu(IDR_MENU_MF);
	menu[1].LoadMenu(IDR_MENU_ADF);
	menu[2].LoadMenu(IDR_MENU_FILE);
	CPoint pt;
	//pt = GetCurrentMessage()->pt;   //��ȡ��ǰ�������Ϣ�������
	GetCursorPos(&pt);
	m_fileTree.ScreenToClient(&pt);   //��������Ļ���꣬ת�������οؼ��Ŀͻ�������
	UINT uFlags = 0;
	HTREEITEM hItem = m_fileTree.HitTest(pt, &uFlags); //Ȼ�����������
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))     //��������λ�����ڽڵ�λ������
	{
		m_fileTree.SelectItem(hItem);
		//���ݲ�ͬ���͵Ľڵ㵯���˵�
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
				MessageBox("itemNo����ȷ��");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText;
	GetDlgItemText(IDC_EDT_TEXT, strText);
	if (strText.GetLength() == 0)
	{
		AfxMessageBox(_T("�������ı�"));
		return;
	}
	//��ȡ��ǰ��ѡ�ڵ�
	HTREEITEM hItem = m_tree.GetSelectedItem();
	//���û��ѡ�У�����Ӹ��ڵ�
	if (hItem == NULL)
		hItem = TVI_ROOT;
	//�ڵ�����
	TVINSERTSTRUCT ts = { 0 };
	//�½ڵ�ĸ��ڵ�
	ts.hParent = hItem;
	//�½ڵ������ͬ���ڵ�����
	ts.hInsertAfter = TVI_LAST;
	//�½ڵ���ı�
	ts.item.pszText = (LPTSTR)(LPCTSTR)strText;
	//���ı���Ա��Ч
	ts.item.mask = TVIF_TEXT;
	//����½ڵ�
	HTREEITEM hNewItem = m_tree.InsertItem(&ts);
	//ѡ���½ڵ�
	m_tree.SelectItem(hNewItem);
	//ȷ���½ڵ��ڿ��ӷ�Χ��
	m_tree.EnsureVisible(hNewItem);
}
void CTreeCtrlDemoDlg::OnBnClickedBtnEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ��ǰѡ�еĽڵ�
	HTREEITEM hItem = m_tree.GetSelectedItem();
	if (hItem == NULL)
	{
		AfxMessageBox(_T("��ѡ��һ���ڵ�"));
		return;
	}
	CString strText;
	GetDlgItemText(IDC_EDT_TEXT, strText);
	if (strText.GetLength() == 0)
	{
		AfxMessageBox(_T("�������ı�"));
		return;
	}
	//�޸Ľڵ��ı�
	m_tree.SetItemText(hItem, strText);
}

//ɾ��ĳ���ڵ���ӽڵ㣬�����ṩ���ַ�����
void CFileView::DelAllChildOfItem(HTREEITEM hItem)
{
	BOOL bRet = FALSE;
	HTREEITEM hChildItem = NULL;
	while (TRUE)
	{
		bRet = m_Tree.ItemHasChildren(hItem);
		if (!bRet)//û�к���
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
	��������
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
//����һ���ݹ麯��, ����һ���ڵ�, ��������:
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


//CTreeCtrl�ؼ��еݹ�ɾ���ڵ�
HTREEITEM CMyTree::DelChild(HTREEITEM hItem)
{
	HTREEITEM hPare = NULL;
	if (!ItemHasChildren(hItem))
	{
		if (m_iCount >= 0)
			m_iCount--; //��̬��Ա����
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
	// TODO: �ڴ���������������
	MessageBox("This is CreateKeyFile");
}


void pageNativePlus::CreateBinary()
{
	// TODO: �ڴ���������������
	MessageBox("This is CreateBinary");
}


void pageNativePlus::CreateRecord()
{
	// TODO: �ڴ���������������
	MessageBox("This is CreateRecord");
}


void pageNativePlus::CreateADF()
{
	// TODO: �ڴ���������������
	MessageBox("This is CreateADF");
}


void pageNativePlus::OpenMF()
{
	// TODO: �ڴ���������������
	MessageBox("This is OpenMF");
}


void pageNativePlus::DelMF()
{
	// TODO: �ڴ���������������
	MessageBox("This is DelMF");
}


void pageNativePlus::OnCreatekeyinadf()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatekeyinadf");
}


void pageNativePlus::OnCreatebinaryinadf()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatebinaryinadf");
}


void pageNativePlus::OnCreaterecordinadf()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreaterecordinadf");
}


void pageNativePlus::OnOpenadf()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnOpenadf");
}


void pageNativePlus::OnDeladf()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnDeladf");
}



void pageNativePlus::OnCreatersapub()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatersapub");
}


void pageNativePlus::OnCreatersapri()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatersapri");
}


void pageNativePlus::OnCreatesm2pub()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatesm2pub");
}


void pageNativePlus::OnCreatesm2pri()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatesm2pri");
}


void pageNativePlus::OnCreatecert()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatecert");
}


void pageNativePlus::OnCreatersapubinadf()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatersapubinadf");
}


void pageNativePlus::OnCreatecertinadf()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatecertinadf");
}


void pageNativePlus::OnCreatersapriinadf()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatersapriinadf");
}


void pageNativePlus::OnCreatesm2pubinadf()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatesm2pubinadf");
}


void pageNativePlus::OnCreatesm2priinadf()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnCreatesm2priinadf");
}


void pageNativePlus::OnIdrOpenFile()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnIdrOpenFile");
}


void pageNativePlus::OnIdrReadFile()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnIdrReadFile");
}


void pageNativePlus::OnIdrWriteFile()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnIdrWriteFile");
}


void pageNativePlus::OnIdrDeleteFile()
{
	// TODO: �ڴ���������������
	MessageBox("This is OnIdrDeleteFile");
}
