/** ��������Դ��MingQQ */

#pragma once

#include <vector>
#include <string>
#include <time.h>
#include <WinSock2.h>
#include <gdiplus.h>

#if defined(UNICODE) || defined(_UNICODE)
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

namespace cbm
{

extern WCHAR * AnsiToUnicode(const CHAR * lpszStr);
extern CHAR * UnicodeToAnsi(const WCHAR * lpszStr);
extern CHAR * AnsiToUtf8(const CHAR * lpszStr);
extern CHAR * Utf8ToAnsi(const CHAR * lpszStr);
extern CHAR * UnicodeToUtf8(const WCHAR * lpszStr);
extern WCHAR * Utf8ToUnicode(const CHAR * lpszStr);

extern BOOL AnsiToUnicode(const CHAR * lpszAnsi, WCHAR * lpszUnicode, int nLen);
extern BOOL UnicodeToAnsi(const WCHAR * lpszUnicode, CHAR * lpszAnsi, int nLen);
extern BOOL AnsiToUtf8(const CHAR * lpszAnsi, CHAR * lpszUtf8, int nLen);
extern BOOL Utf8ToAnsi(const CHAR * lpszUtf8, CHAR * lpszAnsi, int nLen);
extern BOOL UnicodeToUtf8(const WCHAR * lpszUnicode, CHAR * lpszUtf8, int nLen);
extern BOOL Utf8ToUnicode(const CHAR * lpszUtf8, WCHAR * lpszUnicode, int nLen);

extern std::wstring AnsiToUnicode(const std::string& strAnsi);
extern std::string UnicodeToAnsi(const std::wstring& strUnicode);
extern std::string AnsiToUtf8(const std::string& strAnsi);
extern std::string Utf8ToAnsi(const std::string& strUtf8);
extern std::string UnicodeToUtf8(const std::wstring& strUnicode);
extern std::wstring Utf8ToUnicode(const std::string& strUtf8);

extern BOOL ToHexStr(const CHAR * lpStr, int nSrcLen, CHAR * lpHex, int nDestLen);
extern BOOL StrToHex(const CHAR * lpStr, CHAR * lpHex, int nLen);

extern u_short Swap16(u_short nValue);		// 16λ�������������ֽ����������ֽ���ת��
extern u_long Swap32(u_long nValue);		// 32λ�������������ֽ����������ֽ���ת��

extern COLORREF HexStrToRGB(LPCTSTR lpszStr);
extern void RGBToHexStr(COLORREF color, TCHAR * lpBuf, int nLen);

extern void FormatTime(time_t lTime, LPCTSTR lpFmt, TCHAR * lpBuf, int nLen);
extern BOOL IsToday(time_t lTime);

extern BOOL IsToday(SYSTEMTIME * lpTime);
extern BOOL GetFileLastWriteTime(LPCTSTR lpszFileName, SYSTEMTIME * lpSysTime);	// ��ȡ�ļ�����޸�ʱ��

extern BOOL File_ReadAll(const TCHAR * lpszFileName, CHAR **lpData, LONG *lSize);	// ��ȡ�����ļ�

extern BOOL my_isalnum(unsigned char cChar);		// ���ָ���ַ��Ƿ�����ĸ(A-Z��a-z)������(0-9)
extern BOOL my_isalnum(wchar_t cChar);				// ���ָ���ַ��Ƿ�����ĸ(A-Z��a-z)������(0-9)

extern BOOL EnumSysFont(std::vector<tstring> * arrSysFont);	// ö��ϵͳ����
extern BOOL FlashWindowEx(HWND hWnd, int nCount);				// ��˸���ڱ�����
extern BOOL GetTrayWndRect(RECT * lpRect);						// ��ȡϵͳ����������

extern BOOL IsDigit(const WCHAR * lpStr);
extern void Replace(std::string& strText, const CHAR * lpOldStr, const CHAR * lpNewStr);
extern void Replace(std::wstring& strText, const WCHAR * lpOldStr, const WCHAR * lpNewStr);
extern WCHAR ToLower(WCHAR c);
extern void ToLower(WCHAR * lpText);
extern void ToLower(std::wstring& strText);
extern WCHAR ToUpper(WCHAR c);
extern void ToUpper(WCHAR * lpText);
extern void ToUpper(std::wstring& strText);
extern void EncodeHtmlSpecialChars(std::wstring& strText);		// ����Html�����ַ�
extern void DecodeHtmlSpecialChars(std::wstring& strText);		// ����Html�����ַ�

extern tstring GetBetweenString(const TCHAR * pStr, TCHAR cStart, TCHAR cEnd);
extern int GetBetweenInt(const TCHAR * pStr, TCHAR cStart, TCHAR cEnd, int nDefValue = 0);

extern tstring GetBetweenString(const WCHAR * pStr, const WCHAR * pStart, const WCHAR * pEnd);
extern int GetBetweenInt(const WCHAR * pStr, const WCHAR * pStart, 
	const WCHAR * pEnd, int nDefValue = 0);

extern BOOL DllRegisterServer(LPCTSTR lpszFileName);
extern BOOL DllUnregisterServer(LPCTSTR lpszFileName);

extern tstring GetMimeTypeByExtension(const TCHAR * lpExtension);
extern GUID GetFileTypeGuidByExtension(const WCHAR * lpExtension);
extern CLSID GetEncoderClsidByExtension(const WCHAR * lpExtension);
extern CLSID GetEncoderClsidByFileType(REFGUID guidFileType);
extern CLSID GetEncoderClsidByMimeType(const WCHAR * lpMimeType);

extern time_t httpdate_parse(const TCHAR *date);

} // namespace cbm
