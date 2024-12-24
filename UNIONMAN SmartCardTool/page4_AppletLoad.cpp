#include "stdafx.h"
#include "page4_AppletLoad.h"
#include "CSmartToolDlg.h"
#include "afxdialogex.h"

#include "afxwin.h"
#include "afxcmn.h"


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include<io.h>   //C����ͷ�ļ�
#include<iostream>   //for system();

#include <fstream>
#include <iostream>
#include <cmath>

#include "tchar.h"
#include "progress.h"






// PAGE4 �Ի���

page4AppletLOADDlg::page4AppletLOADDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(page4AppletLOADDlg::IDD, pParent)
{

}


void page4AppletLOADDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
		
	DDX_Control(pDX, page4list, page4listpcsc);

	DDX_Control(pDX, page4edtCapFile, page4edtpcscCapFile);
	DDX_Control(pDX, page4edtStatus, page4edtpcscStatus);

	DDX_Control(pDX, page4comboxAid, page4comboxpcscAid);
	DDX_Control(pDX, page4edtISD, page4edtpcscISD);
	DDX_Control(pDX, page4edtS_ENC, page4edtpcscS_ENC);
	DDX_Control(pDX, page4edtS_MAC, page4edtpcscS_MAC);
	DDX_Control(pDX, page4edtDEK, page4edtpcscDEK);	

	DDX_Control(pDX, page4btnGetCardStatus, page4btnpcscGetCardStatus);
	DDX_Control(pDX, page4btnLoadandInstall, page4btnpcscLoadandInstall);
	DDX_Control(pDX, page4btnOpenFile,page4btnpcscOpenFile);
	DDX_Control(pDX, page4process1,page4pcscprocess1);
}


BEGIN_MESSAGE_MAP(page4AppletLOADDlg, CDialogEx)
	ON_BN_CLICKED(page4btnOpenFile, &page4AppletLOADDlg::OnBnClickedpage4btnopenfile)
	ON_BN_CLICKED(page4btnLoadandInstall, &page4AppletLOADDlg::OnBnClickedpage4btnloadandinstall)
	ON_CBN_SELCHANGE(page4comboxAid, &page4AppletLOADDlg::OnCbnSelchangepage4comboxaid)
	ON_BN_CLICKED(page4btnGetCardStatus, &page4AppletLOADDlg::OnBnClickedpage4btngetcardstatus)
	ON_EN_CHANGE(page4edtISD, &page4AppletLOADDlg::OnChangePage4edtisd)
	ON_EN_CHANGE(page4edtDEK, &page4AppletLOADDlg::OnChangePage4edtdek)
	ON_EN_CHANGE(page4edtS_ENC, &page4AppletLOADDlg::OnChangePage4edtsEnc)
	ON_EN_CHANGE(page4edtS_MAC, &page4AppletLOADDlg::OnChangePage4edtsMac)
	ON_CBN_EDITCHANGE(page4comboxAid, &page4AppletLOADDlg::OnEditchangePage4comboxaid)
END_MESSAGE_MAP()





// PAGE2_CardInfo ��Ϣ�������
void page4AppletLOADDlg::setAppletLoadDisp(boolean bootloadStatus)
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	page4comboxpcscAid.ShowWindow(bootloadStatus);
	page4edtpcscISD.ShowWindow(bootloadStatus);
	page4edtpcscS_ENC.ShowWindow(bootloadStatus);
	page4edtpcscS_MAC.ShowWindow(bootloadStatus);
	page4edtpcscDEK.ShowWindow(bootloadStatus);

	page4edtpcscCapFile.ShowWindow(bootloadStatus);
	page4btnpcscLoadandInstall.ShowWindow(bootloadStatus);
	page4btnpcscOpenFile.ShowWindow(bootloadStatus);
	page4pcscprocess1.ShowWindow(bootloadStatus);

	page4listpcsc.ShowWindow(bootloadStatus);
	page4btnpcscGetCardStatus.ShowWindow(bootloadStatus);

	((CEdit*)GetDlgItem(IDC_STATIC_ISD))->ShowWindow(bootloadStatus);
	((CEdit*)GetDlgItem(IDC_STATIC_SENC))->ShowWindow(bootloadStatus);
	((CEdit*)GetDlgItem(IDC_STATIC_SMAC))->ShowWindow(bootloadStatus);
	((CEdit*)GetDlgItem(IDC_STATIC_DEK))->ShowWindow(bootloadStatus);
	((CEdit*)GetDlgItem(IDC_STATIC_AID))->ShowWindow(bootloadStatus);
	if (bootloadStatus)
	{
		if (pDlg->gAtrCosType == _T("�ڿ�_JCOS"))
		{
			page4edtpcscISD.SetWindowText(_T("A0000001510000"));
			page4edtpcscS_ENC.SetWindowText(_T("404142434445464748494A4B4C4D4E4F"));
			page4edtpcscS_MAC.SetWindowText(_T("404142434445464748494A4B4C4D4E4F"));
			page4edtpcscDEK.SetWindowText(_T("404142434445464748494A4B4C4D4E4F"));
		}
		else if (pDlg->gAtrCosType == _T("�㱦_JCOS"))
		{
			page4edtpcscISD.SetWindowText(_T("A0000001510000"));
			page4edtpcscS_ENC.SetWindowText(_T("AEA57E0042780CEBBBD7CA2FE63CFF05"));
			page4edtpcscS_MAC.SetWindowText(_T("888D0508C5AF62E085F7D3FB713DBA33"));
			page4edtpcscDEK.SetWindowText(_T("42C9F4D5271376425FC49D5C7E697CA0"));
		}
		else
		{
			page4edtpcscISD.SetWindowText(_T("A000000003000000"));
			page4edtpcscS_ENC.SetWindowText(_T("404142434445464748494A4B4C4D4E4F"));
			page4edtpcscS_MAC.SetWindowText(_T("404142434445464748494A4B4C4D4E4F"));
			page4edtpcscDEK.SetWindowText(_T("404142434445464748494A4B4C4D4E4F"));
		}
	}
	page4listpcsc.ResetContent();
	page4edtpcscStatus.SetWindowText(_T(""));
	page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}
void page4AppletLOADDlg::getJavaCardInfo()
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//Get Card Type
	if ((pDlg->gAtrCosType == _T("CS.JCOS"))
		|| (pDlg->gAtrCosType == _T("THD88_JCOS"))
		|| (pDlg->gAtrCosType == _T("�ڿ�_JCOS")))
	{
		setAppletLoadDisp(TRUE);
	}
	
	else
	{
		setAppletLoadDisp(FALSE); 
		if (pDlg->gAtrCosType == _T("�㱦_JCOS"))
		{
			MessageBox(_T("��⣺�˹����ݲ�֧�ֺ㱦��SCP10����COS��"));
		}
	}
}
void page4AppletLOADDlg::initAppletLOADPage()
{
	getJavaCardInfo();
}






///////////////////////////////////////////////////////////////////////////////////

//CAP�ļ��������������Ҳ��cap�ļ���
//CAP�ļ�����12�������
//Component Type				Value
//COMPONENT_Header				1
//COMPONENT_Directory			2
//COMPONENT_Applet				3
//COMPONENT_Import				4
//COMPONENT_ConstantPool		5
//COMPONENT_Class				6
//COMPONENT_Method				7
//COMPONENT_StaticField			8
//COMPONENT_ReferenceLocation	9
//COMPONENT_Export				10
//COMPONENT_Descriptor			11
//COMPONENT_Debug				12

//һ��������CAP�ļ�����Applet��Export��Debug����ǿ�ѡ�⣬������Ϊ��ѡ��
//ÿ�������װ��һ��CAP����������Jar���С�����ڿ���ֻ������5�������
//COMPONET_Method��COMPONET_Class��COMPONET_ConstantPool��COMPONET_StaticField�� COMPONET_Export��
//��������ֻ�ǰ�װʱ��ȡ������Ϣ�����ڿ��б��档

//�Ƽ���CAP�����װ˳��
//1.    COMPONENT_Header
//2.    COMPONENT_Directory
//3.    COMPONENT_Import
//4.    COMPONENT_Applet
//5.    COMPONENT_Class
//6.    COMPONENT_Method
//7.    COMPONENT_StaticField
//8.    COMPONENT_Export
//9.    COMPONENT_ConstantPool
//10.   COMPONENT_ReferenceLocation
//11.   COMPONENT_Descriptor(optional)
//
//COMPONENT_Debug�������Ҫ���ص����ڡ�

byte componentTagList[11] = {1,2,4,3,6,7,8,10,5,9,11};//�������11Ϊ��ѡ��ģ����12����Ҫ���ء��������ƱȽ��ϸ�Ŀ����ж����12��û�м��ϣ�������ϻᱨ��SW=6402��
//���е��������ͨ�ýṹ��ʽ�����£�
struct component {
	byte *pTag;      //�޷��ŵ��ֽ����͵����ݱ������ͣ�tagΪ��������ţ���������������Ƶ�˳���1��12����
	unsigned short size;    //�޷���˫�ֽڵ����ݱ������ͣ�sizeΪ�ɱ䳤������info[]��Ԫ�ظ���
	//byte* pInfo;   //����info[]�к��������������Ϣ�����ݸ�������Բ�ͬ��������ͬ
};

unsigned int getBigEndInt(unsigned char* pAddr)
{
	return(((*pAddr)<<24) | ((*(pAddr+1)) << 16) | ((*(pAddr + 2)) << 8) | (*(pAddr + 3)));
}
unsigned int getLitEndInt(unsigned char* pAddr)
{
	return(((*(pAddr+3)) << 24) | ((*(pAddr + 2)) << 16) | ((*(pAddr + 1)) << 8) | (*pAddr));
}

unsigned short getBigEndShort(unsigned char* pAddr)
{
	return(((*pAddr) << 8) | (*(pAddr + 1)));
}
unsigned short getLitEndShort(unsigned char* pAddr)
{
	return(((*(pAddr + 1)) << 8) | (*pAddr));
}

//�μ���ҳ��https://xz.aliyun.com/t/3994
#define TAG_FileEntryHeader 0x504b0304
#define TAG_DataDescriptor 0x504b0708
#define TAG_FileHeader 0x504b0102
#define TAG_FileHeaderEnd 0x504b0506
byte analysisCapFile(unsigned char* pCapData, unsigned int capDataLength, unsigned char* apduData, unsigned int *apduDataLength, unsigned char* capAIDLV, unsigned char* appletAIDCLVO)
{
	unsigned short fileNameLength_ofthisComponent;
	unsigned short extendedFieldLength_ofthisComponent;
	unsigned short zipNotesLength_ofthisComponent;
	unsigned int pCapDataOffset;
	//unsigned char* pthisData;
	component thisComponent, componentList[13];
	CString outDataStr;
	unsigned int outDataLength=0;
	unsigned int outDataOffset;
	unsigned int compressedSize;
	int index,thisLength;

	unsigned int thisCapTag;
	//unsigned int apduDataStr;
	byte tagData;

	memset(componentList, 0x00, sizeof(componentList));

	pCapDataOffset = 0;
	while (pCapDataOffset < capDataLength)
	{
		thisCapTag = getBigEndInt(pCapData + pCapDataOffset);
		
		switch (thisCapTag)
		{
		case TAG_FileEntryHeader://0x504b0304 �ļ�ʵ��ͷ��File Entry Header��
			compressedSize = getLitEndShort(pCapData + pCapDataOffset + 18);
			fileNameLength_ofthisComponent = getLitEndShort(pCapData + pCapDataOffset + 26);
			extendedFieldLength_ofthisComponent = getLitEndShort(pCapData + pCapDataOffset + 28);

			if (compressedSize)//ѹ�����С������0
			{
				thisComponent.pTag = pCapData + pCapDataOffset + 30 + fileNameLength_ofthisComponent + extendedFieldLength_ofthisComponent;
				tagData = *thisComponent.pTag;
				if ((tagData == 0) || (tagData > 12))
					return 2;//tag����ȷ,tagΪ��������ţ�����˳���1��12����
				thisComponent.size = getBigEndShort(pCapData + pCapDataOffset + 30 + fileNameLength_ofthisComponent + extendedFieldLength_ofthisComponent + 1);
				//thisComponent.pInfo = pCapData + pCapDataOffset + 30 + fileNameLength_ofthisComponent + extendedFieldLength_ofthisComponent + 3;

				//����ǰcomponent��Ϣ�ݴ浽component�б��У��Ա�������APDU����ʹ�á�
				componentList[tagData].pTag = thisComponent.pTag;
				componentList[tagData].size = thisComponent.size;
				//componentList[thisComponent.tag].pInfo = thisComponent.pInfo;
				pCapDataOffset += 30 + fileNameLength_ofthisComponent + extendedFieldLength_ofthisComponent + 3 + thisComponent.size;
			}
			else//ѹ�����С����0��Ӧ������������Ϣ��ѹ�����С,δѹ����С����0 �ڱ�����չͷTAG_DataDescriptor�л���� ����֪JCIDE����CAP�ļ��������ʽ��
			{//��������Ϣ������δ֪��ͨ������TAG_DataDescriptorȷ��ƫ��
				pCapDataOffset += 30 + fileNameLength_ofthisComponent + extendedFieldLength_ofthisComponent;
				while (pCapDataOffset < capDataLength)
				{
					if (TAG_DataDescriptor == getBigEndInt(pCapData + pCapDataOffset))
						break;
					pCapDataOffset++;
				}
			}
			break;

		case TAG_DataDescriptor://0x504b0708 ������������Data descriptor�� 
			//���ڱ�ʾ�ļ�ѹ��������ֻ�����ļ�ʵ����ͨ�ñ���ֶεĵ�3bitλΪ1ʱ�Ż���֡�һ��zip��û�������������������Ӧ�ı����ʽ���¡�
			pCapDataOffset += 16;//16
			break;

		case TAG_FileHeader://0x504b0102 �ļ�ͷ��File Header��
			fileNameLength_ofthisComponent = getLitEndShort(pCapData + pCapDataOffset + 28);
			extendedFieldLength_ofthisComponent = getLitEndShort(pCapData + pCapDataOffset + 30);
			pCapDataOffset += 46 + fileNameLength_ofthisComponent + extendedFieldLength_ofthisComponent;
			break;

		case TAG_FileHeaderEnd://0x504b0506 Ŀ¼������ʶ
			zipNotesLength_ofthisComponent = getLitEndShort(pCapData + pCapDataOffset + 20);
			pCapDataOffset += 22 + zipNotesLength_ofthisComponent;
			break;

		default:
			return 1;//CAP�ļ���ʽ����ȷ
		}
	}
	//���Ƽ���CAP�����װ˳��
	//�����ܳ��ȣ�������TL
	for (index = 1; index <= 12; index++)
	{
		//if (((11 != index) && (12 != index))//�������11Ϊ��ѡ������12����Ҫ����
		if (((12 != index))//�������11Ϊ��ѡ������12����Ҫ���ء��������ƱȽ��ϸ�Ŀ����ж����12��û�м��ϣ�������ϻᱨ��SW=6402��
			&&(componentList[index].pTag != 0))
		{
			if (*componentList[index].pTag == index)
				outDataLength += 3 + componentList[index].size;
		}
	}
	outDataOffset = 0;
	apduData[outDataOffset++] = 0xC4;
	if(outDataLength<0x80)
		apduData[outDataOffset++] = outDataLength;
	else if (outDataLength < 0x100)
	{
		apduData[outDataOffset++] = 0x81;
		apduData[outDataOffset++] = outDataLength;
	}
	else if (outDataLength < 0x10000)
	{
		apduData[outDataOffset++] = 0x82;
		apduData[outDataOffset++] = (outDataLength>>8)&0xFF;
		apduData[outDataOffset++] = outDataLength&0xFF;
	}
	else if (outDataLength < 0x80000)
	{
		apduData[outDataOffset++] = 0x83;
		apduData[outDataOffset++] = (outDataLength >> 16) & 0xFF;
		apduData[outDataOffset++] = (outDataLength >> 8) & 0xFF;
		apduData[outDataOffset++] = outDataLength & 0xFF;
	}
	else
	{
		return 3;//�ܳ���̫��
	}
	//��˳������V
	for (index = 0; index < sizeof(componentTagList); index++)
	{
		byte tag = componentTagList[index];

		//if (((11 != tag) && (12 != tag))//�������11Ϊ��ѡ������12����Ҫ���ء��������ƱȽ��ϸ�Ŀ����ж����12��û�м��ϣ�������ϻᱨ��SW=6402��
		if (((12 != tag))//�������11Ϊ��ѡ������12����Ҫ����
			&&(componentList[tag].pTag != 0))
		{
			if (*componentList[tag].pTag == tag)
			{
				thisLength = componentList[tag].size + 3;
				memcpy(apduData + outDataOffset, componentList[tag].pTag, thisLength);
				if (tag == 1)
				{
					memcpy(capAIDLV, componentList[tag].pTag + 3 + 9, *(componentList[tag].pTag + 3 + 9) + 1);
				}
				else if (tag == 3)
				{
					memcpy(appletAIDCLVO, componentList[tag].pTag + 3, getBigEndShort(componentList[tag].pTag + 1));
				}
				outDataOffset += thisLength;
			}
		}
	}
	*apduDataLength = outDataOffset;
	return 0;
}



byte page4AppletLOADDlg::javaCardAuth()
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	CString sAPDU, sAPDU2;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;

	CString isdStr;

	page4edtpcscISD.GetWindowText(isdStr);
	byte isdLen[1];
	isdLen[0] = isdStr.GetLength()/2;

	sAPDU.Format(_T("%s %s %s"), _T("00A40400"), pDlg->Reader.HexToStr(isdLen, 1), isdStr);
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return false;
	}
	if ((Resp[0] != 0x61) && (Resp[0] != 0x90))
	{
		MessageBox(_T("ѡ��ISDʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.SetWindowText(_T("ѡ��ISDʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return false;
	}

	//Initialize Update
	//8050000008 + 0102030405060708; [400:41C] ; SW = 9000sAPDU.Format(_T("%s"), _T("00A4040000") + pDlg->Reader.HexToStr(&isdLen, 1) + isdStr);
	CString hostchallenge = _T("0102030405060708");
	sAPDU.Format(_T("%s %s"), _T("8050000008"),hostchallenge);
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return false;
	}
	if ((Resp[0] != 0x61)|| (Resp[1] != 0x1C))
	{
		MessageBox(_T("Initialize Update ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.SetWindowText(_T("Initialize Update ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return false;
	}
	sAPDU.Format(_T("%s"), _T("00C000001C"));
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return false;
	}
	if ((RespLen != 0x1E) || (Resp[0x1C] != 0x90) || (Resp[0x1D] != 0x00))
	{
		MessageBox(_T("Initialize Update ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.SetWindowText(_T("Initialize Update ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return false;
	}
	//ENC SessionKey
	//Fun_DesEnCBC(0000000000000000, 0182 + [40D:40E] + 000000000000000000000000, 404142434445464748494A4B4C4D4E4F, [521:530])

	//ʹ����Կ0x83C45926A7F6DF1B852D90AE1EBC4703����uidPadData
	byte senc[16], smac[16], inputData[32] = { 0 }, SENC_SessionKey[16], CMAC_SessionKey[16], outputData[32];
	byte icv[8] = { 0 };
	CString sencStr;
	page4edtpcscS_ENC.GetWindowText(sencStr);
	pDlg->Reader.StrToHex(sencStr, senc);
	inputData[0] = 0x01;
	inputData[1] = 0x82;
	inputData[2] = Resp[0x0C];
	inputData[3] = Resp[0x0D];
	desFunc.EncryptCBC(DES_2, senc, icv, 16, inputData, SENC_SessionKey);
	//MessageBox(_T("SENC_SessionKey = ") + pDlg->Reader.HexToStr(SENC_SessionKey,16));

	//Card Cryptogram
	pDlg->Reader.StrToHex(hostchallenge, inputData);
	memcpy(inputData+8, Resp + 0x0C, 8);
	pDlg->Reader.StrToHex(_T("8000000000000000"), inputData + 16);
	desFunc.EncryptCBC(DES_2, SENC_SessionKey, icv, 24, inputData, outputData);
	byte cardCryptogram[8];
	memcpy(cardCryptogram, outputData +16, 8);
	//MessageBox(_T("Card Cryptogram = ") + pDlg->Reader.HexToStr(Resp + 20, 8));
	//MessageBox(_T("����Card Cryptogram = ") + pDlg->Reader.HexToStr(cardCryptogram, 8));
	if(0 != memcmp(cardCryptogram, Resp+20,8))
	{
		page4edtpcscStatus.SetWindowText(_T("Card Cryptogram ��֤ʧ��"));
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(_T("Card Cryptogram ��֤ʧ��"));
		return false;
	}

	//Host Cryptogram
	//Fun_DesEnCBC(0000000000000000, [40D:414] + 01020304050607088000000000000000, [521:530], [531:548])
	memcpy(inputData, Resp + 0x0C, 8);
	pDlg->Reader.StrToHex(hostchallenge, inputData + 8);
	pDlg->Reader.StrToHex(_T("8000000000000000"), inputData + 16);
	desFunc.EncryptCBC(DES_2, SENC_SessionKey, icv, 24, inputData, outputData);
	byte hostCryptogram[8];
	memcpy(hostCryptogram, outputData + 16, 8);

	//MessageBox(_T("����host Cryptogram = ") + pDlg->Reader.HexToStr(hostCryptogram, 8));

	//MAC SessionKey
	//Fun_DesEnCBC(0000000000000000, 0101 + [40D:40E] + 000000000000000000000000, 404142434445464748494A4B4C4D4E4F, [621:630])
	CString smacStr;
	page4edtpcscS_MAC.GetWindowText(smacStr);
	pDlg->Reader.StrToHex(smacStr, smac);
	inputData[0] = 0x01;
	inputData[1] = 0x01;
	inputData[2] = Resp[0x0C];
	inputData[3] = Resp[0x0D];
	memset(inputData+4,0,12);
	desFunc.EncryptCBC(DES_2, smac, icv, 16, inputData, CMAC_SessionKey);

	//MAC
	//Fun_MAC2(0000000000000000, [621:630], 8482000010 + [541:548], [661:668])
	//P1=00:���ڴ���ȫ��Ϣ�����ǿ���ֱ��ʹ���������������upload���Բ��ô�C_MAC��
	pDlg->Reader.StrToHex(_T("8482000010"), inputData);
	memcpy(inputData + 5, hostCryptogram, 8);
	pDlg->Reader.StrToHex(_T("800000"), inputData+13);
	desFunc.mac_encrypt_919(DES_2, CMAC_SessionKey, 16, inputData, outputData);


	//External Authentification
	//8482000010 + [541:548] + [661:668]; SW = 9000
	sAPDU.Format(_T("%s %s %s"), _T("8482000010"), pDlg->Reader.HexToStr(hostCryptogram,8), pDlg->Reader.HexToStr(outputData, 8));
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return false;
	}
	if ((RespLen!=2)||(Resp[0] != 0x90) || (Resp[1] != 0x00))
	{
		MessageBox(_T("External Authentification ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.SetWindowText(_T("External Authentification ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return false;
	}
	return true;
}

void page4AppletLOADDlg::OnBnClickedpage4btnopenfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_fName, FileTitle;
	CString Filter;

	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	//Get Card Type//Get Card Type
	if ((pDlg->gAtrCosType != _T("CS.JCOS"))
		&& (pDlg->gAtrCosType != _T("THD88_JCOS"))
		&& (pDlg->gAtrCosType != _T("�ڿ�_JCOS")))
	{
		MessageBox(_T("��⣺�˿�Ƭ��о��Java Card��������֪Java Card����֧�ְ�װApplet��"));
		return;
	}

	Filter = _T("Java Card CAP File(*.cap)|*.cap||");

	CFileDialog dlgOpen(TRUE, 0, 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, (LPCTSTR)Filter, NULL);
	if (dlgOpen.DoModal() == IDOK)
	{
		m_fName = dlgOpen.GetPathName();//·������
	}
	else
		return;

	page4edtpcscCapFile.SetWindowText(m_fName);

	CString filePath, openInfo;
	byte analysisCapFileStatus;

	page4edtpcscCapFile.GetWindowText(filePath);
	if (filePath == _T(""))
	{
		MessageBox(_T("δѡ��CAP�ļ�������ѡ��CAP�ļ���"));
		return;
	}

	//��
	FILE* pFile = fopen(filePath, _T("rb"));
	byte* pBuf;
	fseek(pFile, 0, SEEK_END);  //��λ���ļ�ĩβ
	int len = ftell(pFile);  //���ļ�����
	if (len > 0x07FFFF)
	{
		MessageBox(_T("CAP�ļ�̫�󣬲�֧�֣�"));
		return;
	}
	pBuf = new byte[len + 1];
	rewind(pFile);  //���¶�λָ�뵽�ļ���ʼ��
	fread(pBuf, 1, len, pFile);
	fclose(pFile);

	//��ʱCAP�ļ��е����ݶ��Ѵ�ŵ�pBuf��

	byte* pWriteBuf;
	pWriteBuf = new byte[len];
	unsigned int writeLen;

	unsigned char capAIDLV[17], appletAIDCLVO[256];

	analysisCapFileStatus = analysisCapFile(pBuf, len, pWriteBuf, &writeLen, capAIDLV, appletAIDCLVO);
	switch (analysisCapFileStatus)
	{
	case 1://CAP�ļ���ʽ����ȷ
		MessageBox(_T("CAP�ļ���ʽ����ȷ��"));
		return;
	case 2://tag����ȷ,tagΪ��������ţ�����˳���1��12����
		MessageBox(_T("���������tag����ȷ��ֵӦ����1��12��"));
		return;
	case 3://�ܳ���̫��
		MessageBox(_T("�ܳ���̫�󣬲�֧�֣�"));
		return;
	case 0:
	default:
		break;
	}
	//���������Ҫ����E8ָ������ݶ���pWriteBuf�У�����ΪwriteLen

	CString comboxStr;
	int offset = 1;
	page4comboxpcscAid.ResetContent();

	for (byte i=0; i < appletAIDCLVO[0]; i++)
	{
		comboxStr = pDlg->Reader.HexToStr(appletAIDCLVO + offset + 1, appletAIDCLVO[offset]);
		page4comboxpcscAid.InsertString(-1, comboxStr);
		offset += appletAIDCLVO[offset]+1;
	}
	page4comboxpcscAid.SetCurSel(0);
}

void page4AppletLOADDlg::OnBnClickedpage4btnloadandinstall()
{
	page4listpcsc.ResetContent();
	page4edtpcscStatus.SetWindowText(_T(""));
	page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	CString filePath, openInfo;
	byte analysisCapFileStatus;

	CString sStatus;
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	CString sAPDU, sAPDU2;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;

	UpdateData(TRUE);
	page4edtpcscStatus.SetWindowText(_T("��ʼ����......"));
	page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);	
	page4pcscprocess1.SetPos(0);
	UpdateData(FALSE);
	UpdateWindow();

	page4edtpcscCapFile.GetWindowText(filePath);
	if (filePath == _T(""))
	{
		MessageBox(_T("δѡ��CAP�ļ�������ѡ��CAP�ļ���"));
		return;
	}

	//��
	FILE* pFile = fopen(filePath, _T("rb"));
	byte* pBuf;
	fseek(pFile, 0, SEEK_END);  //��λ���ļ�ĩβ
	int len = ftell(pFile);  //���ļ�����
	if (len > 0x07FFFF)
	{
		MessageBox(_T("CAP�ļ�̫�󣬲�֧�֣�"));
		return;
	}
	pBuf = new byte[len + 1];
	rewind(pFile);  //���¶�λָ�뵽�ļ���ʼ��
	fread(pBuf, 1, len, pFile);
	fclose(pFile);

	//��ʱCAP�ļ��е����ݶ��Ѵ�ŵ�pBuf��

	byte* pWriteBuf;
	pWriteBuf = new byte[len];
	unsigned int writeLen;

	unsigned char capAIDLV[17], appletAIDCLVO[256];

	analysisCapFileStatus = analysisCapFile(pBuf, len, pWriteBuf, &writeLen, capAIDLV, appletAIDCLVO);
	switch (analysisCapFileStatus)
	{
	case 1://CAP�ļ���ʽ����ȷ
		MessageBox(_T("CAP�ļ���ʽ����ȷ��"));
		return;
	case 2://tag����ȷ,tagΪ��������ţ�����˳���1��12����
		MessageBox(_T("���������tag����ȷ��ֵӦ����1��12��"));
		return;
	case 3://�ܳ���̫��
		MessageBox(_T("�ܳ���̫�󣬲�֧�֣�"));
		return;
	case 0:
	default:
		break;
	}
	//���������Ҫ����E8ָ������ݶ���pWriteBuf�У�����ΪwriteLen

	//����Java���İ�ȫ����֤
	if (!javaCardAuth())
	{
		MessageBox(_T("��Ƭ��֤ʧ�ܣ����ɼ���LOAD��"));
		return;
	}
	page4edtpcscStatus.SetWindowText(_T("��Ƭ��֤ͨ����"));

	//delete cap��capΪ����Ҫ��װ��cap��
	CString capAIDstr;
	capAIDstr.Format(_T("%s %s"), _T("4F"), pDlg->Reader.HexToStr(capAIDLV, capAIDLV[0]+1));
	//80E40080 Lc 4F Len(AID) AID
	byte byteLen[1];
	byteLen[0] = capAIDstr.GetLength()/2;
	sAPDU.Format(_T("%s %s"), _T("80E40080") , pDlg->Reader.HexToStr(byteLen, 1) + capAIDstr);
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	//��ʼ
	page4edtpcscStatus.SetWindowText(_T("��ʼLOAD"));

	//INSTALL[for load]
	//80E60200 Lc capAIDLV ISDLV 00000000
	CString isdStr, sAPDUData;
	byte isdLen[1], Lc[1];
	capAIDstr.Format(_T("%s"), pDlg->Reader.HexToStr(capAIDLV, capAIDLV[0] + 1));
	page4edtpcscISD.GetWindowText(isdStr);
	isdLen[0] = isdStr.GetLength() / 2;
	//sAPDUData.Format(_T("%s"), capAIDstr + pDlg->Reader.HexToStr(isdLen, 1) + isdStr + _T("000000"));//isdStrҲ�ɲ�Ҫ������L�ó�00����
	sAPDUData.Format(_T("%s %s"), capAIDstr , _T("00000000"));//isdStrҲ�ɲ�Ҫ������L�ó�00���ɡ�Ŀǰ��֪�ڿ��Ĳ�֧��+��ȫ��
	Lc[0] = sAPDUData.GetLength() / 2;
	sAPDU.Format(_T("%s %s %s"), _T("80E60200") , pDlg->Reader.HexToStr(Lc, 1) , sAPDUData);
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if ((RespLen != 2) || (Resp[0] != 0x61) || (Resp[1] != 0x01))
	{
		MessageBox(_T("INSTALL[for load]  ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.SetWindowText(_T("INSTALL[for load]  ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	int writeOffset = 0, writeLenLeft = writeLen;
	int steps= writeLen / 0xFF + 1 + 20,stepIndex=0;
	/// ////
	UpdateData(TRUE);
	page4pcscprocess1.SetRange32(0, steps);//�趨�������ؼ��ķ�Χ�����޺�����
	stepIndex = 10;
	page4pcscprocess1.SetPos(stepIndex);

	sStatus.Format(_T("Loadding %d%%"), stepIndex * 100 / steps);
	page4edtpcscStatus.SetWindowText(sStatus);
	page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	page4pcscprocess1.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);
	UpdateWindow();


	//LOAD Command
	//80E800+���+Lc+ data
	//80E880+���+Lc+ data
	//����󳤶ȷ���APDU����Lc=FF
	byte indexandLc[2] = { 0 };
	page4edtpcscStatus.SetWindowText(_T("Applet loading ......"));
	while (writeLenLeft)
	{
		if (writeLenLeft > 0xFF)
		{
			indexandLc[1] = 0xFF;
			sAPDUData = pDlg->Reader.HexToStr(pWriteBuf + writeOffset, indexandLc[1]);
			sAPDU.Format(_T("%s %s %s"), _T("80E800") , pDlg->Reader.HexToStr(indexandLc, 2) , sAPDUData);
		}
		else//���һ�鴫��
		{
			indexandLc[1] = writeLenLeft & 0xFF;
			sAPDUData = pDlg->Reader.HexToStr(pWriteBuf + writeOffset, indexandLc[1]);
			sAPDU.Format(_T("%s %s %s"), _T("80E880") , pDlg->Reader.HexToStr(indexandLc, 2) , sAPDUData);
		}
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return;
		}
		if ((RespLen != 2) || (Resp[0] != 0x61) || (Resp[1] != 0x01))
		{
			MessageBox(_T("LOAD Command  ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.SetWindowText(_T("LOAD Command  ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			page4pcscprocess1.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
		writeOffset += indexandLc[1];
		writeLenLeft -= indexandLc[1];
		indexandLc[0] ++;

		UpdateData(TRUE);
		page4pcscprocess1.SetPos(256 + writeOffset);
		stepIndex ++;
		page4pcscprocess1.SetPos(stepIndex);
		sStatus.Format(_T("Loadding %d%%"), stepIndex * 100 / steps);
		page4edtpcscStatus.SetWindowText(sStatus);
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		page4pcscprocess1.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

		UpdateData(FALSE);
		UpdateWindow();
		//MFC ѭ����������Ľ���취
		//1. ���߳̽����
		// �ɷ���Ϣ
		MSG msg;
		if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
		//�����������:�ѿ�ʼ��ť�е���Щѭ�����ֵ���д��һ�����߳�, �ڰ�ť�Ĵ������в������߳�, ���߳̾Ͳ�����Ϊѭ����������Ϣ��.
		//�μ���https://blog.csdn.net/weixin_34107739/article/details/85560124?utm_medium=distribute.pc_relevant_download.none-task-blog-baidujs-2.nonecase&depth_1-utm_source=distribute.pc_relevant_download.none-task-blog-baidujs-2.nonecase

	}

	//INSTALL[for install]   for Install��for Make Selectable���
	//80E60C00	
	sAPDUData = pDlg->Reader.HexToStr(capAIDLV, capAIDLV[0] + 1);
	//sAPDUData = sAPDUData + pDlg->Reader.HexToStr(appletAIDCLVO + 1, appletAIDCLVO[1] + 1);
	//sAPDUData = sAPDUData + pDlg->Reader.HexToStr(appletAIDCLVO + 1, appletAIDCLVO[1] + 1);

	CString appletAID, appletAIDLV;
	page4comboxpcscAid.GetWindowText(appletAID);
	Lc[0] = appletAID.GetLength() / 2;
	appletAIDLV = pDlg->Reader.HexToStr(Lc, 1) + appletAID;

	sAPDUData = sAPDUData + appletAIDLV;
	sAPDUData = sAPDUData + appletAIDLV;

	sAPDUData = sAPDUData + _T("010002C90000");
	Lc[0] = sAPDUData.GetLength() / 2;
	sAPDU.Format(_T("%s %s %s"), _T("80E60C00") , pDlg->Reader.HexToStr(Lc, 1) , sAPDUData);
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if ((RespLen != 2) || (Resp[0] != 0x61) || (Resp[1] != 0x01))
	{
		MessageBox(_T("INSTALL[for install]  ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.SetWindowText(_T("INSTALL[for install]  ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	UpdateData(TRUE);
	page4pcscprocess1.SetPos(steps);
	sStatus.Format(_T("Congratulations, 100%% loaded and installed."));
	page4edtpcscStatus.SetWindowText(sStatus);
	page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	page4pcscprocess1.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	UpdateData(FALSE);
	UpdateWindow();

	page4edtpcscStatus.SetWindowText(_T("Applet loading and installation complete."));

	////д��ղŶ�ȡ���ļ�
	//FILE* pFileOut = fopen(filePath + _T(".2"), _T("wb"));
	//fwrite(pBuf, 1, len, pFileOut);
	//fclose(pFileOut);
	//free(pBuf); //�ͷ�
	////system("paluse");

	//д��pWriteBuf
	FILE* pFileOut = fopen(filePath + _T(".3"), _T("wb"));
	fwrite(pWriteBuf, 1, writeLen, pFileOut);
	fclose(pFileOut);
	free(pWriteBuf); //�ͷ�
}

void page4AppletLOADDlg::OnCbnSelchangepage4comboxaid()
{
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������
	nSel = page4comboxpcscAid.GetCurSel();
}


void page4AppletLOADDlg::dispCSJavaCardInfo()
{
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();

	if (pDlg->gAtrCosType == _T("CS.JCOS"))
	{
		CString sAPDU, sAPDU2;
		byte APDU[5 + 256];
		byte Resp[256 + 2];
		byte readMacFlag = 0;
		DWORD APDULen = 0;
		DWORD RespLen = 256 + 2;

		CString addStr;
		boolean getMac = true;
		//MT2 CardType + MAC������еĻ���
		//MT2 CardType
		sAPDU.Format(_T("%s"), _T("1801000004"));
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return;
		}
		if (RespLen != 6)
		{
			MessageBox(_T("Get MT2 card type info ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.SetWindowText(_T("Get MT2 card type info ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
		switch (getBigEndInt(Resp))
		{
		case 0x00323131:	addStr.Format(_T("%s"), _T("MT211 "));	getMac = false; break;
		case 0x32323241:	addStr.Format(_T("%s"), _T("MT222A"));	break;
		case 0x32323243:	
		default:			addStr.Format(_T("%s"), _T("MT222"));	break;
		}
		if (getMac)
		{
			//SPP+BLE
			sAPDU.Format(_T("%s"), _T("180100040C"));
			APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
			RespLen = 256 + 2;
			memset(Resp, 0, RespLen);
			if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
			{
				page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
				page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				MessageBox(pDlg->Reader.GetError());
				return;
			}
			if (RespLen != 14)
			{
				MessageBox(_T("Get MAC info ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
				page4edtpcscStatus.SetWindowText(_T("Get MAC info ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
				page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				return;
			}
			addStr += _T("    SPP_MAC:") + pDlg->Reader.HexToStr(Resp, 6) + _T("  BLE_MAC:") + pDlg->Reader.HexToStr(Resp + 6, 6);
		}
		AddJavaCardinfo(addStr);

		//SN + COSVER
		//SN
		sAPDU.Format(_T("%s"), _T("1801000108"));
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return;
		}
		if (RespLen != 10)
		{
			MessageBox(_T("Get SN ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.SetWindowText(_T("Get SN ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
		addStr.Format(_T("%s %s"), _T("SN:"), pDlg->Reader.HexToStr(Resp, 8));

		//COSVer
		sAPDU.Format(_T("%s"), _T("1801000204"));
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return;
		}
		if (RespLen != 6)
		{
			MessageBox(_T("Get COS ver info ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.SetWindowText(_T("Get COS ver info ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
		addStr += _T("    CS.JCOS V") + pDlg->Reader.HexToStr(Resp, 1) + _T(".") + pDlg->Reader.HexToStr(Resp + 1, 1) + _T("_") + pDlg->Reader.HexToStr(Resp + 2, 2);
		AddJavaCardinfo(addStr);

		addStr = _T("--------------------------------------------------------");
		AddJavaCardinfo(addStr);
	}
}


void page4AppletLOADDlg::OnBnClickedpage4btngetcardstatus()
{
	page4listpcsc.ResetContent();
	page4edtpcscStatus.SetWindowText(_T(""));
	page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	dispCSJavaCardInfo();//�����ڲ��ж��Ƿ���MT2�����������ֱ���˳�

	//����Java���İ�ȫ����֤
	if (!javaCardAuth())
	{
		MessageBox(_T("��Ƭ��֤ʧ�ܣ����ɼ���LIST��"));
		return;
	}
	page4edtpcscStatus.SetWindowText(_T("��Ƭ��֤ͨ����"));


	unsigned short flagSW=0x9000;
	//��ʼlist
	CString addStr;
	CSmartToolDlg* pDlg = (CSmartToolDlg*)GetParent()->GetParent();
	DWORD offset;
	byte lifeCycle, moduleNum;
	CString sAPDU, sAPDU2;
	byte APDU[5 + 256];
	byte Resp[256 + 2];
	byte readMacFlag = 0;
	DWORD APDULen = 0;
	DWORD RespLen = 256 + 2;

	//80F28000024F00   ֻ�з����߰�ȫ��
	sAPDU.Format(_T("%s"), _T("80F28000024F00"));
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if ((RespLen != 2) || (Resp[0] != 0x61))
	{
		MessageBox(_T("Get Status[ISD]  ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.SetWindowText(_T("Get Status[ISD]  ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}

	sAPDU.Format(_T("%s %s"), _T("00C00000") , pDlg->Reader.HexToStr(Resp+1,1));
	APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
	RespLen = 256 + 2;
	memset(Resp, 0, RespLen);
	if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
	{
		page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		MessageBox(pDlg->Reader.GetError());
		return;
	}
	if ((RespLen <= 2) || (Resp[RespLen-2] != 0x90))
	{
		MessageBox(_T("Get Status[ISD]  ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.SetWindowText(_T("Get Status[ISD]  ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
		page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		return;
	}
	addStr.Format(_T("%s %s"), _T("Card Manager AID   : ") , pDlg->Reader.HexToStr(Resp+1, Resp[0]));
	AddJavaCardinfo(addStr);

	addStr.Format(_T("%s"), _T("Card Manager state : "));
	switch (Resp[RespLen-4])
	{
	case 0x01:
		addStr += _T("OP_READY"); break;
	case 0x07:
		addStr += _T("SECURED"); break;
	case 0x7F:
		addStr += _T("CARD_LOCKED"); break;
	case 0xFF:
		addStr += _T("TERMINATED"); break;
	default:
		addStr += _T("�����д����ܽ�����"); return;
	}
	AddJavaCardinfo(addStr);

	//80F24000024F00   ֻ��Ӧ�úͰ�ȫ��
	sAPDU.Format(_T("%s"), _T("80F24000024F00"));

	do {
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return;
		}
		if ((RespLen != 2) || ((Resp[0] != 0x61) && (getBigEndShort(Resp)!=0x6A88)))
		{
			MessageBox(_T("Get Status[Ӧ�úͰ�ȫ��]  ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.SetWindowText(_T("Get Status[Ӧ�úͰ�ȫ��]  ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
		if (getBigEndShort(Resp) == 0x6A88)
			break;

		sAPDU.Format(_T("%s %s"), _T("00C00000") , pDlg->Reader.HexToStr(Resp + 1, 1));
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return;
		}
		flagSW = getBigEndShort(Resp + RespLen - 2);
		if ((RespLen <= 2) || (flagSW != 0x9000) && (flagSW != 0x6310))//9000����6310
		{
			MessageBox(_T("Get Status[Ӧ�úͰ�ȫ��]  ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.SetWindowText(_T("Get Status[Ӧ�úͰ�ȫ��]  ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}

		offset = 0;
		while (offset < RespLen - 2)
		{
			addStr.Format(_T("%s"), _T("     Application: "));
			lifeCycle = Resp[offset + 1 + Resp[offset]];
			switch (lifeCycle)
			{
			case 0x03:
				addStr += _T(" INSTALLED (__) "); break;
			case 0x07:
				addStr += _T("SELECTABLE (__) "); break;
			default:
				if ((lifeCycle & 0x83) == 0x83)
				{
					addStr += _T("    LOCKED (__) "); break;
				}
				addStr += _T("�����д����ܽ�����"); return;
			}

			addStr += pDlg->Reader.HexToStr(Resp + offset + 1, Resp[offset]);
			AddJavaCardinfo(addStr);
			offset += Resp[offset] + 3;
		}
		sAPDU.Format(_T("%s"), _T("80F24001024F00"));
	} while (flagSW == 0x6310);


	//80F21000024F00   ֻ�п�ִ��װ���ļ������ǵĿ�ִ��ģ��
	sAPDU.Format(_T("%s"), _T("80F21000024F00"));
	do {
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return;
		}
		if ((RespLen != 2) || ((Resp[0] != 0x61) && (getBigEndShort(Resp) != 0x6A88)))
		{
			MessageBox(_T("Get Status[ִ��װ���ļ������ǵĿ�ִ��ģ��]  ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.SetWindowText(_T("Get Status[ִ��װ���ļ������ǵĿ�ִ��ģ��]  ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}
		if (getBigEndShort(Resp) == 0x6A88)
			break;

		sAPDU.Format(_T("%s %s"), _T("00C00000") , pDlg->Reader.HexToStr(Resp + 1, 1));
		APDULen = pDlg->Reader.StrToHex(sAPDU, APDU);
		RespLen = 256 + 2;
		memset(Resp, 0, RespLen);
		if (!pDlg->Reader.Transmit(APDU, APDULen, Resp, RespLen))
		{
			page4edtpcscStatus.SetWindowText(pDlg->Reader.GetError());
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			MessageBox(pDlg->Reader.GetError());
			return;
		}
		flagSW = getBigEndShort(Resp + RespLen - 2);
		if ((RespLen <= 2) || (flagSW != 0x9000) && (flagSW != 0x6310))//9000����6310
		{
			MessageBox(_T("Get Status[ִ��װ���ļ������ǵĿ�ִ��ģ��]  ʧ�ܣ�\r\nSW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.SetWindowText(_T("Get Status[ִ��װ���ļ������ǵĿ�ִ��ģ��]  ʧ�ܣ� SW=") + pDlg->Reader.HexToStr(Resp, 2));
			page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			return;
		}

		offset = 0;
		while (offset < RespLen - 2)
		{
			addStr.Format(_T("%s"), _T("     Load File  : "));
			lifeCycle = Resp[offset + 1 + Resp[offset]];
			moduleNum = Resp[offset + 3 + Resp[offset]];
			switch (lifeCycle)
			{
			case 0x01:
				addStr += _T("    LOADED (__) "); break;
			default:
				addStr += _T("�����д����ܽ�����"); return;
			}

			addStr += pDlg->Reader.HexToStr(Resp + offset + 1, Resp[offset]);
			AddJavaCardinfo(addStr);
			offset += Resp[offset] + 4;

			//Module
			while (moduleNum--)
			{
				addStr.Format(_T("%s"), _T("      Module    :                 "));
				addStr += pDlg->Reader.HexToStr(Resp + offset + 1, Resp[offset]);
				AddJavaCardinfo(addStr);
				offset += Resp[offset] + 1;
			}
		}
		sAPDU.Format(_T("%s"), _T("80F21001024F00"));
	} while (flagSW == 0x6310);

	int dx = 0;
	CSize sz;
	CDC* pDC = page4listpcsc.GetDC();
	CString str;
	for (int j = 0; j < page4listpcsc.GetCount(); j++)
	{
		page4listpcsc.GetText(j, str);
		sz = pDC->GetTextExtent(str);
		if(sz.cx > dx)
			dx = sz.cx;
	}
	page4listpcsc.ReleaseDC(pDC);
	page4listpcsc.SetHorizontalExtent(dx+24);

	page4edtpcscStatus.SetWindowText(_T("Get Status�ɹ���"));
	page4edtpcscStatus.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}


void page4AppletLOADDlg::AddJavaCardinfo(CString s)
{
	int Index = page4listpcsc.FindString(0, s);
	if (Index < 0)
	{
		page4listpcsc.InsertString(-1, s);//������˳�����С������AddString����������ĸ˳������
	}
}



void page4AppletLOADDlg::CheckInputDataLength(int editIDC, DWORD maxLen)
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CEdit* pEdit = (CEdit*)GetDlgItem(editIDC);
	CString strContent;
	pEdit->GetWindowText(strContent);

	DWORD dwNum = 0;

	dwNum = strContent.GetLength();

	if (dwNum > maxLen)
	{
		SetDlgItemText(editIDC, strContent.Left(maxLen));
		pEdit->SetSel(strContent.GetLength(), strContent.GetLength());//������������λ�� ָ�����           
	}
}


void page4AppletLOADDlg::OnChangePage4edtisd()
{
	CheckInputDataLength(page4edtISD, 16);
}


void page4AppletLOADDlg::OnChangePage4edtdek()
{
	CheckInputDataLength(page4edtDEK, 32);
}


void page4AppletLOADDlg::OnChangePage4edtsEnc()
{
	CheckInputDataLength(page4edtS_ENC, 32);
}


void page4AppletLOADDlg::OnChangePage4edtsMac()
{
	CheckInputDataLength(page4edtS_MAC, 32);
}


void page4AppletLOADDlg::OnEditchangePage4comboxaid()
{
	CheckInputDataLength(page4comboxAid, 16);
}
