////////////////////////////////////////////////////////////////////////////////////////
// 
//	Project:    Class ComAccess
//              Overlapped serial IO communication class
//  System:     Win9x WinNT
//	File:       comaccess.h
//	Start date:	17.11.1997
//	Update:     31.07.1998
//	Version:    1.2
//	Author:     Patrick Feuser pat@das-netz.de Germany
//	Copyright ?1997. Alle Rechte vorbehalten
//
////////////////////////////////////////////////////////////////////////////////////////

#ifndef _COMACCESS_H_
#define _COMACCESS_H_

#include "StdAfx.h"
#include <windows.h>
#include <String>

using namespace std;

class ComAccess 
{
private:

	HANDLE      m_hCom; // Device handle 

	OVERLAPPED  m_ov;   // A structure that contains informations which are
	                    // used for asynchronous input and output operations

	CHAR		m_lpszErrorMessage[256];

public:

	ComAccess(VOID);
	ComAccess(LPCWSTR lpszPortNum);

	~ComAccess() { Close(); }
			                        // For more definitions see <winbase.h>
	BOOL	Open(LPCWSTR lpszPortNum	= L"com1",
			     DWORD  dwBaudRate  = CBR_19200, 
			     BYTE   byParity    = NOPARITY,
			     BYTE   byStopBits  = ONESTOPBIT,
			     BYTE   byByteSize  = 8);

	VOID	Close(VOID);
	
	DWORD	WriteData(LPCVOID pdata, DWORD len);
	DWORD	ReadData(LPVOID  pdest, DWORD len, DWORD dwMaxWait = 500);

	LPSTR	GetErrorMessage(VOID) { return m_lpszErrorMessage; }

	//字节流转换为十六进制字符串  
	void ByteToHexStr(const char* source, char* dest, int sourceLen);
	//字节流转换为十六进制字符串的另一种实现方式  
	void Hex2Str( const char *sSrc,  char *sDest, int nSrcLen );
	//十六进制字符串转换为字节流  
	void HexStrToByte(const char* source, char* dest, int sourceLen);
private:

	VOID	ErrorToString(LPCSTR lpszMessage);

	BOOL	IsNT(VOID);
};


#endif // _COMACCESS_H_
