#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Hook
{
	FARPROC GetProcAddress(HMODULE, LPCSTR);
	HMODULE GetModuleHandle(char*);
	void *HookAPI(HMODULE, const char *, void *, const char *, void *);
	void UnhookAPI(HMODULE, const char *, void *, const char *, void *);
	void *HotPatch(void*, const char*, void*);
	bool UnhookHotPatch(void *, const char *, void *);
	void *IATPatch(HMODULE, DWORD, const char*, void*, const char*, void*);
	bool UnhookIATPatch(HMODULE, DWORD, const char *, void *, const char *, void *);

	struct HOOKING
	{
		void* apiproc;
		char* apiname;
		void* hookproc;
	};
}
