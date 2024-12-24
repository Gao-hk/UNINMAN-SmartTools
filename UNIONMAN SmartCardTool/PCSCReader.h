/*++

Copyright (c) 2021 北京芯盾集团

Module Name:

Core Shield PCSC读卡器类

Abstract:

PCSC读卡器类文件支持的CCID， 此文件的使用环境VS2013 ，VC++

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

