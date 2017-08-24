#include <windows.h>
#include "Logging.h"

namespace Logging
{
	std::ofstream LOG;
}

#define CHECK_TYPE(myChar, myType) \
		case myChar: \
		{ \
			sprintf_s(mybuffer, buffer, va_arg(ap, myType)); \
			break; \
		} \

#define VISIT_TYPE(visit) \
	visit('c', char) \
	visit('C', char) \
	visit('s', void*) \
	visit('S', void*) \
	visit('d', int) \
	visit('i', int) \
	visit('o', UINT) \
	visit('x', UINT) \
	visit('X', UINT) \
	visit('u', UINT) \
	visit('f', float) \
	visit('F', float) \
	visit('e', float) \
	visit('E', float) \
	visit('a', float) \
	visit('A', float) \
	visit('g', float) \
	visit('G', float) \
	visit('n', void*) \
	visit('p', void*) \

void Logging::LogFormat(char * fmt, ...)
{
	// Get arg list
	va_list ap;
	va_start(ap, fmt);

	// Declare vars
	static constexpr DWORD BuffSize = 1024;
	static char buffer[BuffSize];
	static char mybuffer[BuffSize];

	// Setup string
	strcpy_s(buffer, fmt);
	char *loc = strchr(buffer, '%');

	// Loop through string
	while (loc)
	{
		// Get format type
		char myChar = buffer[loc - buffer + 1];

		// Update format string
		switch (myChar)
		{
			VISIT_TYPE(CHECK_TYPE);
		default:
			Log() << "Error in LogFormat type '" << myChar << "'"<< "\n";
			va_end(ap);
			return;
		}

		// Copy format string back
		strcpy_s(buffer, mybuffer);

		// Check for next format
		char *myloc = strchr(buffer, '%');
		if (myloc == loc || !myloc)
		{
			loc = nullptr;
		}
		else
		{
			loc = myloc;
		}
	}

	// End arg list
	va_end(ap);

	// Log results
	Log() << buffer << "\n";
	Log().flush();
}
