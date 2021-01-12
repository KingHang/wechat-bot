#pragma once
#include <Windows.h>
#include <memory>
#include <string>

#include <arris/util/constant.hpp>

using namespace arris::util;

namespace arris{
namespace util {
	std::string __stdcall read_char(HANDLE process, DWORD lpBaseAddress, int size) {
		int memlen = size * sizeof(char);
		std::unique_ptr<char[]> tempbuf = std::make_unique<char[]>(memlen + 1);
		if (process == NULL) {
			process = ::GetCurrentProcess();
		}
		DWORD len;

		if (ReadProcessMemory(process, (LPVOID)lpBaseAddress, tempbuf.get(), memlen + 1, &len) == 0)
		{
			return "";
		}
		std::string ss;
		ss.assign(tempbuf.get());
		return ss;
	}
	DWORD __stdcall read_dword(HANDLE process,DWORD address)
	{
		DWORD node = 0;
		LPDWORD readByte = NULL;
		if (process == NULL) {
			process = ::GetCurrentProcess();
		}
		BOOL is_read = ::ReadProcessMemory(process, (LPVOID)(address), &node, kDwordLength, readByte);
		if (is_read == FALSE)
		{
			return 0;
		}
		return node;
	}

	std::wstring __stdcall read_wchar(HANDLE process,DWORD address, int size)
	{
		int memlen = size * sizeof(wchar_t);
		std::unique_ptr<wchar_t[]> tempbuf = std::make_unique<wchar_t[]>(memlen + 1);
		if (process == NULL) {
			process = ::GetCurrentProcess();
		}
		DWORD len;

		if (ReadProcessMemory(process, (LPVOID)address, tempbuf.get(), memlen + 1, &len) == 0)
		{
			return TEXT("");
		}
		std::wstring ss;
		ss.assign(tempbuf.get());
		return ss;
	}

	BYTE WINAPI read_byte(HANDLE process,DWORD address)
	{
		BYTE node = 0;
		LPDWORD readByte = NULL;
		if (process == NULL) {
			process = ::GetCurrentProcess();
		}
		BOOL is_read = ::ReadProcessMemory(process, (LPVOID)(address), &node, 1, readByte);
		if (is_read == FALSE)
		{
			return 0;
		}
		return node;
	}
		
}//namespace util
}//namespace arris