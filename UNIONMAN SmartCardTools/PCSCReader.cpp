#include "winerror.h"
#include "stdafx.h"
#include "PCSCReader.h"


PCSCReader::PCSCReader()
{


}


PCSCReader::~PCSCReader()
{
}

CString PCSCReader::ToChar(byte bNum)
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

byte PCSCReader::toHex(char a, char b)
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

CString PCSCReader::HexToStr(byte *bByte, UINT iLength)
{
	UINT iIndex;
	CString outStr;

	for (iIndex = 0; iIndex<iLength; iIndex++)
	{
		outStr += ToChar(bByte[iIndex] >> 4 & 0x0F);
		outStr += ToChar(bByte[iIndex] & 0x0F);
	}

	return outStr;
}

int PCSCReader::StrToHex(CString inStr, byte *pByte)
{
	UINT iIndex, iLength;

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
	for (iIndex = 0; iIndex<iLength / 2; iIndex++)
	{
		pByte[iIndex] = this->toHex((char)inStr.GetAt(iIndex * 2), (char)inStr.GetAt(iIndex * 2 + 1));
	}
	return iIndex;
}

bool PCSCReader::EnmuReaders()
{
	readercount = 0;
	ErrCode = SCardEstablishContext(SCARD_SCOPE_USER, 0, 0, &Context);
	if (ErrCode != SCARD_S_SUCCESS) return false;

	if (Context == 0)return false;

	DWORD ReaderBytes = 0;
	
	ErrCode = SCardListReaders(Context, NULL, NULL, &ReaderBytes);
	if (ErrCode != SCARD_S_SUCCESS) return false;
	

	ErrCode = SCardListReaders(Context, NULL, ReaderNamebytes, &ReaderBytes);
	if (ErrCode != SCARD_S_SUCCESS) return false;
	
	DWORD i = 0;
	do
	{
		Readers[readercount] = CString(&ReaderNamebytes[i]);
		if (Readers[readercount] == _T(""))break;
		i += Readers[readercount].GetLength()+1;
		readercount++;
	} while (i<ReaderBytes);
	return true;
}

CString PCSCReader::GetReaderName(int Index)
{
	CString s = _T("");
	if ((Index >= 0) && (Index < readercount))s= Readers[Index];
	return s;
}

bool PCSCReader::ConnectReader(CString ReadName)
{
	ErrCode = SCardConnect(Context, ReadName, SCARD_SHARE_SHARED,
		SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
		&hCard, &activeProtocol);


	activereader = ReadName;

	return ErrCode == SCARD_S_SUCCESS;
}

CString PCSCReader::ATRByResetCard()
{
	DWORD state = SCARD_UNKNOWN;
	DWORD protocol = SCARD_PROTOCOL_UNDEFINED;
	byte atr[200];
	DWORD atrlen = 100;
	CString stratr;

	ErrCode = SCardState(hCard, &state, &protocol, atr, &atrlen);
	if (ErrCode == SCARD_S_SUCCESS)
	{

		activeProtocol = protocol;
		stratr = HexToStr(atr, atrlen);

	}
	cardstate = state;
	return stratr;
}

bool PCSCReader::Transmit(byte *APDU, DWORD APDULen, byte *Response, DWORD &ResponseLen)
{
	SCARD_IO_REQUEST ioSendPci, ioRecPci;
	ioSendPci.dwProtocol = activeProtocol;
	ioSendPci.cbPciLength = 8;
	ioRecPci = ioSendPci;


	ErrCode = SCardTransmit(hCard, &ioSendPci,
		APDU, APDULen,
		&ioRecPci,
		Response, &ResponseLen);

	return ErrCode == SCARD_S_SUCCESS;
}

bool  PCSCReader::DisConnectReader()
{
	//ErrCode = SCardDisconnect(hCard, SCARD_LEAVE_CARD);
	ErrCode = SCardDisconnect(hCard, SCARD_UNPOWER_CARD);
	
	activereader = "";
	return ErrCode == SCARD_S_SUCCESS;
}

bool PCSCReader::FreeReaders()
{
	ErrCode = SCardReleaseContext(Context);
	return SCARD_S_SUCCESS == ErrCode;
}

CString PCSCReader::GetError()
{
	CString s = _T("Unknown Error.");
	switch ((HRESULT)ErrCode)
	{
	case SCARD_S_SUCCESS:s = _T("Success."); break;
	case SCARD_F_INTERNAL_ERROR: s = _T("An internal consistency check failed."); break;
	case SCARD_E_CANCELLED: s = _T("	The action was cancelled by a SCardCancel request."); break;
	case SCARD_E_INVALID_HANDLE: s = _T("The supplied handle was invalid."); break;
	case SCARD_E_INVALID_PARAMETER: s = _T("One or more of the supplied parameters could not be properly interpreted."); break;
	case SCARD_E_INVALID_TARGET: s = _T("Registry startup information is missing or invalid."); break;
	case SCARD_E_NO_MEMORY: s = _T("Not enough memory available to complete this command."); break;
	case SCARD_F_WAITED_TOO_LONG: s = _T("An internal consistency timer has expired."); break;
	case SCARD_E_INSUFFICIENT_BUFFER: s = _T("The data buffer to receive returned data is too small for the returned data."); break;
	case SCARD_E_UNKNOWN_READER: s = _T("The specified reader name is not recognized."); break;
	case SCARD_E_TIMEOUT: s = _T("The user-specified timeout value has expired."); break;
	case SCARD_E_SHARING_VIOLATION: s =_T( "The smart card cannot be accessed because of other connections outstanding."); break;
	case SCARD_E_NO_SMARTCARD: s = _T("The operation requires a smart card, but no smart card is currently in the device."); break;
	case SCARD_E_UNKNOWN_CARD: s = _T("The specified smart card name is not recognized."); break;
	case SCARD_E_CANT_DISPOSE: s = _T("The system could not dispose of the media in the requested manner."); break;
	case SCARD_E_PROTO_MISMATCH: s = _T("The requested protocols are incompatible with the protocol currently in use with the smart card."); break;
	case SCARD_E_NOT_READY: s = _T("The reader or smart card is not ready to accept commands."); break;
	case SCARD_E_INVALID_VALUE: s = _T("One or more of the supplied parameters values could not be properly interpreted."); break;
	case SCARD_E_SYSTEM_CANCELLED: s = _T("The action was cancelled by the system, presumably to log off or shut down."); break;
	case SCARD_F_COMM_ERROR: s = _T("An internal communications error has been detected."); break;
	case SCARD_F_UNKNOWN_ERROR: s = _T("An internal error has been detected, but the source is unknown."); break;
	case SCARD_E_INVALID_ATR: s = _T("An ATR obtained from the registry is not a valid ATR string."); break;
	case SCARD_E_NOT_TRANSACTED: s = _T("An attempt was made to end a non-existent transaction."); break;
	case SCARD_E_READER_UNAVAILABLE: s = _T("The specified reader is not currently available for use."); break;
	case SCARD_P_SHUTDOWN: s = _T("The operation has been aborted to allow the server application to exit."); break;
	case SCARD_E_PCI_TOO_SMALL: s = _T("The PCI Receive buffer was too small."); break;
	case SCARD_E_READER_UNSUPPORTED: s = _T("The reader driver does not meet minimal requirements for support."); break;
	case SCARD_E_DUPLICATE_READER: s = _T("The reader driver did not produce a unique reader name."); break;
	case SCARD_E_CARD_UNSUPPORTED: s = _T("The smart card does not meet minimal requirements for support."); break;
	case SCARD_E_NO_SERVICE: s = _T("The Smart Card Resource Manager is not running."); break;
	case SCARD_E_SERVICE_STOPPED: s = _T("The Smart Card Resource Manager has shut down."); break;
	case SCARD_E_UNEXPECTED: s = _T("An unexpected card error has occurred."); break;
	case SCARD_E_ICC_INSTALLATION: s = _T("No primary provider can be found for the smart card."); break;
	case SCARD_E_ICC_CREATEORDER: s = _T("The requested order of object creation is not supported."); break;
	case SCARD_E_UNSUPPORTED_FEATURE: s = _T("This smart card does not support the requested feature."); break;
	case SCARD_E_DIR_NOT_FOUND: s = _T("The identified directory does not exist in the smart card."); break;
	case SCARD_E_FILE_NOT_FOUND: s = _T("The identified file does not exist in the smart card."); break;
	case SCARD_E_NO_DIR: s = _T("The supplied path does not represent a smart card directory."); break;
	case SCARD_E_NO_FILE: s = _T("The supplied path does not represent a smart card file."); break;
	case SCARD_E_NO_ACCESS: s = _T("Access is denied to this file."); break;
	case SCARD_E_WRITE_TOO_MANY: s = _T("The smart card does not have enough memory to store the information."); break;
	case SCARD_E_BAD_SEEK: s = _T("There was an error trying to set the smart card file object pointer."); break;
	case SCARD_E_INVALID_CHV: s = _T("The supplied PIN is incorrect."); break;
	case SCARD_E_UNKNOWN_RES_MNG: s = _T("An unrecognized error code was returned from a layered component."); break;
	case SCARD_E_NO_SUCH_CERTIFICATE: s = _T("    The requested certificate does not exist."); break;
	case SCARD_E_CERTIFICATE_UNAVAILABLE: s = _T("The requested certificate could not be obtained."); break;
	case SCARD_E_NO_READERS_AVAILABLE: s = _T("Cannot find a smart card reader."); break;
	case SCARD_E_COMM_DATA_LOST: s = _T("A communications error with the smart card has been detected. Retry the operation."); break;
	case SCARD_E_NO_KEY_CONTAINER: s = _T("The requested key container does not exist on the smart card."); break;
	case SCARD_E_SERVER_TOO_BUSY: s = _T("The Smart Card Resource Manager is too busy to complete this operation."); break;
	case SCARD_W_UNSUPPORTED_CARD: s = _T("The reader cannot communicate with the card, due to ATR string configuration conflicts."); break;
	case SCARD_W_UNRESPONSIVE_CARD: s = _T("The smart card is not responding to a reset."); break;
	case SCARD_W_UNPOWERED_CARD: s = _T("Power has been removed from the smart card, so that further communication is not possible."); break;
	case SCARD_W_RESET_CARD: s = _T("The smart card has been reset, so any shared state information is invalid."); break;
	case SCARD_W_REMOVED_CARD: s = _T("The smart card has been removed, so further communication is not possible."); break;
	case SCARD_W_SECURITY_VIOLATION: s = _T("Access was denied because of a security violation."); break;
	case SCARD_W_WRONG_CHV: s = _T("The card cannot be accessed because the wrong PIN was presented."); break;
	case SCARD_W_CHV_BLOCKED: s = _T("The card cannot be accessed because the maximum number of PIN entry attempts has been reached."); break;
	case SCARD_W_EOF: s = _T("The end of the smart card file has been reached."); break;
	case SCARD_W_CANCELLED_BY_USER: s = _T("The action was cancelled by the user."); break;
	case SCARD_W_CARD_NOT_AUTHENTICATED: s = _T("No PIN was presented to the smart card.  "); break;
	}
	return s;
}
