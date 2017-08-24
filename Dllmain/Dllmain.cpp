/**
* Copyright (C) 2017 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/

#include "Dllmain.h"
#include "Logging.h"
#include "..\Hooking\Hook.h"

FARPROC wrapper_func[101] = { nullptr };
DLLEXPORTS dllexports[ArraySize];

VISIT_PROCS(CREATE_PROC_STUB)

// Dll main function
bool APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		// Setup Proc arrays
		VISIT_PROCS(SET_FUNC_STUB);
		VISIT_EXPORTS(SET_DLL_EXPORTS);

		// Init vars
		char path[MAX_PATH];
		char* pdest;
		DWORD Counter = 0;
		HMODULE Script_dll = nullptr;
		HMODULE EXE_dll = nullptr;
		HMODULE System32_dll = nullptr;

		// Enable logging
		GetModuleFileName(hModule, path, sizeof(path));
		pdest = strrchr(path, '.');
		strcpy_s(pdest, MAX_PATH, ".log");
		Logging::LOG.open(path, std::ios::trunc);

		// Loop through each WineD3D file
		for (int x = 0; x < ArraySize; x++)
		{
			// Load dll from script folder
			GetModuleFileName(hModule, path, sizeof(path));
			pdest = strrchr(path, '\\');
			strcpy_s(pdest, MAX_PATH, "\\");
			strcat_s(path, MAX_PATH, dllname[x]);
			Script_dll = LoadLibrary(path);
			Logging::LOG << "Checking " << path << "\n";

			// If WineD3D dll found
			if (Script_dll)
			{
				Logging::LOG << "Found!\n";

				// Load dll from exe folder
				GetModuleFileName(nullptr, path, sizeof(path));
				pdest = strrchr(path, '\\');
				strcpy_s(pdest, MAX_PATH, "\\");
				strcat_s(path, MAX_PATH, dllname[x]);
				EXE_dll = LoadLibrary(path);
				Logging::LOG << path << "\n";

				// Load dll from System32 folder
				GetSystemDirectory(path, MAX_PATH);
				strcat_s(path, MAX_PATH, "\\");
				strcat_s(path, MAX_PATH, dllname[x]);
				System32_dll = LoadLibrary(path);
				Logging::LOG << path << "\n";

				// Check dlls
				if (System32_dll && EXE_dll != Script_dll)
				{
					// Loop through each export item
					for (int y = 0; y < dllexports[x].ArraySize; y++)
					{
						Logging::Log() << "Checking " << dllexports[x].Export[y] << " ...\n";

						// Get export address
						FARPROC Script_proc = Hook::GetFunctionAddress(Script_dll, dllexports[x].Export[y]);
						FARPROC System32_proc = Hook::GetFunctionAddress(System32_dll, dllexports[x].Export[y]);
						FARPROC EXE_proc = (FARPROC)1;
						if (EXE_dll)
						{
							EXE_proc = Hook::GetFunctionAddress(EXE_dll, dllexports[x].Export[y]);
						}

						// Check export addresses
						if (Script_proc && System32_proc && EXE_proc)
						{
							// Wrapper -> Script
							switch (Counter)
							{
								VISIT_PROCS(SET_PROC_STUB);
							default:
								Logging::Log() << "Too many APIs too hook...\n";
								return true;
							}

							// System -> Wrapper
							Logging::Log() << "Hooking " << dllname[x] << " API " << dllexports[x].Export[y] << " ...\n";
							Hook::HookAPI(hModule, dllname[x], System32_proc, dllexports[x].Export[y], wrapper_func[Counter]);

							// Update counter
							Counter++;
						}
					}
				}
			}
		}
	}
	break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return true;
}
