/*++

Copyright (c) 2021 ����о�ܼ���

Module Name:

Core Shield PCSC��������

Abstract:

PCSC���������ļ�֧�ֵ�CCID�� ���ļ���ʹ�û���VS2013 ��VC++

Author: Gaohk


Environment:

Win32

Notes:

--*/
#pragma once

#include "WINSCARD.H"

class PCSCReader
{
private:
	SCARDCONTEXT Context;
	unsigned int ErrCode;
	TCHAR ReaderNamebytes[1000];
	CString Readers[10];
	int readercount;
	CString activereader;
	SCARDHANDLE hCard;
	DWORD activeProtocol;
	int cardstate;

	CString ToChar(byte bNum);
	byte toHex(char a, char b);
public:
	PCSCReader();
	~PCSCReader();
	CString HexToStr(byte *bByte, UINT iLength);
	int StrToHex(CString inStr, byte *pByte);
	int ReaderCount(){ return readercount; }
	CString ActiveReader(){ return activereader; }

	CString GetReaderName(int Index);
	bool EnmuReaders();
	bool ConnectReader(CString ReadName);
	CString ATRByResetCard();
	bool Transmit(byte *APDU, DWORD APDULen, byte *Response, DWORD &ResponseLen);
	bool  DisConnectReader();
	bool FreeReaders();
	CString GetError();
};

