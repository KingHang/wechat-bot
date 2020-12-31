#include <Windows.h>
#include <tchar.h>

namespace arris {
namespace util {
//namespace log{
	int __stdcall __OutputDebugString(LPCTSTR pstrFormat, ...)
	{
		TCHAR szBuffer[2048] = { 0 };
		va_list argList;
		va_start(argList, pstrFormat);
		int iRet = ::_vstprintf_s(szBuffer, pstrFormat, argList);
		va_end(argList);
		
		OutputDebugString(szBuffer);
		return iRet;
	}
//}//namespacde log
}//namespace util
}//namespace arris