#pragma once
#include <Windows.h>
#include <memory>
#include <string>

#include <arris/util/constant.hpp>

using namespace arris::util;

namespace arris{
namespace util {

	DWORD WINAPI read_dword(HANDLE process,DWORD address)
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

	std::wstring read_wstr(HANDLE process,DWORD address, int size)
	{
		std::unique_ptr<BYTE[]> tempbuf = std::make_unique<BYTE[]>(size * 2);
		DWORD len = 0;
		if (process == NULL) {
			process = ::GetCurrentProcess();
		}
		if (ReadProcessMemory(process, (LPVOID)address, tempbuf.get(), size * 2, &len) == 0)
		{
			return TEXT("");
		}

		std::unique_ptr<wchar_t[]> p = std::make_unique<wchar_t[]>(size + 1);
		wmemcpy_s(p.get(), size, (wchar_t*)tempbuf.get(), size);
		std::wstring result = { 0 };
		result.assign(p.get());
		return result;
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