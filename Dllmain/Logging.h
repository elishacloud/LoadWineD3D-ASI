#pragma once

#include <fstream>

namespace Logging
{
	class Log
	{
	public:
		Log();
		~Log();

		template <typename T>
		Log& operator<<(const T& t)
		{
			LOG << t;
			return *this;
		}

	private:
		static wchar_t* Init();
		static std::ofstream LOG;
	};

	void LogFormat(char * fmt, ...);
}
