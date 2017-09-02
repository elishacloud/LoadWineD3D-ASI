#include <windows.h>
#include "Logging.h"

Logging::Log::Log()
{
	SYSTEMTIME st = {};
	GetLocalTime(&st);

	char time[100];
	sprintf_s(time, "%02hu:%02hu:%02hu.%03hu ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	LOG << time;
}

Logging::Log::~Log()
{
	LOG << std::endl;
}

char* Logging::Log::Init()
{
	static char path[MAX_PATH];
	HMODULE hModule = NULL;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR)Init, &hModule);
	GetModuleFileName(hModule, path, MAX_PATH);
	strcpy_s(strrchr(path, '.'), MAX_PATH - strlen(path), ".log");
	return path;
}

void Logging::LogFormat(char * fmt, ...)
{
	// Format arg list
	va_list ap;
	va_start(ap, fmt);
	auto size = vsnprintf(nullptr, 0, fmt, ap);
	std::string output(size + 1, '\0');
	vsprintf_s(&output[0], size + 1, fmt, ap);
	va_end(ap);

	// Log formated text
	Log() << output.c_str();
	return;
}

std::ofstream Logging::Log::LOG(Log::Init());
